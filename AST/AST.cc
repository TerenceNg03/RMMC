#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/Support/raw_ostream.h>
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

#include <vector>
#include <cstdlib>

#include "CodeGen.hh"

typedef llvm::Type *TypePtr;
typedef llvm::ArrayType *ArrayTypePtr;
typedef llvm::FunctionType *FunctionTypePtr;
typedef llvm::Function *FunctionPtr;
typedef llvm::Value *ValuePtr;

using namespace llvm;
using namespace rmmc;

llvm::Type *getLLVMType(std::shared_ptr<IdentifierExpr> type, rmmc::CodeGenContext &context)
{
    std::string name = type->getName();
    std::cout << "getLLVMType: " << name << std::endl;
    // std::cout<<name.compare("int")<<std::endl;
    if (!name.compare("int"))
        return llvm::Type::getInt32Ty(context.theContext);
    if (!name.compare("string"))
        return llvm::Type::getInt8PtrTy(context.theContext);
    std::cout << "Return nullptr" << std::endl;
    return nullptr;
}

llvm::Value *rmmc::DoubleExpr::codeGen(CodeGenContext &context)
{
    this->print();
    return llvm::ConstantFP::get(llvm::Type::getDoubleTy(context.theContext), this->Value);
}

llvm::Value *rmmc::IntegerExpr::codeGen(CodeGenContext &context)
{
    this->print();
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context.theContext), this->Value);
}

llvm::Value *rmmc::BooleanExpr::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::StringExpr::codeGen(CodeGenContext &context)
{
    return context.theBuilder.CreateGlobalString(this->Value, "string");
    //return llvm::ConstantDataArray::getString(context.theContext, this->Value, true);
}

llvm::Value *rmmc::IdentifierExpr::codeGen(CodeGenContext &context)
{
    this->print();
    ValuePtr val = context.getSymbolTable(this->Name);
    if (val == nullptr)
    {
        std::cout << "The identifier not find" << std::endl;
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
    // if( this->FunctionName->getName().compare("printf") == 0 ){
    //     std::vector<llvm::Type *> putsArgs;
    //     putsArgs.push_back(context.theBuilder.getInt8Ty()->getPointerTo());
    //     llvm::ArrayRef<llvm::Type *> argsRef(putsArgs);
    //     llvm::FunctionType *putsType =
    //         llvm::FunctionType::get(context.theBuilder.getInt32Ty(), argsRef, true);
    //     llvm::FunctionCallee putsFunc = context.theModule->getOrInsertFunction("printf", putsType);
    //     context.theBuilder.CreateCall2(putsFunc, context.theBuilder.CreateGlobalStringPtr("%d"), this->Args->at(1)->codeGen());
    //     return nullptr;
    // }
    FunctionPtr callF = context.theModule->getFunction(this->FunctionName->getName());
    if (callF == nullptr)
    {
        std::cout << "Not find the function" << std::endl;
        return nullptr;
    }
    else if (callF->arg_size() != this->Args->size())
    {
        std::cout<<callF->arg_size()<<std::endl;
        std::cout<<this->Args->size()<<std::endl;
        std::cout << "Function Args size different" << std::endl;
        return nullptr;
    }
    else
    {
        ExpressionList::iterator it;
        std::vector<ValuePtr> callArgs;
        for (it = this->Args->begin(); it != this->Args->end(); it++)
        {
            ValuePtr tmp = (*it)->codeGen(context);
            if (tmp == nullptr)
            {
                return nullptr;
            }
            callArgs.push_back(tmp);
        }
        return context.theBuilder.CreateCall(callF, callArgs, "callF");
    }
}

llvm::Value *rmmc::AssignmentExpression::codeGen(CodeGenContext &context)
{
    this->print();
    ValuePtr l = context.getSymbolTable(this->LHS->getName());
    auto lType = context.getSymbolType(this->LHS->getName());
    if (l == nullptr)
    {
        std::cout << "Assignment LHS is nullptr" << std::endl;
        return nullptr;
    }
    ValuePtr r = this->RHS->codeGen(context);
    r = context.typeSystem.cast(r, getLLVMType(lType, context), context.currentBlock());
    if (r == nullptr)
    {
        std::cout << l->getType() << " " << r->getType() << std::endl;
        std::cout << "l  and r type different" << std::endl;
    }
    context.theBuilder.CreateStore(r, l);
    return l;
}

llvm::Value *rmmc::FunctionDeclarationStatement::codeGen(CodeGenContext &context)
{
    this->print();
    // Construct function params type
    std::vector<TypePtr> funcArgs;
    VariableList::iterator it;
    for (auto &perArg : *Args)
    {
        funcArgs.push_back(getLLVMType(perArg->getType(), context));
    }
    std::cout << "Args finished" << std::endl;
    // for (it = this->Args->begin(); it != this->Args->end(); it++)
    // {
    //     std::cout<<"**"<<std::endl;
    //     funcArgs.push_back(getLLVMType((*it)->getType(), context));
    // }
    // Construct function return type
    TypePtr retType = getLLVMType(ReturnType, context);
    if (retType == nullptr)
        std::cout << "Return type is nullptr" << std::endl;
    std::cout << "Return Type Finished" << std::endl;
    // get function type and construct function
    FunctionTypePtr funcType = nullptr;
    if (this->isExternal)
        funcType = llvm::FunctionType::get(retType, funcArgs, false);
    else
        funcType = llvm::FunctionType::get(retType, funcArgs, false);
    std::cout << "Func Type Finished" << std::endl;
    FunctionPtr func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, this->FunctionName->getName().c_str(), context.theModule.get());
    std::cout << "Func Finished" << std::endl;
    if (this->isExternal)
        return func;
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
    ValuePtr returnVal = this->Return->codeGen(context);
    if (returnVal == nullptr)
        std::cout << "Return value is nullptr" << std::endl;
    context.theBuilder.CreateRet(returnVal);
    std::cout << "Return Value Finished" << std::endl;
    // Pop Block
    context.popBlock();
    llvm::verifyFunction(*func);
    std::cout << "Function Finished" << std::endl;
    return func;
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
    if (returnVal == nullptr)
        std::cout << "return value nullptr" << std::endl;
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
