#ifndef __AST_H__
#define __AST_H__

#include <llvm/IR/Value.h>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <cstring>

typedef std::vector<std::shared_ptr<Statment>> StatementList;
typedef std::vector<std::shared_ptr<Expression>> ExpressionList;
typedef std::vector<std::shared_ptr<VariableDeclarationStatement>> VariableList;

class ASTNode
{
public:
    ASTNode() {}
    virtual ~ASTNode() {}
    virtual print()
    {
        std::cout << "ASTNode" << endl;
    }
    virtual llvm::Value *codeGen()
    {
        return (llvm::Value *)0;
    }
};

class Statment : public ASTNode
{
public:
    Statment() {}
};

class Expression : public ASTNode
{
public:
    Expression() {}
};

class DoubleExpr : public Expression
{
private:
    double Value;

public:
    DoubleExpr() {}
};

class LiteralExpr : public Expression
{
private:
    std::string Value;

public:
    LiteralExpr() {}
};

class IdentifierExpr : public Expression
{
private:
    int Type; // to-do
public:
    IdentifierExpr() {}
};

class BinaryOperatorExpr : public Expression
{
private:
    int Type; //+ - * /
    std::shared_ptr<ASTNode> LHS;
    std::shared_ptr<ASTNode> RHS;

public:
    BinaryOperatorExpr() {}
};

class AssignmentExpr : public Expression
{
private:
    std::shared_ptr<ASTNode> LHS;
    std::shared_ptr<ASTNode> RHS;

public:
    AssignmentExpr() {}
};

class FunctionCallExpr : public Expression
{
private:
    std::shared_ptr<IdentifierExpr> FunctionName;
    std::shared_ptr<ExpressionList> Args = std::make_shared<ExpressionList>();

public:
    FunctionCallExpr() {}
};

class VariableDeclarationStatement : public Statment
{
private:
    std::shared_ptr<IdentifierExpr> VariableType;
    std::shared_ptr<IdentifierExpr> VariableName;
    std::shared_ptr<ASTNode> VariableValue;

public:
    VariableDeclarationStatement() {}
};

class FunctionDeclarationStatement : public Statment
{
private:
    std::shared_ptr<IdentifierExpr> ReturnType;
    std::shared_ptr<IdentifierExpr> FunctionName;
    std::shared_ptr<VariableList> Args = std::make_shared<VariableList>();
    std::shared_ptr<StatementList> Content = std::make_shared<StatementList>();

public:
    FunctionDeclarationStatement() {}
};

class StructDeclarationStatement : public Statement
{
private:
    std::shared_ptr<IdentifierExpr> Name;
    std::shared_ptr<VariableList> Members = std::make_shared<VariableList>();

public:
    StructDeclarationStatement() {}
};

class IfStatement : public Statement
{
private:
    std::shared_ptr<ASTNode> Condition;
    std::shared_ptr<StatementList> TrueBlock = std::make_shared<StatementList>();
    std::shared_ptr<StatementList> FalseBlock = std::make_shared<StatementList>();

public:
    IfStatement() {}
};

// to-do
class ForStatement : public Statment
{
private:
public:
    ForStatement() {}
};

class WhileStatement : public Statement
{
private:
    std::shared_ptr<ASTNode> Condition;

public:
    WhileStatement() {}
};

#endif