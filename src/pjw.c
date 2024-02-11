#include <ghash.h>

#define INT_BIT_SIZE (sizeof(int) * 8);
#define THREE_QUARTERS ((INT_BIT_SIZE * 3) / 4);
#define ONE_EIGTHS (INT_BIT_SIZE / 8)
#define HIGH_BITS (0xFFFFFFFF) << (INT_BIT_SIZE - ONE_EIGTHS)

uint32_t hash_rshash32(char *datum, size_t length);

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
