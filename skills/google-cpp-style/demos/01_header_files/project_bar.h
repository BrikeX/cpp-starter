// =============================================================================
// Google C++ Style Guide Demo: Forward Declarations & Include What You Use
// Guide: https://google.github.io/styleguide/cppguide.html#Forward_Declarations
// =============================================================================
//
// ## Forward Declarations
//   "Avoid using forward declarations where possible. Instead, include the
//    headers you need."
//
//   Pros of forward declarations:
//     - Can save compile time and unnecessary recompilation.
//   Cons of forward declarations:
//     - Can hide a dependency, allowing user code to skip recompilation.
//     - May be broken by subsequent library changes.
//     - Forward declaring symbols from namespace std:: yields undefined
//     behavior.
//
//   Decision: "Try to avoid forward declarations of entities defined in
//   another project."
// =============================================================================

#ifndef GOOGLE_CPP_STYLE_DEMOS_01_HEADER_FILES_PROJECT_BAR_H_
#define GOOGLE_CPP_STYLE_DEMOS_01_HEADER_FILES_PROJECT_BAR_H_

// Good: include what you use -- we need Record, so we include its header
// directly rather than forward-declaring it.
#include <string>

#include "project_foo.h"

namespace project_bar {

// Uses project_foo::Record by value, so a full definition is required.
std::string DescribeRecord(const project_foo::Record& record);

}  // namespace project_bar

#endif  // GOOGLE_CPP_STYLE_DEMOS_01_HEADER_FILES_PROJECT_BAR_H_
