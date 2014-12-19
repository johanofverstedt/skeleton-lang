
#pragma once

#include "string_view.h"
#include <stdint.h>
#include <string>
#include <vector>

namespace skeleton {
	enum table_size_enum {
		TABLE_SIZE = 12289,
	};

	struct string_table_id {
		size_t first_index;
		size_t second_index;
	};

	inline
	string_table_id default_table_id() {
		string_table_id id;
		id.first_index = TABLE_SIZE;

	}

	struct string_table {
		std::vector<std::string> buckets[TABLE_SIZE];
	};

	size_t table_hash(const std::string &s) {
		std::hash<std::string> hf;
		return hf(s) % TABLE_SIZE;
	}

	string_table_id add(string_table& table, string_view sv) {
		
	} 

	string_view get(const string_table& table, string_table_id id) {
		assert(table.buckets[id.first_index].size() > id.second_index);
		
		const std::string& str_ref = table.buckets[id.first_index][id.second_index];
		return slice(str_ref, 0, str_ref.length());
	}

}
