#ifndef __TYPE_H__
#define __TYPE_H__

#include "AST.hh"
#include "CodeGen.hh"
/***
 * 
 * return llvm::Type*  
 */
namespace rmmc{
    llvm::Type* getLLVMType(rmmc::IdentifierExpr type, rmmc::CodeGenContext &context)
    {
        std::string name=type.getName();
        if( name.compare("int") )
            return llvm::Type::getInt64Ty(context.theContext);
        return nullptr;
    }
}

#endif