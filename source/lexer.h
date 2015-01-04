
#pragma once

#include <vector>
#include "string_view.h"
#include "string_table.h"

namespace skeleton {
	enum token_id {
		//Keywords
		token_import,    // #import
		token_def,       // def
		token_yield,     // yield
		token_return,    // return
		token_if,        // if
		token_elif,      // elif
		token_else,      // else
		token_for,       // for
		token_while,     // while
		token_struct,    // struct
		token_enum,      // enum
		token_ref,		 // ref
		token_mutable,   // mutable
		token_using,     // using
		token_namespace, // namespace
		token_cast,      // cast
		token_alloc,     // alloc
		token_free,      // free
		token_switch,    // switch
		token_case,      // case
		token_break,     // break
		token_continue,  // continue
		token_assert,    // assert
		token_atomic,    // atomic

		//Operators
		token_op_assign,      // =
		token_op_type_spec,   // :
		token_op_decl_assign, // :=
		token_op_add,         // +
		token_op_sub,         // -
		token_op_mul,         // *
		token_op_div,         // /
		token_op_mod,         // %
		token_op_concat,      // ::
		token_op_power,		  // ^

		//Logic operators
		token_op_eq,            // ==
		token_op_neq,           // !=
		token_op_less,          // <
		token_op_greater,       // >
		token_op_less_or_eq,    // <=
		token_op_greater_or_eq, // >=
		token_op_not,           // !
		token_op_and,			// &&
		token_op_or,			// ||
		token_op_bw_and,		// &
		token_op_bw_or,			// |
		token_op_bw_xor,		// |||

		token_op_in,            // <-
		token_op_to,            // ->

		//Binding operators
		token_left_paren,      // (
		token_right_paren,     // )
		token_left_subscript,  // [
		token_right_subscript, // ]
		token_left_brace,      // { 
		token_right_brace,     // }
		token_semicolon,	   // ;
		token_comma,           // ,
		token_period,          // .
		token_range,           // ..
		token_unspecified,     // ...

		//Other tokens
		token_identifier,     // some_ident0
		token_int_literal,    // 7
		token_float_literal,  // 3.14
		token_bool_literal,   // false/true
		token_string_literal, // "Hello world"
		token_char_literal,   // 'j'
	};

	const char* token_names[] = {
		"import",
		"def",
		"yield",
		"return",
		"if",
		"elif",
		"else",
		"for",
		"while",
		"struct",
		"enum",
		"ref",
		"mutable",
		"using",
		"namespace",
		"cast",
		"alloc",
		"free",
		"switch",
		"case",
		"break",
		"continue",
		"assert",
		"atomic",
		"=",
		":",
		":=",
		"+",
		"-",
		"*",
		"/",
		"%%",
		"::",
		"^",
		"==",
		"!=",
		"<",
		">",
		"<=",
		">=",
		"!",
		"&&",
		"||",
		"&",
		"|",
		"|||",
		"<-",
		"->",
		"(",
		")",
		"[",
		"]",
		"{",
		"}",
		";",
		",",
		".",
		"..",
		"...",
		"identifier",
		"integer",
		"float",
		"bool",
		"string",
		"char",
	};

	struct token {
		token_id id;

		//Source pos
		size_t pos;

		//Meta data
		size_t line;
		size_t col;

		union {
			string_table_id identifier_name;
			uint64_t int_literal_value;
			long double float_literal_value;
			char char_literal_value;
		};
	};

