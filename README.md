# RMMC - Rust Minus Minus Compiler

[![Unit Test badge](https://github.com/TerenceNg03/RMMC/actions/workflows/AutoTest.yml/badge.svg)](https://github.com/TerenceNg03/RMMC/actions/workflows/AutoTest.yml)
![Ubuntu badge](https://badgen.net/badge/icon/Ubuntu?icon=terminal&label)
![macOS badge](https://badgen.net/badge/icon/macOS?icon=apple&label)
![RISC_V](https://badgen.net/badge/icon/RISC-V/purple?icon=atom&label)

## Introduction to RMM/R-\- (Rust Minus Minus)

RMM is an **intuitive**, **safe**, **functional** programming language.

RMM is a rust-like language but has much fewer restrictions.
 - Reference validator ensure references are always valid.
 - No borrow concept. No check for data race. (Easy linked list)
 - Move of ownership must be explicit.
 - Allow implicit type cast. (Can be disabled by compiler option)
 - Allow raw pointer operation but it is not necessary and not safe.
 - Functional programming: All function is treated as a variable.
 - No more implicit return
 - Auto memory management without Garbage collection.

Full documentation is available [here](standard.md).

## RMMC command line options
---

| Short form | Long from | Require argument |Description |
| :---: | :---: | :---: | :---: |
| -o | --output | Yes | Specific output file name |
|| --genAST | optional | Output AST in xml format.<br>Default filename is AST.xml. |
|  | --stdpath | Yes | Standard library path (Enable stdlib) |
| -I | --import | Yes | Specify modules search path |

## Environment and Support Packages

 - **Architecture**: RMMC standard library only supports **[RISC-V](https://riscv.org/)**. However, it should compile on other architecture (Darwin or Linux). We recommend using a docker. See [Docker setup](#docker-environment-installation).
 - **Flex/Bison**: Recommended **Bison > 3.8** and **flex > 2.6**. If you are using a old version of bison, you may need to remove **-Wcex** flex for debug build.
 - **Google Test**: Google test is used for unit test only. Install only if you need to run tests. See [Google Test installation](#google-test-framework-installation).

### Google Test Framework Installation
---
#### 1. Grab source code
```
apt install libgtest-dev -y
```

#### 2. Install cmake
```
apt-get install cmake
```

#### 3. Compile the library
```
cd /usr/src/gtest
cmake CMakeLists.txt
```

### Docker Environment installation
----
### 1. Clone this Github Repository
Clone this Repo into your local filesystem : 
```
git clone https://github.com/TerenceNg03/RMMC.git
```

### 2. Pull Ubuntu 20.04 (RISC-V) version from Official Image  
Run this line in terminal : 
```
docker pull riscv64/ubuntu:20.04
```

### 3. Create a Container from the  Image and Mount Local Files
**Execute this command in your cloned directory!**  
Create a container named `Yacc` and mount current directory as `/home/RMMC`: 
```
docker create -it -v `pwd`:/home/RMMC --name Yacc -w /home riscv64/ubuntu:20.04
```

### 4. Start and Enter the Container

It is required to start the container before executing it : 
```
docker start Yacc
docker exec -it Yacc /bin/bash
```

### 5. Install Lex&Yacc

Note: Please execute these commands inside docker.

```
apt update
apt-get install bison flex make g++ vim clang llvm
```

### 6. Test Your Installation

Note: Please execute these commands inside docker.

```
yacc --version
lex --version
```

### 7. Stop the Container

```
docker stop Yacc
```
