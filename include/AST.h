#ifndef __AST_H__
#define __AST_H__

#include <llvm/IR/Value.h>
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
using std::shared_ptr;
using std::move;

typedef std::vector<std::shared_ptr<Statement>> StatementList;
typedef std::vector<std::shared_ptr<Expression>> ExpressionList;
typedef std::vector<std::shared_ptr<VariableDeclarationStatement>> VariableList;
typedef std::vector<std::shared_ptr<FunctionDeclarationStatement>> FunctionList;

class ASTNode
{
public:
    ASTNode() {}
    virtual ~ASTNode() {}
    virtual void print()
    {
        cout << "ASTNode" << endl;
    }
    virtual llvm::Value *codeGen()
    {
        return (llvm::Value *)0;
    }
};

class Statement : public ASTNode
{
public:
    Statement() {}
    virtual ~Statement() {}
};

class Expression : public ASTNode
{
public:
    Expression() {}
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
    CONDITION
};

class SingleOperatorExpr : public Expression
{
public:
    SingleOperator Type;
    std::shared_ptr<Expression> Expr;

    SingleOperatorExpr() {}
    SingleOperatorExpr(shared_ptr<Expression> &_Expr, SingleOperator _Type)
        : Expr{ move(_Expr) } ,
          Type(_Type) {
    }
    ~SingleOperatorExpr() {}
};

class BinaryOperatorExpr : public Expression
{
public:
    BinaryOperator Type;
    std::shared_ptr<Expression> LHS;
    std::shared_ptr<Expression> RHS;

    BinaryOperatorExpr() {}
    BinaryOperatorExpr(shared_ptr<Expression>& _LHS, shared_ptr<Expression>& _RHS, BinaryOperator _Type)
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
    std::shared_ptr<Expression> LHS;
    std::shared_ptr<Expression> MHS;
    std::shared_ptr<Expression> RHS;

    ThreeOperatorExpr() {}
    ThreeOperatorExpr(shared_ptr<Expression> &_LHS, shared_ptr<Expression> &_MHS, shared_ptr<Expression> &_RHS, ThreeOperator _Type)
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
    std::shared_ptr<IdentifierExpr> FunctionName;
    std::shared_ptr<ExpressionList> Args = std::make_shared<ExpressionList>();

    FunctionCallExpr() {}
    FunctionCallExpr(shared_ptr<IdentifierExpr> &_FunctionName)
        : FunctionName{move(_FunctionName)} {
    }
    FunctionCallExpr(shared_ptr<IdentifierExpr> & _FunctionName, shared_ptr<ExpressionList> & _Args)
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
    std::shared_ptr<IdentifierExpr> VariableType;
    std::shared_ptr<IdentifierExpr> VariableName;
    
    SingleVariableDeclarationStatement() {}
    SingleVariableDeclarationStatement(shared_ptr<IdentifierExpr>& _VariableType, shared_ptr<IdentifierExpr>& _VariableName)
        : VariableType{ move(_VariableType) } ,
          VariableName{ move(_VariableName) } {
    }
    ~SingleVariableDeclarationStatement() {}
};

class ArrayDeclarationStatement : public VariableDeclarationStatement
{
public:
    std::shared_ptr<IdentifierExpr> ArrayName;
    std::shared_ptr<IntegerExpr> ArraySize;

    ArrayDeclarationStatement() {}
    ArrayDeclarationStatement(shared_ptr<IdentifierExpr> &_ArrayName, shared_ptr<IntegerExpr> &_ArraySize)
        : ArrayName{move(_ArrayName)},
          ArraySize{move(_ArraySize)}{
    }
    ~ArrayDeclarationStatement() {}
};

class AssignmentStatement : public Statement
{
public:
    std::shared_ptr<Expression> LHS;
    std::shared_ptr<Expression> RHS;

    AssignmentStatement() {}
    AssignmentStatement(shared_ptr<Expression>& _LHS, shared_ptr<Expression>& _RHS)
        : LHS{ move(_LHS) } ,
          RHS{ move(_RHS) } {
    }
    ~AssignmentStatement() {} 
};


class FunctionDeclarationStatement : public Statement
{
public:
    std::shared_ptr<IdentifierExpr> ReturnType;
    std::shared_ptr<IdentifierExpr> FunctionName;
    std::shared_ptr<VariableList> Args = std::make_shared<VariableList>();
    std::shared_ptr<StatementList> Content = std::make_shared<StatementList>();

