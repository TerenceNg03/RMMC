#include "AST.hh"

using namespace rmmc;

typedef std::pair<std::string, std::string> attribute_t;

std::string to_xml(const std::string& tag, const std::optional<std::string>& content, const std::vector<attribute_t>& attributes = {}){
	std::string tag_head = "<"+tag;
	for(auto &p: attributes){
		tag_head += " "+p.first+"="+p.second;
	}
	if(!content)return tag_head+"/>";

	return tag_head + ">" + *content+ "</" + tag + ">";
};

std::string IntegerExpr::toXML()
{
    return to_xml("IntegerExpr", std::to_string(Value));
}

// std::string UnsignedIntegerExpr::toXML()
// {
//     return to_xml("UnsignedIntegerExpr", std::to_string(Value));
// }

std::string BooleanExpr::toXML()
{
    return to_xml("BooleanExpr", std::to_string(Value));
}

// std::string CharExpr::toXML()
// {
//     return to_xml("CharExpr", std::to_string(Value));
// }

std::string StringExpr::toXML()
{
	return to_xml("StringExpr", Value);
}

std::string IdentifierExpr::toXML()
{
    return to_xml("Identifier", Name);
}

std::string BinaryOperatorExpr::toXML()
{
	std::string content = "";
	if(LHS)content += to_xml("LHS", LHS->toXML());
	else content += to_xml("LHS", {});
	if(RHS)content += to_xml("RHS", RHS->toXML());
	else content += to_xml("RHS", {});
	std::string opname;
	switch(Type){
		case BinaryOperator::SCOPE:
			opname = "::";
		case BinaryOperator::ARRAY_INDEX:
			opname = "[]";
		case BinaryOperator::STRUCT_REF:
			opname = ".";
		case BinaryOperator::STRUCT_DEREF:
			opname = "&gt";
		case BinaryOperator::AS:
			opname = "as";
		case BinaryOperator::ADD:
			opname = "+";
		case BinaryOperator::SUB:
			opname = "-";
		case BinaryOperator::MUL:
			opname = "*";
		case BinaryOperator::DIV:
			opname = "/";
		case BinaryOperator::MOD:
			opname = "%";
		case BinaryOperator::LEFT_SHIFT:
			opname = "&lt&lt";
		case BinaryOperator::RIGHT_SHIFT:
			opname = "&gt&gt";
		case BinaryOperator::LT:
			opname = "&lt";
		case BinaryOperator::ELT:
			opname = "&lt=";
		case BinaryOperator::GT:
			opname = "&gt";
		case BinaryOperator::EGT:
			opname = "&gt=";
		case BinaryOperator::E:
			opname = "==";
		case BinaryOperator::NE:
			opname = "!=";
		case BinaryOperator::AND:
			opname = "&amp";
		case BinaryOperator::XOR:
			opname = "^";
		case BinaryOperator::OR:
			opname = "|";
		case BinaryOperator::LOGICAL_AND:
			opname = "&amp&amp";
		case BinaryOperator::LOGICAL_OR:
			opname = "||";
	};
    return to_xml("BinaryOperator", content, {make_pair("op", opname)});
}

std::string ThreeOperatorExpr::toXML()
{
	std::string content = "";
	if(LHS)content += to_xml("LHS", LHS->toXML());
	else content += to_xml("LHS", {});
	if(MHS)content += to_xml("MHS", MHS->toXML());
	else content += to_xml("MHS", {});
	if(RHS)content += to_xml("RHS", RHS->toXML());
	else content += to_xml("RHS", {});
	std::string opname;
	switch(Type){
		case ThreeOperator::CONDITION:
			opname = "?:";
	}
    return to_xml("ThreeOperator", content, {make_pair("op", opname)});
}

std::string FunctionCallExpr::toXML()
{
	std::string content;
	if(FunctionName) content += to_xml("Function", FunctionName->toXML());
	else content += to_xml("Function", {});

	std::string Arg_content = "";
	int i=0;
    for (auto& Arg : *Args) {
       if(Arg) Arg_content += to_xml("Arg#"+std::to_string(i++), Arg->toXML());
	   else Arg_content += to_xml("Arg#"+std::to_string(i++), {});
    }

	content += Arg_content;
    return to_xml("FunctionCall", content);
}

std::string TypedefStatement::toXML()
{
	std::string content = "";
	if(LHS)content += to_xml("LHS", LHS->toXML());
	else content += to_xml("LHS", {});
	if(RHS)content += to_xml("RHS", RHS->toXML());
	else content += to_xml("RHS", {});
    return to_xml("type", content);
}

