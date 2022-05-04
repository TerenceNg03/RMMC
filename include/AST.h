//
// Created by Yuying on 2022/5/3.
//

#ifndef __AST_H__
#define __AST_H__

#include "llvm/IR/Value.h"
#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <cstring>

using std::cout;
using std::endl;
using std::make_shared;
using std::string;
using std::vector;
using std::unique_ptr;
using std::move;

class Statement;
class Expression;
class VariableDeclarationStatement;
class FunctionDeclarationStatement;

typedef std::vector<std::unique_ptr<Statement>> StatementList;
typedef std::vector<std::unique_ptr<Expression>> ExpressionList;
typedef std::vector<std::unique_ptr<VariableDeclarationStatement>> VariableList;
typedef std::vector<std::unique_ptr<FunctionDeclarationStatement>> FunctionList;

class ASTNode
{
public:
    ASTNode() = default;
    virtual ~ASTNode() = default;
    virtual void print()
    {
        cout << "ASTNode" << endl;
    }
    virtual void toXML()
    {
        
    }
    virtual llvm::Value *codeGen()
    {
        return (llvm::Value *)0;
    }
};

class Statement : public ASTNode
{
public:
    Statement() = default;
    virtual ~Statement() {}
};

class Expression : public ASTNode
{
public:
    Expression() = default;
    virtual ~Expression() {}
};

/***
 * Constant Value : Double Integer UnsignedInteger Boolean
 *
 */
class DoubleExpr : public Expression
{
public:
    double Value;

    DoubleExpr() {}
    DoubleExpr(double _value): Value(_value) {}
    ~DoubleExpr() {}
    virtual void print(){
        std::cout<<"Double Expression"<<endl;
    }
};

class IntegerExpr : public Expression
{
public:
    long long Value;

    IntegerExpr() {}
    IntegerExpr(long long _value): Value(_value) {}
    ~IntegerExpr() {}
};

class UnsignedIntegerExpr : public Expression
{
public:
    unsigned long long Value;

    UnsignedIntegerExpr() {}
    UnsignedIntegerExpr(unsigned long long _value): Value(_value) {}
    ~UnsignedIntegerExpr() {}
};

class BooleanExpr : public Expression
{
public:
    bool Value;

    BooleanExpr() {}
    BooleanExpr(bool _value): Value(_value) {}
    ~BooleanExpr() {}
};

class CharExpr : public Expression
{
public:
    char Value;

    CharExpr() {}
    CharExpr(char _value) : Value(_value) {}
    ~CharExpr() {}
};

class IdentifierExpr : public Expression
{
public:
    string Name;

    IdentifierExpr() {}
    IdentifierExpr(string _name): Name(_name) {}
};

enum BinaryOperator
{
    SCOPE,          //::
    ARRAY_INDEX,    //[]
    MEMBER_ACCESS,  //. ->
    AS,             //as
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,            //%
    LEFT_SHIFT,
    RIGHT_SHIFT,
    LT,             //<
    ELT,            //<=
    GT,             //>
    EGT,            //>=
    E,              //==
    NE,             //!=
    AND,            //&
    XOR,            //^
    OR,             //|
    LOGICAL_AND,    //&&
    LOGICAL_OR,     //||
};

enum SingleOperator
{
    LOGICAL_NOT, //
    BITWISE_NOT, //~
    INDIRECTION, //*
    ADDRESS_OF,  //&
    MOVE,        //move
};

enum ThreeOperator
{
    CONDITION  //? : ;
};

class SingleOperatorExpr : public Expression
{
public:
    SingleOperator Type;
    std::unique_ptr<Expression> Expr;

    SingleOperatorExpr() {}
    SingleOperatorExpr(std::unique_ptr<Expression> _Expr, SingleOperator _Type)
            : Expr(move(_Expr)) ,
              Type(_Type) {
    }
    ~SingleOperatorExpr() {}
};

class BinaryOperatorExpr : public Expression
{
public:
    BinaryOperator Type;
    std::unique_ptr<Expression> LHS;
    std::unique_ptr<Expression> RHS;

