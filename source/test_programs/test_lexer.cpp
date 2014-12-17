
#include <iostream>
#include "../lexer.h"

using namespace skeleton;

int main(int argc, char **argv) {
	const char* test_string = "// Test program\n /**\n * Testing the comments...\n **/\n#import \"math.sc\";\ndef hello_world(name: string) {\n    print(\"Hello world to you \" :: name);\n}\n";

	std::string test_source = test_string;

	std::cout << "<Test program to lex>:" << std::endl << test_source << std::endl;

	lexer the_lexer = lex(test_source);

	//for(size_t i = 0; i < the_lexer.tokens.size(); ++i) {
	for(auto tok : the_lexer.tokens) {
		std::cout << tok.id << " at line: " << tok.line << ", col: " << tok.col << std::endl;
	} 

	if(the_lexer.errors.size() > 0) {
		for(auto err : the_lexer.errors) {
			std::cout << "Lexical error: " << err.msg << " at line: " << err.line << ", col: " << err.col << std::endl;
		} 
	}

	return 0;
}
