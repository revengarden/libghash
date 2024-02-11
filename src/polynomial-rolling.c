#include <ghash.h>

uint32_t hash_rolling32(const char *datum, size_t length, const uint32_t prime,
                        const uint32_t mod, const char low) {
  uint32_t hash = 0;
  uint32_t power = 1;
  size_t i = 0;

  for (i = 0; i < length; ++i) {
    hash = (hash + (*datum++ - low + 1) * power) % mod;
    power = (power * prime) % mod;
  }

  return hash;
}
