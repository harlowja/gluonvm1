#pragma once

#include <set>
#include <list>
#include <memory>
#include <queue>
//#include "gsl/array_view.h"
#include <cstdint>

// set features for use in code in this file
#include "g_FEATURE.h"

// Default value (set in CMakeLists.txt, do not edit here)
#ifndef G_DEBUG
#   define G_DEBUG 1
#endif

#if __BYTE_ORDER == __LITTLE_ENDIAN
#   define G_BIGENDIAN      0
#else
#   define G_BIGENDIAN      1
#endif

#if __GNUC__
#   if __x86_64__ || __ppc64__
#       define G_HARDWARE_BITS 64
#   else
#       define G_HARDWARE_BITS 32
#   endif
#else
#   error "Define platform bit width detection code"
#endif

#define FMT_HEX "%zx"
#define FMT_0xHEX "0x" FMT_HEX
#define FMT_SWORD "%zi"
#define FMT_UWORD "%zu"

namespace gluon {

#define DECL_EXCEPTION(NAME)                      \
  class NAME: public std::runtime_error {         \
  public:                                         \
    NAME(const char *e): std::runtime_error(e) {} \
    virtual const char *what() const noexcept;    \
  };
#define IMPL_EXCEPTION(NAME)            \
  const char *NAME::what() const noexcept { \
    return std::runtime_error::what();  \
  }
#define DECL_IMPL_EXCEPTION(NAME) DECL_EXCEPTION(NAME) IMPL_EXCEPTION(NAME)

  namespace err {
    DECL_EXCEPTION(feature_missing_error)
    DECL_EXCEPTION(todo_error)
    DECL_EXCEPTION(beam_load_error)
    DECL_EXCEPTION(scheduler_error)
    DECL_EXCEPTION(code_server_error)
    DECL_EXCEPTION(process_error)
  } // ns err

  constexpr unsigned int get_hardware_bits() {
    return (8*sizeof(void*));
  }

  //template <typename T>
  //using array_view = gsl::array_view<T>;

  // Self-deleting RAII-style pointer holder
  template <typename V>
  using UniquePtr = std::unique_ptr<V>;

  // Self-deleting refcounted copyable pointer
  template <typename V>
  using RcPtr = std::shared_ptr<V>;

  template <typename A, typename B>
  using Pair = std::pair<A, B>;

  template <typename A>
  using List = std::list<A>;

  // Single-ended queue with push to end/pop front operations
  template <typename A>
  using Queue = std::queue<A>;

  template <typename A>
  using Set = std::set<A>;

  using word_t = std::size_t;
  using sword_t = std::ptrdiff_t;

  constexpr inline word_t word_size(word_t x) {
    return (x + sizeof(word_t) - 1) / sizeof(word_t);
  }

  using u8_t = std::uint8_t;
  using i8_t = std::int8_t;
  using u16_t = std::uint16_t;
  using s16_t = std::int16_t;
  using u32_t = std::uint32_t;
  using s32_t = std::int32_t;
  using u64_t = std::uint64_t;
  using s64_t = std::int64_t;

#if FEATURE_FLOAT
  using float_t = float;
  using f32_t = float;
  using f64_t = double;
#endif

  // Used to shun debug printfs in release
  inline void dummy_printf(const char *, ...) {}

  // Wraps a type into a class to make it separate type
  template <typename T>
  class Wrap {
  private:
    T value_;
  public:
    Wrap(): value_() {}
    explicit Wrap(T x): value_(x) {}
    T value() const { return value_; }
    void value(T newvalue) { value_ = newvalue; }
  };
  // Index in label table, wrapped to create a distinct compile-time type
  using LabelIndex = Wrap<word_t>;

  namespace erts {
    // How many reds will a process be allowed to run before next proc wakes up
    // Adjust this for slow devices. 2000 is used for regular modern hardware.
    constexpr word_t reductions_per_slice = 250;

    constexpr word_t max_fun_arity = 16;
    constexpr word_t max_regs = 64; // (max arity of fun + captured terms)
    constexpr word_t max_stack = 128; // is not enforced anywhere yet
    constexpr word_t max_fp_regs = 2;
  } // vm

#if FEATURE_LINE_NUMBERS
  namespace line {
    constexpr bool is_valid_loc(word_t File, word_t Line) {
        return (File < 255 && Line < ((1 << 24) - 1));
    }
    constexpr word_t make_location(word_t File, word_t Line) {
      return (File << 24) | Line;
    }
    constexpr word_t get_loc_file(word_t Loc) {
      return Loc >> 24;
    }
    constexpr word_t get_loc_line(word_t Loc) {
      return Loc & ((1 << 24)-1);
    }

    const static word_t invalid_location = make_location(0, 0);
  } // ns line
#endif


} // ns gluon

// Branch prediction helper macros, use when something is going to happen much
// more or much less often
#define G_LIKELY(x)       __builtin_expect((x),1)
#define G_UNLIKELY(x)     __builtin_expect((x),0)

#define G_NORETURN __attribute__((noreturn))

#define G_FAIL(MSG) ::fprintf(stderr, "FAIL: %s (%s:%d)\n", MSG, __FILE__, __LINE__); ::abort();

// TODO: debug macro goes here
#if G_DEBUG
#   define G_ASSERT(X) if (!(X)) { G_FAIL(#X); }
#   define G_ASSERT_MSG(X, MSG) if (!(X)) { G_FAIL(MSG); }
#   define G_TODO(what) { \
      ::fprintf(stderr, "TODO: %s (%s:%d)\n", what, __FILE__, __LINE__);  \
      throw gluon::err::todo_error(what); \
      }
    // Famous io:format/2 skill on Linkedin!
#   define G_LOG gluon::Std::fmt
#   define G_IF_NODEBUG(X)

#else // no G_DEBUG

#   define G_ASSERT(X)
#   define G_ASSERT_MSG(X, MSG)
#   define G_TODO(X)
#   define G_LOG dummy_printf
#   define G_IF_NODEBUG(X) X
#endif

// TODO: borrow hot/cold table or build my own
#define G_ATTR_HOT __attribute((__hot__))
#define G_ATTR_COLD __attribute((__cold__))
