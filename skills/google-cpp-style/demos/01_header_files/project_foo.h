// =============================================================================
// Google C++ Style Guide Demo: Header Files
// Guide: https://google.github.io/styleguide/cppguide.html#Header_Files
// =============================================================================
//
// ## Self-contained Headers
//   "Header files should be self-contained (compile on their own) and end in
//    .h. All header files should have header guards and include all other
//    headers it needs."
//
// ## The #define Guard
//   "All header files should have #define guards to prevent multiple inclusion.
//    The format of the symbol name should be <PROJECT>_<PATH>_<FILE>_H_."
//
// ## Include What You Use
//   "If a source or header file refers to a symbol defined elsewhere, the file
//    should directly include a header file which properly intends to provide a
//    declaration or definition of that symbol. Do not rely on transitive
//    inclusions."
//
// ## Defining Functions in Header Files
//   "Include the definition of a function at its point of declaration in a
//    header file only when the definition is short."
// =============================================================================

#ifndef GOOGLE_CPP_STYLE_DEMOS_01_HEADER_FILES_PROJECT_FOO_H_
#define GOOGLE_CPP_STYLE_DEMOS_01_HEADER_FILES_PROJECT_FOO_H_

#include <string>
#include <vector>

namespace project_foo {

// A data record used to demonstrate header-file rules.
struct Record {
  std::string name;
  int id;
};

// Short function defined inline in the header (acceptable per the guide).
inline int RecordId(const Record& record) { return record.id; }

// Declared here, defined in the .cc file (non-trivial body).
std::string SummarizeRecords(const std::vector<Record>& records);

}  // namespace project_foo

#endif  // GOOGLE_CPP_STYLE_DEMOS_01_HEADER_FILES_PROJECT_FOO_H_
