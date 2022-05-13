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
#include "location.hh"
#include "CodeGen.hh"

namespace rmmc{

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
    location loc;
    virtual ~ASTNode();

    virtual void print() =0; 
    virtual void toXML() =0;
    virtual llvm::Value *codeGen(CodeGenContext &context) = 0;
};

class Statement : public ASTNode
{
public:
    virtual ~Statement() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context) ;
};

class Expression : public ASTNode
{
public:    
    virtual ~Expression() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context) ;
};

/***
 * Constant Value : Double Integer UnsignedInteger Boolean
 *
 */
class DoubleExpr : public Expression
{
public:
    double Value;

    DoubleExpr(double _value, location _loc): Value(_value){
        loc=_loc;
    }
    ~DoubleExpr() {}

    virtual void print(){
        std::cout<<"Generate constant double = "<<Value<<std::endl;
    }
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class IntegerExpr : public Expression
{
public:
    long long Value;

    IntegerExpr(long long _value, location _loc): Value(_value) {
        loc=_loc;
    }
    ~IntegerExpr() {}

    virtual void print(){
        std::cout << "Generate constant integer = " << Value << std::endl;
    }
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

// class UnsignedIntegerExpr : public Expression
// {
// public:
//     unsigned long long Value;

//     UnsignedIntegerExpr(unsigned long long _value, location _loc): Value(_value) {
//         loc=_loc;
//     }
//     ~UnsignedIntegerExpr() {}

//     virtual void print();
//     virtual void toXML();
//     virtual llvm::Value *codeGen();
// };
//<--------------To-Do------------------>
class BooleanExpr : public Expression
{
public:
    bool Value;

    BooleanExpr(bool _value, location _loc): Value(_value) {
        loc=_loc;
    }
    ~BooleanExpr() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen();
};

class StringExpr : public Expression
{
public:
    std::string Value;

    StringExpr(std::string _value, location _loc) : Value(_value) {
        loc=_loc;
    }
    ~StringExpr() {}

    virtual void print(){
        std::cout << "Generate constant string = " << Value << std::endl;
    }
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

// class CharExpr : public Expression
// {
// public:
//     char Value;

//     CharExpr(char _value, location _loc) : Value(_value) {
//         loc=_loc;
//     }
//     ~CharExpr() {}

//     virtual void print();
//     virtual void toXML();
//     virtual llvm::Value *codeGen();
// };

class IdentifierExpr : public Expression
{
public:
    std::string Name;

    IdentifierExpr(std::string _name, location _loc): Name(_name) {
        loc=_loc;
    }

    virtual void print(){
        std::cout<<"Generate identifier "
                 <<Name<<" "
                 <<std::endl;
    }
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
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

    SingleOperatorExpr(std::unique_ptr<Expression> _Expr, SingleOperator _Type, location _loc)
            : Expr(std::move(_Expr)) ,
              Type(_Type) {
        loc=_loc;
    }
    ~SingleOperatorExpr() {}

    virtual void print(){
        std::cout<<"Generate single operator "
                 <<Type
                 <<std::endl;
    }
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class BinaryOperatorExpr : public Expression
{
public:
    BinaryOperator Type;
    std::unique_ptr<Expression> LHS;
    std::unique_ptr<Expression> RHS;

    BinaryOperatorExpr(std::unique_ptr<Expression> _LHS, std::unique_ptr<Expression> _RHS, BinaryOperator _Type, location _loc)
            : LHS{ std::move(_LHS) } ,
              RHS{ std::move(_RHS) } ,
              Type(_Type){
        loc=_loc;
    }
    ~BinaryOperatorExpr() {}

    virtual void print(){
        std::cout << "Generate binary operator "
                  << Type
                  << std::endl;
    }
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class ThreeOperatorExpr : public Expression
{
public:
    ThreeOperator Type;
    std::unique_ptr<Expression> LHS;
    std::unique_ptr<Expression> MHS;
    std::unique_ptr<Expression> RHS;

    ThreeOperatorExpr(std::unique_ptr<Expression> _LHS, std::unique_ptr<Expression> _MHS, std::unique_ptr<Expression> _RHS, ThreeOperator _Type, location _loc)
            : LHS{std::move(_LHS)},
              MHS{std::move(_MHS)},
              RHS{std::move(_RHS)},
              Type(_Type){
        loc=_loc;
    }
    ~ThreeOperatorExpr() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class FunctionCallExpr : public Expression
{
public:
    std::unique_ptr<IdentifierExpr> FunctionName;
    std::unique_ptr<ExpressionList> Args ;

    FunctionCallExpr(std::unique_ptr<IdentifierExpr> _FunctionName, location _loc)
            : FunctionName{std::move(_FunctionName)} {
        loc=_loc;
    }
    FunctionCallExpr(std::unique_ptr<IdentifierExpr> _FunctionName, std::unique_ptr<ExpressionList> _Args, location _loc)
            : FunctionName{std::move(_FunctionName)},
              Args{std::move(_Args)} {
        loc=_loc;
    }
    ~FunctionCallExpr() {}

    virtual void print(){
        std::cout<<"Generate functin call :"
                 <<FunctionName->Name<<" "
                 <<std::endl;
    }
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class AssignmentExpression : public Expression
{
public:
    std::unique_ptr<Expression> LHS;
    std::unique_ptr<Expression> RHS;

    AssignmentExpression(std::unique_ptr<Expression> _LHS,
                         std::unique_ptr<Expression> _RHS,
                         location _loc)
            : LHS{ std::move(_LHS) } ,
              RHS{ std::move(_RHS) } {
        loc=_loc;
    }
    ~AssignmentExpression() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

/***
 * Statement
 *
 */


class VariableDeclarationStatement : public Statement
{
public:
    enum DeclareType{
        MUTABLE,
        NOT_MUTABLE
    };
    DeclareType dType;

    virtual IdentifierExpr getType();
    virtual IdentifierExpr getName();

    virtual ~VariableDeclarationStatement() {}
    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class SingleVariableDeclarationStatement : public VariableDeclarationStatement
{
public:
    std::unique_ptr<IdentifierExpr> VariableType;
    std::unique_ptr<IdentifierExpr> VariableName;

    SingleVariableDeclarationStatement(std::unique_ptr<IdentifierExpr> _VariableType,
                                       std::unique_ptr<IdentifierExpr> _VariableName, 
                                       location _loc,
                                       DeclareType _dType)
            : VariableType{ std::move(_VariableType) } ,
              VariableName{ std::move(_VariableName) } {
        loc=_loc;
        dType=_dType;
    }
    ~SingleVariableDeclarationStatement() {}

    virtual IdentifierExpr getType(){
        return (*VariableType);
    }
    virtual IdentifierExpr getName(){
        return (*VariableName);
    }

    virtual void print()
    {
        std::cout << "Generating single varible declaration: " 
        <<this->dType << " " 
        << this->VariableType->Name << " "
        << this->VariableName->Name << std::endl;
    }
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class ArrayDeclarationStatement : public VariableDeclarationStatement
{
public:
    std::unique_ptr<IdentifierExpr> ArrayType;
    std::unique_ptr<IdentifierExpr> ArrayName;
    std::unique_ptr<IntegerExpr> ArraySize;

    ArrayDeclarationStatement(std::unique_ptr<IdentifierExpr> _ArrayType, 
                              std::unique_ptr<IdentifierExpr> _ArrayName,
                              std::unique_ptr<IntegerExpr> _ArraySize,
                              location _loc,
                              DeclareType _dType)
        : ArrayType{std::move(_ArrayType)},
          ArrayName{std::move(_ArrayName)},
          ArraySize{std::move(_ArraySize)}{
        loc=_loc;
        dType=_dType;
    }
    ~ArrayDeclarationStatement() {}

    virtual IdentifierExpr getType(){
        return (*ArrayType);
    }
    virtual IdentifierExpr getName(){
        return (*ArrayName);
    }

    virtual void print(){
        std::cout << "Generating array varible declaration: "
                  << this->dType << " "
                  << this->ArrayType->Name << " "
                  << this->ArrayName->Name << " "
                  << this->ArraySize->Value
                  << std::endl;
    }   
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class StructDeclarationStatement : public Statement
{
public:
    std::unique_ptr<IdentifierExpr> Name;
    std::unique_ptr<VariableList> Members ;
    std::unique_ptr<FunctionList> FuncMembers;

    StructDeclarationStatement(std::unique_ptr<IdentifierExpr> Name,
                               std::unique_ptr<VariableList> Members,
                               std::unique_ptr<FunctionList> FuncMembers,
                               location _loc)
        : Name{std::move(Name)},
          Members{std::move(Members)},
          FuncMembers{std::move(FuncMembers)}{
        loc=_loc;
    }
    ~StructDeclarationStatement() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class BlockStatement : public Statement
{
public:
    std::unique_ptr<StatementList> Content;
    BlockStatement(std::unique_ptr<StatementList> _Content)
                : Content( std::move(_Content) ) {}
    ~BlockStatement() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class ReturnStatement : public Statement
{
public:
    std::unique_ptr<Expression> ReturnValue;
    ReturnStatement(std::unique_ptr<Expression> _ReturnValue, location _loc)
        : ReturnValue(std::move(_ReturnValue)) {
            loc=_loc;
    }
    ~ReturnStatement() {}

    virtual void print(){
        std::cout<<"Generate Return"
                 <<std::endl;
    }
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class FunctionDeclarationStatement : public Statement
{
public:
    std::unique_ptr<IdentifierExpr> ReturnType;
    std::unique_ptr<IdentifierExpr> FunctionName;
    std::unique_ptr<VariableList> Args;
    std::unique_ptr<BlockStatement> Content;
    std::unique_ptr<ReturnStatement> Return;

    FunctionDeclarationStatement(std::unique_ptr<IdentifierExpr> _ReturnType,
                                 std::unique_ptr<IdentifierExpr> _FunctionName,
                                 std::unique_ptr<VariableList> _Args,
                                 std::unique_ptr<BlockStatement> _Content,
                                 std::unique_ptr<ReturnStatement> _Return,
                                 location _loc)
            : ReturnType{std::move(_ReturnType)},
              FunctionName{std::move(_FunctionName)},
              Args{std::move(_Args)},
              Content{std::move(_Content)} 
              Return{std::move(_Return)}{
        loc=_loc;
    }

    virtual void print(){
        std::cout<<"Function Decalration :"
        <<ReturnType->Name<<"  "
        <<FunctionName->Name<<"  ";
        for(auto &perArg : *Args){
            perArg->print();
        }
        std::cout<<std::endl;
    }
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context) ;
};

class TypedefStatement: public Statement
{
public:
    std::unique_ptr<IdentifierExpr> LHS;
    std::unique_ptr<IdentifierExpr> RHS;

    TypedefStatement(std::unique_ptr<IdentifierExpr> LHS, std::unique_ptr<IdentifierExpr> RHS, location _loc)
        : LHS{std::move(LHS)},
          RHS{std::move(RHS)}{
        loc=_loc;
    }
    ~TypedefStatement() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class IfStatement : public Statement
{
public:
    std::unique_ptr<Expression> Condition;
    std::unique_ptr<StatementList> TrueBlock ;
    std::unique_ptr<StatementList> FalseBlock ;

    IfStatement(std::unique_ptr<Expression> Condition,
                std::unique_ptr<StatementList> TrueBlock,
                std::unique_ptr<StatementList> FalseBlock,
                location _loc)
        : Condition{std::move(Condition)},
          TrueBlock{std::move(TrueBlock)},
          FalseBlock{std::move(FalseBlock)}{
        loc=_loc;
    }
    ~IfStatement() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class WhileStatement : public Statement
{
public:
    std::unique_ptr<Expression> Condition;
    std::unique_ptr<StatementList> Block;

    WhileStatement(std::unique_ptr<Expression> Condition,
                   std::unique_ptr<StatementList> Block,
                   location _loc)
        : Condition{std::move(Condition)},
          Block{std::move(Block)}{
        loc=_loc;
    }
    ~WhileStatement() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class BreakStatement : public Statement
{
public:
    BreakStatement() = default;
    BreakStatement(location _loc){
        loc=_loc;
    }
    virtual ~BreakStatement() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class ContinueStatement : public Statement
{
public:
    ContinueStatement() = default;
    ContinueStatement(location _loc){
        loc=_loc;
    }
    virtual ~ContinueStatement() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class NameSpaceStatement : public Statement
{
public:
    std::unique_ptr<IdentifierExpr> Name;
    std::unique_ptr<StatementList> Block;

    NameSpaceStatement(std::unique_ptr<IdentifierExpr> Name,
                       std::unique_ptr<StatementList> Block,
                       location _loc)
        : Name{std::move(Name)},
          Block{std::move(Block)}{
        loc=_loc;
    }
    ~NameSpaceStatement() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class UseStatement : public Statement
{
public:
    std::unique_ptr<IdentifierExpr> Name;

    UseStatement(std::unique_ptr<IdentifierExpr> Name, location _loc)
        : Name{std::move(Name)}{
        loc=_loc;
    }
    ~UseStatement() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class ImportStatement : public Statement
{
public:
    std::unique_ptr<Expression> Name;

    ImportStatement(std::unique_ptr<Expression> Name, location _loc)
        : Name{std::move(Name)}{
        loc=_loc;
    }
    ~ImportStatement() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class FromStatement : public Statement
{
public:
    std::unique_ptr<Expression> FromName;
    std::unique_ptr<Expression> ImportName;

    FromStatement(std::unique_ptr<Expression> FromName,
                  std::unique_ptr<Expression> ImportName,
                  location _loc)
        : FromName{std::move(FromName)},
          ImportName{std::move(ImportName)}{
        loc=_loc;
    }
    ~FromStatement() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};

class ExportStatement : public Statement
{
public:
    std::unique_ptr<Expression> Name;

    ExportStatement(std::unique_ptr<Expression> Name, location _loc)
        : Name{std::move(Name)}{
        loc=_loc;
    }
    ~ExportStatement() {}

    virtual void print();
    virtual void toXML();
    virtual llvm::Value *codeGen(CodeGenContext &context);
};
}


#endif