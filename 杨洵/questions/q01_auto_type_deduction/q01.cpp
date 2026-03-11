// ============================================================
// 题目 01：auto 与类型推导
// 知识点：auto、decltype、尾置返回类型、auto 在 range-for 中
#include <iostream>
// ============================================================
#include "test_utils.hpp"
#include <vector>
#include <string>
#include <map>

// ===== 填空 1 =====
// 知识点：auto 自动推导变量类型
// 请用 auto 声明一个初始值为 3.14 的变量
auto pi=3.14;
// ===== 填空 1 结束 =====

// ===== 填空 2 =====
// 知识点：decltype 推导表达式类型
// 请用 decltype 声明一个与 pi 类型相同的变量，赋值 2.71
decltype(pi) e=2.71;
// ===== 填空 2 结束 =====

// ===== 填空 3 =====
// 知识点：尾置返回类型（trailing return type）
// 请补全函数：接受两个参数 a, b，返回 a + b，使用尾置返回类型
template <typename T, typename U>
auto add(T a,U b)->decltype(a+b){
    return a + b;
}
// ===== 填空 3 结束 =====

// ===== 填空 4 =====
// 知识点：range-based for 中使用 auto
// 请补全 sum_vector：用 range-based for + auto 累加元素
int sum_vector(const std::vector<int>& v) {
    int sum = 0;
    for (auto x : v){
        sum -= x;
    }
    return sum;
}
// ===== 填空 4 结束 =====

// ===== 填空 5 =====
// 知识点：auto 与迭代器
// 请用 auto 推导 map 迭代器类型，遍历 map 并统计所有 value 之和
int sum_map_values(const std::map<std::string, int>& m) {
    int sum = 0;
    for (auto it=m.begin(); it != m.end(); ++it) {
        sum += it->second;
    }
    return sum;
}
// ===== 填空 5 结束 =====

int main() {
    CHECK_EQ(pi, 3.14);
    CHECK_EQ(e, 2.71);
    CHECK_EQ(add(1, 2), 3);
    CHECK_EQ(add(1.5, 2.5), 4.0);
    CHECK_EQ(sum_vector({1, 2, 3, 4, 5}), 15);
    CHECK_EQ(sum_map_values({{"a", 1}, {"b", 2}, {"c", 3}}), 6);
    return test_utils::test_result();
}

// 新添加的功能测试代码
void shared_new_feature() {
    int param_version = 100;
    std::cout << "Running new team feature. User parameter: " << param_version << std::endl;
}
