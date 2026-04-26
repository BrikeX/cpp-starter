// =============================================================================
// Google C++ Style Guide Demo: Other C++ Features
// Guide: https://google.github.io/styleguide/cppguide.html#Other_C++_Features
// =============================================================================
//
// ## Rvalue References
//   "Use rvalue references only in certain special cases: move constructors,
//    move assignment, &&-qualified methods that consume *this, forwarding
//    references with std::forward, and pairs of overloads (Foo&& / const
//    Foo&)."
//
// ## Friends
//   "We allow use of friend classes and functions, within reason."
//   "Friends should usually be defined in the same file."
//
// ## Exceptions
//   "We do not use C++ exceptions."
//
// ## noexcept
//   "Specify noexcept when it is useful and correct."
//   "Specifying move constructors as noexcept improves performance in some
//    cases, e.g., std::vector<T>::resize() moves rather than copies."
//
// ## RTTI
//   "Avoid using run-time type information (RTTI)."
//   "Virtual methods are the preferred way of executing different code paths
//    depending on a specific subclass type."
//
// ## Casting
//   "Use C++-style casts like static_cast<float>(double_value), or brace
//    initialization for conversion of arithmetic types like int64_t y =
//    int64_t{1} << 42. Do not use cast formats like (int)x."
//   "Use static_cast for value conversions and well-known upcasts/downcasts."
//   "Use const_cast to remove const."
//   "Use reinterpret_cast for unsafe pointer conversions (know what you do)."
//
// ## Streams
//   "Use streams where appropriate, and stick to 'simple' usages."
//   "Overload << for streaming only for types representing values."
//
// ## Preincrement and Predecrement
//   "Use the prefix form (++i) of the increment and decrement operators
//    unless you need postfix semantics."
//
// ## Use of const
//   "In APIs, use const whenever it makes sense."
//   "We strongly recommend using const in APIs wherever it is meaningful."
//   "Declare methods to be const unless they alter the logical state."
//   "Putting the const first is arguably more readable."
//
// ## constexpr, constinit, and consteval
//   "Use constexpr to define true constants or to ensure constant
//    initialization. Use constinit to ensure constant initialization
//    for non-constant variables."
//
// ## Integer Types
//   "Of the built-in C++ integer types, the only one used is int. If a
//    program needs a different size, use exact-width types from <stdint.h>."
//   "Do not use unsigned types to say a number will never be negative."
//
// ## 0 and nullptr/NULL
//   "Use nullptr for pointers, and '\0' for chars (not the 0 literal)."
//
// ## sizeof
//   "Prefer sizeof(varname) to sizeof(type)."
//
// ## Type Deduction (auto)
//   "Use type deduction only if it makes the code clearer to readers."
//   "You can assume that the return type of make_unique<Foo>() is obvious."
//
// ## Class Template Argument Deduction (CTAD)
//   "Use CTAD only with templates that have explicitly opted into
//    supporting it."
//   "std::array a = {1, 2, 3};  // OK: std has opted in"
//
// ## Designated Initializers
//   "Use designated initializers only in their C++20-compliant form."
//   Initializers must appear in the same order as fields.
//
// ## Lambda Expressions
//   "Use lambda expressions where appropriate. Prefer explicit captures
//    when the lambda will escape the current scope."
//   "Use default capture by reference ([&]) only when the lifetime of the
//    lambda is obviously shorter than any potential captures."
//
// ## Template Metaprogramming
//   "Avoid complicated template programming."
//
// ## Concepts and Constraints
//   "Use concepts sparingly. Prefer constraints over template
//    metaprogramming, and avoid the template<Concept T> syntax; instead,
//    use the requires(Concept<T>) syntax."
//   "Predefined concepts in the standard library should be preferred to
//    type traits."
//
// ## Switch Statements
//   "Switch statements should always have a default case (unless on enum)."
//   "Fall-through must be annotated using [[fallthrough]]."
//
// ## Aliases
//   "Use using instead of typedef."
// =============================================================================

#include <algorithm>
#include <array>
#include <concepts>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <numbers>
#include <string>
#include <utility>
#include <vector>

namespace style_demo {

// ---------------------------------------------------------------------------
// Rvalue References: move constructor with noexcept
// ---------------------------------------------------------------------------
class Buffer {
 public:
  explicit Buffer(size_t size) : data_(new char[size]), size_(size) {
    std::memset(data_, 0, size_);
  }

  // Good: noexcept on move constructor
  Buffer(Buffer&& other) noexcept : data_(other.data_), size_(other.size_) {
    other.data_ = nullptr;
    other.size_ = 0;
  }