	std::string to_string(const string_table &table, const token& tok) {
		std::string result;
        
		//Special case
		if(tok.id == token_identifier) {
            string_view sv = get(table, tok.identifier_name);
			result += "[identifier '";
			result += to_string(sv);
			result += "']";
		} else if(tok.id == token_int_literal) {
            //string_view sv = get(table, tok.identifier_name);
			result += "[integer '";
            result += std::to_string(tok.int_literal_value);
			result += "']";
		} else if(tok.id == token_float_literal) {
            //string_view sv = get(table, tok.identifier_name);
			result += "[float '";
            result += std::to_string(tok.float_literal_value);
			result += "']";
		} else if(tok.id == token_string_literal) {
            string_view sv = get(table, tok.identifier_name);
			result += "[string '";
			result += to_string(sv);
			result += "']";
		} else if(tok.id == token_char_literal) {
			result += "[char '";
			result += tok.char_literal_value;
			result += "']";
		} else if(tok.id == token_bool_literal) {
            string_view sv = get(table, tok.identifier_name);
			result += "[bool '";
			result += to_string(sv);
			result += "']";
		} else {
			result += "['";
			result += token_names[tok.id];
			result += "']";
		}

		result += " @ Line: ";
		result += std::to_string(tok.line);
		result += " Col: ";
		result += std::to_string(tok.col);
		result += ". ";

		return result;
	}

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

