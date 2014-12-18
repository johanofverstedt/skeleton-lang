
#pragma once

#include <stdint.h>
#include "string_view.h"

namespace skeleton {
	namespace ast {
		enum type_id_enum {
			type_id_bool,
			type_id_char,
			type_id_s8,
			type_id_u8,
			type_id_s16,
			type_id_u16,
			type_id_s32,
			type_id_u32,
			type_id_s64,
			type_id_u64,
			type_id_int,
			type_id_uint,
			type_id_float32,
			type_id_float64,
			type_id_string,
			type_id_struct,
			type_id_array,
		};

		struct ast_type {
			type_id_enum id;
			string_view type_name;
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

		//
		// Base class for all entities in the AST.
		//
		struct ast_node {
			ast_node_type_enum node_type;
		};

		struct ast_value {
			ast_type type;

		};

		struct ast_expr {
			size_t type_index;
			size_t value_index;

			union {
				std::vector<ast*> children;

			};
		};
	}
}
