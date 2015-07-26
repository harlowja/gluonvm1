#pragma once

#include "g_defs.h"
#include "g_term.h"
#include "g_error.h"

namespace gluon {

class Module;
class Process;

// Set of stuff we take from Process struct to keep running, this will be saved
// by loop runner on context switch or loop end
typedef struct {
//  Module *mod = nullptr;
  word_t *ip = nullptr;   // code pointer
  // continuation, works like return address for a single call. If more nested
  // calls are done, cp is saved to stack
  word_t *cp = nullptr;
  word_t live = 0; // saved registers count

  Term    regs[VM_MAX_REGS];
#if FEATURE_FLOAT
  //float_t fp_regs[MAX_FP_REGS];
#endif
} runtime_ctx_t;

class ProcessStack {
  Vector<Term> cells;
public:
  ProcessStack() {}
  void push(Term t) {
    cells.push_back(t);
  }
  Term pop() {
    Term t = cells.back();
    cells.pop_back();
    return t;
  }
  void set(word_t offset, Term t) {
    G_ASSERT(offset < cells.size());
    cells[top_nth_index(offset)] = t;
  }
  Term get(word_t offset) const {
    G_ASSERT(offset < cells.size());
    return cells[top_nth_index(offset)];
  }
  void push_n_nils(word_t n) {
    cells.reserve(cells.size() + n);
    while (n > 0) {
      cells.push_back(Term::make_nil());
      n--;
    }
  }
  void drop_n(word_t n) {
    G_ASSERT(cells.size() >= n);
    cells.resize(cells.size() - n);
  }
  word_t size() const {
    return cells.size();
  }

protected:
  inline word_t top_nth_index(word_t offset) const {
    return cells.size() - 1 - offset;
  }
};

//------------------------------------------------------------------------------
// Thread of execution in VM
// Has own heap (well TODO, using shared now)
// Has own set of registers, own stack, own instruction pointer, mailbox and
// process dictionary
//------------------------------------------------------------------------------
class Process {
public:
  Term    m_stack_trace = Term::make_non_value();
  word_t        m_catch_level = 0;

protected:
  runtime_ctx_t m_ctx;
  ProcessStack  m_stack;
  Term          m_pid;

public:
  Process() {
    // TODO: fill pid?
  }

  Term get_pid() const {
    return m_pid;
  }
  // Resolves M:F/Arity and sets instruction pointer to it. Runs no code.
  MaybeError call(Term m, Term f, word_t arity, Term args);
  runtime_ctx_t &get_runtime_ctx() {
    return m_ctx;
  }
  ProcessStack *get_stack() {
    return &m_stack;
  }
  Heap *get_heap();

  // Not inlined, ask module for pointer to its code. Safety off!
  word_t *get_ip() const;
//  word_t *get_code_base() const;
};

} // ns gluon
