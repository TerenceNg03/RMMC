#include "AST.hh"

using namespace rmmc;

typedef std::pair<std::string, std::string> attribute_t;


std::string to_json(const std::string& name) {
  return "{ \"name\" : \"" + name + "\" }";
}
std::string to_json(const std::string& name, const std::vector<std::string>& children) {
  std::string result = "{ \"name\" : \"" + name + "\", \"children\" : [ ";
  int i = 0;
  for(auto &child : children) {
    if(i != children.size() - 1)
      result += (std::string)child + ", ";
    else
      result += (std::string)child + " ";
    i++;
 }
  return result+"] }";
}
std::string to_json(const std::string& name, const std::string& value) {
  return to_json(name, std::vector<std::string>{value});
}


std::string IntegerExpr::toJSON()
{
    return to_json("IntegerExpr", to_json(std::to_string(Value)));
}

// std::string UnsignedIntegerExpr::toXML()
// {
//     return to_xml("UnsignedIntegerExpr", std::to_string(Value));
// }

std::string BooleanExpr::toJSON()
{
    return to_json("BooleanExpr", to_json(std::to_string(Value)));
}

// std::string CharExpr::toXML()
// {
//     return to_xml("CharExpr", std::to_string(Value));
// }

std::string StringExpr::toJSON()
{
	return to_json("StringExpr", to_json(Value));
}

std::string IdentifierExpr::toJSON()
{
    return to_json("Identifier", to_json(Name));
}

std::string BinaryOperatorExpr::toJSON()
{
	std::vector<std::string> children;
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
	children.push_back(LHS->toJSON());
	children.push_back(to_json("op",to_json(opname)));
	children.push_back(RHS->toJSON());
    return to_json("BinaryOperator", children);
}

std::string ThreeOperatorExpr::toJSON()
{
	std::vector<std::string> children;
	std::string opname;
	switch(Type){
		case ThreeOperator::CONDITION:
			opname = "?:";
	}
	children.push_back(LHS->toJSON());
	children.push_back(MHS->toJSON());
	children.push_back(RHS->toJSON());
	children.push_back(to_json("op",to_json(opname)));
    return to_json("ThreeOperator",children);
}

std::string FunctionCallExpr::toJSON()
{
	std::vector<std::string> children;
	if(FunctionName) children.push_back(to_json("FunctionName",FunctionName->toJSON()));

	std::vector<std::string> Arg_content ;
	int i=0;
    for (auto& Arg : *Args) {
       if(Arg) {
         Arg_content.push_back(Arg->toJSON());
		 i++;
	   }
    }
    if(i)
	children.push_back(to_json("Args",Arg_content));
    return to_json("FunctionCall", children);
}

std::string AssignmentExpression::toJSON()
{
	std::vector<std::string> children;
	children.push_back(LHS->toJSON());
	children.push_back(RHS->toJSON());
    return to_json("assignment", children);
}

std::string TypedefStatement::toJSON()
{
	std::vector<std::string> children;
	children.push_back(LHS->toJSON());
	children.push_back(RHS->toJSON());
    return to_json("type", children);
}

std::string IfStatement::toJSON()
{

	std::vector<std::string> children;
	if(Condition) children.push_back(to_json("Condition",Condition->toJSON()));
	/*** Chnage later ***/
    return to_json("if", children);
}

std::string WhileStatement::toJSON()
{
	std::vector<std::string> children;
	if(Condition) children.push_back(to_json("Condition",Condition->toJSON()));
	/*** Chnage later ***/
    return to_json("while", children);
}

std::string BreakStatement::toJSON()
{
    return to_json("break");
}

std::string ContinueStatement::toJSON()
{
    return to_json("continue");
}

std::string  NameSpaceStatement::toJSON()
{
	std::vector<std::string> children;
	if(Name) children.push_back(to_json("Name",Name->toJSON()));
	/*** Chnage later ***/
    return to_json("mod", children);
}

std::string  UseStatement::toJSON()
{
	if(Name)
		return to_json("use", Name->toJSON());
	else
		return to_json("use");

}

std::string  ImportStatement::toJSON()
{
	if(Name)
		return to_json("import", Name->toJSON());
	else
		return to_json("import");
}

std::string FromStatement::toJSON()
{
	std::vector<std::string> children;
	if(FromName) children.push_back(FromName->toJSON());
	if(ImportName) children.push_back(ImportName->toJSON());


    return to_json("from", children);
}

std::string  ExportStatement::toJSON()
{
	if(Name)
		return to_json("export", Name->toJSON());
	else
		return to_json("export");
}


std::string FunctionDeclarationStatement::toJSON()
{
	std::vector<std::string> children;
    if(FunctionName) children.push_back(to_json("FunctionName",FunctionName->toJSON()));
	if(ReturnType) children.push_back(to_json("ReturnType",ReturnType->toJSON()));
	if(Content) children.push_back(to_json("Content",Content->toJSON()));
	if(Return) children.push_back(to_json("Return",Return->toJSON()));
	std::vector<std::string> Arg_content;
	int i1=0;
	for (auto& Arg : *Args){
		if(Arg) 
		{
			Arg_content.push_back(Arg->toJSON());
			i1++;
		}
		
	}
	if(i1) children.push_back(to_json("Args",Arg_content));
	return to_json("FunctionDeclaration", children);
}

std::string ReturnStatement::toJSON()
{
	std::vector<std::string> children;
	if(ReturnValue) children.push_back(to_json("ReturnValue",ReturnValue->toJSON()));
	return to_json("Return", children);
}

std::string SingleVariableDeclarationStatement::toJSON()
{
	std::vector<std::string> children;

	if (VariableType)
		children.push_back(to_json("VariableType",VariableType->toJSON()));
	if (VariableName)
		children.push_back(to_json("VariableName",VariableName->toJSON()));
	return to_json("Single Variable Declaration", children);
}

std::string ArrayDeclarationStatement::toJSON()
{
	std::vector<std::string> children;
	if (ArrayType)
		children.push_back(to_json("ArrayType",ArrayType->toJSON()));
	if (ArrayName)
		children.push_back(to_json("ArrayName",ArrayName->toJSON()));
	if (ArraySize)
		children.push_back(to_json("ArraySize",ArraySize->toJSON()));
	return to_json("Array Declaration", children);
}

std::string StructDeclarationStatement::toJSON()
{
	std::vector<std::string> children;
	if (Name)
		children.push_back(to_json("StructureName",Name->toJSON()));
	std::vector<std::string> mem_content;
	int i1=0,i2=0;
	for (auto& member : *Members){
		if (member)
		{
			mem_content.push_back(member->toJSON());
			i1++;
		}
			
	}
	if(i1)
	children.push_back(to_json("Members",mem_content));
	std::vector<std::string> fun_content;
	for (auto &member : *FuncMembers){
		if (member)
		{
			fun_content.push_back(member->toJSON());
			i2++;
		}	
	}
	if(i2)
	children.push_back(to_json("FuncMembers",fun_content));
	return to_json("Struct Declaration", children);
}

std::string BlockStatement::toJSON()
{
	std::vector<std::string> children;
	std::vector<std::string> p_content;
	int i=0;
	for(auto& perContent : *Content){
		if (perContent)
		{
			p_content.push_back(perContent->toJSON());
			i++;
		}	
	}
	if(i)
	children.push_back(to_json("Content",p_content));
	return to_json("Block", children);
}