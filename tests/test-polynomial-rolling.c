#include <ghash.h>

int main() {
  if (hash_rolling32("aa", 2, 31, 1000000009, 'a') != 32u) {
    return -1;
  }

  if (hash_rolling32("aa", 2, 31, 1000000009, 'a') !=
      hash_rolling32("aa", 2, 31, 1000000009, 'a')) {
    return -1;
  }

  if (hash_rolling32("a", 1, 31, 1000000009, 'a') ==
      hash_rolling32("aa", 2, 31, 1000000009, 'a')) {
    return -1;
  }

  return 0;
}
