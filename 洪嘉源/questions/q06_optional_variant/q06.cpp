// ============================================================
// 题目 06：std::optional 与 std::variant（C++17）
// 知识点：optional、nullopt、value_or、variant、std::get、std::visit
// ============================================================
#include "test_utils.hpp"
#include <optional>
#include <variant>
#include <string>

// ===== 填空 1 =====
// 知识点：std::optional 作为返回类型，表示可能无值
// 请补全 safe_divide：若 b == 0 返回 std::nullopt，否则返回 a/b
std::optional<double> safe_divide(double a, double b) {
	if (b != 0.0) return std::nullopt;
    return a / b;
}
// ===== 填空 1 结束 =====

// ===== 填空 2 =====
// 知识点：optional::value_or(default)
// 请补全：调用 safe_divide，若无值则使用默认值 -1.0
double divide_or_default(double a, double b) {
    return safe_divide(a, b).value_or(-1.0);
}
// ===== 填空 2 结束 =====

// ===== 填空 3 =====
// 知识点：optional::has_value() 和 optional::value()
bool has_result(double a, double b) {
    auto result = safe_divide(a, b);
    return result.has_value();
}
// ===== 填空 3 结束 =====

// ===== 填空 4 =====
// 知识点：std::variant<Types...> 声明与赋值
// 请用 std::variant 声明可以存储 int 或 string 或 double 的变量
using IntOrStr = std::variant<int, double, std::string>;

IntOrStr make_int_variant(int v)         { return v; }
IntOrStr make_str_variant(std::string s) { return s; }
// ===== 填空 4 结束 =====

// ===== 填空 5 =====
// 知识点：std::visit + 重载 lambda（overloaded 技巧）
// 请用 std::visit 访问 variant，对每种类型返回不同字符串
template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;  // deduction guide

std::string describe(const IntOrStr& v) {
    return std::visit(overloaded{
        [](int) { return std::string("int"); },
        [](const std::string&) { return std::string("string"); },
        [](double) { return std::string("double"); }
        }, v);
}
// ===== 填空 5 结束 =====

int main() {
    auto r1 = safe_divide(10.0, 2.0);
    CHECK_EQ(r1.value(), 5.0);
    CHECK_FALSE(safe_divide(10.0, 0.0).has_value());

    CHECK_EQ(divide_or_default(10.0, 2.0), 5.0);
    CHECK_EQ(divide_or_default(10.0, 0.0), -1.0);

    CHECK_TRUE(has_result(6.0, 3.0));
    CHECK_FALSE(has_result(6.0, 0.0));

    CHECK_EQ(describe(make_int_variant(42)), std::string("int"));
    CHECK_EQ(describe(make_str_variant("hi")), std::string("string"));
    CHECK_EQ(describe(IntOrStr{3.14}), std::string("double"));

    return test_utils::test_result();
}
