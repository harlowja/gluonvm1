#pragma once

#include "g_defs.h"
#include "g_term.h"
#include "g_error.h"
#include "g_dist.h"

namespace gluon {

using str_atom_map_t = Map<Str, Term>;
using atom_str_map_t = Map<Term, Str>;

class Heap;

// Note: singleton, do not instantiate even
class VM {
private:
  VM() = delete;
  static str_atom_map_t g_atoms;
  static atom_str_map_t g_atoms_reverse;
  static word_t g_atom_counter;
  static Node *g_this_node;

public:
  static void init();
  static MaybeError load_module(const Str &filename);

  static Term to_atom(const Str &s);
  static Term to_existing_atom(const Str &s);
  static Term new_atom(const Str &s);
  static Str find_atom(Term a);

  static Node *dist_this_node();

  // Heap management
  typedef enum {
    HEAP_CODE,
    HEAP_LOADER_TMP
  } heap_t;
  static Heap *get_heap(heap_t);
};

} // ns gluon
