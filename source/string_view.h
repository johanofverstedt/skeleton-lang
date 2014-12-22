
#pragma once

#include <string>
#include <stdint.h>
#include <assert.h>

#define FMV_OFFSET 14695981039346656037ULL
#define FMV_PRIME 1099511628211ULL

namespace skeleton {
	struct string_view {
		string_view() : hash(0), ptr(nullptr), length(0) {}
		uint64_t hash;
		const char* ptr;
		size_t length;
	};

	//This hash function only works properly for little endian architectures
	inline
	uint64_t hash(const char* ptr, size_t len) {
		uint64_t hc = FMV_OFFSET;
		unsigned char* hc_char_ptr = (unsigned char*)&hc;
		for(size_t i = 0; i < len; ++i) {
			hc *= FMV_PRIME;
			(*hc_char_ptr) ^= (unsigned char)ptr[i];
		}
        return hc;
	}

	inline
	void hash_string_view(string_view& sv) {
		sv.hash = hash(sv.ptr, sv.length);
	}

	bool compare(const string_view& x, const string_view& y) {
		if((x.hash != 0 && y.hash != 0) && x.hash != y.hash)
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

	inline
	const char* begin(const string_view& sv) {
		return sv.ptr;
	}
	inline
	const char* end(const string_view& sv) {
		return sv.ptr + sv.length;
	}

	std::string to_string(const string_view& sv) {
		return std::string(sv.ptr, sv.length);
	}

	string_view slice(const char* ptr, size_t pos, size_t length, bool do_hash = true) {
		string_view ret;

		ret.ptr = ptr + pos;
		ret.length = length;
		if(do_hash)
			hash_string_view(ret);
		else
			ret.hash = 0ULL;

		return ret;
	}

	string_view slice(const string_view& sv, size_t pos, size_t length, bool do_hash = true) {
		assert(skeleton::length(sv) >= pos + length);

		return slice(sv.ptr, pos, length, do_hash);
	}

	string_view slice(const std::string& s, size_t pos, size_t length, bool do_hash = true) {
		assert(s.length() >= pos + length);

		return slice(s.c_str(), pos, length, do_hash);
	}

	int64_t to_int(const string_view& sv) {
		assert(sv.length > 0);

		int64_t result = 0;
		for(size_t i = 0; i < sv.length; ++i) {
			result *= 10;
			result += (int64_t)(*(sv.ptr + i) - '0');
		}
		return result;
	}

	uint64_t to_uint(const string_view& sv) {
		assert(sv.length > 0);

		uint64_t result = 0U;
		for(size_t i = 0; i < sv.length; ++i) {
			result *= 10U;
			result += (uint64_t)(*(sv.ptr + i) - '0');
		}
		return result;
	}

	long double to_long_double(const string_view& sv) {
		assert(sv.length > 0);

		std::string str = std::string(sv.ptr, sv.length);
		return std::stold(str);
	}

	char to_char(const string_view& sv) {
		assert(sv.length > 0);

		return *sv.ptr;
	}

	bool to_bool(const string_view& sv) {
		assert(sv.length > 0);
		return *sv.ptr == 't';
	}
}
