// ============================================================
// 题目 02：Lambda 表达式
// 知识点：捕获方式、参数、返回类型、泛型 lambda、mutable
// ============================================================
#include "test_utils.hpp"
#include <vector>
#include <algorithm>
#include <functional>

// ===== 填空 1 =====
// 知识点：lambda 值捕获 [=]
// 请补全 make_adder：返回一个 lambda，按值捕获 n，并将其加到参数上
std::function<int(int)> make_adder(int n) {
    return [=](int x) {return x+n;};/* _____ */
}
// ===== 填空 1 结束 =====

// ===== 填空 2 =====
// 知识点：lambda 引用捕获 [&]
// 请补全 count_if_ref：用引用捕获 threshold，统计 v 中大于 threshold 的元素个数
int count_above(const std::vector<int>& v, int threshold) {
    int count = 0;
    std::for_each(v.begin(), v.end(), [&](int x)/* _____ */ {
        if (x > threshold) ++count;
    });
    return count;
}
// ===== 填空 2 结束 =====

// ===== 填空 3 =====
// 知识点：C++14 泛型 lambda（auto 参数）
// 请定义一个泛型 lambda identity，接受任意类型参数并原样返回
auto identity = [] (auto x) { return x; };/* _____ */;
// ===== 填空 3 结束 =====

// ===== 填空 4 =====
// 知识点：mutable lambda（修改按值捕获的变量）
// 请补全：按值捕获 counter，用 mutable 使其可在 lambda 内被修改
//         每次调用计数器 +1，返回旧值
std::function<int()> make_counter() {
    int counter = 0;
    return [=]() mutable { return counter++;}/* _____ */;
}
// ===== 填空 4 结束 =====

// ===== 填空 5 =====
// 知识点：lambda 作为比较器传入 sort
// 请用 lambda 对 vector 按降序排序
void sort_descending(std::vector<int>& v) {
    std::sort(v.begin(), v.end(), [](int a, int b) {return a > b;}/* _____ */);
}
// ===== 填空 5 结束 =====

int main() {
    auto add5 = make_adder(5);
    CHECK_EQ(add5(3), 8);
    CHECK_EQ(add5(10), 15);

    CHECK_EQ(count_above({1, 5, 3, 8, 2}, 4), 2);

    CHECK_EQ(identity(42), 42);
    CHECK_EQ(identity(std::string("hi")), std::string("hi"));

    auto cnt = make_counter();
    CHECK_EQ(cnt(), 0);
    CHECK_EQ(cnt(), 1);
    CHECK_EQ(cnt(), 2);

    std::vector<int> v{3, 1, 4, 1, 5, 9, 2, 6};
    sort_descending(v);
    CHECK_EQ(v[0], 9);
    CHECK_EQ(v[1], 6);

    return test_utils::test_result();
}
