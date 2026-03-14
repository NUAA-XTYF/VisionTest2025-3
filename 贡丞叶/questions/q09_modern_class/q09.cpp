// ============================================================
// 题目 09：现代类特性（C++11）
// 知识点：override、final、=default、=delete、委托构造函数
// ============================================================
#include "test_utils.hpp"
#include <string>

// ===== 填空 1 =====
// 知识点：override 说明符，显式声明覆盖虚函数
struct Animal {
    virtual std::string sound() const { return "..."; }
    virtual ~Animal() = default;
};

struct Dog : Animal {
    std::string sound() const override/* _____ */ {
        return "Woof";
    }
};
// ===== 填空 1 结束 =====

// ===== 填空 2 =====
// 知识点：final 说明符，禁止进一步派生/覆盖
struct Cat /* _____ */final : Animal {
    std::string sound() const override { return "Meow"; }
};
// ===== 填空 2 结束 =====

// ===== 填空 3 =====
// 知识点：= default，显式要求编译器生成默认实现
struct Trivial {
    int x;
    Trivial() = default; /* _____ */
    Trivial(const Trivial&) = default;
};
// ===== 填空 3 结束 =====

// ===== 填空 4 =====
// 知识点：= delete，禁用特定函数
struct NonCopyable {
    int value;
    explicit NonCopyable(int v) : value(v) {}
    NonCopyable(const NonCopyable&)  = delete;          /* _____ */
    NonCopyable& operator=(const NonCopyable&) = delete;/* _____ */
};
// ===== 填空 4 结束 =====

// ===== 填空 5 =====
// 知识点：委托构造函数（delegating constructor）
struct Config {
    std::string host;
    int         port;
    bool        verbose;

    // 主构造函数
    Config(std::string h, int p, bool v)
        : host(std::move(h)), port(p), verbose(v) {}

    // 委托给主构造函数，提供默认值
    Config(std::string h, int p)
        : Config(std::move(h), p, false) {}/* _____ */

    Config()
        : Config("localhost", 8080, false)/* _____ */ {}
};
// ===== 填空 5 结束 =====

int main() {
    Dog dog;
    Cat cat;
    Animal* a1 = &dog;
    Animal* a2 = &cat;
    CHECK_EQ(a1->sound(), std::string("Woof"));
    CHECK_EQ(a2->sound(), std::string("Meow"));

    Trivial t;
    t.x = 5;
    Trivial t2 = t;
    CHECK_EQ(t2.x, 5);

    NonCopyable nc(42);
    CHECK_EQ(nc.value, 42);
    // NonCopyable nc2 = nc;  // 无法编译：已 delete

    Config c1;
    CHECK_EQ(c1.host, std::string("localhost"));
    CHECK_EQ(c1.port, 8080);
    CHECK_FALSE(c1.verbose);

    Config c2("example.com", 443);
    CHECK_EQ(c2.host, std::string("example.com"));
    CHECK_EQ(c2.port, 443);

    Config c3("prod.server", 9000, true);
    CHECK_TRUE(c3.verbose);

    return test_utils::test_result();
}
