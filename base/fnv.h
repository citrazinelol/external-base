#pragma once
#include "includes.h"

#define HASH( str ) \
       []() { \
           constexpr hash_t ret = hash::fnv1a_ct( str ); \
           return ret; \
       }() \

using hash_t = uint32_t;

namespace hash {
	enum MagicNumbers : uint32_t {
		FNV1A_PRIME = 16777619u,
		FNV1A_BIAS = 2166136261u
	};

	
	__forceinline hash_t fnv1a(const void *data, size_t len) {
		hash_t  out;
		uint8_t *enc;

		if (!data || !len)
			return hash_t{};

		
		out = FNV1A_BIAS;
		enc = (uint8_t *)data;

		
		for (size_t i{}; i < len; ++i) {
			out ^= enc[i];
			out *= FNV1A_PRIME;
		}

		return out;
	}

	
	__forceinline hash_t fnv1a(const std::string &str) {
		return fnv1a(str.c_str(), str.length());
	}

	
	constexpr hash_t fnv1a_ct(const char *str, hash_t start = FNV1A_BIAS) {
		return (*str != '\0') ? fnv1a_ct(str + 1, (*str ^ start) * FNV1A_PRIME) : start;
	}
};