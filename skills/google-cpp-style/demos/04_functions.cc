// =============================================================================
// Google C++ Style Guide Demo: Functions
// Guide: https://google.github.io/styleguide/cppguide.html#Functions
// =============================================================================
//
// ## Inputs and Outputs
//   "Prefer using return values over output parameters: they improve
//    readability, and often provide the same or better performance."
//   "Prefer to return by value or, failing that, return by reference."
//   "Non-optional input parameters should usually be values or const
//    references, while non-optional output and input/output parameters
//    should usually be references (which cannot be null)."
//   "Generally, use std::optional to represent optional by-value inputs."
//   "When ordering function parameters, put all input-only parameters
//    before any output parameters."
//
// ## Write Short Functions
//   "Prefer small and focused functions."
//   "If a function exceeds about 40 lines, think about whether it can be
//    broken up without harming the structure of the program."
//
// ## Function Overloading
//   "Use overloaded functions only if a reader looking at a call site can
//    get a good idea of what is happening without having to first figure
//    out exactly which overload is being called."
//   "You may overload a function when there are no semantic differences
//    between variants."
//
// ## Default Arguments
//   "Default arguments are allowed on non-virtual functions when the
//    default is guaranteed to always have the same value."
//   "Default arguments are banned on virtual functions."
//
// ## Trailing Return Type Syntax
//   "Use trailing return types only where using the ordinary syntax
//    (leading return types) is impractical or much less readable."
//   "Trailing return types are the only way to explicitly specify the
//    return type of a lambda expression."
//   Example:
//     template <typename T, typename U>
//     auto Add(T t, U u) -> decltype(t + u);
// =============================================================================

#include <charconv>
#include <iostream>
#include <numeric>
#include <optional>
#include <string>
#include <vector>

namespace style_demo {

// ---------------------------------------------------------------------------
// Inputs and Outputs: return by value, const& for inputs, inputs before outputs
// ---------------------------------------------------------------------------

// Good: return by value, input as const reference
std::string FormatName(const std::string& first, const std::string& last) {
  return last + ", " + first;
}

// Good: optional input parameter using std::optional
std::string Greet(const std::string& name,
                  std::optional<std::string> title = std::nullopt) {
  if (title.has_value()) {
    return "Hello, " + *title + " " + name + "!";
  }
  return "Hello, " + name + "!";
}

// Good: output via return value, not output parameter
struct ParseResult {
  bool success;
  int value;
  std::string error;
};

ParseResult ParseInt(const std::string& input) {
  int val = 0;
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  const char* const input_end = input.data() + input.size();
  auto [ptr, ec] = std::from_chars(input.data(), input_end, val);
  if (ec == std::errc{} && ptr == input_end) {
    return ParseResult{.success = true, .value = val, .error = ""};
  }
  return ParseResult{
      .success = false, .value = 0, .error = "Failed to parse: " + input};
}

// If output parameters are necessary: inputs before outputs
void SplitString(const std::string& input, char delimiter,
                 std::vector<std::string>& output) {
  output.clear();
  std::string current;
  for (char c : input) {
    if (c == delimiter) {
      output.push_back(current);
      current.clear();
    } else {
      current += c;
    }
  }
  if (!current.empty()) {
    output.push_back(current);
  }
}

// ---------------------------------------------------------------------------
// Function Overloading: semantic equivalence across variants
// ---------------------------------------------------------------------------

// Overloads with no semantic difference -- all compute an average
double Average(const std::vector<int>& values) {
  if (values.empty()) {
    return 0.0;
  }
  return static_cast<double>(std::accumulate(values.begin(), values.end(), 0)) /
         static_cast<double>(values.size());
}

double Average(const std::vector<double>& values) {
  if (values.empty()) {
    return 0.0;
  }
  return std::accumulate(values.begin(), values.end(), 0.0) /
         static_cast<double>(values.size());
}

// ---------------------------------------------------------------------------
// Default Arguments: guaranteed same value, non-virtual
// ---------------------------------------------------------------------------
std::string Repeat(const std::string& text, int times = 1) {
  std::string result;
  for (int i = 0; i < times; ++i) {
    if (i > 0) {
      result += " ";
    }
    result += text;
  }
  return result;
}

// ---------------------------------------------------------------------------
// Trailing Return Type Syntax: useful when return type depends on parameters
// ---------------------------------------------------------------------------
template <typename T, typename U>
auto Add(T lhs, U rhs) -> decltype(lhs + rhs) {
  return lhs + rhs;
}

// Ordinary leading return type is fine for simple cases
int Multiply(int val1, int val2) { return val1 * val2; }

}  // namespace style_demo

int main() {
  using style_demo::Add;
  using style_demo::Average;
  using style_demo::FormatName;
  using style_demo::Greet;
  using style_demo::Multiply;
  using style_demo::ParseInt;
  using style_demo::Repeat;
  using style_demo::SplitString;

  std::cout << "=== Functions Demo ===" << std::endl;

  // Inputs and Outputs
  std::cout << "FormatName: " << FormatName("John", "Doe") << std::endl;
  std::cout << "Greet: " << Greet("Alice") << std::endl;
  std::cout << "Greet: " << Greet("Bob", "Dr.") << std::endl;

  auto result = ParseInt("42");
  std::cout << "ParseInt(\"42\"): success=" << result.success
            << " value=" << result.value << std::endl;
  auto bad = ParseInt("xyz");
  std::cout << "ParseInt(\"xyz\"): success=" << bad.success
            << " error=" << bad.error << std::endl;

  std::vector<std::string> parts;
  SplitString("a:b:c", ':', parts);
  std::cout << "SplitString: ";
  for (const auto& p : parts) {
    std::cout << "[" << p << "] ";
  }
  std::cout << std::endl;

  // Function Overloading
  std::vector<int> ints = {10, 20, 30};
  std::vector<double> doubles = {1.5, 2.5, 3.5};
  std::cout << "Average(ints): " << Average(ints) << std::endl;
  std::cout << "Average(doubles): " << Average(doubles) << std::endl;

  // Default Arguments
  std::cout << "Repeat: " << Repeat("hello") << std::endl;
  std::cout << "Repeat x3: " << Repeat("hello", 3) << std::endl;

  // Trailing Return Type
  std::cout << "Add(1, 2.5): " << Add(1, 2.5) << std::endl;
  std::cout << "Multiply(3, 4): " << Multiply(3, 4) << std::endl;

  return 0;
}
