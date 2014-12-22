
#pragma once

#include "string_view.h"
#include <stdint.h>
#include <string>
#include <vector>
#include <iostream>

namespace skeleton {
	//Table size found at http://www.orcca.on.ca/~yxie/courses/cs2210b-2011/htmls/extra/PlanetMath_%20goodhashtable.pdf
	enum table_size_enum {
		TABLE_SIZE = 193,//196613,
	};

	struct string_table_id {
		size_t first_index;
		size_t second_index;
	};
	inline
	bool operator==(const string_table_id& x, const string_table_id& y) {
		return x.first_index == y.first_index && x.second_index == y.second_index;
	}
	inline
	bool operator!=(const string_table_id& x, const string_table_id& y) {
		return !(x == y);
	}


	inline
	string_table_id default_table_id() {
		string_table_id id;
		id.first_index = TABLE_SIZE;
        return id;
	}

	struct string_table {
		struct bucket {
			std::string str;
			uint64_t hash;
		};
		std::vector<bucket> buckets[TABLE_SIZE];
	};

	void print_string_table(const string_table& table) {
		for(size_t i = 0; i < TABLE_SIZE; ++i) {
			if(!table.buckets[i].empty()) {
				std::cout << "[" << i << ": ";
				for(size_t j = 0; j < table.buckets[i].size(); ++j) {
					std::cout << "(" << j << ", '" << table.buckets[i][j].str << "')";
					if(j + 1 != table.buckets[i].size()) {
						std::cout << ", ";
					}
				}
				std::cout << "]" << std::endl;
			}
		}
	}

	string_table_id add(string_table& table, string_view sv) {
		auto sv_hash = sv.hash;
		size_t thash = (size_t)(sv_hash % TABLE_SIZE);
		auto &v = table.buckets[thash];
		auto v_len = v.size();
		for(size_t i = 0; i < v_len; ++i) {
			auto& bucket_ref = v[i];
			if(bucket_ref.hash == sv_hash) {
				string_table_id id;
				id.first_index = thash;
				id.second_index = i;
				return id;
			}
		}

		//The string was not in the table already
		//Add it to the table and return the index to its bucket

        string_table::bucket b;
		b.str = to_string(sv);
		b.hash = sv_hash;
		v.push_back(b);

		{
			string_table_id id;
			id.first_index = thash;
			id.second_index = v_len;
			return id;
		}
	} 

	string_table_id add(string_table& table, const std::string& s) {
		string_view sv;
		sv.ptr = s.c_str();
		sv.length = s.length();
		hash_string_view(sv);
		return add(table, sv);
	}

	string_view get(const string_table& table, string_table_id id) {
		assert(table.buckets[id.first_index].size() > id.second_index);
		
		auto& bucket_ref = table.buckets[id.first_index][id.second_index];
		string_view sv =  slice(bucket_ref.str, 0, bucket_ref.str.length(), false);
		sv.hash = bucket_ref.hash;
		return sv;
	}

}
