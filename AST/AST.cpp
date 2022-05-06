#include "AST.h"
std::string getJsonString(std::string name) {
    return "{ \"name\" : \"" + name + "\" }";
}

std::string getJsonString(std::string name, vector<std::string> children) {
    std::string result = "{ \"name\" : \"" + name + "\", \"children\" : [ ";
    int i = 0;
    for (auto& child : children) {
        if (i != children.size() - 1)
            result += child + ", ";
        else
            result += child + " ";
        i++;
    }
    return result + " ] }";
}

std::string getJsonString(std::string name, std::string value) {
    return getJsonString(name, vector<std::string>{value});
}

std::string getJsonString(std::string name, std::string value, vector<std::string> children) {
    std::string result = "{ \"name\" : \"" + name + "\", \"value\" : \"" + value + "\", \"children\" : [ ";
    int i = 0;
    for (auto& child : children) {
        if (i != children.size() - 1)
            result += child + ", ";
        else
            result += child + " ";
        i++;
    }
    return result + " ] }";
}
std::string DoubleExpr::toXML()
{
    return getJsonString("DoubleExpr", getJsonString(std::to_string(Value));
}

std::string IntegerExpr::toXML()
{
    return getJsonString("IntegerExpr", getJsonString(std::to_string(Value));
}

std::string UnsignedIntegerExpr::toXML()
{
    return getJsonString("UnsignedIntegerExpr", getJsonString(std::to_string(Value));
}

std::string BooleanExpr::toXML()
{
    return getJsonString("BooleanExpr", getJsonString(std::to_string(Value));
}

std::string CharExpr::toXML()
{
    return getJsonString("CharExpr", getJsonString(std::to_string(Value));
}

std::string IdentifierExpr::toXML()
{
    return getJsonString("IdentifierExpr", getJsonString(Value);
}

std::string BinaryOperatorExpr::toXML()
{
    vector<std::string> children;
    children.push_back(LHS->toXML());
    //opString��Ӧ����
    children.push_back(getJsonString(opString[Type]));
    children.push_back(RHS->toXML());
    return getJsonString("BinaryOperatorExpr", children);
}

std::string ThreeOperatorExpr::toXML()
{
    vector<std::string> children;
    children.push_back(LHS->toXML());
    children.push_back(MHS->toXML());
    children.push_back(RHS->toXML());
    children.push_back(getJsonString(opString[Type]));
    return getJsonString("ThreeOperatorExpr", children);
}

std::string FunctionCallExpr::toXML()
{
    vector<std::string> children;
    children.push_back(FunctionName->toXML());
    vector<std::string> ArgsJson;
    for (auto& Arg : *Args) {
        ArgsJson.push_back(Arg->toXML());
    }
    children.push_back(getJsonString("ExpressionList", ArgsJson));
    return getJsonString("FunctionCallExpr", children);
}

std::string SingleVariableDeclarationStatement::toXML()
{
    vector<std::string> children;
    children.push_back(VariableType->toXML());
    children.push_back(VariableName->toXML());
    return getJsonString("SingleVariableDeclarationStatement", children);
}

std::string ArrayDeclarationStatement::toXML()
{
    vector<std::string> children;
    children.push_back(ArrayType->toXML());
    children.push_back(ArrayName->toXML());
    children.push_back(ArraySize->toXML());
    return getJsonString("ArrayDeclarationStatement", children);
}

std::string AssignmentStatement::toXML()
{
    vector<std::string> children;
    children.push_back(LHS->toXML());
    children.push_back(RHS->toXML());
    return getJsonString("AssignmentStatement", children);
}

std::string FunctionDeclarationStatement::toXML()
{
    vector<std::string> children;
    children.push_back(ReturnType->toXML());
    children.push_back(FunctionName->toXML());
    vector<string> ArgsJson;
    for (auto& Arg : *Args) {
        ArgsJson.push_back(Arg->toXML());
    }
    children.push_back(getJsonString("VariableList", ArgsJson));
    vector<std::string> ContentJson;
    for (auto& Con : *Content) {
        ContentJson.push_back(Con->toXML());
    }
    children.push_back(getJsonString("StatementList", ContentJson));
    return getJsonString("FunctionDeclarationStatement", children);
}

std::string StructDeclarationStatement::toXML()
{
    vector<std::string> children;
    children.push_back(Name->toXML());
    vector<std::string> MembersJson;
    for (auto& Mem : *Members) {
        MembersJson.push_back(Mem->toXML());
    }
    children.push_back(getJsonString("VariableList", MembersJson));
    vector<std::string> FuncMembersJson;
    for (auto& Func : *FuncMembers) {
        FuncMembersJson.push_back(Fun->toXML());
    }
    children.push_back(getJsonString("FunctionList", FuncMembersJson));
    return getJsonString("StructDeclarationStatement", children);
}

std::string TypedefStatement::toXML()
{
    vector<std::string> children;
    children.push_back(LHS->toXML());
    children.push_back(RHS->toXML());
    return getJsonString("TypedefStatement", children);
}

std::string IfStatement::toXML()
{
    vector<std::string> children;
    children.push_back(Condition->toXML());
    vector<std::string> TrueBlockJson;
    for (auto& T : *TrueBlock) {
        TrueBlockJson.push_back(T->toXML());
    }
    children.push_back(getJsonString("StatementList", TrueBlockJson));
    vector<std::string> FalseBlockJson;
    for (auto& F : *FalseBlock) {
        FalseBlockJson.push_back(F->toXML());
    }
    children.push_back(getJsonString("StatementList", FalseBlockJson));
    return getJsonString("IfStatement", children);
}

std::string WhileStatement::toXML()
{
    vector<std::string> children;
    children.push_back(Condition->toXML());
    vector<std::string> BlockJson;
    for (auto& B : *Block) {
        BlockJson.push_back(B->toXML());
    }
    children.push_back(getJsonString("StatementList", BlockJson));
    return getJsonString("WhileStatement", children);
}

std::string BreakStatement::toXML()
{
    return getJsonString("BreakStatement");
}

std::string ContinueStatement::toXML()
{
    return getJsonString("ContinueStatement");
}

std::string  NameSpaceStatement::toXML()
{
    vector<std::string> children;
    children.push_back(Name->toXML());
    vector<std::string> BlockJson;
    for (auto& B : *Block) {
        BlockJson.push_back(B->toXML());
    }
    children.push_back(getJsonString("StatementList", BlockJson));
    return getJsonString("NameSpaceStatement", children);
}

std::string  UseStatement::toXML()
{
    vector<std::string> children;
    children.push_back(Name->toXML());
    return getJsonString("UseStatement", children);
}

std::string  ImportStatement::toXML()
{
    vector<std::string> children;
    children.push_back(Name->toXML());
    return getJsonString("ImportStatement", children);
}

std::string FromStatement::toXML()
{
    vector<std::string> children;
    children.push_back(FromName->toXML());
    children.push_back(ImportName->toXML());
    return getJsonString("FromStatement", children);
}

std::string  ExportStatement::toXML()
{
    vector<std::string> children;
    children.push_back(Name->toXML());
    return getJsonString("ExportStatement", children);
}