		string_table* str_table;
		std::vector<token> tokens;
		std::vector<lexer_error> errors;
		std::vector<string_table_id> keywords;
		std::vector<token_id> keyword_ids;
	};

	template <size_t N>
	void lexer_add_keyword(lexer& the_lexer, const char (&kw)[N], token_id id) {
		string_view sv = slice(kw, 0, N - 1);
		the_lexer.keywords.push_back(add(*the_lexer.str_table, sv));
		the_lexer.keyword_ids.push_back(id);
	}

	inline
	void lexer_add_keywords(lexer& the_lexer) {
		the_lexer.keywords.reserve(23);
		the_lexer.keyword_ids.reserve(23);

		lexer_add_keyword(the_lexer, "def", token_def);
		lexer_add_keyword(the_lexer, "import", token_import);
		lexer_add_keyword(the_lexer, "for", token_for);
		lexer_add_keyword(the_lexer, "struct", token_struct);
		lexer_add_keyword(the_lexer, "using", token_using);
		lexer_add_keyword(the_lexer, "yield", token_yield);
		lexer_add_keyword(the_lexer, "return", token_return);
		lexer_add_keyword(the_lexer, "if", token_if);
		lexer_add_keyword(the_lexer, "else", token_else);
		lexer_add_keyword(the_lexer, "elif", token_elif);
		lexer_add_keyword(the_lexer, "ref", token_ref);
		lexer_add_keyword(the_lexer, "mutable", token_mutable);
		lexer_add_keyword(the_lexer, "while", token_while);
		lexer_add_keyword(the_lexer, "enum", token_enum);
		lexer_add_keyword(the_lexer, "false", token_bool_literal);
		lexer_add_keyword(the_lexer, "true", token_bool_literal);
		lexer_add_keyword(the_lexer, "namespace", token_namespace);
		lexer_add_keyword(the_lexer, "cast", token_cast);
		lexer_add_keyword(the_lexer, "alloc", token_alloc);
		lexer_add_keyword(the_lexer, "free", token_free);
		lexer_add_keyword(the_lexer, "switch", token_switch);
		lexer_add_keyword(the_lexer, "case", token_case);
		lexer_add_keyword(the_lexer, "break", token_break);
		lexer_add_keyword(the_lexer, "continue", token_continue);
		lexer_add_keyword(the_lexer, "assert", token_assert);
		lexer_add_keyword(the_lexer, "atomic", token_atomic);
	}

	inline
	void lexer_add_token(lexer& the_lexer, token the_token) {
		the_lexer.tokens.push_back(the_token);
	}

	inline
	void lexer_report_error(lexer& the_lexer, std::string msg) {
		lexer_error err;
		err.pos = the_lexer.pos;
		err.line = the_lexer.line;
		err.col = the_lexer.col;
		err.msg = msg;

		the_lexer.errors.push_back(err);
	}

	inline
	bool is_eof(const lexer& the_lexer) {
		return the_lexer.pos >= the_lexer.source.length();
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
				if(c2 == '*') {
                    advance(the_lexer, c2);
					lex_multi_line_comment(the_lexer);
				}
			} else if(c == '*' && !is_eof(the_lexer)) {
				char c2 = get_char(the_lexer);
				if(c2 == '/') {
                    advance(the_lexer, c2);
					return;
				}
			}
		}

		lexer_error err;
		err.pos = begin_pos;
		err.line = begin_line;
		err.col = begin_col;
		err.msg = "Unmatched opening of multi-line comment.";

		the_lexer.errors.push_back(err);
	}

	void lex_identifier(lexer& the_lexer) {
		token tok;
		tok.pos = the_lexer.pos;
		tok.line = the_lexer.line;
		tok.col = the_lexer.col;

		while(!is_eof(the_lexer)) {
			char c = get_char(the_lexer);

			if((c >= 'a' && c <= 'z')) {
				;
			} else if((c >= 'A' && c <= 'Z')) {
				;
			} else if((c >= '0' && c <= '9')) {
				;
			} else if(c == '_') {
				;
			} else {
				break;
			}
			
			advance(the_lexer, c);
		}

		auto len = the_lexer.pos - tok.pos;

		//Find out if the string matches one of the language keywords, otherwise report as identifier
		tok.identifier_name = add(*the_lexer.str_table, slice(the_lexer.source, tok.pos, len));
		tok.id = token_identifier;

		const auto sz = the_lexer.keywords.size();
		for(size_t i = 0; i < sz; ++i) {
			if(tok.identifier_name == the_lexer.keywords[i]) {
				tok.id = the_lexer.keyword_ids[i];
				break;
			}
		}

		lexer_add_token(the_lexer, tok);
	}

	void lex_operator(lexer& the_lexer) {
		token tok;
		tok.pos = the_lexer.pos;
		tok.line = the_lexer.line;
		tok.col = the_lexer.col;

		char first_char = get_char(the_lexer);
		advance(the_lexer, first_char);

		//For the two character operators we need to check the next character
		char second_char = '\0';
		if(!is_eof(the_lexer)) {
			second_char = get_char(the_lexer);
		}

		switch(first_char) {
			case '=':
				{
					if(second_char == '=') {
						tok.id = token_op_eq;
						advance(the_lexer, second_char);
					} else {
						tok.id = token_op_assign;
					}
				}
				break;
			case '<':
				{
					if(second_char == '=') {
						tok.id = token_op_less_or_eq;
						advance(the_lexer, second_char);
					} else if(second_char == '-') {
						tok.id = token_op_in;
						advance(the_lexer, second_char);
					} else {
						tok.id = token_op_less;
					}
				}
				break;
			case '>':
				{
					if(second_char == '=') {
						tok.id = token_op_greater_or_eq;
						advance(the_lexer, second_char);
					} else {
						tok.id = token_op_greater;
					}
				}
				break;
			case '!':
				{
					if(second_char == '=') {
						tok.id = token_op_neq;
						advance(the_lexer, second_char);
					} else {
						tok.id = token_op_not;
					}
				}
				break;
			case '&':
				{
					if(second_char == '&') {
						tok.id = token_op_and;
						advance(the_lexer, second_char);
					} else {
						tok.id = token_op_bw_and;
					}
				}
				break;
			case '|':
				{
					if(second_char == '|') {
						advance(the_lexer, '|');
						if(!is_eof(the_lexer) && get_char(the_lexer) == '|') {
							tok.id = token_op_bw_xor;
							advance(the_lexer, second_char);
						} else {
							tok.id = token_op_or;
						}
					} else {
						tok.id = token_op_bw_or;
					}
				}
				break;
			case ',':
				tok.id = token_comma;
				break;
			case '.':
				{
					if(second_char == '.') {
						tok.id = token_range;
						advance(the_lexer, second_char);
						if(!is_eof(the_lexer) && get_char(the_lexer) == '.') {
							tok.id = token_unspecified;
							advance(the_lexer, '.');
						}
					} else {
						tok.id = token_period;
					}
				}
				break;
			case ':':
				{
					if(second_char == '=') {
						tok.id = token_op_decl_assign;
						advance(the_lexer, second_char);
					} else if(second_char == ':') {
						tok.id = token_op_concat;
						advance(the_lexer, second_char);
					} else {
						tok.id = token_op_type_spec;
					}
				}
				break;
			case '(':
				tok.id = token_left_paren;
				break;
			case ')':
				tok.id = token_right_paren;
				break;
			case '[':
				tok.id = token_left_subscript;
				break;
			case ']':
				tok.id = token_right_subscript;
				break;
			case '{':
				tok.id = token_left_brace;
				break;
			case '}':
				tok.id = token_right_brace;
				break;
			case '+':
				tok.id = token_op_add;
				break;
			case '-':
				{
					if(second_char == '>') {
						tok.id = token_op_to;
						advance(the_lexer, second_char);
					} else {
						tok.id = token_op_sub;
					}
				}
				break;
			case '*':
				tok.id = token_op_mul;
				break;
			case '/':
				{
					if(second_char == '/') {
						advance(the_lexer, second_char);
						lex_single_line_comment(the_lexer);
						return;
					}
					if(second_char == '*') {
						advance(the_lexer, second_char);
						lex_multi_line_comment(the_lexer);
						return;
					}
					tok.id = token_op_div;
				}
				break;
			case '%':
				tok.id = token_op_mod;
				break;
			case '^':
				tok.id = token_op_power;
				break;
			case ';':
				tok.id = token_semicolon;
				break;

			default:
				assert(false); //Should never reach this
				break;
		}

		lexer_add_token(the_lexer, tok);
	}

	inline
	void lex_numeric_literal(lexer& the_lexer) {
		token tok;
		tok.pos = the_lexer.pos;
		tok.line = the_lexer.line;
		tok.col = the_lexer.col;

		bool is_float = false;

		while(!is_eof(the_lexer)) {
			char c = get_char(the_lexer);

			bool found = false;			
			switch(c) {
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					advance(the_lexer, c);
					found = true;
					break;
			}

			if(!found)
				break;
		}

		if(!is_eof(the_lexer)) {
			char c = get_char(the_lexer);

			if(c == '.') {
				is_float = true;
				advance(the_lexer, c);
			}
		}

		while(!is_eof(the_lexer)) {
			char c = get_char(the_lexer);

			bool found = false;			
			switch(c) {
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					advance(the_lexer, c);
					found = true;
					break;
			}

			if(!found)
				break;
		}

        auto len = the_lexer.pos - tok.pos;
		if(is_float) {
			tok.id = token_float_literal;
			tok.float_literal_value = to_long_double(slice(the_lexer.source, tok.pos, len));
		} else {
			tok.id = token_int_literal;
			tok.int_literal_value = to_uint(slice(the_lexer.source, tok.pos, len));
		}
		//tok.identifier_name = add(*the_lexer.str_table, slice(the_lexer.source, tok.pos, len));

		lexer_add_token(the_lexer, tok);		
	}

	void lex_string_literal(lexer& the_lexer) {
		char pre = get_char(the_lexer);
		assert(pre == '\"');

		advance(the_lexer, pre);

		token tok;
		tok.pos = the_lexer.pos;
		tok.line = the_lexer.line;
		tok.col = the_lexer.col;

		while(!is_eof(the_lexer)) {
			char c = get_char(the_lexer);
			if(c == '\"')
				break;

			advance(the_lexer, c);
		}

		tok.id = token_string_literal;
        auto len = the_lexer.pos - tok.pos;
        tok.identifier_name = add(*the_lexer.str_table, slice(the_lexer.source, tok.pos, len));
//		tok.identifier_name = slice(the_lexer.source, tok.pos, the_lexer.pos - tok.pos);

		char post = '\0';
		if(!is_eof(the_lexer)) {
			post = get_char(the_lexer);
			advance(the_lexer, post);
		}

		if(post != '\"') {
			lexer_error err;
			err.pos = tok.pos;
			err.line = tok.line;
			err.col = tok.col;
			err.msg = "Unmatched opening of string literal.";

			the_lexer.errors.push_back(err);
		} else {
			the_lexer.tokens.push_back(tok);
		}
	}

	void lex_char_literal(lexer& the_lexer) {
		char pre = get_char(the_lexer);
		assert(pre == '\'');

		advance(the_lexer, pre);

		token tok;
		tok.pos = the_lexer.pos;
		tok.line = the_lexer.line;
		tok.col = the_lexer.col;

		if(is_eof(the_lexer)) {
			lexer_error err;
			err.pos = tok.pos;
			err.line = tok.line;
			err.col = tok.col;
			err.msg = "Unmatched opening of char literal.";

			the_lexer.errors.push_back(err);
			return;
		}

		advance(the_lexer);

		if(is_eof(the_lexer) || get_char(the_lexer) != '\'') {
			lexer_error err;
			err.pos = tok.pos;
			err.line = tok.line;
			err.col = tok.col;
			err.msg = "Unmatched opening of char literal.";

			the_lexer.errors.push_back(err);
			return;
		}

		tok.id = token_char_literal;
		tok.char_literal_value = the_lexer.source[tok.pos];
        //tok.identifier_name = add(*the_lexer.str_table, slice(the_lexer.source, tok.pos, len));

		the_lexer.tokens.push_back(tok);

		advance(the_lexer, '\'');
	}

	inline
	lexer lex(std::string str, string_table &str_table) {
		lexer res;
        
        res.str_table = &str_table;

		res.source = str;
		res.pos = 0;
		res.line = 1;
		res.col = 1;

		res.tokens.reserve(1024);
        
        lexer_add_keywords(res);

		while(res.pos < res.source.length()) {
			char c = get_char(res);
			switch(c) {
				//Whitespace
				case ' ':
				case '\t':
				case '\r':
				case '\n':
					advance(res, c);
					break;

				//Compiler directives
				case '#':
					advance(res, c);
					break;

				//Annotations
				case '@':
					advance(res, c);
					break;

				//Identifiers and keywords, and bool literals
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
				case 'H':
				case 'I':
				case 'J':
				case 'K':
				case 'L':
				case 'M':
				case 'N':
				case 'O':
				case 'P':
				case 'Q':
				case 'R':
				case 'S':
				case 'T':
				case 'U':
				case 'V':
				case 'W':
				case 'X':
				case 'Y':
				case 'Z':
				case 'a':
				case 'b':
				case 'c':
				case 'd':
				case 'e':
				case 'f':
				case 'g':
				case 'h':
				case 'i':
				case 'j':
				case 'k':
				case 'l':
				case 'm':
				case 'n':
				case 'o':
				case 'p':
				case 'q':
				case 'r':
				case 's':
				case 't':
				case 'u':
				case 'v':
				case 'w':
				case 'x':
				case 'y':
				case 'z':
				case '_':
                    lex_identifier(res);
					break;

				//Numeric literals
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					lex_numeric_literal(res);
					break;

				//String literals
				case '\"':
					lex_string_literal(res);
					break;

				//Character literals
				case '\'':
					lex_char_literal(res);
					break;

				//Operators
				case '=':
				case '<':
				case '>':
				case '!':
				case '&':
				case '|':
				case ',':
				case '.':
				case ':':
				case '^':
				case '(':
				case ')':
				case '[':
				case ']':
				case '{':
				case '}':
				case '+':
				case '-':
				case '*':
				case '/':
				case '%':
				case ';':
					lex_operator(res);
					//advance(res, c);
					break;

				default:
					{
						std::string err_msg = "Unrecognized character '";
						err_msg += c;
						err_msg += "' found.";
						lexer_report_error(res, err_msg);
						advance(res, c);
					}
					break;
			} // end of switch
		
		} // end of while-loop

		return res;
	} //end of lex-function

} // end of namespace skeleton
