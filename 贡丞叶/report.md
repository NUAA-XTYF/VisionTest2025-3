git 指令
1. 配置与初始化

· git config --global user.name "Your Name"：设置全局用户名。
· git config --global user.email "your_email@example.com"：设置全局邮箱。
· git init：在当前目录初始化一个新的Git仓库。
· git clone <repository-url>：从远程仓库克隆到本地。

2. 基本操作

· git status：查看工作区、暂存区状态。
· git add <file>：将文件添加到暂存区（可使用git add .添加所有改动）。
· git commit -m "提交信息"：将暂存区内容提交到本地仓库。
· git log：查看提交历史（--oneline 可简化显示）。
· git diff：查看工作区与暂存区的差异（git diff --cached 查看暂存区与上次提交的差异）。

3. 分支管理

· git branch：列出本地分支（当前分支前有*号）。
· git branch <branch-name>：创建新分支。
· git checkout <branch-name> 或 git switch <branch-name>：切换到指定分支。
· git checkout -b <branch-name> 或 git switch -c <branch-name>：创建并切换到新分支。
· git merge <branch-name>：将指定分支合并到当前分支。
· git branch -d <branch-name>：删除本地分支

4. 远程仓库交互

· git remote add origin <repository-url>：关联远程仓库（通常命名为origin）。
· git push origin <branch-name>：将本地分支推送到远程仓库。
· git pull origin <branch-name>：从远程仓库拉取并合并到当前分支（相当于git fetch + git merge）。
· git fetch origin：仅从远程获取更新，不自动合并。
· git clone <repository-url>：克隆远程仓库到本地，自动关联远程。

5. 撤销与恢复

· git restore <file>：丢弃工作区的修改（Git 2.23+）。
· git restore --staged <file>：将文件从暂存区移除。
· git reset --hard <commit-hash>：将当前分支重置到指定提交，并丢弃之后的所有改动（慎用）。
· git revert <commit-hash>：生成一个新提交，撤销指定提交的改动（安全，适合已推送的提交）。
· git log -- <file>：查看某个文件的修改历史。
· git blame <file>：逐行查看文件最后修改者。

pr

1. Fork与Clone

· 在GitHub上找到目标仓库，点击“Fork”将仓库复制到自己的账号下。
· 将Fork后的仓库克隆到本地：`git clone https://github.com/your-username/repo.git`。
· 添加原仓库为上游（upstream），以便同步更新：
  ```bash
  git remote add upstream https://github.com/original-owner/repo.git
  ```

2. 创建新分支并开发

· 在本地创建功能分支：git checkout -b feature/your-feature。
· 进行代码修改，提交更改：
  ```bash
  git add .
  git commit -m "Add: 实现登录功能"
  ```

3. 同步上游更新

为避免冲突，开发过程中应定期拉取上游主分支的更新：

```bash
git checkout main
git pull upstream main          # 拉取原仓库main分支
git push origin main             # 更新自己的远程main
git checkout feature/your-feature
git merge main                   # 将最新代码合并到功能分支
```


4. 推送分支并创建PR

· 将本地功能分支推送到自己的远程仓库：
  ```bash
  git push origin feature/your-feature
  ```
· 在GitHub上，进入自己的仓库页面，会出现提示“feature/your-feature had recent pushes”，点击“Compare & pull request”。
· 填写PR标题和描述，说明改动内容，然后点击“Create pull request”。