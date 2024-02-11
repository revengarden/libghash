#ifndef GHASH_H
#define GHASH_H

#include <stddef.h>
#include <stdint.h>

uint32_t hash_rshash32(char *datum, size_t length);
uint64_t hash_rshash64(char *datum, size_t length);

uint32_t hash_pjw32_4(const char *datum, size_t length);
uint32_t hash_pjw32_5(const char *datum, size_t length);

uint32_t hash_rolling32(const char *datum, size_t length, const uint32_t prime,
                        const uint32_t mod, const char low);

#endif
