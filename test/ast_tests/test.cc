//
// Created by Yuying on 2022/5/3.
//
#include "CodeGen.hh"
using namespace std;
using namespace rmmc;
using namespace llvm;
int main()
{
    cout << "Hello World" << endl;
    //<---------------Case1------------->
    location loc;
    shared_ptr<IdentifierExpr> ReturnType = make_shared<IdentifierExpr>("int", loc);
    shared_ptr<IdentifierExpr> FunctionName = make_shared<IdentifierExpr>("main", loc);
    // unique_ptr<VariableDeclarationStatement> arg1 = make_shared<VariableDeclarationStatement>();
    shared_ptr<VariableList> Args = make_shared<VariableList>();
    shared_ptr<Statement> st1 = make_shared<SingleVariableDeclarationStatement>(
        move(make_shared<IdentifierExpr>("int")),
        move(make_shared<IdentifierExpr>("a")),
        loc,
        VariableDeclarationStatement::MUTABLE);
    // unique_ptr<Statement> st2 = make_shared<AssignmentExpression>()
    shared_ptr<StatementList> contentList = make_shared<StatementList>();
    contentList->push_back(st1);
    shared_ptr<BlockStatement> Content = make_shared<BlockStatement>(move(contentList), loc);
    shared_ptr<ReturnStatement> Return = make_shared<ReturnStatement>(
        move(make_shared<IntegerExpr>(0, loc)),
        loc);
    shared_ptr<FunctionDeclarationStatement> main = make_shared<FunctionDeclarationStatement>(
        move(ReturnType),
        move(FunctionName),
        move(Args),
        move(Content),
        move(Return),
        loc);
    CodeGenContext code;
    code.CodeGen(move(main));
    code.theModule->dump();
    return 0;
}
