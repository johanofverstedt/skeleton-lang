
#pragma once

#include <vector>
#include "string_view.h"

namespace skeleton {
	enum token_id {
		//Keywords
		token_import, // #import
		token_def, // def
		token_yield, // yield
		token_if, // if
		token_else_if, // else if
		token_else, // else
		token_for, // for
		token_struct, // struct

		//Operators
		token_op_assign, // =
		token_op_type_spec, // :
		token_op_decl_assign, // :=
		token_op_add, // +
		token_op_sub, // -
		token_op_mul, // *
		token_op_div, // /
		token_op_mod, // %

		//Logic operators
		token_op_eq, // ==
		token_op_neq, // !=
		token_op_less, // <
		token_op_greater, // >
		token_op_less_or_eq, // <=
		token_op_greater_or_eq, // >=
		token_op_not, // !

		//Binding operators
		token_left_paren, // (
		token_right_paren, // )
		token_left_subscript, // [
		token_right_subscript, // ]
		token_left_brace, // { 
		token_right_brace, // }
		token_comma, // ,
		token_period, // .

		//Other tokens
		token_identifier, // some_ident0
		token_int_literal, // 7
		token_float_literal, // 3.14
		token_bool_literal, // false/true
		token_string_literal, // "Hello world"
		token_char_literal, // 'j'
	};


	struct token {
		token_id id;

		//Source pos
		size_t pos;
		size_t length;

		//Meta data
		size_t line;
		size_t col;
	};

	struct lexer {
		std::string source;
		size_t pos;
		size_t line;
		size_t col;

		std::vector<token> tokens;
	};

	void advance(lexer& the_lexer) {
		++the_lexer.pos;
		++the_lexer.col;
	}
	void advanceln(lexer& the_lexer) {
		++the_lexer.pos;
		++the_lexer.line;
		the_lexer.col = 1;
	}
	void advancetab(lexer& the_lexer) {
		++the_lexer.pos;
		the_lexer.col += 4;
	}

	void lex_single_line_comment(lexer& the_lexer) {
		char c = the_lexer.source[the_lexer.pos];
		while(c == ' ' || c == '\t') {
			if(c == ' ') {

			}

			c = the_lexer.source[the_lexer.pos];
		}
	}

	lexer lex(std::string str) {
		lexer res;

		res.source = str;
		res.pos = 0;
		res.line = 1;
		res.col = 1;

		res.tokens.reserve(1024);

		while(res.pos < res.source.length()) {

		}
	}
}
