// =============================================================================
// Google C++ Style Guide Demo: Naming
// Guide: https://google.github.io/styleguide/cppguide.html#Naming
// =============================================================================
//
// ## General Rule
//   "The most important consistency rules are those that govern naming."
//   "A 'word' is anything that you would write in English without internal
//    spaces. Either words are all lowercase, with underscores between words
//    (snake_case), or words are mixed case with the first letter of each
//    word capitalized (PascalCase)."
//
// ## File Names
//   "Filenames should be all lowercase and can include underscores (_) or
//    dashes (-). C++ files should have a .cc extension, and header files
//    should have a .h extension."
//   Examples: my_useful_class.cc, my-useful-class.cc
//
// ## Type Names (PascalCase)
//   "Type names start with a capital letter and have a capital letter for
//    each new word, with no underscores: MyExcitingClass, MyExcitingEnum."
//   Applies to: classes, structs, type aliases, enums, type template params.
//
// ## Concept Names
//   "Concept names follow the same rules as type names."
//
// ## Variable Names (snake_case)
//   "Variable names (including function parameters) are snake_case."
//   "Data members of classes additionally have trailing underscores."
//   "Struct data members do NOT have trailing underscores."
//
// ## Constant Names (kPascalCase)
//   "Variables declared constexpr or const, and whose value is fixed for
//    the duration of the program, are named with a leading 'k' followed
//    by mixed case."
//   "const int kDaysInAWeek = 7;"
//
// ## Function Names (PascalCase)
//   "Ordinarily, functions follow PascalCase."
//   "Accessors and mutators (get and set functions) may be named like
//    variables, in snake_case."
//
// ## Namespace Names (snake_case)
//   "Namespace names are snake_case."
//
// ## Enumerator Names (kPascalCase)
//   "Enumerators should be named like constants, not like macros."
//   "enum class UrlTableError { kOk = 0, kOutOfMemory, kMalformedInput };"
//
// ## Template Parameter Names
//   "Type template parameters should follow the rules for naming types,
//    and non-type template parameters should follow the rules for naming
//    variables or constants."
//
// ## Macro Names (ALL_CAPS)
//   "If you define a macro: MY_MACRO_THAT_SCARES_EVERYONE."
//   "Named with all capitals and underscores, and with a project-specific
//    prefix."
//
// ## Aliases
//   "The name follows the same principles as any other new name."
//
// ## Exceptions to Naming Rules
//   "If you are naming something analogous to an existing C or C++ entity,
//    you can follow the existing naming convention scheme."
//   Examples: bigopen() following open(), sparse_hash_map following STL.
// =============================================================================

#include <array>
#include <iostream>
#include <numbers>
#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// Macro Names: ALL_CAPS with project-specific prefix (avoid macros generally)
// ---------------------------------------------------------------------------
#define STYLE_DEMO_VERSION_MAJOR 1

// ---------------------------------------------------------------------------
// Namespace Names: snake_case
// ---------------------------------------------------------------------------
namespace naming_demo {

// ---------------------------------------------------------------------------
// Type Names: PascalCase for classes, structs, enums, type aliases
// ---------------------------------------------------------------------------
class UrlTable {
 public:
  // Function Names: PascalCase
  void AddEntry(const std::string& url, int priority) {
    entries_.push_back(Entry{.url = url, .priority = priority});
  }

  int EntryCount() const { return static_cast<int>(entries_.size()); }

  // Accessors/Mutators: may use snake_case
  const std::string& table_name() const { return table_name_; }
  void set_table_name(const std::string& name) { table_name_ = name; }

 private:
  // Class Data Members: snake_case WITH trailing underscore
  struct Entry {
    std::string url;  // struct members: NO trailing underscore
    int priority;
  };

