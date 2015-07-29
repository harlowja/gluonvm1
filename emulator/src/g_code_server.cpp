#include "g_code_server.h"
#include "g_module.h"
#include "g_sys_fs.h"
#include "g_heap.h"
#include "g_vm.h"

namespace gluon {
namespace code {

//mod_map_t Server::g_modules;
//List<Str> Server::g_search_path;

//void Server::init() {
//}

MaybeError Server::load_module(Term name_atom, const u8_t *bytes, word_t size)
{
  auto lm_result = load_module_internal(name_atom, bytes, size);
  G_RETURN_IF_ERROR(lm_result);

  // TODO: module versions for hot code loading
  // TODO: free if module already existed, check module usage by processes
  Module *m = lm_result.get_result();
  m_modules[m->get_name()] = m;

  // assume that mod already registered own functions in own fun index
  // code to fun/arity mapping should be updated on loading stage
#if FEATURE_CODE_RANGES
  auto range = m->get_code_range();
  m_mod_index.add(range, m);
#endif

  return success();
}

MaybeError Server::load_module(Term name)
{
  // Scan for locations where module file can be found
  Str mod_filename = name.atom_str() + ".beam";

  for (const Str &dir: m_search_path) {
    Str path = dir + "/" + mod_filename;
    if (fs::exists(path)) {
      fs::File f;
      auto open_result = f.open(path);
      G_RETURN_IF_ERROR_UNLIKELY(open_result);
      word_t  size = f.size();
      Heap    *heap = VM::get_heap(VM::HEAP_CODE);
      u8_t    *tmp_buffer = Heap::alloc_bytes(heap, size);
      f.seek(0);
      f.read(tmp_buffer, size);

      auto    result = load_module(name, tmp_buffer, size);
      Heap::free_bytes(heap, tmp_buffer);
      return result;
    }
  }
  return "module not found";
}

Result<Module *> Server::find_module(Term m, find_opt_t load)
{
  auto iter = m_modules.find(m);
  if (iter == m_modules.end()) {
    if (load == Server::FIND_EXISTING) {
      return error<Module *>("function not found");
    } else {
      auto res = load_module(m);
      G_RETURN_REWRAP_IF_ERROR(res, Module *);
      return success(m_modules[m]);
    }
  }
  return success(iter->second);
}

void Server::path_append(const Str &p)
{
  m_search_path.push_back(p);
}

void Server::path_prepend(const Str &p)
{
  m_search_path.push_front(p);
}

bool Server::print_mfa(word_t *ptr) const {
  auto mfa = find_mfa(ptr);
  if (mfa.mod.is_non_value()) {
    return false;
  }
  printf("%s:%s/%zu", mfa.mod.atom_c_str(), mfa.fun.atom_c_str(), mfa.arity);
  return true;
}

mfarity_t Server::find_mfa(word_t *ptr) const
{
  Module *m = m_mod_index.find(ptr);
  if (!m) {
    return mfarity_t();
  }
  auto fa = m->find_fun_arity(ptr);
  return mfarity_t(m->get_name(), fa.first, fa.second);
}

} // ns code
} // ns gluon