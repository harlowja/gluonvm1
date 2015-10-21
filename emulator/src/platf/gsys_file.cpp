#include "gsys_file.h"
//#include "g_error.h"
#include "struct/g_str.h"

#include <stdio.h>
#include <sys/stat.h>

namespace gluon {

namespace err {
  DECL_IMPL_EXCEPTION(file_error)
} // ns err

namespace fs {

bool exists(const Str &name) {
  struct stat buffer;
  return (::stat (name.c_str(), &buffer) == 0);
}


inline void *to_internal(FILE *f) { return reinterpret_cast<void *>(f); }
inline FILE *to_file(void *f) { return reinterpret_cast<FILE *>(f); }

File::File(void *f): m_handle(f) {
}
File::File(): m_handle(nullptr) {
}

void fs::File::open(const Str &name) {
  auto handle = ::fopen(name.c_str(), "rb");
  if (!handle) {
    throw err::file_error("open error");
  }
  m_handle = to_internal(handle);
  return;
}

File::~File() {
  if (m_handle) {
    ::fclose(to_file(m_handle));
  }
}

word_t File::size() {
  auto f = to_file(m_handle);
  //auto old_pos = ::ftell(f);

  ::fseek(f, 0, SEEK_END);
  return static_cast<word_t>(::ftell(f));
}

void File::seek(word_t offset) {
  ::fseek(to_file(m_handle), (ssize_t)offset, SEEK_SET);
}

word_t File::read(u8_t *dst, word_t bytes) {
  auto result = ::fread(dst, 1, bytes, to_file(m_handle));
  return result;
}

} // ns fs
} // ns gluon