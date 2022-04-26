### 1. llvm 安装

默认安装版本10.0.0

```
apt-get install llvm clang
```

查看版本

```
llvm-as --version
clang -v
```

添加路径

```
export PATH="$PATH:/usr/lib/llvm-10/bin"
export PATH="$PATH:/usr/lib/llvm-10/include"
```

### 2. 编译命令

`toy.cpp` 为编译文件

```
clang++ -g -O3 toy.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -o toy
```

