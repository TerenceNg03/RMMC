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
    return getJsonString("DoubleExpr", getJsonString(to_string(Value));
}

std::string IntegerExpr::toXML()
{
    return getJsonString("IntegerExpr", getJsonString(to_string(Value));
}

std::string UnsignedIntegerExpr::toXML()
{
    return getJsonString("UnsignedIntegerExpr", getJsonString(to_string(Value));
}

std::string BooleanExpr::toXML()
{
    return getJsonString("BooleanExpr", getJsonString(to_string(Value));
}

std::string CharExpr::toXML()
{
    return getJsonString("CharExpr", getJsonString(to_string(Value));
}

std::string IdentifierExpr::toXML()
{
    return getJsonString("IdentifierExpr", getJsonString(Value);
}

std::string BinaryOperatorExpr::toXML()
{
    vector<string> children;
    children.push_back(LHS->getJson());
    children.push_back(getJsonString(opString[Type]));
    children.push_back(RHS->getJson());
    return getJsonString("BinaryOperatorExpr", children);
}

std::string ThreeOperatorExpr::toXML()
{
    vector<string> children;
    children.push_back(LHS->getJson());
    children.push_back(MHS->getJson());
    children.push_back(RHS->getJson());
    children.push_back(getJsonString(opString[Type]));
    return getJsonString("ThreeOperatorExpr", children);
}

std::string FunctionCallExpr::toXML()
{
    vector<string> children;
    children.push_back(FunctionName->getJson());
    vector<string> ArgsJson;
    for (auto& Arg : *Args) {
        ArgsJson.push_back(Arg->getJson());
    }
    children.push_back(getJsonString("ExpressionList", ArgsJson));
    return getJsonString("FunctionCallExpr", children);
}

std::string SingleVariableDeclarationStatement::toXML()
{
    vector<string> children;
    children.push_back(VariableType->getJson());
    children.push_back(VariableName->getJson());
    return getJsonString("SingleVariableDeclarationStatement", children);
}

std::string ArrayDeclarationStatement::toXML()
{
    vector<string> children;
    children.push_back(ArrayType->getJson());
    children.push_back(ArrayName->getJson());
    children.push_back(ArraySize->getJson());
    return getJsonString("ArrayDeclarationStatement", children);
}

std::string AssignmentStatement::toXML()
{
    vector<string> children;
    children.push_back(LHS->getJson());
    children.push_back(RHS->getJson());
    return getJsonString("AssignmentStatement", children);
}

std::string FunctionDeclarationStatement::toXML()
{
    vector<string> children;
    children.push_back(ReturnType->getJson());
    children.push_back(FunctionName->getJson());
    vector<string> ArgsJson;
    for (auto& Arg : *Args) {
        ArgsJson.push_back(Arg->getJson());
    }
    children.push_back(getJsonString("VariableList", ArgsJson));
    vector<string> ContentJson;
    for (auto& Con : *Content) {
        ContentJson.push_back(Con->getJson());
    }
    children.push_back(getJsonString("StatementList", ContentJson));
    return getJsonString("FunctionDeclarationStatement", children);
}

std::string StructDeclarationStatement::toXML()
{
    vector<string> children;
    children.push_back(Name->getJson());
    vector<string> MembersJson;
    for (auto& Mem : *Members) {
        MembersJson.push_back(Mem->getJson());
    }
    children.push_back(getJsonString("VariableList", MembersJson));
    vector<string> FuncMembersJson;
    for (auto& Func : *FuncMembers) {
        FuncMembersJson.push_back(Fun->getJson());
    }
    children.push_back(getJsonString("FunctionList", FuncMembersJson));
    return getJsonString("StructDeclarationStatement", children);
}

std::string TypedefStatement::toXML()
{
    vector<string> children;
    children.push_back(LHS->getJson());
    children.push_back(RHS->getJson());
    return getJsonString("TypedefStatement", children);
}

std::string IfStatement::toXML()
{
    vector<string> children;
    children.push_back(Condition->getJson());
    vector<string> TrueBlockJson;
    for (auto& T : *TrueBlock) {
        TrueBlockJson.push_back(T->getJson());
    }
    children.push_back(getJsonString("StatementList", TrueBlockJson));
    vector<string> FalseBlockJson;
    for (auto& F : *FalseBlock) {
        FalseBlockJson.push_back(F->getJson());
    }
    children.push_back(getJsonString("StatementList", FalseBlockJson));
    return getJsonString("IfStatement", children);
}

std::string WhileStatement::toXML()
{
    vector<string> children;
    children.push_back(Condition->getJson());
    vector<string> BlockJson;
    for (auto& B : *Block) {
        BlockJson.push_back(B->getJson());
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
    vector<string> children;
    children.push_back(Name->getJson());
    vector<string> BlockJson;
    for (auto& B : *Block) {
        BlockJson.push_back(B->getJson());
    }
    children.push_back(getJsonString("StatementList", BlockJson));
    return getJsonString("NameSpaceStatement", children);
}

std::string  UseStatement::toXML()
{
    vector<string> children;
    children.push_back(Name->getJson());
    return getJsonString("UseStatement", children);
}

std::string  ImportStatement::toXML()
{
    vector<string> children;
    children.push_back(Name->getJson());
    return getJsonString("ImportStatement", children);
}

std::string FromStatement::toXML()
{
    vector<string> children;
    children.push_back(FromName->getJson());
    children.push_back(ImportName->getJson());
    return getJsonString("FromStatement", children);
}

std::string  ExportStatement::toXML()
{
    vector<string> children;
    children.push_back(Name->getJson());
    return getJsonString("ExportStatement", children);
}