// ============================================================
// 题目 04：移动语义与完美转发
// 知识点：std::move、右值引用 &&、移动构造函数、std::forward
// ============================================================
#include "test_utils.hpp"
#include <string>
#include <vector>
#include <utility>

// ===== 填空 1 =====
// 知识点：std::move 将左值转为右值引用，触发移动构造
// 请用 std::move 将 src 字符串移入返回值，移动后 src 变为空
std::string move_string(std::string& src) {
    return std::move(src);
}
// ===== 填空 1 结束 =====

// ===== 填空 2 =====
// 知识点：右值引用参数 T&&，接受临时对象
// 请完成 sink 函数，参数为 string 的右值引用，将其内容存入全局 vector
std::vector<std::string> g_sink_results;
void sink(std::string&& s) {
    g_sink_results.push_back(std::move(s));
}
// ===== 填空 2 结束 =====

// ===== 填空 3 =====
// 知识点：移动构造函数（noexcept + std::exchange）
// 请补全 Buffer 的移动构造函数
struct Buffer {
    int* data;
    int  size;

    explicit Buffer(int n) : data(new int[n]()), size(n) {}
    ~Buffer() { delete[] data; }

    // 禁用拷贝
    Buffer(const Buffer&)            = delete;
    Buffer& operator=(const Buffer&) = delete;

    // ===== 移动构造 =====
    Buffer(Buffer&& other) noexcept
        : data(std::exchange(other.data, nullptr)),
          size(std::exchange(other.size, 0))
    {}
    // ===== 结束 =====
};
// ===== 填空 3 结束 =====

// ===== 填空 4 =====
// 知识点：完美转发 std::forward<T>
// 请补全 wrapper，完美转发参数 arg 给 sink
template <typename T>
void wrapper(T&& arg) {
    sink(std::forward<T>(arg));
}
// ===== 填空 4 结束 =====

int main() {
    std::string s = "hello";
    auto moved = move_string(s);
    CHECK_EQ(moved, std::string("hello"));
    CHECK_TRUE(s.empty());

    sink(std::string("world"));
    CHECK_EQ(g_sink_results[0], std::string("world"));

    Buffer b1(10);
    b1.data[0] = 42;
    Buffer b2(std::move(b1));
    CHECK_EQ(b2.data[0], 42);
    CHECK_EQ(b2.size, 10);
    CHECK_TRUE(b1.data == nullptr);

    wrapper(std::string("forwarded"));
    CHECK_EQ(g_sink_results[1], std::string("forwarded"));

    return test_utils::test_result();
}
