
#pragma once

#include <string>
#include <assert.h>

namespace skeleton {
	struct string_view {
		string_view() : ptr(nullptr), length(0), hash(0) {}
		const char* ptr;
		size_t length;
		size_t hash;
	};

	struct string_hash_map {
		string_hash_map() {
			for(size_t i = 0; i < 65535; ++i)
				data[i] = {};
		}
		string_view data[65535];
	};

	size_t hash(const char* ptr, size_t len) {
		size_t hc = 0;
		for(size_t i = 0; i < len; ++i) {
			hc += (i + 15) * ptr[i];
		}
		return hc;
	}
/*
	string_view& add(string_hash_map& hm, const string_view& sv) {
		auto hc = hash(sv.ptr, sv.length) & 65535;

		if(data[hc].ptr) {
			if(compare(data[hc], sv)) {

			}
		}
	}
*/
	bool compare(const string_view& x, const string_view& y) {
		if(x.hash != y.hash)
			return false;

		auto x_len = x.length;
		if(x_len != y.length)
			return false;
		const char* x_ptr = x.ptr;
		const char* y_ptr = y.ptr;
		for(size_t i = 0; i < x_len; ++i) {
			if(x_ptr[i] != y_ptr[i])
				return false;
		}
		return true;
	}

	inline
	size_t length(const string_view& sv) {
		return sv.length;
	}

	std::string to_string(const string_view& sv) {
		return std::string(sv.ptr, sv.length);
	}

	string_view slice(const char* ptr, size_t pos, size_t length) {
		string_view ret;

		ret.ptr = ptr + pos;
		ret.length = length;
		ret.hash = hash(ret.ptr, ret.length);

		return ret;
	}

	string_view slice(const string_view& sv, size_t pos, size_t length) {
		assert(skeleton::length(sv) >= pos + length);

		return slice(sv.ptr, pos, length);
	}

	string_view slice(const std::string& s, size_t pos, size_t length) {
		assert(s.length() >= pos + length);

		return slice(s.c_str(), pos, length);
	}
}
