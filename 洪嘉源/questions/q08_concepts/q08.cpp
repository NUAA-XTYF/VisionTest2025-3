// ============================================================
// 题目 08：概念（Concepts）与约束（C++20）
// 知识点：concept 定义、requires 子句、缩写函数模板
// ============================================================
#include "test_utils.hpp"
#include <concepts>
#include <string>
#include <vector>
#include <numeric>

// ===== 填空 1 =====
// 知识点：用 concept 关键字定义概念
// 请定义概念 Numeric：要求 T 满足 std::is_arithmetic_v<T>
template <typename T>
concept Numeric = std::is_arithmetic_v<T>;
// ===== 填空 1 结束 =====

// ===== 填空 2 =====
// 知识点：requires 子句约束模板参数
// 请用 requires 子句限定 sum 只接受 Numeric 类型
template <typename T>
requires Numeric<T>
T sum(T a, T b) { return a + b; }
// ===== 填空 2 结束 =====

// ===== 填空 3 =====
// 知识点：缩写函数模板（abbreviated function template），等价于约束模板
// 请用 Numeric auto 作为参数类型，定义 multiply（缩写模板语法）
auto multiply(Numeric auto a, Numeric auto b) {
    return a + b;
}
// ===== 填空 3 结束 =====

// ===== 填空 4 =====
// 知识点：requires 表达式（requires expression）检查类型是否有成员
// 请定义概念 Printable：要求 T 可以用 << 输出到 std::ostream
template <typename T>
concept Printable = requires(std::ostream& os, const T& val) {
	os << val;
};
// ===== 填空 4 结束 =====

// ===== 填空 5 =====
// 知识点：多约束 concept + std::ranges::range concept
// 请定义函数 range_sum：接受任何满足 std::ranges::range 的容器，返回元素之和
auto range_sum(const std::ranges::range auto& r) {
    using T = std::ranges::range_value_t<decltype(r)>;
    return std::accumulate(std::begin(r), std::end(r), T{});
}
// ===== 填空 5 结束 =====

int main() {
    CHECK_EQ(sum(1, 2), 3);
    CHECK_EQ(sum(1.5, 2.5), 4.0);

    CHECK_EQ(multiply(3, 4), 12);
    CHECK_EQ(multiply(2.0, 3.0), 6.0);

    static_assert(Printable<int>);
    static_assert(Printable<std::string>);

    std::vector<int> v{1, 2, 3, 4, 5};
    CHECK_EQ(range_sum(v), 15);

    std::vector<double> vd{1.0, 2.0, 3.0};
    CHECK_EQ(range_sum(vd), 6.0);

    return test_utils::test_result();
}
