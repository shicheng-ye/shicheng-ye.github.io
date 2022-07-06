## YouCompleteMe 安装

github 项目地址：https://github.com/ycm-core/YouCompleteMe

该项目有子模块，github 被墙的情况下很难克隆。我 ssh 连接导实验室的无人机为之 vim 配置该插件，不是很懂怎么命令行翻墙。因此，我是本地电脑翻墙克隆后，再输入如下指令克隆它的子模块。

```
git submodule update --init --recursive
```

针对 github 被墙，可用工具：dev-sidecar，pigcha。

克隆了子模块后，上传至 onedrive，并获取下载链接。在 linux 终端输入如下指令下载：

```
wget -c <url> -O </path/name>
```

解压 zip

```
unzip <filename>
```

按教程安装依赖包：https://github.com/ycm-core/YouCompleteMe#linux-64-bit

在 .vimrc 中加入 ycm-core/YouCompleteMe 后，编译 YCM。

```
cd ~/.vim/bundle/YouCompleteMe
python3 install.py --all(所有语言语法检查) 
or python3 install.py --clangd-completer(C系列语言语法检查) 
or python3 install.py (没有语法检查)
```

可能出现的问题： Your C++ compiler does NOT fully support C++17

解决：https://stackoverflow.com/questions/65284572/your-c-compiler-does-not-fully-support-c17

下载 clangd：https://www.cnblogs.com/zi-wang/p/13550305.html

编译生成 ycm_core，https://github.com/ycm-core/YouCompleteMe/wiki/Full-Installation-Guide



注意：更新 Vim 至 8.1

先克隆 8.1.2424 版本的 vim

```
git clone -b <tag> url
```

按照如下教程配置：https://github.com/ycm-core/YouCompleteMe/wiki/Building-Vim-from-source

查看版本

```
vim --version |grep VIM
```

查看是否支持 python3

```
vim --version |grep python
```

