#include "g_vm.h"
#include "g_code_server.h"
#include "g_sys_fs.h"
#include "g_sys_mem.h"
#include "g_dist.h"
#include "g_heap.h"
#include "g_predef_atoms.h"
#include "g_process.h"
#include "bif/g_bif_misc.h"

namespace gluon {

str_atom_map_t  VM::g_atoms;
atom_str_map_t  VM::g_atoms_reverse;
word_t          VM::g_atom_counter; // initialized in init_predef_atoms
Node           *VM::g_this_node = nullptr;
const void    **VM::g_opcode_labels;
Str             VM::g_empty_str;
Scheduler      *VM::g_scheduler = nullptr;
code::Server   *VM::g_cs = nullptr;

void VM::init()
{
  g_this_node = new Node;
  g_cs = new code::Server;

  vm_loop(true); // initialize labels

  init_predef_atoms();
}

Term VM::to_atom(const Str &s)
{
  Term a = to_existing_atom(s);
  return a.is_nil() ? new_atom(s) : a;
}

Term VM::to_existing_atom(const Str &s) {
  auto iter = g_atoms.find(s);
  if (iter != g_atoms.end()) {
    return iter->second;
  }
  return NIL;
}

Term VM::new_atom(const Str &s) {
//  auto iter = g_atoms.find(s);
//  if (iter != g_atoms.end()) {
//    G_FAIL("atom exists")
//    G_IF_NODEBUG(return NIL);
//  }
  Term new_a = Term::make_atom(g_atom_counter);
  g_atoms[s]             = new_a;
  g_atoms_reverse[new_a] = s;
  g_atom_counter++;
  return new_a;
}

void VM::init_predef_atoms()
{
  const char *p = atom::g_predef_atoms;
  g_atom_counter = 1;

  while (*p) {
    word_t len = (word_t)(p[0]);
    new_atom(Str(p+1, len));
    p += len + 1;
  }

  // TODO: get rid of
}

const Str &VM::find_atom(Term a)
{
  G_ASSERT(a.is_atom());
  auto iter = g_atoms_reverse.find(a);
  if (iter != g_atoms_reverse.end()) {
    return iter->second;
  }
  return g_empty_str;
}

Node *VM::dist_this_node() {
#if FEATURE_ERL_DIST
  G_TODO("implement Node and this node variable")
#endif
  return g_this_node;
}

// For now all heaps are located in normal C++ heap
Heap *VM::get_heap(VM::heap_t) {
  return nullptr;
}

bif0_fn VM::resolve_bif0(mfarity_t &mfa)
{
  return nullptr;
}

bif1_fn VM::resolve_bif1(mfarity_t &mfa)
{
  G_ASSERT(mfa.arity == 1);
  if (mfa.mod == atom::ERLANG) {
    if (mfa.fun == atom::LENGTH)       { return &bif::bif_length_1; }
    if (mfa.fun == atom::ATOM_TO_LIST) { return &bif::bif_atom_to_list_1; }
  }
  return nullptr;
}

bif2_fn VM::resolve_bif2(mfarity_t &mfa)
{
  G_ASSERT(mfa.arity == 2);
  if (mfa.mod == atom::ERLANG) {
    if (mfa.fun == atom::Q_MINUS)        { return &bif::bif_minus_2; }
    if (mfa.fun == atom::Q_PLUS)         { return &bif::bif_plus_2; }
    if (mfa.fun == atom::Q_MULTIPLY)     { return &bif::bif_multiply_2; }
    if (mfa.fun == atom::Q_DIVIDE)       { return &bif::bif_divide_2; }
    if (mfa.fun == atom::Q_EQUALS)       { return &bif::bif_equals_2; }
    if (mfa.fun == atom::Q_EQUALS_EXACT) { return &bif::bif_equals_exact_2; }
    if (mfa.fun == atom::Q_LESS_EQUAL)   { return &bif::bif_less_equal_2; }
    if (mfa.fun == atom::Q_GREATER_EQUAL){ return &bif::bif_greater_equal_2; }
  }
  return nullptr;
}

bif3_fn VM::resolve_bif3(mfarity_t &mfa)
{
  G_ASSERT(mfa.arity == 3);
  if (mfa.mod == atom::ERLANG) {
    if (mfa.fun == atom::MAKE_FUN) { return &bif::bif_make_fun_3; }
  }
  return nullptr;
}

// TODO: replace with bif search indes
void *VM::find_bif(mfarity_t &mfa)
{
  switch (mfa.arity) {
  case 0: {
      auto b0 = resolve_bif0(mfa);
      return (void *)b0;
    }
  case 1: {
      auto b1 = resolve_bif1(mfa);
      return (void *)b1;
    }
  case 2: {
      auto b2 = resolve_bif2(mfa);
      return (void *)b2;
    }
  case 3: {
      auto b3 = resolve_bif3(mfa);
      return (void *)b3;
    }
  }
  return nullptr;
}

Term VM::apply_bif(Process *proc, mfarity_t &mfa, Term *args)
{
  switch (mfa.arity) {
  case 0: {
      auto b0 = resolve_bif0(mfa);
      if (b0) {
        return b0(proc);
      }
      break;
    }
  case 1: {
      auto b1 = resolve_bif1(mfa);
      if (b1) {
        return b1(proc, args[0]);
      }
      break;
    }
  case 2: {
      auto b2 = resolve_bif2(mfa);
      if (b2) {
        return b2(proc, args[0], args[1]);
      }
      break;
    }
  case 3: {
      auto b3 = resolve_bif3(mfa);
      if (b3) {
        return b3(proc, args[0], args[1], args[2]);
      }
      break;
    }
  }
  return proc->bif_error(atom::UNDEF);
}

Term VM::apply_bif(Process *proc, word_t arity, void *fn, Term *args)
{
  if (!fn) {
    return proc->bif_error(atom::BADFUN);
  }
  switch (arity) {
  case 0: return ((bif0_fn)fn)(proc);
  case 1: return ((bif1_fn)fn)(proc, args[0]);
  case 2: return ((bif2_fn)fn)(proc, args[0], args[1]);
  case 3: return ((bif3_fn)fn)(proc, args[0], args[1], args[2]);
  }
  return proc->bif_error(atom::UNDEF);
}

Scheduler *VM::get_scheduler() {
  if (g_scheduler == nullptr) {
    g_scheduler = Heap::alloc_object<Scheduler>(get_heap(HEAP_VM_INTERNAL));
  }
  return g_scheduler;
}


} // ns gluon