  Buffer& operator=(Buffer&& other) noexcept {
    if (this != &other) {
      delete[] data_;
      data_ = other.data_;
      size_ = other.size_;
      other.data_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  Buffer(const Buffer&) = delete;
  Buffer& operator=(const Buffer&) = delete;

  ~Buffer() { delete[] data_; }

  size_t size() const { return size_; }

 private:
  char* data_;
  size_t size_;
};

// ---------------------------------------------------------------------------
// Friends: defined in the same file
// ---------------------------------------------------------------------------
class Secret {
 public:
  explicit Secret(int value) : value_(value) {}

 private:
  int value_;
  friend void PrintSecret(const Secret& secret);
};

void PrintSecret(const Secret& secret) {
  std::cout << "  Secret value: " << secret.value_ << std::endl;
}

// ---------------------------------------------------------------------------
// Casting: use C++ style casts, brace initialization for arithmetic
// ---------------------------------------------------------------------------
void DemoCasting() {
  double pi = std::numbers::pi;

  // Good: static_cast for value conversion
  int truncated = static_cast<int>(pi);

  // Good: brace initialization for safe arithmetic conversion
  int64_t big = int64_t{1} << 40;

  // Bad (shown in comment): C-style cast
  //   int bad = (int)pi;

  std::cout << "  static_cast<int>(3.14159) = " << truncated << std::endl;
  std::cout << "  int64_t{1} << 40 = " << big << std::endl;

  // sizeof: prefer sizeof(varname) over sizeof(type)
  std::array<int, 10> data{};
  std::cout << "  sizeof(data) = " << sizeof(data)
            << ", sizeof(data[0]) = " << sizeof(data[0]) << std::endl;
}

// ---------------------------------------------------------------------------
// const: const methods, const references in APIs
// ---------------------------------------------------------------------------
class Config {
 public:
  explicit Config(std::string name) : name_(std::move(name)) {}

  // Good: const method -- does not modify logical state
  const std::string& name() const { return name_; }

  void set_name(const std::string& name) { name_ = name; }

 private:
  std::string name_;
};

// ---------------------------------------------------------------------------
// constexpr / consteval
// ---------------------------------------------------------------------------
constexpr int Factorial(int n) {
  int result = 1;
  for (int i = 2; i <= n; ++i) {
    result *= i;
  }
  return result;
}

consteval int CompileTimeSquare(int value) { return value * value; }  // NOLINT

// ---------------------------------------------------------------------------
// nullptr: use nullptr, not 0 or NULL
// ---------------------------------------------------------------------------
void ProcessPointer(const int* ptr) {
  if (ptr != nullptr) {
    std::cout << "  *ptr = " << *ptr << std::endl;
  } else {
    std::cout << "  ptr is nullptr" << std::endl;
  }
}

// ---------------------------------------------------------------------------
// Type Deduction (auto): use where it makes code clearer
// ---------------------------------------------------------------------------
void DemoAuto() {
  // Good: make_unique return type is obvious
  auto widget = std::make_unique<Config>("auto-demo");
  std::cout << "  auto widget: " << widget->name() << std::endl;

  // Good: iterator type is boilerplate
  std::vector<std::string> items = {"alpha", "beta", "gamma"};
  // NOLINTNEXTLINE(modernize-loop-convert)
  for (auto it = items.begin(); it != items.end(); ++it) {
    std::cout << "  " << *it << std::endl;
  }

  // Structured bindings (C++17)
  struct Result {
    bool ok;
    int code;
  };
  // NOLINTNEXTLINE(modernize-use-designated-initializers)
  auto [ok, code] = Result{true, 200};
  std::cout << "  Structured binding: ok=" << ok << " code=" << code
            << std::endl;
}

// ---------------------------------------------------------------------------
// CTAD: only where the template has opted in (std:: types)
// ---------------------------------------------------------------------------
void DemoCTAD() {
  // Good: std::array has explicit deduction guides
  std::array numbers = {10, 20, 30, 40};
  std::cout << "  CTAD std::array size: " << numbers.size() << std::endl;

  // Good: std::pair
  std::pair entry = {42, std::string("answer")};
  std::cout << "  CTAD std::pair: " << entry.first << " -> " << entry.second
            << std::endl;
}

// ---------------------------------------------------------------------------
// Designated Initializers (C++20): fields in declaration order
// ---------------------------------------------------------------------------
struct Options {
  int width = 80;
  int height = 24;
  bool fullscreen = false;
};

void DemoDesignatedInit() {
  Options opts = {
      .width = 120, .height = 40,
      // fullscreen uses default (false)
  };
  std::cout << "  Options: " << opts.width << "x" << opts.height
            << " fullscreen=" << opts.fullscreen << std::endl;
}

// ---------------------------------------------------------------------------
// Lambda Expressions: explicit captures, short lambdas
// ---------------------------------------------------------------------------
void DemoLambdas() {
  std::vector<int> v = {5, 3, 1, 4, 2};

  // Good: short lambda, auto parameters in sort are idiomatic
  // NOLINTNEXTLINE(modernize-use-ranges)
  std::sort(v.begin(), v.end(),
            [](int left, int right) { return left < right; });

  std::cout << "  Sorted: ";
  for (int value : v) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // Good: explicit capture when lambda could escape
  int multiplier = 10;
  auto scale = [multiplier](int value) { return value * multiplier; };
  std::cout << "  scale(3) = " << scale(3) << std::endl;

  // Init capture for move-only types
  auto buf = std::make_unique<Buffer>(64);
  auto processor = [buf = std::move(buf)]() {
    std::cout << "  Captured buffer size: " << buf->size() << std::endl;
  };
  processor();
}

// ---------------------------------------------------------------------------
// Concepts and Constraints (C++20): prefer requires() syntax
// ---------------------------------------------------------------------------
template <typename T>
requires std::integral<T>  // NOLINT
    T SafeAdd(T lhs, T rhs) {
  return lhs + rhs;
}

// ---------------------------------------------------------------------------
// Switch Statements: default case, [[fallthrough]]
// ---------------------------------------------------------------------------
void DemoSwitch(int level) {
  switch (level) {
    case 1:
      std::cout << "  Level 1: basic" << std::endl;
      break;
    case 2:
      std::cout << "  Level 2: includes level 3 features" << std::endl;
      [[fallthrough]];
    case 3:
      std::cout << "  Level 3: advanced" << std::endl;
      break;
    default:
      std::cout << "  Unknown level: " << level << std::endl;
      break;
  }
}

// ---------------------------------------------------------------------------
// Aliases: prefer using over typedef
// ---------------------------------------------------------------------------
// Good:
using StringVec = std::vector<std::string>;
// Bad (shown in comment): typedef std::vector<std::string> StringVec;

// Preincrement: prefer ++i
void DemoPreincrement() {
  int total = 0;
  for (int i = 0; i < 5; ++i) {  // Good: prefix ++i
    total += i;
  }
  std::cout << "  Preincrement sum(0..4) = " << total << std::endl;
}

}  // namespace style_demo

int main() {
  using style_demo::Buffer;
  using style_demo::CompileTimeSquare;
  using style_demo::Config;
  using style_demo::DemoAuto;
  using style_demo::DemoCasting;
  using style_demo::DemoCTAD;
  using style_demo::DemoDesignatedInit;
  using style_demo::DemoLambdas;
  using style_demo::DemoPreincrement;
  using style_demo::DemoSwitch;
  using style_demo::Factorial;
  using style_demo::PrintSecret;
  using style_demo::ProcessPointer;
  using style_demo::SafeAdd;
  using style_demo::Secret;
  using style_demo::StringVec;

  std::cout << "=== Modern C++ Features Demo ===" << std::endl;

  std::cout << "\n--- Rvalue References & noexcept ---" << std::endl;
  Buffer b1(128);
  Buffer b2 = std::move(b1);
  std::cout << "  Moved buffer size: " << b2.size() << std::endl;

  std::cout << "\n--- Friends ---" << std::endl;
  PrintSecret(Secret(42));

  std::cout << "\n--- Casting & sizeof ---" << std::endl;
  DemoCasting();

  std::cout << "\n--- const ---" << std::endl;
  Config cfg("my_app");
  std::cout << "  Config: " << cfg.name() << std::endl;

  std::cout << "\n--- constexpr / consteval ---" << std::endl;
  constexpr int kFact5 = Factorial(5);
  constexpr int kSq7 = CompileTimeSquare(7);
  std::cout << "  Factorial(5) = " << kFact5 << std::endl;
  std::cout << "  CompileTimeSquare(7) = " << kSq7 << std::endl;

  std::cout << "\n--- nullptr ---" << std::endl;
  int val = 99;
  ProcessPointer(&val);
  ProcessPointer(nullptr);

  std::cout << "\n--- auto / Type Deduction ---" << std::endl;
  DemoAuto();

  std::cout << "\n--- CTAD ---" << std::endl;
  DemoCTAD();

  std::cout << "\n--- Designated Initializers ---" << std::endl;
  DemoDesignatedInit();

  std::cout << "\n--- Lambdas ---" << std::endl;
  DemoLambdas();

  std::cout << "\n--- Concepts ---" << std::endl;
  std::cout << "  SafeAdd(3, 4) = " << SafeAdd(3, 4) << std::endl;  // NOLINT

  std::cout << "\n--- Switch / [[fallthrough]] ---" << std::endl;
  DemoSwitch(1);
  DemoSwitch(2);
  DemoSwitch(99);

  std::cout << "\n--- Aliases & Preincrement ---" << std::endl;
  StringVec names = {"one", "two", "three"};
  std::cout << "  StringVec size: " << names.size() << std::endl;
  DemoPreincrement();

  return 0;
}
