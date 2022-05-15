#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/Support/raw_ostream.h>

#include <vector>
#include <cstdlib>

#include "AST.hh"
#include "CodeGen.hh"
#include "TypeSystem.hh"

typedef llvm::Type *TypePtr;
typedef llvm::ArrayType *ArrayTypePtr;
typedef llvm::FunctionType *FunctionTypePtr;
typedef llvm::Function *FunctionPtr;
typedef llvm::Value *ValuePtr;

// using namespace llvm;
using namespace rmmc;
using namespace llvm;

llvm::Value *rmmc::DoubleExpr::codeGen(CodeGenContext &context)
{
    this->print();
    return llvm::ConstantFP::get(llvm::Type::getDoubleTy(context.theContext), this->Value);
}

llvm::Value *rmmc::IntegerExpr::codeGen(CodeGenContext &context)
{
    this->print();
    return llvm::ConstantInt::get(llvm::Type::getInt64Ty(context.theContext), this->Value);
}

llvm::Value *rmmc::BooleanExpr::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::StringExpr::codeGen(CodeGenContext &context)
{
    return llvm::ConstantDataArray::getString(context.theContext, this->Value, true);
}

llvm::Value *rmmc::IdentifierExpr::codeGen(CodeGenContext &context)
{
    this->print();
    ValuePtr val = context.getSymbolTable(this->Name);
    if(val==nullptr){
        return nullptr;
    }
    return context.theBuilder.CreateLoad(val, false, "");
}


// To-Do
llvm::Value *rmmc::SingleOperatorExpr::codeGen(CodeGenContext &context)
{
    this->print();
    ValuePtr exp = this->Expr->codeGen(context);
    switch (Type)
    {
    case LOGICAL_NOT:
        return context.theBuilder.CreateNot(exp, "not");
    default:
        break;
    }
    return nullptr;
}
// To-Do
llvm::Value *rmmc::BinaryOperatorExpr::codeGen(CodeGenContext &context)
{
    this->print();
    ValuePtr lhs = this->LHS->codeGen(context);
    ValuePtr rhs = this->RHS->codeGen(context);
    switch (this->Type)
    {
    case ADD:
        return context.theBuilder.CreateFAdd(lhs, rhs, "addf");
    case SUB:
        return context.theBuilder.CreateFSub(lhs, rhs, "subf");
    case MUL:
        return context.theBuilder.CreateFMul(lhs, rhs, "mulf");
    case DIV:
        return context.theBuilder.CreateFDiv(lhs, rhs, "divf");
    case LT:
        return context.theBuilder.CreateFCmpOLT(lhs, rhs, "LTf");
    case ELT:
        return context.theBuilder.CreateFCmpOLE(lhs, rhs, "LEf");
    case GT:
        return context.theBuilder.CreateFCmpOGT(lhs, rhs, "GTf");
    case EGT:
        return context.theBuilder.CreateFCmpOGE(lhs, rhs, "GEf");
    case E:
        return context.theBuilder.CreateFCmpOEQ(lhs, rhs, "EQf");
    case NE:
        return context.theBuilder.CreateFCmpONE(lhs, rhs, "NEf");
    case AND:
        return context.theBuilder.CreateAnd(lhs, rhs, "and");
    case XOR:
        return context.theBuilder.CreateXor(lhs, rhs, "xor");
    case OR:
        return context.theBuilder.CreateOr(lhs, rhs, "or");
    default:
        break;
    }
    return nullptr;
}

llvm::Value *rmmc::ThreeOperatorExpr::codeGen(CodeGenContext &context)
{
    return nullptr;
}


llvm::Value *rmmc::FunctionCallExpr::codeGen(CodeGenContext &context)
{
    this->print();
    FunctionPtr callF = context.theModule->getFunction(this->FunctionName->getName());
    if(callF==nullptr){
        return nullptr;
    }else if(callF->arg_size()!=this->Args->size()){
        return nullptr;
    }else{
        ExpressionList::iterator it;
        std::vector<ValuePtr> callArgs;
        for(it=this->Args->begin();it!=this->Args->end();it++)
        {
            ValuePtr tmp = (*it)->codeGen(context);
            if(tmp==nullptr){
                return nullptr;
            }
            callArgs.push_back( tmp );
        }
        return context.theBuilder.CreateCall(callF, callArgs, "callF");
    }
}

llvm::Value *rmmc::AssignmentExpression::codeGen(CodeGenContext &context)
{
    return nullptr;
}



llvm::Value *rmmc::FunctionDeclarationStatement::codeGen(CodeGenContext &context)
{
    this->print();
    // Construct function params type
    std::vector<TypePtr> funcArgs;
    VariableList::iterator it;
    for (it = this->Args->begin(); it != this->Args->end(); it++)
    {
        funcArgs.push_back(getLLVMType((*it)->getType(), context));
    }
    // Construct function return type
    TypePtr retType = getLLVMType(ReturnType, context);
    // get function type and construct function
    FunctionTypePtr funcType = llvm::FunctionType::get(retType, funcArgs, false);
    FunctionPtr func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, this->FunctionName->getName().c_str(), context.theModule.get());
    // entry block
    BasicBlockPtr entryBlock = llvm::BasicBlock::Create(context.theContext, "entry", func, nullptr);
    context.theBuilder.SetInsertPoint(entryBlock);
    context.pushBlock(entryBlock);
    // store the params
    it = this->Args->begin();
    for (auto &perArg : func->args())
    {
        perArg.setName((*it)->getName().getName());
        // ValuePtr argAlloc = (*it)->codeGen(context);
        // context.theBuilder.CreateStore(&perArg, &perArg, false);
        context.setSymbolTable((*it)->getName().getName(), &perArg);
        context.setSymbolType((*it)->getName().getName(), (*it)->getType());
        it++;
    }
    // Generate the code of function content
    this->Content->codeGen(context);
    // Return Value
    ValuePtr returnVal=this->Return->codeGen(context);
    context.theBuilder.CreateRet(returnVal);
    // Pop Block
    context.popBlock();
    return nullptr;
}
/***
 *
 *
 */
llvm::Value *rmmc::SingleVariableDeclarationStatement::codeGen(CodeGenContext &context)
{
    this->print();
    TypePtr type = getLLVMType(this->VariableType, context);
    ValuePtr alloca = context.theBuilder.CreateAlloca(type);

    context.setSymbolTable(this->VariableName->getName(), alloca);
    context.setSymbolType(this->VariableName->getName(), this->VariableType);

    return alloca;
}

llvm::Value *rmmc::ArrayDeclarationStatement::codeGen(CodeGenContext &context)
{
    this->print();
    ArrayTypePtr type = llvm::ArrayType::get(getLLVMType(this->ArrayType, context), ArraySize->getValue());
    ValuePtr alloca = context.theBuilder.CreateAlloca(type);

    context.setSymbolTable(this->ArrayName->getName(), alloca);
    context.setSymbolType(this->ArrayName->getName(), this->ArrayType);

    return alloca;
}

llvm::Value *rmmc::StructDeclarationStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::BlockStatement::codeGen(CodeGenContext &context)
{
    StatementList::iterator it;
    for (it = this->Content->begin(); it != this->Content->end(); it++)
    {
        (*it)->codeGen(context);
    }
    return nullptr;
}

llvm::Value *rmmc::ReturnStatement::codeGen(CodeGenContext &context)
{
    ValuePtr returnVal = this->ReturnValue->codeGen(context);
    return returnVal;
}

llvm::Value *rmmc::TypedefStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::IfStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::WhileStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::BreakStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::ContinueStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::NameSpaceStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::UseStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::ImportStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::FromStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::ExportStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}