    FunctionDeclarationStatement() {}
    FunctionDeclarationStatement(shared_ptr<IdentifierExpr> &_ReturnType,
                                 shared_ptr<IdentifierExpr> &_FunctionName,
                                 shared_ptr<VariableList> &_Args,
                                 shared_ptr<StatementList> &_Content)
        : ReturnType{move(_ReturnType)},
          FunctionName{move(_FunctionName)},
          Args{move(_Args)},
          Content{move(_Content)} {
    }
};

class StructDeclarationStatement : public Statement
{
public:
    std::shared_ptr<IdentifierExpr> Name;
    std::shared_ptr<VariableList> Members = std::make_shared<VariableList>();
    std::shared_ptr<FunctionList> FuncMembers = std::make_shared<FunctionList>();

    StructDeclarationStatement() {}
    StructDeclarationStatement(shared_ptr<IdentifierExpr> &_Name,
                               shared_ptr<VariableList> &_Members,
                               shared_ptr<FunctionList> &_FuncMembers) 
        : Name{move(_Name)},
          Members{move(_Members)},
          FuncMembers{move(_FuncMembers)}                           
    {}
    ~StructDeclarationStatement() {}
};

class TypedefStatement: public Statement
{
public:
    std::shared_ptr<IdentifierExpr> LHS;
    std::shared_ptr<IdentifierExpr> RHS;

    TypedefStatement() {}
    TypedefStatement(shared_ptr<IdentifierExpr> &_LHS, shared_ptr<IdentifierExpr> &_RHS)
        : LHS{move(_LHS)},
          RHS{move(_RHS)}
    {
    }
    ~TypedefStatement() {}
};

class IfStatement : public Statement
{
public:
    std::shared_ptr<Expression> Condition;
    std::shared_ptr<StatementList> TrueBlock = std::make_shared<StatementList>();
    std::shared_ptr<StatementList> FalseBlock = std::make_shared<StatementList>();

    IfStatement() {}
    IfStatement(shared_ptr<Expression> &_Condition,
                shared_ptr<StatementList> &_TrueBlock,
                shared_ptr<StatementList> &_FalseBlock)
        : Condition{move(_Condition)},
          TrueBlock{move(_TrueBlock)},
          FalseBlock{move(_FalseBlock)}
    {
    }
    ~IfStatement() {}
};

class WhileStatement : public Statement
{
public:
    std::shared_ptr<Expression> Condition;
    std::shared_ptr<StatementList> Block = std::make_shared<StatementList>();

    WhileStatement() {}
    WhileStatement(shared_ptr<Expression> &_Condition,
                   shared_ptr<StatementList> &_Block)
        : Condition{move(_Condition)},
          Block{move(_Block)}
    {
    }
    ~WhileStatement() {}
};

class BreakStatement : public Statement
{
public:
    BreakStatement() {}
};

class ContinueStatement : public Statement
{
public:
    ContinueStatement() {}
};

class NameSpaceStatement : public Statement
{
public:
    std::shared_ptr<IdentifierExpr> Name;
    std::shared_ptr<StatementList> Block = std::make_shared<StatementList>();

    NameSpaceStatement() {}
    NameSpaceStatement(shared_ptr<IdentifierExpr> &_Name,
                       shared_ptr<StatementList> &_Block)
        : Name{move(_Name)},
          Block{move(_Block)}
    {
    }
    ~NameSpaceStatement() {}
};

class UseStatement : public Statement
{
public:
    std::shared_ptr<IdentifierExpr> Name;

    UseStatement() {}
    UseStatement(shared_ptr<IdentifierExpr> &_Name)
        : Name{move(_Name)}
    {
    }
    ~UseStatement() {}
};

class ImportStatement : public Statement
{
public:
    std::shared_ptr<Expression> Name;

    ImportStatement() {}
    ImportStatement(shared_ptr<Expression> &_Name)
        : Name{move(_Name)}
    {
    }
    ~ImportStatement() {}
};

class FromStatement : public Statement
{
public:
    std::shared_ptr<Expression> FromName;
    std::shared_ptr<Expression> ImportName;

    FromStatement() {}
    FromStatement(shared_ptr<Expression> &_FromName,
                  shared_ptr<Expression> &_ImportName)
        : FromName{move(_FromName)},
          ImportName{move(_ImportName)}
    {
    }
    ~FromStatement() {}
};

class ExportStatement : public Statement
{
public:
    std::shared_ptr<Expression> Name;

    ExportStatement() {}
    ExportStatement(shared_ptr<Expression> &_Name)
        : Name{move(_Name)}
    {
    }
    ~ExportStatement() {}
};



#endif