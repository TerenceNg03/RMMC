# 2022-ZJU-Compiler-Team
Course Project for 2022 ZJU Compiler Construction Principle and Practice 

## Introduction to RMM/R-\- (Rust Minus Minus)

RMM is a rust-like but has much fewer restrictions.
 - No borrow checker, ownership, lifetime
 - Allow implicit type cast
 - Allow raw pointer operation
 - Functional programming: All function is treated as a variable.<br> Lambda expressions supported natively.

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
git clone https://github.com/TerenceNg03/2022-ZJU-Compiler-Team.git
```

### 2. Pull Ubuntu 20.04 (RISC-V) version from Official Image  
Run this line in terminal : 
```
docker pull riscv64/ubuntu:20.04
```

### 3. Create a Container from the  Image and Mount Local Files
**Execute this command in your cloned directory!**  
Create a container named `Yacc` and mount current directory as `/home/2022-ZJU-Compiler`: 
```
docker create -it -v `pwd`:/home/2022-ZJU-Compiler --name Yacc -w /home riscv64/ubuntu:20.04
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
apt-get install bison flex make g++ vim
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
