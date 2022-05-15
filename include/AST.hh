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

namespace rmmc
{

    class Statement;
    class Expression;
    class VariableDeclarationStatement;
    class FunctionDeclarationStatement;
    class CodeGenBlock;
    class CodeGenContext;

    typedef std::vector<std::shared_ptr<Statement>> StatementList;
    typedef std::vector<std::shared_ptr<Expression>> ExpressionList;
    typedef std::vector<std::shared_ptr<VariableDeclarationStatement>> VariableList;
    typedef std::vector<std::shared_ptr<FunctionDeclarationStatement>> FunctionList;

    class ASTNode
    {
    protected:
        location loc;

    public:
        virtual ~ASTNode() {}

        virtual void print() = 0;
        virtual std::string toXML() = 0;
        virtual llvm::Value *codeGen(CodeGenContext &context) = 0;
    };

    class Statement : public ASTNode
    {
    public:
        virtual ~Statement() {}

        virtual void print() =0;
        virtual std::string toXML() =0;
        virtual llvm::Value *codeGen(CodeGenContext &context) =0;
    };

    class Expression : public ASTNode
    {
    public:
        virtual ~Expression() {}

        virtual void print() =0;
        virtual std::string toXML() =0;
        virtual llvm::Value *codeGen(CodeGenContext &context) =0;
    };

    /***
     * Constant Value : Double Integer UnsignedInteger Boolean
     *
     */
    class DoubleExpr : public Expression
    {
        double Value;

    public:
        DoubleExpr(double _value, location _loc) : Value(_value)
        {
            loc = _loc;
        }
        virtual ~DoubleExpr() {}

        virtual void print() override
        {
            std::cout << "Generate constant double = " << Value << std::endl;
        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;

        double getValue() const
        {
            return this->Value;
        }
    };

    class IntegerExpr : public Expression
    {
        long long Value;

    public:
        IntegerExpr(long long _value, location _loc) : Value(_value)
        {
            loc = _loc;
        }
        virtual ~IntegerExpr() {}

