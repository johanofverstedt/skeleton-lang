
#include <iostream>
#include "../lexer.h"

using namespace skeleton;

int main(int argc, char **argv) {
	const char* test_string = "// Test program\n /**\n * /*Testing nested multi-line comments... */\n **/\n#import \"math.sc\";\ndef hello_world(name: string) -> bool {\n    a: int = 256;\n    b:= 256.097;\n    c:= \"test_#string_over\nmultiple rows\";\n    d: char = 'j';\n    e: [..., 7] = zeros(7);\n    if(!(hej == false)) {\n        print(\"Hello world to you \" :: name);\n    }\n    for (x, y) <- xx, yy {;}\n    return true;\n}\n\nnamespace test_ns {}";

	std::string test_source = test_string;

	std::cout << "<Test program to lex>:" << std::endl << test_source << std::endl;

	lexer the_lexer = lex(test_source);

	//for(size_t i = 0; i < the_lexer.tokens.size(); ++i) {
	for(auto tok : the_lexer.tokens) {
		std::cout << to_string(tok) << std::endl;
	} 

	if(the_lexer.errors.size() > 0) {
		for(auto err : the_lexer.errors) {
			std::cout << "Syntax error: " << err.msg << " at line: " << err.line << ", col: " << err.col << std::endl;
		} 
	}

	return 0;
}
