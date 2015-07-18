#!/usr/bin/python
# takes: genop.tab from erlang/otp
# produces: g_genop.h header with arrays that map erlang asm opcodes to numbers
import libgenop

ops = libgenop.load()

print("// Generated by codegen/genop_emu.py")
print("#pragma once")

print("namespace gluon {")
print("namespace genop {")

print

print("const unsigned int MIN_OPCODE = %d;" % libgenop.MIN_OPCODE)
print("const unsigned int MAX_OPCODE = %d;" % libgenop.MAX_OPCODE)
print

# make op map by opcode
ops_by_code = {}
for op in ops:
    ops_by_code[op['opcode']] = op

# print constants
for opcode in range(libgenop.MIN_OPCODE, libgenop.MAX_OPCODE+1):
    op = ops_by_code[opcode]
    print("const u8_t OPCODE_%s = %d; // 0x%x" % (op['name'].upper(), opcode, opcode));
print

# print arity map
print("const unsigned char arity_map[] = {0, // opcode 0 does not exist")
for opcode in range(libgenop.MIN_OPCODE, libgenop.MAX_OPCODE+1):
    op = ops_by_code[opcode]
    print("    %d, // opcode: %d (%s)" % (op['arity'], opcode, op['name']))
print("};")
print

# print opcode names map
print("#if G_DEBUG")
print("extern const char *opcode_name_map[];")
print("const char *opcode_name_map[] = {nullptr, // opcode 0 does not exist")
for opcode in range(libgenop.MIN_OPCODE, libgenop.MAX_OPCODE+1):
    op = ops_by_code[opcode]
    print("    \"%s\", // opcode: %d" % (op['name'], opcode))
print("};")
print("#endif // G_DEBUG")
print

print("} // ns genop")
print("} // ns gluon")
print
