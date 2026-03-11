// ============================================================
// 题目 03：智能指针
// 知识点：unique_ptr、shared_ptr、weak_ptr、make_unique、make_shared
// ============================================================
#include "test_utils.hpp"
#include <string>

struct Node {
    int value;
    explicit Node(int v) : value(v) {}
};

// ===== 填空 1 =====
// 知识点：std::make_unique<T>(args...)
// 请用 make_unique 创建一个 Node，值为 42
std::unique_ptr<Node> make_node(int v) {
    return std::make_unique<Node>(v);
}
// ===== 填空 1 结束 =====

// ===== 填空 2 =====
// 知识点：unique_ptr 转移所有权（std::move）
// 请用 std::move 将 p 的所有权转移到返回值
std::unique_ptr<Node> transfer(std::unique_ptr<Node> p) {
    return std::move(p);
}
// ===== 填空 2 结束 =====

// ===== 填空 3 =====
// 知识点：std::make_shared<T>(args...)，shared_ptr 引用计数
// 请用 make_shared 创建一个 shared_ptr<string>，然后复制它以增加引用计数
int shared_use_count() {
    auto sp1 = std::make_shared<std::string>();
    auto sp2 = sp1;  // 复制，引用计数 +1
    return static_cast<int>(sp1.use_count());  // 应为 2
}
// ===== 填空 3 结束 =====

// ===== 填空 4 =====
// 知识点：weak_ptr + lock()
// 请用 weak_ptr 观察 shared_ptr，并用 lock() 获取临时 shared_ptr
bool weak_ptr_demo() {
    auto sp = std::make_shared<int>(10);
    std::weak_ptr<int> wp=sp;
    if (auto locked = wp.lock()) {
        return *locked == 10;
    }
    return false;
}
// ===== 填空 4 结束 =====

// ===== 填空 5 =====
// 知识点：unique_ptr::reset()，reset 后指针为 nullptr
// 请补全：对 unique_ptr 调用 reset()，验证其变为 nullptr
bool reset_demo() {
    auto p = std::make_unique<int>(99);
    p.reset(nullptr);
    return p == nullptr;
}
// ===== 填空 5 结束 =====

int main() {
    auto n = make_node(42);
    CHECK_EQ(n->value, 42);

    auto n2 = transfer(make_node(7));
    CHECK_EQ(n2->value, 7);

    auto n3 = transfer(make_node(8));
    CHECK_EQ(n3->value, 8);

    CHECK_EQ(shared_use_count(), 3);
    CHECK_TRUE(weak_ptr_demo());
    CHECK_TRUE(reset_demo());

    return test_utils::test_result();
}
