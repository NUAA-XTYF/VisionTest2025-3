# 破坏方式参考手册

> 本文件列出了助教在「GitHub 保卫战」阶段可能采用的破坏方式。  
> 所有破坏操作均通过 **Git 提交**记录，因此可以被 Git 完整追踪与溯源。  
> 了解这些方式有助于你更快速地定位问题、撰写高质量的 Issue 并完成修复。

---

## 一、代码内容级破坏

这类破坏直接修改源文件内容，是最常见的形式。

### 1.1 删除关键代码行

将某道题中已填好的答案行直接删除，留下空白或注释。

```diff
- auto result = std::make_unique<int>(42);
+ // TODO: 此处已被删除
```

**追踪方法：** `git log --oneline --all`，找到破坏提交后使用 `git diff <破坏前commit> <破坏后commit>`。

---

### 1.2 替换为错误实现

将正确答案替换为语法合法但语义错误的代码，使编译通过但测试失败。

```diff
- return std::forward<T>(val);
+ return val;  // 完美转发被静默破坏
```

**追踪方法：** 运行 `ctest` 查看哪道题的测试失败，再用 `git diff` 定位具体行。

---

### 1.3 修改字面量或常量

将数值、字符串等字面量改为错误值。

```diff
- constexpr int factorial_5 = 120;
+ constexpr int factorial_5 = 100;
```

**追踪方法：** 测试报告中会显示期望值与实际值的差异，据此定位。

---

### 1.4 注释掉关键语句

用 `//` 或 `/* */` 注释掉一行或多行答案代码，不删除内容但使其失效。

```diff
- ptr.reset();
+ // ptr.reset();
```

**追踪方法：** `git show <commit>` 可直接看到被注释的内容。

---

## 二、文件级破坏

### 2.1 删除整个源文件

将某道题的 `.cpp` 文件从仓库中删除（`git rm`）。

**追踪方法：**
```bash
git log --diff-filter=D --name-only  # 列出所有被删除的文件
git checkout <删除前的commit> -- path/to/file.cpp  # 恢复文件
```

---

### 2.2 清空文件内容

保留文件但将其内容清空（等效于 `> file.cpp`）。

**追踪方法：** `git show <commit>:path/to/file.cpp` 查看历史版本内容并恢复。

---

### 2.3 重命名文件

将文件重命名，破坏 CMake 构建链。

```diff
- q03_smart_pointers/q03.cpp
+ q03_smart_pointers/q03_backup.cpp
```

**追踪方法：** `git log --follow --name-status` 追踪文件重命名历史。

---

## 三、配置文件级破坏

### 3.1 修改 CMakeLists.txt

删除或注释掉某个子目录的 `add_subdirectory`，使该题无法参与编译。

```diff
- add_subdirectory(q03_smart_pointers)
+ # add_subdirectory(q03_smart_pointers)
```

**追踪方法：** 构建时某道题的目标消失，结合 `git diff` 快速定位。

---

### 3.2 修改编译标准

将 `CMakeLists.txt` 中的 C++ 标准从 20 降低，导致 C++20 特性编译失败。

```diff
- set(CMAKE_CXX_STANDARD 20)
+ set(CMAKE_CXX_STANDARD 14)
```

**追踪方法：** 编译器报错提示特性不支持，结合 `git log -p CMakeLists.txt` 定位。

---

## 四、Git 溯源工具速查

| 场景 | 命令 |
|------|------|
| 查看所有提交历史 | `git log --oneline --all --graph` |
| 查看某次提交的改动 | `git show <commit-hash>` |
| 对比两个提交之间的差异 | `git diff <commit-A> <commit-B>` |
| 查看某文件的修改历史 | `git log -p -- path/to/file` |
| 找出引入 bug 的提交 | `git bisect start` / `git bisect good` / `git bisect bad` |
| 恢复某文件到历史版本 | `git checkout <commit-hash> -- path/to/file` |
| 查看已删除的文件 | `git log --diff-filter=D --name-only` |
| 撤销某次破坏性提交 | `git revert <commit-hash>` |

---

## 五、修复建议

1. **发现破坏后，第一时间在 Issues 中描述**，包括：受影响的文件路径、破坏前后的 `git diff` 以及你使用的定位方法。
2. 修复时优先考虑 `git revert` 或 `git checkout`，避免手动重写引入新错误。
3. 修复完成后，重新运行 `ctest` 确保所有测试通过，再发起 PR。
4. 修复 PR 的描述中引用对应的 Issue 编号（如 `Fixes #3`），便于关联追踪。
