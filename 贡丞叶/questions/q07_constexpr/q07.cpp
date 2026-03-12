// ============================================================
// 题目 07：constexpr 与编译期计算（C++11/14/17/20）
// 知识点：constexpr 函数、constexpr 变量、if constexpr、static_assert、consteval
// ============================================================
#include "test_utils.hpp"
#include <type_traits>
#include <string>

// ===== 填空 1 =====
// 知识点：constexpr 函数（C++11）—— 编译期可求值
// 请在函数前加 constexpr，使 factorial 可在编译期计算
/* _____ */ long long factorial(long long n) { // 破坏：移除了 constexpr
    return n <= 1 ? 1LL : n * factorial(n - 1);
}
// ===== 填空 1 结束 =====

// ===== 填空 2 =====
// 知识点：constexpr 变量（C++11）
// 请用 constexpr 声明编译期常量
constexpr int MAX_SIZE=256;
/* _____ */
// ===== 填空 2 结束 =====

// ===== 填空 3 =====
// 知识点：if constexpr（C++17）—— 编译期分支
// 请补全：若 T 是整数类型返回 "integral"，否则返回 "other"
template <typename T>
std::string type_category() {
    /* _____ */if constexpr (std::is_same_v<T, int>) {
        return "integral";
    }
    else if constexpr (std::is_same_v<T, char>) {
        return "integral";
    } else {
        return "other";
    }
}
// ===== 填空 3 结束 =====

// ===== 填空 4 =====
// 知识点：static_assert —— 编译期断言
// 请用 static_assert 断言 MAX_SIZE 大于 0（编译期验证）
static_assert (MAX_SIZE > 0);
/* _____ */
// ===== 填空 4 结束 =====

// ===== 填空 5 =====
// 知识点：consteval（C++20）—— 只能在编译期求值
// 请在函数前加 consteval，使 square 只能在编译期调用
/* _____ */
consteval int square(int n) {
    return n * n;
}
// ===== 填空 5 结束 =====

int main() {
    // 编译期计算
    constexpr long long f5 = factorial(5);
    CHECK_EQ(f5, 120LL);
    CHECK_EQ(factorial(0), 1LL);
    CHECK_EQ(factorial(10), 3628800LL);

    CHECK_EQ(MAX_SIZE, 256);

    CHECK_EQ(type_category<int>(), std::string("integral"));
    CHECK_EQ(type_category<char>(), std::string("integral"));
    CHECK_EQ(type_category<double>(), std::string("other"));

    constexpr int s = square(7);
    CHECK_EQ(s, 49);

    return test_utils::test_result();
}
