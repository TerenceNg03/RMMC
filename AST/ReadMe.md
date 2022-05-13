1. llvm 安装

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

### 3. To-Do

namespace :: 作为二元运算符

union and match 

```
clang++ test.cpp -I /include `llvm-config --cxxflags --ldflags --system-libs --libs core` -o test.out
```



#### Example

```c++
#include "AST.hh"
#include "location.hh"
#include<memory>
int main()
{
    //single variable declaration
    //let a : i32 = 'c';
    rmmc::location loc;
    std::unique_ptr<rmmc::IdentifierExpr> id_type=std::make_unique<rmmc::IdentifierExpr>("i32");
    std::unique_ptr<rmmc::IdentifierExpr> id_name=std::make_unique<rmmc::IdentifierExpr>("a");
    std::unique_ptr<rmmc::SingleVariableDeclarationStatement> decla_root=std::make_unique<rmmc::SingleVariableDeclarationStatement>(move(id_type), move(id_name), loc, rmmc::VariableDeclarationStatement::NOT_MUTABLE);
    std::unique_ptr<rmmc::CharExpr> const_char=std::make_unique<rmmc::CharExpr>('c');
    std::unique_ptr<rmmc::IdentifierExpr> id_name = std::make_unique<rmmc::IdentifierExpr>("a");
    std::unique_ptr<rmmc::AssignmentExpression> ass_root=std::unique_ptr<rmmc::AssignmentExpression>(move(id_name), move(const_char));

    // let main : auto = < argc : i32, argv : **char;
    // i32 >
    // {
    //     var array : [ i32, 6 ] = [ 6, 1, 3, 5, 2, 0 ];
    //     sort(6, &array[0]);
    //     var i : i32 = 0;
    //     while (i < 6)
    //     {
    //         std::io::printInt(array[i]);
    //         std::io::prints(" ");
    //         i = i + 1;
    //     };
    //     return 0;
    // };
    std::unique_ptr<rmmc::>
    std::unique_ptr<rmmc::FunctionDeclarationStatement> func_root=std::make_unique<rmmc::FunctionDeclarationStatement>();
    return 0;
}

```

