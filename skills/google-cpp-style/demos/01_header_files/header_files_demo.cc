// =============================================================================
// Google C++ Style Guide Demo: Names and Order of Includes
// Guide:
// https://google.github.io/styleguide/cppguide.html#Names_and_Order_of_Includes
// =============================================================================
//
// ## Names and Order of Includes
//   "Include headers in the following order: Related header, C system headers,
//    C++ standard library headers, other libraries' headers, your project's
//    headers."
//
//   "Within each section the includes should be ordered alphabetically."
//
//   "With the preferred ordering, if the related header (e.g., foo.h) omits
//    any necessary includes, the build of foo.cc or foo_test.cc will break.
//    This rule ensures that build breaks show up first for the people working
//    on these files, not for innocent people in other packages."
//
//   "You should include all the headers that define the symbols you rely upon,
//    except in the unusual case of forward declarations. If you rely on
//    symbols from bar.h, don't count on the fact that you included foo.h
//    which (currently) includes bar.h: include bar.h yourself, unless foo.h
//    explicitly demonstrates its intent to provide you the symbols of bar.h."
// =============================================================================

// 1. Related header (this file's own header, if any -- not applicable here)
// 2. C system headers (none needed)
// 3. C++ standard library headers
#include <iostream>
#include <string>
#include <vector>

// 4. Other libraries' headers (none)
// 5. Your project's headers (alphabetical)
#include "project_bar.h"
#include "project_foo.h"

namespace project_foo {

std::string SummarizeRecords(const std::vector<Record>& records) {
  std::string result;
  for (const auto& r : records) {
    result += r.name + "(" + std::to_string(r.id) + ") ";
  }
  return result;
}

}  // namespace project_foo

namespace project_bar {

std::string DescribeRecord(const project_foo::Record& record) {
  return "Record: " + record.name + " #" + std::to_string(record.id);
}

}  // namespace project_bar

int main() {
  std::vector<project_foo::Record> records = {{.name = "Alice", .id = 1},
                                              {.name = "Bob", .id = 2}};

  std::cout << "=== Header Files Demo ===" << std::endl;
  std::cout << "Summary: " << project_foo::SummarizeRecords(records)
            << std::endl;
  std::cout << "Inline RecordId: " << project_foo::RecordId(records[0])
            << std::endl;
  std::cout << project_bar::DescribeRecord(records[1]) << std::endl;

  return 0;
}
