---
name: google-cpp-style
description: >-
  Enforce and reference the Google C++ Style Guide when writing, reviewing, or
  refactoring C++ code. Use when the user asks about C++ style, naming
  conventions, header guards, class design, smart pointers, formatting, or
  mentions Google style, cpplint, or cppguide.
---

# Google C++ Style Guide

Apply the Google C++ Style Guide when writing or reviewing C++ code in this
project. Compilable demos for every major section live under `demos/`.

## Quick Reference

### Header Files

- Every `.h` has a `#define` guard: `PROJECT_PATH_FILE_H_`
- Headers are self-contained (compile on their own)
- Include what you use; do not rely on transitive inclusions
- Avoid forward declarations; include the header instead
- Include order: related header, C system, C++ stdlib, other libs, project

### Scoping

- All code in a namespace (no `using namespace` directives)
- Terminate namespaces with `}  // namespace name`
- Use unnamed namespace or `static` for file-local symbols in `.cc`
- Declare variables in the narrowest scope, initialized at declaration
- Static/global variables must be trivially destructible
- Use `constexpr string_view` for global string constants
- Namespace-scope `thread_local` must be `constinit`

### Classes

- `explicit` on single-argument constructors and conversion operators
- Explicitly declare or delete copy/move to make the API clear
- `struct` for passive data only; `class` for everything else
- Struct members: `snake_case`. Class members: `snake_case_` (trailing `_`)
- Prefer composition over inheritance; all inheritance `public`
- Use `override` (not `virtual`) when overriding; use `final` sparingly
- Do not overload `&&`, `||`, `,`, unary `&`, or `operator""`
- Declaration order: types, constants, factory, ctors, dtor, methods, data

### Functions

- Return by value; use `const&` for inputs, reference for outputs
- Inputs before outputs in parameter order
- Use `std::optional` for optional by-value inputs
- Keep functions under ~40 lines
- Overloads must be semantically equivalent
- No default arguments on virtual functions
- Trailing return type only when it improves readability

### Ownership & Smart Pointers

- Prefer `std::unique_ptr` for ownership transfer
- Pass raw `&` / `*` for non-owning access
- `std::shared_ptr<const T>` only when sharing immutable data is justified
- Never use `std::auto_ptr`

### Modern C++ Features

- `noexcept` on move constructors
- No C++ exceptions (Google policy)
- Avoid RTTI; use virtual dispatch instead
- C++ casts only (`static_cast`, `const_cast`, `reinterpret_cast`); no C casts
- Prefer `++i` over `i++`
- `const` on all APIs where meaningful; `constexpr` for true constants
- `auto` only when it makes code clearer (e.g., `make_unique` return)
- CTAD only with opted-in templates (std types are fine)
- Designated initializers in field-declaration order
- Explicit lambda captures when the lambda may escape scope
- `requires(Concept<T>)` syntax, not `template<Concept T>`
- `[[fallthrough]]` for switch fall-through; always have `default:`

### Naming

| Entity | Style | Example |
| ------ | ----- | ------- |
| File | `snake_case.cc` / `.h` | `my_class.cc` |
| Type (class/struct/enum/alias) | `PascalCase` | `UrlTable` |
| Variable / parameter | `snake_case` | `table_name` |
| Class data member | `snake_case_` | `table_name_` |
| Struct data member | `snake_case` | `table_name` |
| Constant (`constexpr`/`const`) | `kPascalCase` | `kMaxRetries` |
| Function | `PascalCase` | `DeleteUrl()` |
| Accessor/mutator | `snake_case` | `count()`, `set_count()` |
| Namespace | `snake_case` | `my_project` |
| Enum value | `kPascalCase` | `kOutOfMemory` |
| Macro | `ALL_CAPS` + prefix | `MYPROJECT_ROUND` |

### Comments & Formatting

- 80-column line limit
- 2-space indent, no tabs
- `//` comments preferred; every class/function gets a comment
- TODO format: `// TODO: bug 12345 - description`
- Always use braces for `if`/`for`/`while` bodies
- `int* ptr` (asterisk with type) for pointer declarations
- Namespace contents not indented

## Demos

Build and run the demos to see every rule in action:

```bash
cd demos && mkdir build && cd build
cmake .. && cmake --build .
```

| Demo | Covers |
| ---- | ------ |
| `01_header_files/` | Guards, include order, forward decls, inline |
| `02_scoping` | Namespaces, linkage, local/static/global/thread_local vars |
| `03_classes` | Ctors, explicit, copy/move, structs, inheritance, operators |
| `04_functions` | I/O, overloading, defaults, trailing return |
| `05_ownership` | unique_ptr, shared_ptr, non-owning access |
| `06_modern_cpp` | Rvalue refs, casting, const/constexpr, auto, lambdas, concepts |
| `07_naming` | All naming conventions |
| `08_comments_formatting` | Comments, formatting, braces, whitespace |

## Formatting with clang-format

The project root has a `.clang-format` using `BasedOnStyle: Google`. Format
any C++ file with:

```bash
clang-format -i -style=file path/to/file.cc
```

Format all demo files at once:

```bash
cd demos
find . \( -name '*.cc' -o -name '*.h' \) -exec clang-format -i -style=file {} +
```

Key behaviours of the Google clang-format style:

- 2-space indentation, no tabs
- 80-column line limit
- Access specifiers (`public:`, `private:`) indented 1 space
- `PointerAlignment: Left` (`int* ptr`, not `int *ptr`)
- `BreakBeforeBraces: Attach`
- Includes sorted and grouped automatically

## Full Guide

For the complete text of the Google C++ Style Guide, see
<https://google.github.io/styleguide/cppguide.html>.
