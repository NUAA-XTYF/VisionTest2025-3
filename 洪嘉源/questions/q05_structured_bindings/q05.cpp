// ============================================================
// 题目 05：结构化绑定（C++17）
// 知识点：auto [x,y]、pair/tuple/struct 绑定、range-for 中的绑定
// ============================================================
#include "test_utils.hpp"
#include <tuple>
#include <map>
#include <string>
#include <vector>
#include <utility>

// ===== 填空 1 =====
// 知识点：std::pair 的结构化绑定
// 请补全：用结构化绑定从 pair 中取出 first 和 second
std::pair<int, int> split_pair(std::pair<int, int> p) {
	auto [a, b] = p;
    return {a, b};    // 交换返回
}
// ===== 填空 1 结束 =====

// ===== 填空 2 =====
// 知识点：std::tuple 的结构化绑定
// 请补全：从三元素 tuple 中用结构化绑定取出三个值，并返回其和
int sum_tuple(std::tuple<int, int, int> t) {
	auto [x, y, z] = t;
    return x + y + z;
}
// ===== 填空 2 结束 =====

// ===== 填空 3 =====
// 知识点：聚合结构体的结构化绑定
struct Point { int x; int y; };
int manhattan(Point p) {
	auto [x, y] = p;
    return (x < 0 ? -x : x) + (y < 0 ? -y : y);
}
// ===== 填空 3 结束 =====

// ===== 填空 4 =====
// 知识点：range-for 中对 map 使用结构化绑定
int sum_map(const std::map<std::string, int>& m) {
    int total = 0;
    for (auto [index , val] : m) {
        total += val;
    }
    return total;
}
// ===== 填空 4 结束 =====

// ===== 填空 5 =====
// 知识点：结构化绑定 + vector of pairs
std::vector<int> seconds(const std::vector<std::pair<int,int>>& v) {
    std::vector<int> result;
    for (auto [first, second] : v) {
        result.push_back(second);
    }
    return result;
}
// ===== 填空 5 结束 =====

int main() {
    auto [a, b] = split_pair({1, 2});
    CHECK_EQ(a, 2);
    CHECK_EQ(b, 1);

    CHECK_EQ(sum_tuple({1, 2, 3}), 6);
    CHECK_EQ(manhattan({-3, 4}), 7);

    std::map<std::string, int> m{{"a", 10}, {"b", 20}, {"c", 30}};
    CHECK_EQ(sum_map(m), 60);

    auto s = seconds({{1, 10}, {2, 20}, {3, 30}});
    CHECK_EQ(s[0], 10);
    CHECK_EQ(s[1], 20);
    CHECK_EQ(s[2], 30);

    return test_utils::test_result();
}