  static constexpr int kMaxEntries = 1000;  // constant: kPascalCase
  std::string table_name_;                  // trailing underscore
  std::vector<Entry> entries_;              // trailing underscore
};

// ---------------------------------------------------------------------------
// Struct Data Members: snake_case WITHOUT trailing underscore
// ---------------------------------------------------------------------------
struct UrlTableProperties {
  std::string name;
  int num_entries;
};

// ---------------------------------------------------------------------------
// Enum Names: PascalCase type, kPascalCase enumerators
// ---------------------------------------------------------------------------
// NOLINTNEXTLINE(performance-enum-size) -- intentional default `int` base demo
enum class UrlTableError {
  kOk = 0,
  kOutOfMemory,
  kMalformedInput,
};

// (Bad style, shown as comment only):
// enum class AlternateUrlTableError {
//   OK = 0,               // Bad: MACRO_CASE for enumerators
//   OUT_OF_MEMORY = 1,
//   MALFORMED_INPUT = 2,
// };

// ---------------------------------------------------------------------------
// Constant Names: kPascalCase
// ---------------------------------------------------------------------------
constexpr int kDaysInAWeek = 7;
constexpr double kPi = std::numbers::pi;
// NOLINTNEXTLINE(readability-identifier-naming)
constexpr int kAndroid8_0_0 = 24;  // per guide: Android 8.0.0

// ---------------------------------------------------------------------------
// Type Aliases: PascalCase (using, not typedef)
// ---------------------------------------------------------------------------
using EntryList = std::vector<std::string>;

// ---------------------------------------------------------------------------
// Template Parameter Names: types follow type rules, values follow variable
// ---------------------------------------------------------------------------
// NOLINTNEXTLINE(readability-identifier-naming)
template <typename ElementType, int kMaxSize>
class FixedStack {
 public:
  void Push(const ElementType& value) {
    if (count_ < kMaxSize) {
      data_.at(count_++) = value;
    }
  }

  ElementType Pop() {
    if (count_ == 0) {
      return ElementType{};
    }
    return data_.at(--count_);
  }

  int count() const { return count_; }

 private:
  std::array<ElementType, kMaxSize> data_{};
  int count_ = 0;
};

// ---------------------------------------------------------------------------
// Function Names: PascalCase, short helper functions
// ---------------------------------------------------------------------------
std::string ErrorToString(UrlTableError error) {
  switch (error) {
    case UrlTableError::kOk:
      return "OK";
    case UrlTableError::kOutOfMemory:
      return "OutOfMemory";
    case UrlTableError::kMalformedInput:
      return "MalformedInput";
  }
  return "Unknown";
}

// Variable Names: snake_case
void DemoVariableNaming() {
  // Local variables: snake_case
  int table_count = 3;
  std::string current_url = "https://example.com";
  bool is_valid = true;

  std::cout << "  table_count = " << table_count << std::endl;
  std::cout << "  current_url = " << current_url << std::endl;
  std::cout << "  is_valid = " << is_valid << std::endl;
}

// Choosing Names: descriptive, avoid abbreviations
// Good: int num_errors;
// Bad:  int n;  (too short for wide scope)
// Bad:  int nerr;  (ambiguous abbreviation)
// Bad:  int n_comp_conns;  (deletes letters)

}  // namespace naming_demo

#undef STYLE_DEMO_VERSION_MAJOR

int main() {
  using naming_demo::DemoVariableNaming;
  using naming_demo::EntryList;
  using naming_demo::ErrorToString;
  using naming_demo::FixedStack;
  using naming_demo::kAndroid8_0_0;
  using naming_demo::kDaysInAWeek;
  using naming_demo::kPi;
  using naming_demo::UrlTable;
  using naming_demo::UrlTableError;
  using naming_demo::UrlTableProperties;

  std::cout << "=== Naming Demo ===" << std::endl;

  // Type Names: PascalCase
  UrlTable table;
  table.set_table_name("MainTable");
  table.AddEntry("https://google.com", 1);
  table.AddEntry("https://github.com", 2);
  std::cout << "UrlTable '" << table.table_name() << "' has "
            << table.EntryCount() << " entries" << std::endl;

  // Struct: no trailing underscore on members
  UrlTableProperties props{.name = "MyTable", .num_entries = 42};
  std::cout << "UrlTableProperties: name=" << props.name
            << " num_entries=" << props.num_entries << std::endl;

  // Enum: kPascalCase
  UrlTableError err = UrlTableError::kMalformedInput;
  std::cout << "Error: " << ErrorToString(err) << std::endl;

  // Constants: kPascalCase
  std::cout << "kDaysInAWeek = " << kDaysInAWeek << std::endl;
  std::cout << "kPi = " << kPi << std::endl;
  std::cout << "kAndroid8_0_0 = " << kAndroid8_0_0 << std::endl;

  // Template parameter naming
  FixedStack<int, 8> stack;
  stack.Push(10);
  stack.Push(20);
  std::cout << "FixedStack count: " << stack.count() << std::endl;

  // Variable naming
  std::cout << "\n--- Variable Naming ---" << std::endl;
  DemoVariableNaming();

  // Type alias
  EntryList entries = {"one", "two", "three"};
  std::cout << "EntryList size: " << entries.size() << std::endl;

  return 0;
}
