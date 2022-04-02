# 2022-ZJU-Compiler-Team
Course Project for 2022 ZJU Compiler Construction Principle and Practice 

### (Updated) Important: Docker Environment installation
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
