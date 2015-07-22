#!/usr/bin/python
# takes: genop.tab from erlang/otp
# produces: g_vm_loop includable file with label copypaste template for vm 
# loop function
import libgenop

libgenop.load()

print("""// Generated by codegen/vm_loop.py

#include "g_vm.h"
#include "g_process.h"

// has own gluon namespace
#include "g_vm_impl.h"

namespace gluon {
""")

print("""void VM::vm_loop(Process *proc) {
  impl::vm_runtime_ctx_t ctx;
  void *jmp_to;

  if (!proc) {
    goto vm_jump_table_init;
  }

  ctx.load(proc); // get copies of quick access data from environment

next_instr:
  jmp_to = (void *)(*ctx.ip);
  printf("[0x%zx]: ", (word_t)(ctx.ip - ctx.base));
  ctx.ip++;
  goto *jmp_to;
""")
for opcode in range(libgenop.MIN_OPCODE, libgenop.MAX_OPCODE+1):
    op = libgenop.ops_by_code[opcode]
    if op['name'] == "int_code_end":
        print("""OP_%s: // opcode: %s
  goto vm_end;
""" % (op['name'], opcode))
        continue

    print("OP_%s: // opcode: %d" % (op['name'], opcode))
    if op['name'] in libgenop.implemented_ops:
        print('  printf("%s/%d args=");' % (op['name'], op['arity']))
        print('  ctx.print_args(%d);' % (op['arity']))
        if op['name'] == 'return':
            # special instruction which can interrupt loop
            print("""  if (! impl::opcode_%s(proc, ctx)) {
    return;
  }""" % (op['name']))
        else:
            print("  impl::opcode_%s(proc, ctx);" % (op['name']))
        print("  goto next_instr;")
    else:
        print("  G_FAIL(\"notimpl %s\");" % (op['name']))
        print("  G_IF_NODEBUG(goto next_instr;)")
    print

#
# Init table with labels and export it to global scope
#
print("""vm_jump_table_init: {
  // Init table with labels and export it to global scope
  static const void *l_opcode_labels[] = { nullptr,""")

for opcode in range(libgenop.MIN_OPCODE, libgenop.MAX_OPCODE+1):
    op = libgenop.ops_by_code[opcode]
    print("      &&OP_%s, // opcode %d" % (op['name'], opcode))

print("""    };
    g_opcode_labels = l_opcode_labels;
  } // end init

vm_end: ;
}

} // ns gluon
""")
