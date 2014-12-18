
#include <vector>
#include <string>
#include "string_view.h"

#include "ast.h"

namespace skeleton {
	struct program_master {
		//Types and values
		std::unordered_map<std::string, type>
		//Program structures
		std::vector<std::string> files;
		std::vector<ast_node*> ast;
	};
}
