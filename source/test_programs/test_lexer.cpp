
#include <iostream>
#include "../lexer.h"

using namespace skeleton;

int main(int argc, char **argv) {
	const char* test_string = "// Test program\n /**\n * /*Testing nested multi-line comments... */\n **/\n#import \"math.sc\";\n"
	                          "def hello_world(name: string) -> bool {\n    a: int = 256;\n    b:= 256.097;\n    c:= \"test_#string_over\n"
	                          "multiple rows\";\n    d: char = 'j';\n    e: [..., 7] = zeros(7);\n    if(!(hej == false) && true || false) {\n"
	                          "        print(\"Hello world to you \" :: name);\n    }\n    for (x, y) <- xx, yy {;}\n    bw:= (19 & 1) | (13 ||| 15);\n"
	                          "    return true;\n}\n\nnamespace test_ns {}";

	std::string test_source = test_string;
    string_table str_table;

	std::cout << "<Test program to lex>:" << std::endl << test_source << std::endl;

	lexer the_lexer = lex(test_source, str_table);

	//for(size_t i = 0; i < the_lexer.tokens.size(); ++i) {
	for(auto tok : the_lexer.tokens) {
		std::cout << to_string(*the_lexer.str_table, tok) << std::endl;
	}

	if(the_lexer.errors.size() > 0) {
		for(auto err : the_lexer.errors) {
			std::cout << "Syntax error: " << err.msg << " at line: " << err.line << ", col: " << err.col << std::endl;
		} 
	}
    
    print_string_table(*the_lexer.str_table);
/*
	string_table st;

	add(st, "def");
	add(st, "x");
	add(st, "int");
	add(st, "float32");
	add(st, "float64");
	add(st, "float64");
	add(st, "float65");
	add(st, "gloat65");
    add(st, "hloat65");
    add(st, "hloat66");
    add(st, "hloat67");

	print_string_table(st);
*/
	return 0;
}
