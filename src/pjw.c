#include <ghash.h>

uint32_t hash_pjw32_4(const char *datum, size_t length) {
  uint32_t hash = 0;
  uint32_t bits = 0;
  size_t i = 0;

  for (i = 0; i < length; i++) {
    hash = (hash << 4) + *datum++;
    if ((bits = hash & 0xF0000000) != 0) {
      hash ^= bits >> 24;
    }
    hash &= ~bits;
  }

  return hash;
}

uint32_t hash_pjw32_5(const char *datum, size_t length) {
  uint32_t hash = 0;
  uint32_t bits = 0;
  size_t i = 0;

  for (i = 0; i < length; i++) {
    hash = (hash << 5) + *datum++;
    if ((bits = hash & 0xF0000000) != 0) {
      hash ^= bits >> 24;
    }
    hash &= ~bits;
  }

  return hash;
}
