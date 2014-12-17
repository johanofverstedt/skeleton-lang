
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

	struct lexer_error {
		size_t pos;
		size_t line;
		size_t col;
		std::string msg;
	};

	struct lexer {
		std::string source;
		size_t pos;
		size_t line;
		size_t col;

		std::vector<token> tokens;
		std::vector<lexer_error> errors;
	};

	inline
	bool is_eof(const lexer& the_lexer) {
		return the_lexer.pos < the_lexer.source.length();
	}

	inline
	char get_char(const lexer& the_lexer) {
		assert(!is_eof(the_lexer));
		return the_lexer.source[the_lexer.pos];
	}

	inline
	void advance(lexer& the_lexer, char c) {
		if(c == '\n') {
			++the_lexer.line;
			the_lexer.col = 1;
		} else if(c == '\t') {
			the_lexer.col += 4;
		} else {
			++the_lexer.col;
		}
		++the_lexer.pos;
	}
	inline
	void advance(lexer& the_lexer) {
		char c = get_char(the_lexer);
		advance(the_lexer, c);
	}

	void lex_single_line_comment(lexer& the_lexer) {
		while(!is_eof(the_lexer)) {
			char c = get_char(the_lexer);
			advance(the_lexer, c);

			if(c == '\r') {
				if(!is_eof(the_lexer)) {
					char c2 = get_char(the_lexer);
					if(c2 == '\n') {
						advance(the_lexer, c2);
						return;
					}
				}
			}
			if(c == '\n') {
				advance(the_lexer, c);
				return;
			}
		}
	}

	void lex_multi_line_comment(lexer& the_lexer) {
		assert(the_lexer.col >= 3);

		auto begin_pos = the_lexer.pos;
		auto begin_line = the_lexer.line;
		auto begin_col = the_lexer.col - 2;

		while(!is_eof(the_lexer)) {
			char c = get_char(the_lexer);
			advance(the_lexer, c);

			if(c == '/' && !is_eof(the_lexer)) {
				char c2 = get_char(the_lexer);
				advance(the_lexer, c2);
				if(c2 == '*') {
					lex_multi_line_comment(the_lexer);
				}
			} else if(c == '*' && !is_eof(the_lexer)) {
				char c2 = get_char(the_lexer);
				advance(the_lexer, c2);
				if(c2 == '/') {
					return;
				}
			}
		}

		lexer_error err;
		err.pos = begin_pos;
		err.line = begin_line;
		err.col = begin.col;
		err.msg = "Unmatched opening of multi-line comment.";
		the_lexer.errors.push_back(err);
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
