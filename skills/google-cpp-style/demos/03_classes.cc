// =============================================================================
// Google C++ Style Guide Demo: Classes
// Guide: https://google.github.io/styleguide/cppguide.html#Classes
// =============================================================================
//
// ## Doing Work in Constructors
//   "Avoid virtual method calls in constructors, and avoid initialization
//    that can fail if you can't signal an error."
//   "Constructors should never call virtual functions."
//
// ## Implicit Conversions
//   "Do not define implicit conversions. Use the explicit keyword for
//    conversion operators and single-argument constructors."
//   "Copy and move constructors should not be explicit, since they do not
//    perform type conversion."
//   "Constructors that cannot be called with a single argument may omit
//    explicit."
//
// ## Copyable and Movable Types
//   "A class's public API must make clear whether the class is copyable,
//    move-only, or neither copyable nor movable."
//
// ## Structs vs. Classes
//   "Use a struct only for passive objects that carry data; everything
//    else is a class."
//   "Note that member variables in structs and classes have different
//    naming rules."
//
// ## Structs vs. Pairs and Tuples
//   "Prefer to use a struct instead of a pair or a tuple whenever the
//    elements can have meaningful names."
//
// ## Inheritance
//   "Composition is often more appropriate than inheritance. When using
//    inheritance, make it public."
//   "All inheritance should be public."
//   "Explicitly annotate overrides of virtual functions or virtual
//    destructors with exactly one of an override or (less frequently)
//    final specifier. Do not use virtual when declaring an override."
//
// ## Operator Overloading
//   "Define overloaded operators only if their meaning is obvious,
//    unsurprising, and consistent with the corresponding built-in operators."
//   "For a type T whose values can be compared for equality, define a
//    non-member operator==."
//   "Do not overload &&, ||, , (comma), or unary &. Do not overload
//    operator\"\", i.e., do not introduce user-defined literals."
//
// ## Access Control
//   "Make classes' data members private, unless they are constants."
//
// ## Declaration Order
//   "Group similar declarations together, placing public parts earlier."
//   "A class definition should usually start with a public: section,
//    followed by protected:, then private:."
//   Order within each section:
//     1. Types and type aliases
//     2. Static constants
//     3. Factory functions
//     4. Constructors and assignment operators
//     5. Destructor
//     6. All other functions
//     7. All other data members
// =============================================================================

#include <iostream>
#include <memory>
#include <numbers>
#include <string>
#include <utility>

// ---------------------------------------------------------------------------
// Structs vs. Classes: struct for passive data, no invariants
// ---------------------------------------------------------------------------
// "Use a struct only for passive objects that carry data."
// Struct members: snake_case WITHOUT trailing underscore.
struct Point {
  float x = 0.0F;
  float y = 0.0F;
};

// "Prefer to use a struct instead of a pair or a tuple whenever the
//  elements can have meaningful names."
struct LatLng {
  double latitude;
  double longitude;
};

namespace style_demo {

// ---------------------------------------------------------------------------
// Implicit Conversions: use explicit for single-argument constructors
// ---------------------------------------------------------------------------
class Distance {
 public:
  // Good: explicit prevents implicit conversion from double
  explicit Distance(double meters) : meters_(meters) {}

  // Good: explicit conversion operator
  explicit operator double() const { return meters_; }

  double meters() const { return meters_; }

  // Operator overloading: obvious and consistent with built-in semantics
  friend bool operator==(const Distance& lhs, const Distance& rhs) = default;
  friend auto operator<=>(const Distance& lhs, const Distance& rhs) = default;

  friend Distance operator+(const Distance& lhs, const Distance& rhs) {
    return Distance(lhs.meters_ + rhs.meters_);
  }

  friend std::ostream& operator<<(std::ostream& os, const Distance& dist) {
    return os << dist.meters_ << "m";
  }

 private:
  double meters_;
};

// ---------------------------------------------------------------------------
// Copyable type: explicitly declare copy operations
// ---------------------------------------------------------------------------
class CopyableBuffer {
 public:
  explicit CopyableBuffer(int size) : size_(size) {}

  CopyableBuffer(const CopyableBuffer& other) = default;
  CopyableBuffer& operator=(const CopyableBuffer& other) = default;
  CopyableBuffer(CopyableBuffer&& other) = default;
  CopyableBuffer& operator=(CopyableBuffer&& other) = default;
  ~CopyableBuffer() = default;

  int size() const { return size_; }

 private:
  int size_;
};

// ---------------------------------------------------------------------------
// Move-only type: declare move operations, delete copy
// ---------------------------------------------------------------------------
class UniqueResource {
 public:
  explicit UniqueResource(std::string name) : name_(std::move(name)) {}

  UniqueResource(UniqueResource&& other) = default;
  UniqueResource& operator=(UniqueResource&& other) = default;

