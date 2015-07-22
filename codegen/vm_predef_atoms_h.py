#!/usr/bin/python
# takes: genop.tab from erlang/otp
# produces: predef atoms include file with constants
import libgenop

libgenop.load()

print("""// Generated by codegen/vm_predef_atoms_*.py

#include "g_term.h"

namespace gluon {
namespace atom {
""")

# print atom constants
atom_id = 1
for a in libgenop.atom_tab:
    if 'cname' in a:
        constname = "Q_" + a['cname'].upper()
    else:
        constname = a['atom'].upper()
    print("  const Term %s = Term::make_atom(%d);" % (constname, atom_id))
    atom_id += 1

print("""
  extern const char *g_predef_atoms;

} // ns atom
} // ns gluon
""")