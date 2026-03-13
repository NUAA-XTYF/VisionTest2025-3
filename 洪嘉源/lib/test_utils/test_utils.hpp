#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

// ============================================================
// 工具库 test_utils — 本文件也有填空练习
// ============================================================

namespace test_utils {

// ===== 填空 1 =====
// 知识点：C++17 inline 变量
// 请用 inline 关键字定义两个全局计数器（已填好，参考即可）
inline int g_tests_run = 0;
inline int g_tests_failed = 0;
// ===== 填空 1 结束 =====

// ===== 填空 2 =====
// 知识点：C++20 requires 约束 + if constexpr
// 请补全：若类型 T 可以输出到 ostream，则返回其字符串表示；否则返回 "<not-printable>"
template <typename T>
std::string to_string_repr(const T& val) {
    if constexpr (requires (std::ostringstream & os, const T & v) { os << v; }) {
        std::ostringstream oss;
        oss << val;
        return oss.str();
    } else {
        return "<not-printable>";
    }
}
// ===== 填空 2 结束 =====

inline int test_result() {
    if (g_tests_failed == 0) {
        std::cout << "All " << g_tests_run << " tests passed!\n";
        return 0;
    } else {
        std::cerr << g_tests_failed << "/" << g_tests_run << " tests FAILED!\n";
        return 1;
    }
}

} // namespace test_utils

// ---------- 测试宏 ----------

#define CHECK(expr)                                                          \
    do {                                                                     \
        ++test_utils::g_tests_run;                                           \
        if (!(expr)) {                                                       \
            ++test_utils::g_tests_failed;                                    \
            std::cerr << "[FAILED] " #expr                                   \
                      << "  (" << __FILE__ << ":" << __LINE__ << ")\n";      \
        }                                                                    \
    } while (0)

#define CHECK_EQ(a, b)                                                       \
    do {                                                                     \
        ++test_utils::g_tests_run;                                           \
        auto&& _a = (a);                                                     \
        auto&& _b = (b);                                                     \
        if (!(_a == _b)) {                                                   \
            ++test_utils::g_tests_failed;                                    \
            std::cerr << "[FAILED] " #a " == " #b                           \
                      << "\n  left:  " << test_utils::to_string_repr(_a)     \
                      << "\n  right: " << test_utils::to_string_repr(_b)     \
                      << "  (" << __FILE__ << ":" << __LINE__ << ")\n";      \
        }                                                                    \
    } while (0)

#define CHECK_NE(a, b) CHECK(!((a) == (b)))
#define CHECK_TRUE(expr)  CHECK(expr)
#define CHECK_FALSE(expr) CHECK(!(expr))
#define CHECK_GT(a, b) CHECK((a) > (b))
#define CHECK_LT(a, b) CHECK((a) < (b))
