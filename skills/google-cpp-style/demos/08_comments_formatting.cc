// =============================================================================
// Google C++ Style Guide Demo: Comments and Formatting
// Guide: https://google.github.io/styleguide/cppguide.html#Comments
//        https://google.github.io/styleguide/cppguide.html#Formatting
// =============================================================================
//
// ## Comment Style
//   "Use either the // or /* */ syntax, as long as you are consistent."
//   "// is much more common."
//
// ## File Comments
//   "Start each file with license boilerplate."
//   "If a source file declares multiple user-facing abstractions, include
//    a comment describing the collection."
//
// ## Struct and Class Comments
//   "Every non-obvious class or struct declaration should have an
//    accompanying comment that describes what it is for and how it
//    should be used."
//
// ## Function Comments
//   "Almost every function declaration should have comments immediately
//    preceding it that describe what the function does and how to use it."
//   "Function comments should be written with an implied subject of
//    'This function' and should start with the verb phrase."
//
// ## Variable Comments
//   "The purpose of each class data member must be clear."
//   "All global variables should have a comment."
//
// ## Implementation Comments
//   "Do not state the obvious. Provide higher-level comments that describe
//    WHY the code does what it does."
//
// ## Function Argument Comments
//   "When the meaning of a function argument is nonobvious, consider
//    using a named constant, an enum argument, or a comment at the call
//    site: CalculateProduct(values, options, /*completion_callback=*/nullptr)."
//
// ## TODO Comments
//   "Use TODO comments for code that is temporary, a short-term solution,
//    or good-enough but not perfect."
//   "// TODO: bug 12345678 - Remove this after the 2047q4 window expires."
//   "// TODO(John): Use a '*' here for concatenation operator."
//
// ## Line Length
//   "Each line of text in your code should be at most 80 characters long."
//
// ## Spaces vs. Tabs
//   "Use only spaces, and indent 2 spaces at a time."
//
// ## Function Declarations and Definitions
//   "Return type on the same line as function name, parameters on same
//    line if they fit. Wrap at 80 columns."
//
// ## Looping and branching statements
//   "Use braces for all loops and branches, even one-liners."
//   "For empty loop bodies, use either an empty pair of braces or continue."
//
// ## Pointer and Reference Expressions
//   "No spaces around period or arrow. Pointer operators have no trailing
//    space. When declaring a pointer or reference, place the asterisk/
//    ampersand adjacent to the type when possible."
//
// ## Boolean Expressions
//   "When a boolean expression spans multiple lines, be consistent with
//    the line-breaking style."
//
// ## Variable and Array Initialization
//   "You may choose between =, (), and {}; prefer {} for aggregates."
//
// ## Preprocessor Directives
//   "The hash mark that starts a preprocessor directive should always be
//    at the beginning of the line."
//
// ## Class Format
//   "public:, protected:, private: sections each indented one space."
//
// ## Constructor Initializer Lists
//   "Put each initializer on its own line if the list spans multiple lines."
//
// ## Namespace Formatting
//   "The contents of namespaces are not indented."
//   "Terminate namespaces with a comment: }  // namespace foo"
//
// ## Horizontal Whitespace
//   "Use of horizontal whitespace depends on location."
//   "Never trailing whitespace at the end of a line."
//   "Open braces should always have a space before them."
//
// ## Vertical Whitespace
//   "Minimize use of vertical whitespace. Limit to one blank line between
//    functions."
// =============================================================================

#include <iostream>
#include <string>
#include <vector>

namespace formatting_demo {

// The total number of demo sections in this file.
constexpr int kNumDemoSections = 5;

// ---------------------------------------------------------------------------
// Class Comments: describe purpose and usage.
// ---------------------------------------------------------------------------

// Tracks a running average of numeric values. Thread-compatible but not
// thread-safe.
//
// Example:
//   RunningAverage avg;
//   avg.Add(10.0);
//   avg.Add(20.0);
//   double mean = avg.Average();  // 15.0
class RunningAverage {
 public:  // one-space indent for access specifiers
  RunningAverage() = default;

  // Adds `value` to the running total.
  void Add(double value) {
    sum_ += value;
    ++count_;
  }

  // Returns the average of all added values, or 0.0 if empty.
  double Average() const {
    if (count_ == 0) {
      return 0.0;
    }
    return sum_ / static_cast<double>(count_);
  }

  int count() const { return count_; }

