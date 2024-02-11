#include <ghash.h>

int main() {
  if (hash_pjw32_4("", 0) != 0u) {
    return -1;
  }

  if (hash_pjw32_5("", 0) != 0u) {
    return -1;
  }

  if (hash_pjw32_4("Hello", 5) != 5161775u) {
    return -1;
  }

  if (hash_pjw32_5("Hello", 5) != 78921199u) {
    return -1;
  }

  if (hash_pjw32_4("Hello", 5) != hash_pjw32_4("Hello", 5)) {
    return -1;
  }
}
