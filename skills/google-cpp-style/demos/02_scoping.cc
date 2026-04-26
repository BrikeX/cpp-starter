// =============================================================================
// Google C++ Style Guide Demo: Scoping
// Guide: https://google.github.io/styleguide/cppguide.html#Scoping
// =============================================================================
//
// ## Namespaces
//   "With few exceptions, place code in a namespace. Namespaces should have
//    unique names based on the project name, and possibly its path. Do not use
//    using-directives (e.g., using namespace foo). Do not use inline
//    namespaces."
//
//   "Terminate multi-line namespaces with comments as shown."
//   "Namespaces wrap the entire source file after includes."
//   "Single-line nested namespace declarations are preferred in new code."
//
// ## Internal Linkage
//   "When definitions in a .cc file do not need to be referenced outside that
//    file, give them internal linkage by placing them in an unnamed namespace
//    or declaring them static."
//
// ## Nonmember, Static Member, and Global Functions
//   "Prefer placing nonmember functions in a namespace; use completely global
//    functions rarely. Do not use a class simply to group static members."
//
// ## Local Variables
//   "Place a function's variables in the narrowest scope possible, and
//    initialize variables in the declaration."
//
//   "int i;
//    i = f();      // Bad -- initialization separate from declaration.
//    int i = f();  // Good -- declaration has initialization."
//
// ## Static and Global Variables
//   "Objects with static storage duration are forbidden unless they are
//    trivially destructible."
//
//   "const int kNum = 10;  // Allowed"
//   "constexpr std::array<int, 3> kArray = {1, 2, 3};  // Allowed"
//   "const std::string kFoo = \"foo\";  // Bad: non-trivial destructor"
//
//   "Global strings: consider using a constexpr variable of string_view,
//    character array, or character pointer, pointing to a string literal."
//
// ## thread_local Variables
//   "thread_local variables at class or namespace scope must be initialized
//    with a true compile-time constant, and this must be enforced by using
//    the constinit attribute."
//
//   "thread_local variables inside a function have no initialization
//    concerns, but still risk use-after-free during thread exit."
// =============================================================================

#include <array>
#include <iostream>
#include <string_view>
#include <thread>
#include <vector>

// ---------------------------------------------------------------------------
// Internal Linkage: unnamed namespace for file-local helpers
// ---------------------------------------------------------------------------
namespace {

int ComputeSquare(int val) { return val * val; }

}  // namespace

// ---------------------------------------------------------------------------
// Namespaces: nested declaration style (C++17)
// ---------------------------------------------------------------------------
namespace my_project::scoping_demo {

// Good: trivially destructible static constants
constexpr int kMaxItems = 100;
constexpr std::array<int, 4> kPrimes = {2, 3, 5, 7};

// Good: string_view for global string constants (trivially destructible)
constexpr std::string_view kProjectName = "ScopingDemo";

// Bad (shown as comment only -- would compile but violates the guide):
//   const std::string kBadGlobal = "non-trivial destructor";

// ---------------------------------------------------------------------------
// Nonmember function in a namespace (preferred over global or static-member)
// ---------------------------------------------------------------------------
int SumPrimes() {
  int total = 0;
  for (int prime : kPrimes) {
    total += prime;
  }
  return total;
}

// ---------------------------------------------------------------------------
// Local Variables: declare in narrowest scope, initialize at declaration
// ---------------------------------------------------------------------------
constexpr int kSquareInput = 5;
constexpr int kSampleA = 10;
constexpr int kSampleB = 20;
constexpr int kSampleC = 30;

void DemoLocalVariables() {
  // Good: declaration has initialization
  int squared = ComputeSquare(kSquareInput);
  std::cout << "  ComputeSquare(5) = " << squared << std::endl;

  // Good: variable declared inside the loop scope
  std::vector<int> values = {kSampleA, kSampleB, kSampleC};
  for (const int value : values) {
    int doubled = value * 2;  // narrow scope, initialized
    std::cout << "  " << value << " * 2 = " << doubled << std::endl;
  }

  // Good: use brace initialization
  std::vector<int> vec = {1, 2, 3};
  std::cout << "  v.size() = " << vec.size() << std::endl;
}

// ---------------------------------------------------------------------------
// Static Local Variable: allowed with dynamic init (function-local)
// ---------------------------------------------------------------------------
const std::vector<int>& GetCachedData() {
  // Function-local static with dynamic init is allowed.
  static const auto* const kCachedEntries = new std::vector<int>{1, 2, 3, 4, 5};
  return *kCachedEntries;
}

// ---------------------------------------------------------------------------
// thread_local: function-scope is safe; namespace-scope needs constinit
// ---------------------------------------------------------------------------
// NOTE: constinit is a C++20 keyword. Some clangd versions may not recognize
// it if not configured for C++20; the code compiles correctly with CMake.
// NOLINTNEXTLINE namespace-scope needs constinit
constinit thread_local int tl_counter = 0;

void DemoThreadLocal() {
  // Function-scope thread_local with dynamic init is allowed
  auto worker = [](int id) {
    thread_local int call_count = 0;
    ++call_count;
    ++tl_counter;
    std::cout << "  Thread " << id << ": call_count=" << call_count
              << ", tl_counter=" << tl_counter << std::endl;
  };

  std::thread t1(worker, 1);
  std::thread t2(worker, 2);
  t1.join();
  t2.join();
}

}  // namespace my_project::scoping_demo

int main() {
  using my_project::scoping_demo::DemoLocalVariables;
  using my_project::scoping_demo::DemoThreadLocal;
  using my_project::scoping_demo::GetCachedData;
  using my_project::scoping_demo::kMaxItems;
  using my_project::scoping_demo::kProjectName;
  using my_project::scoping_demo::SumPrimes;

  std::cout << "=== Scoping Demo ===" << std::endl;
  std::cout << "Project: " << kProjectName << std::endl;
  std::cout << "SumPrimes: " << SumPrimes() << std::endl;
  std::cout << "kMaxItems: " << kMaxItems << std::endl;

  std::cout << "\n--- Local Variables ---" << std::endl;
  DemoLocalVariables();

  std::cout << "\n--- Cached Static Data ---" << std::endl;
  const auto& cached = GetCachedData();
  std::cout << "  size = " << cached.size() << std::endl;

  std::cout << "\n--- thread_local ---" << std::endl;
  DemoThreadLocal();

  return 0;
}