  UniqueResource(const UniqueResource&) = delete;
  UniqueResource& operator=(const UniqueResource&) = delete;

  ~UniqueResource() = default;

  const std::string& name() const { return name_; }

 private:
  std::string name_;
};

// ---------------------------------------------------------------------------
// Non-copyable, non-movable type
// ---------------------------------------------------------------------------
class Singleton {
 public:
  static Singleton& Instance() {
    static Singleton instance("global");
    return instance;
  }

  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(Singleton&&) = delete;

  const std::string& name() const { return name_; }

 private:
  explicit Singleton(std::string name) : name_(std::move(name)) {}
  ~Singleton() = default;
  std::string name_;
};

// ---------------------------------------------------------------------------
// Inheritance: public inheritance, override annotation, no virtual keyword
// ---------------------------------------------------------------------------
class Shape {
 public:
  Shape(const Shape&) = delete;
  Shape& operator=(const Shape&) = delete;
  Shape(Shape&&) = delete;
  Shape& operator=(Shape&&) = delete;
  virtual ~Shape() = default;
  virtual double Area() const = 0;
  virtual std::string Describe() const = 0;

 protected:
  Shape() = default;
};

class Circle : public Shape {
 public:
  explicit Circle(double radius) : radius_(radius) {}

  // Good: use override, not virtual
  double Area() const override { return std::numbers::pi * radius_ * radius_; }
  std::string Describe() const override {
    return "Circle(r=" + std::to_string(radius_) + ")";
  }

 private:
  double radius_;
};

class Square final : public Shape {
 public:
  explicit Square(double side) : side_(side) {}

  // Good: final class, still use override
  double Area() const override { return side_ * side_; }
  std::string Describe() const override {
    return "Square(s=" + std::to_string(side_) + ")";
  }

 private:
  double side_;
};

// ---------------------------------------------------------------------------
// Declaration Order demo: follows the prescribed ordering
// ---------------------------------------------------------------------------
class Widget {
 public:
  // 1. Types and type aliases
  using Id = int;

  // 2. Static constants
  static constexpr Id kInvalidId = -1;

  // 3. Factory functions
  static std::unique_ptr<Widget> Create(Id id, std::string label) {
    return std::unique_ptr<Widget>(new Widget(id, std::move(label)));
  }

  // 4. Constructors and assignment operators
  Widget(const Widget&) = delete;
  Widget& operator=(const Widget&) = delete;
  Widget(Widget&&) = delete;
  Widget& operator=(Widget&&) = delete;

  // 5. Destructor
  ~Widget() = default;

  // 6. All other functions
  Id id() const { return id_; }
  const std::string& label() const { return label_; }

 private:
  // Class data members: snake_case WITH trailing underscore
  Widget(Id id, std::string label) : id_(id), label_(std::move(label)) {}
  Id id_;
  std::string label_;
};

}  // namespace style_demo

int main() {
  using style_demo::Circle;
  using style_demo::CopyableBuffer;
  using style_demo::Distance;
  using style_demo::Shape;
  using style_demo::Singleton;
  using style_demo::Square;
  using style_demo::UniqueResource;
  using style_demo::Widget;

  std::cout << "=== Classes Demo ===" << std::endl;

  // Struct (passive data, no trailing underscore on members)
  Point p{.x = 3.0F, .y = 4.0F};
  std::cout << "Point: (" << p.x << ", " << p.y << ")" << std::endl;

  LatLng loc{.latitude = 37.7749, .longitude = -122.4194};
  std::cout << "LatLng: " << loc.latitude << ", " << loc.longitude << std::endl;

  // Implicit conversion: explicit keyword prevents Distance d = 5.0;
  Distance d1(10.0);
  Distance d2(20.0);
  std::cout << "Distance: " << d1 << " + " << d2 << " = " << (d1 + d2)
            << std::endl;
  std::cout << "d1 < d2: " << (d1 < d2 ? "true" : "false") << std::endl;

  // Copyable
  CopyableBuffer buf1(1024);
  CopyableBuffer buf2 = buf1;
  std::cout << "CopyableBuffer: " << buf1.size() << ", " << buf2.size()
            << std::endl;

  // Move-only
  UniqueResource res("database_conn");
  UniqueResource moved_res = std::move(res);
  std::cout << "UniqueResource: " << moved_res.name() << std::endl;

  // Singleton
  std::cout << "Singleton: " << Singleton::Instance().name() << std::endl;

  // Inheritance with override
  Circle circle(5.0);
  Square square(4.0);
  for (const Shape* shape : {static_cast<const Shape*>(&circle),
                             static_cast<const Shape*>(&square)}) {
    std::cout << shape->Describe() << " area=" << shape->Area() << std::endl;
  }

  // Declaration order / factory
  auto widget = Widget::Create(42, "Gizmo");
  std::cout << "Widget: id=" << widget->id() << " label=" << widget->label()
            << std::endl;

  return 0;
}
