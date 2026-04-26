// =============================================================================
// Google C++ Style Guide Demo: Ownership and Smart Pointers
// Guide:
// https://google.github.io/styleguide/cppguide.html#Ownership_and_Smart_Pointers
// =============================================================================
//
// ## Ownership and Smart Pointers
//   "Prefer to have single, fixed owners for dynamically allocated objects.
//    Prefer to transfer ownership with smart pointers."
//
//   "If dynamic allocation is necessary, prefer to keep ownership with the
//    code that allocated it. If other code needs access to the object,
//    consider passing it a copy, or passing a pointer or reference without
//    transferring ownership."
//
//   "Prefer to use std::unique_ptr to make ownership transfer explicit."
//     std::unique_ptr<Foo> FooFactory();
//     void FooConsumer(std::unique_ptr<Foo> ptr);
//
//   "Do not design your code to use shared ownership without a very good
//    reason. One such reason is to avoid expensive copy operations, but you
//    should only do this if the performance benefits are significant, and
//    the underlying object is immutable (i.e., std::shared_ptr<const Foo>)."
//
//   "Never use std::auto_ptr. Instead, use std::unique_ptr."
//
//   Non-owning access: pass raw pointer or reference. The guide says:
//   "If other code needs access to the object, consider passing it a copy,
//    or passing a pointer or reference without transferring ownership."
// =============================================================================

#include <iostream>
#include <memory>
#include <string>

namespace style_demo {

// A resource managed via smart pointers
class Connection {
 public:
  explicit Connection(std::string endpoint) : endpoint_(std::move(endpoint)) {
    std::cout << "  Connection opened: " << endpoint_ << std::endl;
  }

  Connection(const Connection&) = delete;
  Connection& operator=(const Connection&) = delete;
  Connection(Connection&&) = delete;
  Connection& operator=(Connection&&) = delete;

  ~Connection() {
    std::cout << "  Connection closed: " << endpoint_ << std::endl;
  }

  void Send(const std::string& data) const {
    std::cout << "  Sending to " << endpoint_ << ": " << data << std::endl;
  }

  const std::string& endpoint() const { return endpoint_; }

 private:
  std::string endpoint_;
};

// ---------------------------------------------------------------------------
// Factory returning unique_ptr: clear ownership transfer
// ---------------------------------------------------------------------------
std::unique_ptr<Connection> CreateConnection(const std::string& endpoint) {
  return std::make_unique<Connection>(endpoint);
}

// ---------------------------------------------------------------------------
// Consumer taking unique_ptr: takes ownership
// ---------------------------------------------------------------------------
void CloseConnection(std::unique_ptr<Connection> conn) {
  std::cout << "  CloseConnection taking ownership of: " << conn->endpoint()
            << std::endl;
  // conn is destroyed at end of scope
}

// ---------------------------------------------------------------------------
// Non-owning access: raw reference (preferred when non-null is guaranteed)
// ---------------------------------------------------------------------------
void UseConnection(const Connection& conn) { conn.Send("ping"); }

// ---------------------------------------------------------------------------
// Non-owning access: raw pointer (when nullptr is a valid input)
// ---------------------------------------------------------------------------
void MaybeUseConnection(const Connection* conn) {
  if (conn != nullptr) {
    conn->Send("optional-ping");
  } else {
    std::cout << "  No connection available" << std::endl;
  }
}

// ---------------------------------------------------------------------------
// Shared ownership: only when immutable and there's a good reason
// ---------------------------------------------------------------------------
class Config {
 public:
  explicit Config(std::string data) : data_(std::move(data)) {}
  const std::string& data() const { return data_; }

 private:
  std::string data_;
};

void PrintConfig(std::shared_ptr<const Config>
                     config) {  // NOLINT(performance-unnecessary-value-param)
  std::cout << "  Config (use_count=" << config.use_count()
            << "): " << config->data() << std::endl;
}

}  // namespace style_demo

int main() {
  using style_demo::CloseConnection;
  using style_demo::Config;
  using style_demo::CreateConnection;
  using style_demo::MaybeUseConnection;
  using style_demo::PrintConfig;
  using style_demo::UseConnection;

  std::cout << "=== Ownership Demo ===" << std::endl;

  // unique_ptr: factory creates, caller owns
  std::cout << "\n--- unique_ptr factory ---" << std::endl;
  auto conn = CreateConnection("localhost:8080");

  // Non-owning access via reference
  std::cout << "\n--- Non-owning reference ---" << std::endl;
  UseConnection(*conn);

  // Non-owning access via pointer (nullable)
  std::cout << "\n--- Non-owning pointer ---" << std::endl;
  MaybeUseConnection(conn.get());
  MaybeUseConnection(nullptr);

  // Transfer ownership
  std::cout << "\n--- Ownership transfer ---" << std::endl;
  CloseConnection(std::move(conn));
  // conn is now nullptr

  // Shared ownership: immutable config shared among components
  std::cout << "\n--- shared_ptr<const T> ---" << std::endl;
  auto config = std::make_shared<const Config>("production");
  PrintConfig(config);
  // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
  auto config_copy = config;  // demo shared ownership
  PrintConfig(config_copy);

  std::cout << "\n--- Cleanup ---" << std::endl;
  return 0;
}
