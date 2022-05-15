//
// Created by Yuying on 2022/5/3.
//
#include "CodeGen.hh"
using namespace std;
using namespace rmmc;
using namespace llvm;
int main()
{
    cout<<"Hello World"<<endl;
    //<---------------Case1------------->
    location loc;
    unique_ptr<IdentifierExpr> ReturnType = make_unique<IdentifierExpr>("int", loc);
    unique_ptr<IdentifierExpr> FunctionName = make_unique<IdentifierExpr>("main", loc);
    //unique_ptr<VariableDeclarationStatement> arg1 = make_unique<VariableDeclarationStatement>();
    unique_ptr<VariableList> Args = make_unique<VariableList>();
    unique_ptr<Statement> st1 = make_unique<SingleVariableDeclarationStatement>(
        move( make_unique<IdentifierExpr>("int") ),
        move( make_unique<IdentifierExpr>("a") ),
        loc,
        VariableDeclarationStatement::MUTABLE
    );
    //unique_ptr<Statement> st2 = make_unique<AssignmentExpression>()
    unique_ptr<StatementList> contentList = make_unique<StatementList>();
    contentList->push_back(st1);
    unique_ptr<BlockStatement> Content = make_unique<BlockStatement>(move(contentList), loc);
    unique_ptr<ReturnStatement> Return = make_unique<ReturnStatement>(
        move(make_unique<IntegerExpr>(0, loc)),
        loc
    );
    unique_ptr<FunctionDeclarationStatement> main= make_unique<FunctionDeclarationStatement>(
        move(ReturnType),
        move(FunctionName),
        move(Args),
        move(Content),
        move(Return),
        loc
    );
    CodeGenContext code;
    code.CodeGen(move(main));
    code.theModule->dump();
    return 0;
}

