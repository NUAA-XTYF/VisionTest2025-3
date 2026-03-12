Git 常用命令：
git init
创建本地仓库
git clone
克隆远程仓库到本地
git pull
拉取远程仓库并放到工作区
git push
将工作区内容上传到远程仓库
git log
查看文件修改信息
git diff
查看文件差异
git bisect
判断文件变化，过程如下
{
    git bisect start
    git bisect good <file>
    git bisect bad <file>
}
git add
将代码从本地仓库提交到暂存区
git commit
将代码从暂存区提交到本地仓库
git reset --hard commitID
切换版本，回退版本


分支管理：
git branch
查看分支
git branch <branch>
创建分支
git checkout
切换不同分支信息
git checkout -b <branch>
创建并切换到一个分支
git branch -d <branch>
检查并删除分支
git branch -D <branch>
强制删除分支


PR 流程：
1.fork整个repository到自己的账户上，复制http地址
2.git clone到本地
3.将修改后的文件git add. , git push或在vscode上链接到远程仓库后直接提交到远程仓库上


遇到的问题与解决方法：
找不到破坏之处，通过github上的actions知道哪些文件被破坏，先cmake发现一部分错误，在执行test时又发现一些问题
使用git bisect start，git log --oneload --grep="<文件名>",git bisect good <以前的版本>,git bisect bad HEAD,gcc测试发现问题并修改