#include <ghash.h>

uint32_t hash_rshash32(char *datum, size_t length) {
  uint32_t b = 378551u;
  uint32_t a = 63689u;
  uint32_t hash = 0;
  size_t i = 0;

  for (i = 0; i < length; ++datum, ++i) {
    hash = hash * a + (*datum);
    a = a * b;
  }
  return hash;
}

uint64_t hash_rshash64(char *datum, size_t length) {
  uint64_t b = 378551u;
  uint64_t a = 63689u;
  uint64_t hash = 0;
  size_t i = 0;

  for (i = 0; i < length; ++datum, ++i) {
    hash = hash * a + (*datum);
    a = a * b;
  }

  return hash;
}