std::string IfStatement::toXML()
{

	std::string content = "";
	if(Condition)content += to_xml("Condition", Condition->toXML());
	else content += to_xml("Condition", {});
	/*** Chnage later ***/
    return to_xml("if", content);
}

std::string WhileStatement::toXML()
{
	std::string content = "";
	if(Condition)content += to_xml("Condition", Condition->toXML());
	else content += to_xml("Condition", {});
	/*** Chnage later ***/
    return to_xml("while", content);
}

std::string BreakStatement::toXML()
{
    return to_xml("break", {});
}

std::string ContinueStatement::toXML()
{
    return to_xml("continue", {});
}

std::string  NameSpaceStatement::toXML()
{
	std::string content = "";
	if(Name)content += to_xml("mod_id", Name->toXML());
	else content += to_xml("mod_id", {});
	/*** Chnage later ***/
    return to_xml("mod", content);
}

std::string  UseStatement::toXML()
{
	if(Name)
		return to_xml("use", Name->toXML());
	else
		return to_xml("use", {});

}

std::string  ImportStatement::toXML()
{
	if(Name)
		return to_xml("import", Name->toXML());
	else
		return to_xml("import", {});
}

std::string FromStatement::toXML()
{
	std::string content = "";
	if(FromName) content += to_xml("source", FromName->toXML());
	else content += to_xml("source", {});
	if(ImportName) content += to_xml("source", ImportName->toXML());
	else content += to_xml("source", {});

    return to_xml("from", content);
}

std::string  ExportStatement::toXML()
{
	if(Name)
		return to_xml("export", Name->toXML());
	else
		return to_xml("export", {});
}

std::string FunctionDeclarationStatement::toXML()
{
	std::string content="";
	if(FunctionName) content += to_xml("Function", FunctionName->toXML());
	else content += to_xml("Function", {});

	std::string Arg_content = "";
	int i=0l;
	for (auto& Arg : *Args){
		if(Arg) Arg_content += to_xml("Arg#"+std::to_string(i++), Arg->toXML());
		else
			Arg_content += to_xml("Arg#" + std::to_string(i++), {});
	}
	content += Arg_content;
	return to_xml("FunctionDeclaration", content);
}

std::string ReturnStatement::toXML()
{
	std::string content="";
	if(ReturnValue) content = to_xml("Return Expression", ReturnValue->toXML());
	else content = to_xml("Return Expression", {});
	return to_xml("Return", content);
}

std::string SingleVariableDeclarationStatement::toXML()
{
	std::string content="";

	if (VariableType)
		content += to_xml("Variable Type", VariableType->toXML());
	else
		content += to_xml("Variable Type", {});
	if (VariableName)
		content += to_xml("Variable Name", VariableName->toXML());
	else
		content += to_xml("Variable Name", {});
	return to_xml("Single Variable Declaration", content);
}

std::string ArrayDeclarationStatement::toXML()
{
	std::string content = "";

	if (ArrayType)
		content += to_xml("Array Type", ArrayType->toXML());
	else
		content += to_xml("Array Type", {});
	if (ArrayName)
		content += to_xml("Array Name", ArrayName->toXML());
	else
		content += to_xml("Array Name", {});
	if (ArraySize)
		content += to_xml("Array Size", ArraySize->toXML());
	else
		content += to_xml("Array Size", {});
	return to_xml("Array Declaration", content);
}

std::string StructDeclarationStatement::toXML()
{
	std::string content = "";
	if (Name)
		content += to_xml("Struct Name", Name->toXML());
	else
		content += to_xml("Struct Name", {});
	std::string mem_content ="";
	int i=0;
	for (auto& member : *Members){
		if (member)
			mem_content += to_xml("Member#" + std::to_string(i++), member->toXML());
		else
			mem_content += to_xml("Member#" + std::to_string(i++), {});
	}
	for (auto &member : *FuncMembers){
		if (member)
			mem_content += to_xml("FuncMember#" + std::to_string(i++), member->toXML());
		else
			mem_content += to_xml("FuncMember#" + std::to_string(i++), {});
	}
	content+=mem_content;
	return to_xml("Struct Declaration", content);
}

std::string BlockStatement::toXML()
{
	std::string content = "";
	int i=0;
	for(auto& perContent : *Content){
		if (perContent)
			content += to_xml("Statement#" + std::to_string(i++), perContent->toXML());
		else
			content += to_xml("Statement#" + std::to_string(i++), {});
	}
	return to_xml("Block", content);
}