    BinaryOperatorExpr() {}
    BinaryOperatorExpr(unique_ptr<Expression> _LHS, unique_ptr<Expression> _RHS, BinaryOperator _Type)
            : LHS{ move(_LHS) } ,
              RHS{ move(_RHS) } ,
              Type(_Type){
    }
    ~BinaryOperatorExpr() {}
};

class ThreeOperatorExpr : public Expression
{
public:
    ThreeOperator Type;
    std::unique_ptr<Expression> LHS;
    std::unique_ptr<Expression> MHS;
    std::unique_ptr<Expression> RHS;

    ThreeOperatorExpr() {}
    ThreeOperatorExpr(unique_ptr<Expression> _LHS, unique_ptr<Expression> _MHS, unique_ptr<Expression> _RHS, ThreeOperator _Type)
            : LHS{move(_LHS)},
              MHS{move(_MHS)},
              RHS{move(_RHS)},
              Type(_Type)
    {
    }
    ~ThreeOperatorExpr() {}
};

class FunctionCallExpr : public Expression
{
public:
    std::unique_ptr<IdentifierExpr> FunctionName;
    std::unique_ptr<ExpressionList> Args ;

    FunctionCallExpr() {}
    FunctionCallExpr(unique_ptr<IdentifierExpr> _FunctionName)
            : FunctionName{move(_FunctionName)} {
    }
    FunctionCallExpr(unique_ptr<IdentifierExpr> _FunctionName, unique_ptr<ExpressionList> _Args)
            : FunctionName{move(_FunctionName)},
              Args{move(_Args)} {
    }
    ~FunctionCallExpr() {}
};

/***
 * Statement
 *
 */


class VariableDeclarationStatement : public Statement
{
public:
    VariableDeclarationStatement() {}
    virtual ~VariableDeclarationStatement() {}
};

class SingleVariableDeclarationStatement : public VariableDeclarationStatement
{
public:
    std::unique_ptr<IdentifierExpr> VariableType;
    std::unique_ptr<IdentifierExpr> VariableName;

    SingleVariableDeclarationStatement() {}
    SingleVariableDeclarationStatement(unique_ptr<IdentifierExpr> _VariableType, unique_ptr<IdentifierExpr> _VariableName)
            : VariableType{ move(_VariableType) } ,
              VariableName{ move(_VariableName) } {
    }
    ~SingleVariableDeclarationStatement() {}
};

class ArrayDeclarationStatement : public VariableDeclarationStatement
{
public:
    std::unique_ptr<IdentifierExpr> ArrayType;
    std::unique_ptr<IdentifierExpr> ArrayName;
    std::unique_ptr<IntegerExpr> ArraySize;

    ArrayDeclarationStatement() {}
    ArrayDeclarationStatement(unique_ptr<IdentifierExpr> _ArrayType, unique_ptr<IdentifierExpr> _ArrayName, unique_ptr<IntegerExpr> _ArraySize)
        : ArrayType{move(_ArrayType)},
          ArrayName{move(_ArrayName)},
          ArraySize{move(_ArraySize)}
    {
    }
    ~ArrayDeclarationStatement() {}
};

class AssignmentStatement : public Statement
{
public:
    std::unique_ptr<Expression> LHS;
    std::unique_ptr<Expression> RHS;

    AssignmentStatement() {}
    AssignmentStatement(unique_ptr<Expression> _LHS, unique_ptr<Expression> _RHS)
            : LHS{ move(_LHS) } ,
              RHS{ move(_RHS) } {
    }
    ~AssignmentStatement() {}
};


class FunctionDeclarationStatement : public Statement
{
public:
    std::unique_ptr<IdentifierExpr> ReturnType;
    std::unique_ptr<IdentifierExpr> FunctionName;
    std::unique_ptr<VariableList> Args;
    std::unique_ptr<StatementList> Content;

    FunctionDeclarationStatement() {}
    FunctionDeclarationStatement(unique_ptr<IdentifierExpr> _ReturnType,
                                 unique_ptr<IdentifierExpr> _FunctionName,
                                 unique_ptr<VariableList> _Args,
                                 unique_ptr<StatementList> _Content)
            : ReturnType{move(_ReturnType)},
              FunctionName{move(_FunctionName)},
              Args{move(_Args)},
              Content{move(_Content)} {
    }
};