        virtual void print() override
        {
            std::cout << "Generate constant integer = " << Value << std::endl;
        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;

        long long getValue() const
        {
            return this->Value;
        }
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
        bool Value;

    public:
        BooleanExpr(bool _value, location _loc) : Value(_value)
        {
            loc = _loc;
        }
        virtual ~BooleanExpr() {}

        virtual void print() override
        {
        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;

        bool getValue() const
        {
            return this->Value;
        }
    };

    class StringExpr : public Expression
    {
        std::string Value;

    public:
        StringExpr(std::string _value, location _loc) : Value(_value)
        {
            loc = _loc;
        }
        virtual ~StringExpr() {}

        virtual void print() override
        {
            std::cout << "Generate constant string = " << Value << std::endl;
        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;

        std::string getValue() const
        {
            return this->Value;
        }
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
        std::string Name;

    public:
        IdentifierExpr(std::string _name, location _loc) : Name(_name)
        {
            loc = _loc;
        }
        virtual ~IdentifierExpr() {}

        virtual void print() override
        {
            std::cout << "Generate identifier "
                      << Name << " "
                      << std::endl;
        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;

        std::string getName() const
        {
            return this->Name;
        }
    };

    enum BinaryOperator
    {
        SCOPE,        //::
        ARRAY_INDEX,  //[]
        STRUCT_REF,   //.
        STRUCT_DEREF, //->
        AS,           // as
        ADD,
        SUB,
        MUL,
        DIV,
        MOD, //%
        LEFT_SHIFT,
        RIGHT_SHIFT,
        LT,          //<
        ELT,         //<=
        GT,          //>
        EGT,         //>=
        E,           //==
        NE,          //!=
        AND,         //&
        XOR,         //^
        OR,          //|
        LOGICAL_AND, //&&
        LOGICAL_OR,  //||
    };

    enum SingleOperator
    {
        LOGICAL_NOT, //
        BITWISE_NOT, //~
        INDIRECTION, //*
        ADDRESS_OF,  //&
        MOVE,        // move
    };

    enum ThreeOperator
    {
        CONDITION //? : ;
    };

    class SingleOperatorExpr : public Expression
    {
        SingleOperator Type;
        std::shared_ptr<Expression> Expr = nullptr;

    public:
        SingleOperatorExpr(std::shared_ptr<Expression> _Expr, SingleOperator _Type, location _loc)
            : Type(_Type),
              Expr(std::move(_Expr))
        {
            loc = _loc;
        }
        virtual ~SingleOperatorExpr() {}

        virtual void print() override
        {
            std::cout << "Generate single operator "
                      << Type
                      << std::endl;
        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class BinaryOperatorExpr : public Expression
    {
        BinaryOperator Type;
        std::shared_ptr<Expression> LHS = nullptr;
        std::shared_ptr<Expression> RHS = nullptr;

    public:
        BinaryOperatorExpr(std::shared_ptr<Expression> _LHS, std::shared_ptr<Expression> _RHS, BinaryOperator _Type, location _loc)
            : Type(_Type),
              LHS{std::move(_LHS)},
              RHS{std::move(_RHS)}
        {
            loc = _loc;
        }
        virtual ~BinaryOperatorExpr() {}

        virtual void print() override
        {
            std::cout << "Generate binary operator "
                      << Type
                      << std::endl;
        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class ThreeOperatorExpr : public Expression
    {
        ThreeOperator Type;
        std::shared_ptr<Expression> LHS = nullptr;
        std::shared_ptr<Expression> MHS = nullptr;
        std::shared_ptr<Expression> RHS = nullptr;

    public:
        ThreeOperatorExpr(std::shared_ptr<Expression> _LHS, std::shared_ptr<Expression> _MHS, std::shared_ptr<Expression> _RHS, ThreeOperator _Type, location _loc)
            : Type(_Type),
              LHS{std::move(_LHS)},
              MHS{std::move(_MHS)},
              RHS{std::move(_RHS)}
        {
            loc = _loc;
        }
        virtual ~ThreeOperatorExpr() {}

        virtual void print() override{

        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class FunctionCallExpr : public Expression
    {
    public:
        std::shared_ptr<IdentifierExpr> FunctionName = nullptr;
        std::shared_ptr<ExpressionList> Args = nullptr;

        FunctionCallExpr(std::shared_ptr<IdentifierExpr> _FunctionName, location _loc)
            : FunctionName{std::move(_FunctionName)}
        {
            loc = _loc;
        }
        FunctionCallExpr(std::shared_ptr<IdentifierExpr> _FunctionName, std::shared_ptr<ExpressionList> _Args, location _loc)
            : FunctionName{std::move(_FunctionName)},
              Args{std::move(_Args)}
        {
            loc = _loc;
        }
        virtual ~FunctionCallExpr() {}

        virtual void print() override
        {
            std::cout << "Generate functin call :"
                      << FunctionName->getName() << " "
                      << std::endl;
        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class AssignmentExpression : public Expression
    {
    public:
        std::shared_ptr<Expression> LHS = nullptr;
        std::shared_ptr<Expression> RHS = nullptr;

        AssignmentExpression(std::shared_ptr<Expression> _LHS,
                             std::shared_ptr<Expression> _RHS,
                             location _loc)
            : LHS{std::move(_LHS)},
              RHS{std::move(_RHS)}
        {
            loc = _loc;
        }
        virtual ~AssignmentExpression() {}

        virtual void print() override
        {
        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    /***
     * Statement
     *
     */

    class VariableDeclarationStatement : public Statement
    {
    public:
        enum DeclareType
        {
            MUTABLE,
            NOT_MUTABLE
        };
        DeclareType dType;

        virtual std::shared_ptr<IdentifierExpr> getType() =0;
        virtual IdentifierExpr getName() =0;

        virtual ~VariableDeclarationStatement() {}
        virtual void print() =0;
        virtual std::string toXML() =0;
        virtual llvm::Value *codeGen(CodeGenContext &context) =0;
    };

    class SingleVariableDeclarationStatement : public VariableDeclarationStatement
    {
        std::shared_ptr<IdentifierExpr> VariableType = nullptr;
        std::shared_ptr<IdentifierExpr> VariableName = nullptr;

    public:
        SingleVariableDeclarationStatement(std::shared_ptr<IdentifierExpr> _VariableType,
                                           std::shared_ptr<IdentifierExpr> _VariableName,
                                           location _loc,
                                           DeclareType _dType)
            : VariableType{std::move(_VariableType)},
              VariableName{std::move(_VariableName)}
        {
            loc = _loc;
            dType = _dType;
        }
        virtual ~SingleVariableDeclarationStatement() {}

        virtual std::shared_ptr<IdentifierExpr> getType()
        {
            return VariableType;
        }
        virtual IdentifierExpr getName()
        {
            return (*VariableName);
        }

        virtual void print() override
        {
            std::cout << "Generating single varible declaration: "
                      << this->dType << " "
                      << this->VariableType->getName() << " "
                      << this->VariableName->getName() << std::endl;
        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class ArrayDeclarationStatement : public VariableDeclarationStatement
    {
        std::shared_ptr<IdentifierExpr> ArrayType = nullptr;
        std::shared_ptr<IdentifierExpr> ArrayName = nullptr;
        std::shared_ptr<IntegerExpr> ArraySize = nullptr;

        ArrayDeclarationStatement(std::shared_ptr<IdentifierExpr> _ArrayType,
                                  std::shared_ptr<IdentifierExpr> _ArrayName,
                                  std::shared_ptr<IntegerExpr> _ArraySize,
                                  location _loc,
                                  DeclareType _dType)
            : ArrayType{std::move(_ArrayType)},
              ArrayName{std::move(_ArrayName)},
              ArraySize{std::move(_ArraySize)}
        {
            loc = _loc;
            dType = _dType;
        }
        virtual ~ArrayDeclarationStatement() {}

        virtual std::shared_ptr<IdentifierExpr> getType()
        {
            return ArrayType;
        }
        virtual IdentifierExpr getName()
        {
            return (*ArrayName);
        }

        virtual void print() override
        {
            std::cout << "Generating array varible declaration: "
                      << this->dType << " "
                      << this->ArrayType->getName() << " "
                      << this->ArrayName->getName() << " "
                      << this->ArraySize->getValue()
                      << std::endl;
        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class StructDeclarationStatement : public Statement
    {
    public:
        std::shared_ptr<IdentifierExpr> Name = nullptr;
        std::shared_ptr<VariableList> Members = nullptr;
        std::shared_ptr<FunctionList> FuncMembers = nullptr;

        StructDeclarationStatement(std::shared_ptr<IdentifierExpr> Name,
                                   std::shared_ptr<VariableList> Members,
                                   std::shared_ptr<FunctionList> FuncMembers,
                                   location _loc)
            : Name{std::move(Name)},
              Members{std::move(Members)},
              FuncMembers{std::move(FuncMembers)}
        {
            loc = _loc;
        }
        virtual ~StructDeclarationStatement() {}

        virtual void print() override
        {
        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class BlockStatement : public Statement
    {
    public:
        std::shared_ptr<StatementList> Content = nullptr;
        BlockStatement(std::shared_ptr<StatementList> _Content)
            : Content(std::move(_Content)) {}
        virtual ~BlockStatement() {}

        virtual void print(){

        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class ReturnStatement : public Statement
    {
    public:
        std::shared_ptr<Expression> ReturnValue = nullptr;
        ReturnStatement(std::shared_ptr<Expression> _ReturnValue, location _loc)
            : ReturnValue(std::move(_ReturnValue))
        {
            loc = _loc;
        }
        virtual ~ReturnStatement() {}

        virtual void print() override
        {
            std::cout << "Generate Return"
                      << std::endl;
        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class FunctionDeclarationStatement : public Statement
    {
        std::shared_ptr<IdentifierExpr> ReturnType = nullptr;
        std::shared_ptr<IdentifierExpr> FunctionName = nullptr;
        std::shared_ptr<VariableList> Args = nullptr;
        std::shared_ptr<BlockStatement> Content = nullptr;
        std::shared_ptr<ReturnStatement> Return = nullptr;

    public:
        FunctionDeclarationStatement(std::shared_ptr<IdentifierExpr> _ReturnType,
                                     std::shared_ptr<IdentifierExpr> _FunctionName,
                                     std::shared_ptr<VariableList> _Args,
                                     std::shared_ptr<BlockStatement> _Content,
                                     std::shared_ptr<ReturnStatement> _Return,
                                     location _loc)
            : ReturnType{std::move(_ReturnType)},
              FunctionName{std::move(_FunctionName)},
              Args{std::move(_Args)},
              Content{std::move(_Content)},
              Return{std::move(_Return)}
        {
            loc = _loc;
        }

        virtual void print() override
        {
            std::cout << "Function Decalration :"
                      << ReturnType->getName() << "  "
                      << FunctionName->getName() << "  ";
            for (auto &perArg : *Args)
            {
                perArg->print();
            }
            std::cout << std::endl;
        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class TypedefStatement : public Statement
    {
        std::shared_ptr<IdentifierExpr> LHS = nullptr;
        std::shared_ptr<IdentifierExpr> RHS = nullptr;

    public:
        TypedefStatement(std::shared_ptr<IdentifierExpr> LHS, std::shared_ptr<IdentifierExpr> RHS, location _loc)
            : LHS{std::move(LHS)},
              RHS{std::move(RHS)}
        {
            loc = _loc;
        }
        virtual ~TypedefStatement() {}

        virtual void print() override{

        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class IfStatement : public Statement
    {
        std::shared_ptr<Expression> Condition = nullptr;
        std::shared_ptr<StatementList> TrueBlock = nullptr;
        std::shared_ptr<StatementList> FalseBlock = nullptr;

    public:
        IfStatement(std::shared_ptr<Expression> Condition,
                    std::shared_ptr<StatementList> TrueBlock,
                    std::shared_ptr<StatementList> FalseBlock,
                    location _loc)
            : Condition{std::move(Condition)},
              TrueBlock{std::move(TrueBlock)},
              FalseBlock{std::move(FalseBlock)}
        {
            loc = _loc;
        }
        virtual ~IfStatement() {}

        virtual void print() override{

        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override; 
    };

    class WhileStatement : public Statement
    {
        std::shared_ptr<Expression> Condition = nullptr;
        std::shared_ptr<StatementList> Block = nullptr;

    public:
        WhileStatement(std::shared_ptr<Expression> Condition,
                       std::shared_ptr<StatementList> Block,
                       location _loc)
            : Condition{std::move(Condition)},
              Block{std::move(Block)}
        {
            loc = _loc;
        }
        virtual ~WhileStatement() {}

        virtual void print() override{

        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class BreakStatement : public Statement
    {
    public:
        BreakStatement(location _loc)
        {
            loc = _loc;
        }
        virtual ~BreakStatement() {}

        virtual void print() override
        {
        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class ContinueStatement : public Statement
    {
    public:
        ContinueStatement(location _loc)
        {
            loc = _loc;
        }
        virtual ~ContinueStatement() {}

        virtual void print() override{

        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class NameSpaceStatement : public Statement
    {
        std::shared_ptr<IdentifierExpr> Name = nullptr;
        std::shared_ptr<StatementList> Block = nullptr;

    public:
        NameSpaceStatement(std::shared_ptr<IdentifierExpr> Name,
                           std::shared_ptr<StatementList> Block,
                           location _loc)
            : Name{std::move(Name)},
              Block{std::move(Block)}
        {
            loc = _loc;
        }
        ~NameSpaceStatement() {}

        virtual void print() override{

        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class UseStatement : public Statement
    {
        std::shared_ptr<IdentifierExpr> Name = nullptr;

    public:
        UseStatement(std::shared_ptr<IdentifierExpr> Name, location _loc)
            : Name{std::move(Name)}
        {
            loc = _loc;
        }
        ~UseStatement() {}

        virtual void print() override{

        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class ImportStatement : public Statement
    {
        std::shared_ptr<Expression> Name = nullptr;

    public:
        ImportStatement(std::shared_ptr<Expression> Name, location _loc)
            : Name{std::move(Name)}
        {
            loc = _loc;
        }
        ~ImportStatement() {}

        virtual void print() override{

        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class FromStatement : public Statement
    {
        std::shared_ptr<Expression> FromName = nullptr;
        std::shared_ptr<Expression> ImportName = nullptr;

    public:
        FromStatement(std::shared_ptr<Expression> FromName,
                      std::shared_ptr<Expression> ImportName,
                      location _loc)
            : FromName{std::move(FromName)},
              ImportName{std::move(ImportName)}
        {
            loc = _loc;
        }
        ~FromStatement() {}

        virtual void print() override
        {
        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class ExportStatement : public Statement
    {
        std::shared_ptr<Expression> Name = nullptr;

    public:
        ExportStatement(std::shared_ptr<Expression> Name, location _loc)
            : Name{std::move(Name)}
        {
            loc = _loc;
        }
        ~ExportStatement() {}

        virtual void print() override{

        }
        virtual std::string toXML() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };
}

#endif