 private:
  double sum_ = 0.0;
  int count_ = 0;
};

// ---------------------------------------------------------------------------
// Function Comments: verb phrase, implied subject "This function".
// ---------------------------------------------------------------------------

// Clamps `value` to the range [lo, hi]. Returns lo if value < lo,
// hi if value > hi, otherwise value.
double Clamp(double value, double lo, double hi) {
  if (value < lo) {
    return lo;
  }
  if (value > hi) {
    return hi;
  }
  return value;
}

// Formats a table row as "| key | value |". The `key` is left-padded
// to `key_width` characters.
std::string FormatRow(const std::string& key, const std::string& value,
                      int key_width) {
  std::string padded_key = key;
  while (static_cast<int>(padded_key.size()) < key_width) {
    padded_key.insert(0, " ");
  }
  std::string row;
  row.append("| ");
  row.append(padded_key);
  row.append(" | ");
  row.append(value);
  row.append(" |");
  return row;
}

// TODO: bug 12345 - Replace with a proper formatting library.
std::string QuickFormat(int number) { return std::to_string(number); }

// ---------------------------------------------------------------------------
// Formatting rules demonstrated in code structure
// ---------------------------------------------------------------------------

// Looping and branching: always use braces
void DemoBraces() {
  std::vector<int> values = {1, 2, 3, 4, 5};

  // Good: braces even for single-statement body
  for (int v : values) {
    std::cout << "  " << v;
  }
  std::cout << std::endl;

  // Good: braces on if/else, even if one-liner
  if (values.empty()) {
    std::cout << "  empty" << std::endl;
  } else {
    std::cout << "  not empty" << std::endl;
  }

  // Empty loop body: use braces or continue
  // while (SomeCondition()) {}
  // while (SomeCondition()) { continue; }
}

// Pointer and reference formatting
void DemoPointerStyle() {
  int x = 42;
  int* ptr = &x;  // asterisk adjacent to type
  int& ref = x;   // ampersand adjacent to type
  const int* cptr = &x;

  std::cout << "  *ptr = " << *ptr << ", ref = " << ref << ", *cptr = " << *cptr
            << std::endl;
}

// Boolean expressions: consistent line-breaking
bool IsInRange(int value, int lo, int hi, bool inclusive) {
  // Multi-line boolean: operator at the start of the continuation line
  return (inclusive && value >= lo && value <= hi) ||
         (!inclusive && value > lo && value < hi);
}

// Variable and array initialization styles
void DemoInitialization() {
  // All three forms are acceptable; {} preferred for aggregates
  int a = 5;
  int b(5);
  int c{5};
  std::vector<int> v = {1, 2, 3};

  std::cout << "  a=" << a << " b=" << b << " c=" << c
            << " v.size()=" << v.size() << std::endl;
}

// Constructor initializer lists: each on its own line when spanning
class Widget {
 public:
  Widget(int id, std::string name, double weight)
      : id_(id), name_(std::move(name)), weight_(weight) {}

  Widget(const Widget&) = default;
  Widget& operator=(const Widget&) = default;
  Widget(Widget&&) = default;
  Widget& operator=(Widget&&) = default;
  ~Widget() = default;

  void Print() const {
    std::cout << "  Widget(id=" << id_ << ", name=" << name_
              << ", weight=" << weight_ << ")" << std::endl;
  }

 private:
  int id_;
  std::string name_;
  double weight_;
};

// Function argument comments for non-obvious parameters
double ComputeScore(double raw_score, double weight, bool apply_penalty) {
  double score = raw_score * weight;
  if (apply_penalty) {
    score *= 0.9;
  }
  return score;
}

// Preprocessor directives: # always at column 0
#ifdef STYLE_DEMO_EXTRA_FEATURES
#define STYLE_DEMO_USE_FAST_PATH 1
#endif

}  // namespace formatting_demo

int main() {
  using formatting_demo::Clamp;
  using formatting_demo::ComputeScore;
  using formatting_demo::DemoBraces;
  using formatting_demo::DemoInitialization;
  using formatting_demo::DemoPointerStyle;
  using formatting_demo::FormatRow;
  using formatting_demo::IsInRange;
  using formatting_demo::kNumDemoSections;
  using formatting_demo::RunningAverage;
  using formatting_demo::Widget;

  std::cout << "=== Comments & Formatting Demo ===" << std::endl;
  std::cout << "Sections: " << kNumDemoSections << std::endl;

  // Class usage
  std::cout << "\n--- RunningAverage ---" << std::endl;
  RunningAverage avg;
  avg.Add(10.0);
  avg.Add(20.0);
  avg.Add(30.0);
  std::cout << "  Average of " << avg.count() << " values: " << avg.Average()
            << std::endl;

  // Function with clear comments
  std::cout << "\n--- Clamp ---" << std::endl;
  std::cout << "  Clamp(15, 0, 10) = " << Clamp(15, 0, 10) << std::endl;
  std::cout << "  Clamp(-5, 0, 10) = " << Clamp(-5, 0, 10) << std::endl;

  // Table formatting
  std::cout << "\n--- FormatRow ---" << std::endl;
  std::cout << FormatRow("Name", "Alice", 10) << std::endl;
  std::cout << FormatRow("Score", "95", 10) << std::endl;

  // Braces
  std::cout << "\n--- Braces ---" << std::endl;
  DemoBraces();

  // Pointers
  std::cout << "\n--- Pointer Style ---" << std::endl;
  DemoPointerStyle();

  // Boolean
  std::cout << "\n--- Boolean Expressions ---" << std::endl;
  std::cout << "  IsInRange(5, 1, 10, true) = " << IsInRange(5, 1, 10, true)
            << std::endl;

  // Initialization
  std::cout << "\n--- Initialization ---" << std::endl;
  DemoInitialization();

  // Constructor initializer list
  std::cout << "\n--- Constructor Initializer ---" << std::endl;
  Widget w(1, "Gadget", 2.5);
  w.Print();

  // Function argument comments
  std::cout << "\n--- Argument Comments ---" << std::endl;
  double score = ComputeScore(
      /*raw_score=*/85.0,
      /*weight=*/1.2,
      /*apply_penalty=*/true);
  std::cout << "  Score: " << score << std::endl;

  return 0;
}
