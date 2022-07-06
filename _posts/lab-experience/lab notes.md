##### 建立 SSH 链接

公钥登录。

添加公钥，这一段是写给在服务器上已经有账号的。反之，cd home+mkdir 用户名。

拿到新的公钥，并且创建新的账号的文件夹底下。

先查看文件夹下是否存在.ssh文件夹 否则运行sudo mkdir ./.ssh

然后将公钥id_rsa.pub上传到对应的账户的.ssh文件夹下，并且改名为 authorized_key

用 sudo chown 用户名 authorized_key 修改公钥的所有人

用 sudo chmod 600 authorized_key 给公钥添加运行权限



##### Vim

插件管理：Bundle

好用的插件：Nerdtree，TagBar，jedi-python



##### SVN

权限修改，文件夹创建





##### FRP

http://39.107.92.9:5636/dokuwiki/doku.php?id=term_script



##### Linux

tail nohup.out：在当前路径生成一个nohup.out

top htop ps -ef grep pstree：查看进程

scp -r /root/lk root@43.224.34.73:/home/lk/cpfile：Linux 之间拷贝Secure Copy

nautilus /file：终端打开文件 



##### 操作服务器时遇到的问题

鼠标不见了/卡死？ctrl+alt+f1 回到登陆界面，重新登录。

终端如何粘贴？ctrl+shift+v。

找不到home？点开文件界面，左侧最下栏。