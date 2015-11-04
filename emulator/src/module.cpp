#include "module.h"
#include "reader.h"
#include "vm.h"
#include "g_functional.h"

namespace gluon {

Word* Module::resolve_label(LabelIndex label) {
  if (label.value() >= labels_.size()) {
    throw err::BeamLoad("label index too big");
  }
  auto lptr = labels_.find_ptr(label.value());
  return lptr ? *lptr : nullptr;
}

void Module::set_exports(Module::Exports& e) {
  exports_ = std::move(e);

  // Replace known BIFs in exports with their BIF pointer and flag them as such
  auto exps = exports_.all();
  for_each(exps, [this](auto fa_exp) {
    void* bif_ptr = vm_->find_bif(MFArity(name_, fa_exp->first));
    if (bif_ptr) {
      exports_.insert(fa_exp->first, Export(bif_ptr));
    }
  });
}

#if FEATURE_CODE_RANGES
bool Module::find_fun_arity(const Word* ptr, FunArity& out) const {
  return fun_index_.find(ptr, out);
}
#endif

#if FEATURE_CODE_RANGES
code::Range Module::get_code_range() {
  return code::Range(code_.data(), (&code_.back()) + 1);
}
#endif

}  // ns gluon