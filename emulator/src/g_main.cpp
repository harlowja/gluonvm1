#include "g_vm.h"
#include "g_process.h"
#include "g_error.h"

#include <stdio.h>

using vm = gluon::VM;

#if G_TEST
void run_tests(int argc, const char *argv[]) {
  gluon::term_test(argc, argv);
}
#endif

int main(int argc, const char *argv[]) {

  vm::init();

#if G_TEST
  // test runner
  run_tests(argc, argv);
  return 0;
#else

  // normal start
  vm::load_module("../test/g_test1.S.gleam");
  gluon::Process p;
  auto j_result = p.call(vm::to_atom("g_test1"), vm::to_atom("test1"), 0,
                         gluon::Term::make_nil());
  if (j_result.is_error()) {
    printf("jump error: %s\n", j_result.get_error());
  } else {
    printf("ok");
  }

  return 0;
#endif
}
