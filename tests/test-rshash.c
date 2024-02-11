#include <ghash.h>

int main() {
  if (hash_rshash32("", 0) != 0) {
    return -1;
  }

  if (hash_rshash64("", 0) != 0) {
    return -1;
  }

  if (hash_rshash32("jdfgsdhfsdfsd 6445dsfsd7fg/*/+bfjsdgf%$^", 40) !=
      2012450421u) {
    return -1;
  }

  if (hash_rshash32("Hello", 5) != 2507753586u) {
    return -1;
  }

#if (__WORDSIZE >= 64)
  if (hash_rshash64("Hello", 5) != 16194690116432250994LU) {
    return -1;
  }
#endif
}
