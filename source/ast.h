
#pragma once

#include <vector>
#include <stdint.h>
#include "lexer.h"
#include "string_table.h"
#include "string_view.h"

namespace skeleton {
	namespace ast {
		enum type_id_enum {
			type_id_unknown,
			type_id_bool,
			type_id_s8,
			type_id_u8,
			type_id_s16,
			type_id_u16,
			type_id_s32,
			type_id_u32,
			type_id_s64,
			type_id_u64,
			type_id_float32,
			type_id_float64,
			type_id_string,
			type_id_struct,
			type_id_array,
		};

		struct ast_type {
			type_id_enum id;
			string_table_id type_name;
			ast_type* sub_type;
		};

		enum ast_node_type_enum {
			ast_node_type_func_def,
			ast_node_type_struct_def,
			ast_node_type_func_call,
			ast_node_type_scope,
			ast_node_type_statement,
			ast_node_type_unary_op,
			ast_node_type_binary_op,
			ast_node_type_atom,
			ast_node_control_flow,
		};

		//Expressions

		struct ast_unary_operator {
			ast_expr* operand;
		};

		struct ast_binary_operator {
			ast_expr* left;
			ast_expr* right;
		};

		struct ast_func_call {
			string_table_id name;
			std::vector<ast_expr> arg;
		};

		struct ast_variable {
			string_table_id name;
		};

		struct ast_expr {
			ast_type result_type;
			union {
				ast_unary_operator unary_op;
				ast_binary_operator binary_op;
				ast_func_call func_call;
				ast_variable variable;
			};
		};



		struct ast_declaration {
			std::vector<ast_declaration> declarations;
			std::vector<ast_statement> statements;
		};


	}
}