class StructDeclarationStatement : public Statement
{
public:
    std::unique_ptr<IdentifierExpr> Name;
    std::unique_ptr<VariableList> Members ;
    std::unique_ptr<FunctionList> FuncMembers;

    StructDeclarationStatement() = default;
    StructDeclarationStatement(unique_ptr<IdentifierExpr> Name,
                               unique_ptr<VariableList> Members,
                               unique_ptr<FunctionList> FuncMembers)
            : Name{move(Name)},
              Members{move(Members)},
              FuncMembers{move(FuncMembers)}
    {}
    ~StructDeclarationStatement() {}
};

class TypedefStatement: public Statement
{
public:
    std::unique_ptr<IdentifierExpr> LHS;
    std::unique_ptr<IdentifierExpr> RHS;

    TypedefStatement() = default;
    TypedefStatement(unique_ptr<IdentifierExpr> LHS, unique_ptr<IdentifierExpr> RHS)
            : LHS{move(LHS)},
              RHS{move(RHS)}
    {
    }
    ~TypedefStatement() {}
};

class IfStatement : public Statement
{
public:
    std::unique_ptr<Expression> Condition;
    std::unique_ptr<StatementList> TrueBlock ;
    std::unique_ptr<StatementList> FalseBlock ;

    IfStatement() = default;
    IfStatement(unique_ptr<Expression> Condition,
                unique_ptr<StatementList> TrueBlock,
                unique_ptr<StatementList> FalseBlock)
            : Condition{move(Condition)},
              TrueBlock{move(TrueBlock)},
              FalseBlock{move(FalseBlock)}
    {
    }
    ~IfStatement() {}
};

class WhileStatement : public Statement
{
public:
    std::unique_ptr<Expression> Condition;
    std::unique_ptr<StatementList> Block;

    WhileStatement() = default;
    WhileStatement(unique_ptr<Expression> Condition,
                   unique_ptr<StatementList> Block)
            : Condition{move(Condition)},
              Block{move(Block)}
    {
    }
    ~WhileStatement() {}
};

class BreakStatement : public Statement
{
public:
    BreakStatement() = default;
};

class ContinueStatement : public Statement
{
public:
    ContinueStatement() = default;
};

class NameSpaceStatement : public Statement
{
public:
    std::unique_ptr<IdentifierExpr> Name;
    std::unique_ptr<StatementList> Block;

    NameSpaceStatement() = default;
    NameSpaceStatement(unique_ptr<IdentifierExpr> Name,
                       unique_ptr<StatementList> Block)
            : Name{move(Name)},
              Block{move(Block)}
    {
    }
    ~NameSpaceStatement() {}
};

class UseStatement : public Statement
{
public:
    std::unique_ptr<IdentifierExpr> Name;

    UseStatement() = default;
    UseStatement(unique_ptr<IdentifierExpr> Name)
            : Name{move(Name)}
    {
    }
    ~UseStatement() {}
};

class ImportStatement : public Statement
{
public:
    std::unique_ptr<Expression> Name;

    ImportStatement() = default;
    ImportStatement(unique_ptr<Expression> Name)
            : Name{move(Name)}
    {
    }
    ~ImportStatement() {}
};

class FromStatement : public Statement
{
public:
    std::unique_ptr<Expression> FromName;
    std::unique_ptr<Expression> ImportName;

    FromStatement() = default;
    FromStatement(unique_ptr<Expression> FromName,
                  unique_ptr<Expression> ImportName)
            : FromName{move(FromName)},
              ImportName{move(ImportName)}
    {
    }
    ~FromStatement() {}
};

class ExportStatement : public Statement
{
public:
    std::unique_ptr<Expression> Name;

    ExportStatement() = default;
    ExportStatement(unique_ptr<Expression> Name)
            : Name{move(Name)}
    {
    }
    ~ExportStatement() {}
};



#endif