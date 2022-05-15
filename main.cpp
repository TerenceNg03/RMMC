#include "driver.hh"
#include <signal.h>
#include <unistd.h>
#include <getopt.h>
#include <string>
#include <string.h>
#include <filesystem>
#include <fstream>
#include "CodeGen.hh"
using namespace rmmc;
using namespace llvm;

using namespace std;


int main(int argc, char *const *argv)
{
	/*
		bool use_import = false;
		string import_path = "";
		string output_file = "a.out";

		bool AST_required = false;
		string AST_file = "AST.xml";

		bool use_std = false;
		string std_path = "";
		int c;

		while (1) {
			int option_index = 0;
			static struct option long_options[] = {
				{"output",	required_argument,	0,  0 },
				{"genAST",	optional_argument,	0,  0 },
				{"stdpath",	required_argument,	0,  0 },
				{"import",	required_argument,	0,  0 },
				{0,         0,					0,  0 }
			};

			c = getopt_long(argc, argv, "o:I:",
					long_options, &option_index);
			if (c == -1)
				break;

			switch (c) {
				case 0:
					if(!strcmp(long_options[option_index].name, "output")){
						output_file = optarg;
	#if DEBUG
					printf("[Debug info] Output file name: %s\n", optarg);
	#endif
					}
					if(!strcmp(long_options[option_index].name, "genAST")){
						AST_required = true;
						if(optarg)AST_file = optarg;
	#if DEBUG
					printf("[Debug info] AST generation enabled\n");
					printf("[Debug info] AST output file: %s\n", AST_file.c_str());
	#endif
					}
					if(!strcmp(long_options[option_index].name, "stdpath")){
						use_std = true;
						std_path = optarg;
	#if DEBUG
					printf("[Debug info] Standard library enabled\n");
					printf("[Debug info] Standard library search path: %s\n", optarg);
	#endif
					}
					if(!strcmp(long_options[option_index].name, "import")){
						use_import = true;
						import_path = optarg;
	#if DEBUG
					printf("[Debug info] Output file name: %s\n", optarg);
	#endif
					}
					break;

				case 'o':
	#if DEBUG
					printf("[Debug info] Output file name: %s\n", optarg);
	#endif
					import_path = optarg;
					break;

				case 'I':
	#if DEBUG
					printf("[Debug info] Import search path %s\n", optarg);
	#endif
					use_import = true;
					import_path = optarg;
					break;

				case '?':
					return -1;
					break;

				default:
					printf("?? getopt returned character code 0%o ??\n", c);
					return -1;
			};
		}

		string input_file;
		if (optind < argc) {
	#if DEBUG
			printf("[DEBUG] Input file: %s\n", argv[optind]);
	#endif
			input_file = argv[optind];
		}else{
			printf("Error33[1;31mErrorError33[0m: No input file\n");
			return -1;
		}

		//validate files and pathes
		if(!filesystem::is_regular_file(filesystem::path(input_file))){
			printf("Error33[1;31mErrorError33[0m: Input file not valid\n");
			return -1;
		}
		if(use_std && !filesystem::is_directory(filesystem::path(std_path))){
			printf("Error33[1;31mErrorError33[0m: Standard library path not valid\n");
			return -1;
		}
		if(use_import && !filesystem::is_directory(filesystem::path(import_path))){
			printf("Error33[1;31mErrorError33[0m: Import path not valid\n");
			return -1;
		}

		//setup driver
		rmmc::Driver driver(input_file);
	*/
	cout << "Hello World" << endl;
	//<---------------Case1------------->
	location loc;
	shared_ptr<IdentifierExpr> ReturnType = make_shared<IdentifierExpr>(string("int"), loc);
	shared_ptr<IdentifierExpr> FunctionName = make_shared<IdentifierExpr>(string("main"), loc);
	// unique_ptr<VariableDeclarationStatement> arg1 = make_shared<VariableDeclarationStatement>();
	shared_ptr<VariableList> Args = make_shared<VariableList>();
	shared_ptr<Statement> st1 = make_shared<SingleVariableDeclarationStatement>(
		move(make_shared<IdentifierExpr>("int", loc)),
		move(make_shared<IdentifierExpr>("a", loc)),
		loc,
		VariableDeclarationStatement::MUTABLE);
	// unique_ptr<Statement> st2 = make_shared<AssignmentExpression>()
	shared_ptr<StatementList> contentList = make_shared<StatementList>();
	contentList->push_back(st1);
	shared_ptr<BlockStatement> Content = make_shared<BlockStatement>(move(contentList));
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
	//code.CodeGen(move(main));
	string xml=main->toXML();
	//cout<<xml<<endl;
	fstream out("AST.xml");
	if(out.is_open()){
		out<<xml;
		out.close();
	}
	//dfs(main);
	//code.theModule->print(llvm::errs(), nullptr);
	return 0;
}
