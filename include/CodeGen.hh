#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <vector>
#include <memory>
#include <cstring>
#include <map>

#include "AST.hh"

namespace rmmc
{

    typedef llvm::BasicBlock *BasicBlockPtr;
    typedef llvm::Value *ValuePtr;
    typedef llvm::Type *TypePtr;
    typedef CodeGenBlock *CodeGenBlockPtr;

    class CodeGenBlock
    {
    public:
        BasicBlockPtr block;
        std::map<std::string, ValuePtr> SymbolTable;
        std::map<std::string, std::shared_ptr<IdentifierExpr> > SymbolType;
    };

    class CodeGenContext
    {
    public:
        std::vector<CodeGenBlockPtr> blockStack;

        static llvm::LLVMContext theContext;
        llvm::IRBuilder<> theBuilder;
        std::unique_ptr<llvm::Module> theModule;

        CodeGenContext() : theBuilder(theContext)
        {
            theModule = std::make_unique<llvm::Module>("main", this->theContext);
        }

        void CodeGen(std::shared_ptr<ASTNode> root);

        void pushBlock(BasicBlockPtr block)
        {
            CodeGenBlockPtr newBlock = new CodeGenBlock();
            newBlock->block = block;
            blockStack.push_back(newBlock);
        }

        void popBlock()
        {
            CodeGenBlockPtr delBlock = blockStack.back();
            blockStack.pop_back();
            delete delBlock;
        }

        void setSymbolTable(std::string name, ValuePtr alloca)
        {
            blockStack.back()->SymbolTable[name] = alloca;
        }
        void setSymbolType(std::string name, std::shared_ptr<IdentifierExpr> type)
        {
            blockStack.back()->SymbolType[name] = type;
        }
        ValuePtr getSymbolTable(std::string name)
        {
            std::vector<CodeGenBlockPtr>::reverse_iterator it;
            for (it = this->blockStack.rbegin(); it != this->blockStack.rend(); it++)
            {
                if ((*it)->SymbolTable.find(name) != (*it)->SymbolTable.end())
                {
                    return (*it)->SymbolTable[name];
                }
            }
            return nullptr;
        }
    };
}
#endif
