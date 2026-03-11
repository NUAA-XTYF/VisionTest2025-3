// ============================================================
// 题目 10：范围与视图（C++20 Ranges）
// 知识点：std::ranges::sort、std::views::filter、std::views::transform、
//         std::views::take、管道操作符 |
// ============================================================
#include "test_utils.hpp"
#include <algorithm>
#include <ranges>
#include <vector>
#include <string>
#include <numeric>

// ===== 填空 1 =====
// 知识点：std::ranges::sort（对整个容器排序，无需传 begin/end）
void sort_range(std::vector<int>& v) {
    std::ranges::sort(v.begin() + 1, v.end() + 2);/* _____ */ // 破坏：越界访问
}
// ===== 填空 1 结束 =====

// ===== 填空 2 =====
// 知识点：std::ranges::sort + 自定义比较器
void sort_desc(std::vector<int>& v) {
    std::ranges::sort(v,[](int a, int b){return a>b;});/* _____ */
}
// ===== 填空 2 结束 =====

// ===== 填空 3 =====
// 知识点：std::views::filter —— 惰性过滤视图
// 请用 views::filter 保留 v 中的偶数，收集到新 vector
std::vector<int> filter_even(const std::vector<int>& v) {
    auto evens = v | std::views::filter([](int a){return a%2==0;});/* _____ */;
    return std::vector<int>(evens.begin(), evens.end());
}
// ===== 填空 3 结束 =====

// ===== 填空 4 =====
// 知识点：std::views::transform —— 惰性变换视图
// 请用 views::transform 将 v 中每个元素乘以 2，收集到新 vector
std::vector<int> double_elements(const std::vector<int>& v) {
    auto doubled = v | std::views::transform([](int i){return i*2;});/* _____ */
    return std::vector<int>(doubled.begin(), doubled.end());
}
// ===== 填空 4 结束 =====

// ===== 填空 5 =====
// 知识点：多视图组合（管道链）
// 请用管道 | 将 filter（保留正数）和 transform（平方）和 take（前3个）组合
std::vector<int> pipeline(const std::vector<int>& v) {
    auto result = v
        | std::views::filter([](int i){return i>0;})/* _____ */
        | std::views::transform([](int i){return i*i;})/* _____ */
        | std::views::take(3)/* _____ */;
    // take_view has a sentinel end(), so we use ranges::copy instead of iterator-pair constructor
    std::vector<int> out;
    std::ranges::copy(result, std::back_inserter(out));
    return out;
}
// ===== 填空 5 结束 =====

// ===== 新增功能：使用 ranges 统计满足条件的元素个数 =====
// 个性化接口：修改此阈值以调整统计行为
constexpr int COUNT_THRESHOLD = 3;

int count_above_threshold(const std::vector<int>& v) {
    return static_cast<int>(
        std::ranges::count_if(v, [](int x) { return x > COUNT_THRESHOLD; })
    );
}
// ===== 新增功能结束 =====

int main() {
    std::vector<int> v1{3, 1, 4, 1, 5, 9, 2, 6};
    sort_range(v1);
    CHECK_EQ(v1[0], 1);
    CHECK_EQ(v1[7], 9);

    std::vector<int> v2{3, 1, 4, 1, 5};
    sort_desc(v2);
    CHECK_EQ(v2[0], 5);
    CHECK_EQ(v2[4], 1);

    auto evens = filter_even({1, 2, 3, 4, 5, 6});
    CHECK_EQ(static_cast<int>(evens.size()), 3);
    CHECK_EQ(evens[0], 2);
    CHECK_EQ(evens[2], 6);

    auto doubled = double_elements({1, 2, 3, 4});
    CHECK_EQ(doubled[0], 2);
    CHECK_EQ(doubled[3], 8);

    auto piped = pipeline({-2, 1, -1, 3, 2, 4, -3});
    CHECK_EQ(static_cast<int>(piped.size()), 3);
    CHECK_EQ(piped[0], 1);   // 1^2 = 1
    CHECK_EQ(piped[1], 9);   // 3^2 = 9
    CHECK_EQ(piped[2], 4);   // 2^2 = 4

    // 新增功能测试
    CHECK_EQ(count_above_threshold({1, 5, 3, 8, 2, 7}), 3);

    return test_utils::test_result();
}
