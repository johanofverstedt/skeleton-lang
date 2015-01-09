
#pragma once

#include <vector>
#include <stdint.h>

#include "lexer.h"
#include "ast.h"

namespace skeleton {
	struct parser {
		std::vector<token> tokens;
		size_t index;
		string_table_id file_path_string_id;
	};
	inline
	ast::ast_declaration *parse_declaration(parser& p, )

}