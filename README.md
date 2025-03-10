# CNOC
在大学自己突发奇想写的代码（）

1. git add . 添加到暂存区
2. git status  查看暂存区状态、本地commit状态
3. git commit -m '' 添加commit信息，-m 是 message的简写
4. git push 推送
   git push -f 强制推送，用本地的commit树覆盖远程的


   这里带个云朵的是远程，蓝色的那个代表本地，现在这个说明，本地比远程领先了一个提交，领先的内容就是里面的ceshi

后悔了可以用  git reset --soft HEAD^ 撤回一次提交，如果提交到远程了，就强制推送覆盖远程的内容


------

git pull 拉取远程的内容