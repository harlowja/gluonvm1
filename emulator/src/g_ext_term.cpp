#include "g_vm.h"
#include "g_ext_term.h"

namespace gluon {
namespace etf {

// Reads long atom as string and attempts to create it in atom table.
Term read_atom_string_i16(tool::Reader &r) {
  word_t sz = r.read_bigendian_i16();
  Str atom_str = r.read_string(sz);
  return VM::to_atom(atom_str);
}


// Reads short atom as string and attempts to create it in atom table.
Term read_atom_string_i8(tool::Reader &r) {
  word_t sz = r.read_byte();
  Str atom_str = r.read_string(sz);
  return VM::to_atom(atom_str);
}


// Reads tag byte, then reads long or short atom as string and attempts to
// create it in atom table.
Term read_tagged_atom_string(tool::Reader &r) {
  u8_t tag = r.read_byte();
  switch (tag) {
    case ATOM_EXT: return read_atom_string_i16(r);
    case SMALL_ATOM_EXT: return read_atom_string_i16(r);
  }
  return Term::make_nil();
}


Node *get_node(Term /*sysname*/, dist::creation_t /*creation*/) {
#if FEATURE_ERL_DIST
  G_TODO("distribution support pid etf")
#endif
  return VM::dist_this_node();
}


Term make_pid(Term sysname, word_t id, word_t serial, u8_t creation) {
  if ( !Term::is_valid_pid_id(id)
    || !Term::is_valid_pid_serial(serial)) {
    return Term::make_nil();
  }
  // TODO: check valid creation
  word_t data = Term::make_pid_data(serial, id);
  auto node = get_node(sysname, creation);

  if (node == VM::dist_this_node()) {
    return Term::make_short_pid(data);
  }
#if FEATURE_ERL_DIST
  G_TODO("distribution support pid etf");
#endif
  return Term::make_nil(); // distribution disabled, no want remote pids
}


Term read_tuple(Heap *heap, tool::Reader &r, word_t n_elements) {
  if (n_elements == 0) {
    return Term::make_zero_tuple();
  }

  Term *elements = Heap::alloc<Term>(heap, n_elements+1);

  // fill elements or die horribly if something does not decode
  for (auto i = 0; i < n_elements; ++i) {
    auto elem = read_ext_term2(heap, r);
    if (elem.is_non_value()) {
      Heap::free_terms(heap, elements, n_elements);
      return Term::make_nil();
    }
    elements[i] = elem;
  }

  return Term::make_tuple(elements, n_elements);
}


Term read_ext_term(Heap *heap, tool::Reader &r) {
  r.assert_byte(ETF_MARKER);
  return read_ext_term2(heap, r);
}


#if FEATURE_MAPS
Term read_map(Heap *heap, tool::Reader &r) {
  word_t arity = r.read_bigendian_i32();

  if (arity == 0) {
    return Term::make_zero_map();
  }

  for (auto i = 0; i < arity; ++i) {
    Term key = read_ext_term2(heap, r);
    if (key.is_non_value()) {
      return Term::make_nil();
    }

    Term val = read_ext_term2(heap, r);
    if (val.is_non_value()) {
      return Term::make_nil();
    }
  }
}
#endif // FEATURE_MAPS


Term read_string_ext(Heap *heap, tool::Reader &r) {
  word_t length = r.read_bigendian_i16();
  if (length == 0) {
    return Term::make_nil();
  }

  Term result = Term::make_nil();
  Term *elements = Heap::alloc<Term>(heap, length * 2);
  Term *write_p = elements;

  for (int i = length - 1; i >= 0; i--) {
    Term cons = Term::make_cons(write_p);
    *write_p++ = Term::make_small(r.read_byte());
    *write_p++ = result;
    result = cons;
  }

  return result;
}


Term read_ext_term2(Heap *heap, tool::Reader &r) {
  switch (r.read_byte()) {
  case COMPRESSED:
    // =80; 4 bytes size; compressed data
    G_TODO("compressed etf");

  case SMALL_INTEGER_EXT:
    return Term::make_small(r.read_byte());

  case INTEGER_EXT: {
      // 32-bit integer
      word_t n = r.read_bigendian_i32();
      if (get_hardware_bits() > 32) {
        // fits into small_int if platform is x64
        return Term::make_small(n);
      } else { // hardware bits = 32
#if FEATURE_BIGNUM
      if (Term::is_big(n)) {
        G_TODO("construct bignum etf");
      } else {
        return Term::make_small(n);
      }
#else
      // no bignum, and hardware bits not enough: much fail here
      return Term::make_nil();
#endif
      } // hardware bits = 32
    } // integer_ext

  case OLD_FLOAT_STRING_EXT: {
#if FEATURE_FLOAT
    G_TODO("parse float string etf");
#else
    return Term::make_nil(); // sorry no floats
#endif
    } // old string float_ext

  case IEEE_FLOAT_EXT: {
#if FEATURE_FLOAT
      G_TODO("make ieee 8byte double etf");
#else
      return Term::make_nil();
#endif
    } // new 8byte double float_ext

  case ATOM_EXT: return read_atom_string_i16(r);
  case SMALL_ATOM_EXT: return read_atom_string_i8(r);

  case REFERENCE_EXT: {
      // format: N atom string, 4byte id, 1byte creation
//      Term node = read_atom_string(r);
//      word_t id = r.read_bigendian_i32();
//      u8_t creation = r.read_byte();
      G_TODO("ref etf");
    } // end reference_ext

  case PORT_EXT: {
      // format: N atom string, 4byte id, 1byte creation
//      Term node = read_atom_string(r);
//      word_t id = r.read_bigendian_i32();
//      u8_t creation = r.read_byte();
      G_TODO("port etf");
    } // end reference_ext

  case PID_EXT: {
      // format: N atom string, 4byte id, 4byte serial, 1byte cre
      Term node     = read_tagged_atom_string(r);
      word_t id     = r.read_bigendian_i32();
      word_t serial = r.read_bigendian_i32();
      u8_t creation = r.read_byte();
      return make_pid(node, id, serial, creation);
    } // end reference_ext

  case SMALL_TUPLE_EXT: return read_tuple(heap, r, r.read_byte());
  case LARGE_TUPLE_EXT: return read_tuple(heap, r, r.read_bigendian_i32());

  case MAP_EXT:
#if FEATURE_MAPS
    return read_map(heap, r);
#else
    return Term::make_nil();
#endif

  case NIL_EXT: return Term::make_nil();
  case STRING_EXT: return read_string_ext(heap, r);

  } // switch tag

  G_TODO("something not finished etf")
} // parse function


} // ns etf
} // ns gluon