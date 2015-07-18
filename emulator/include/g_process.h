#pragma once

#include "g_defs.h"
#include "g_term.h"
#include "g_error.h"

namespace gluon {

class Module;

static const word_t MAX_REGS = 16; // max arity of fun which can be called
static const word_t MAX_FP_REGS = 2;

typedef struct gleam_ptr_t {
  Module        *module;
  code_offset_t  offset;

  gleam_ptr_t(): module(nullptr) {
    offset.value = 0;
  }
  inline bool is_good() const {
    return module != nullptr;
  }
  word_t next_word();
} gleam_ptr_t;

// Thread of execution in VM
// Has own heap (well TODO, using shared now)
// Has own set of registers, own stack, own instruction pointer, mailbox and
// process dictionary
class Process {
private:
  Term      m_reg[MAX_REGS];
#if FEATURE_FLOAT
  //float_t   m_fp_reg[MAX_FP_REGS];
#endif
  // Instruction pointer, relative to a given code object. Has no meaning
  // without a code object (a module pointer)
  gleam_ptr_t m_ip;
public:
  Process() {
  }

  MaybeError call(Term m, Term f, word_t arity, Term args);

  // Reads next instruction from code (instruction pointer)
  void *vm_fetch_instr();
};

} // ns gluon
