#include "sloth_permutation.h"
#include <stdio.h>

int main() {
    SlothPermutation* sp = sloth_permutation_new();
    if (!sp) {
        printf("Failed to create SlothPermutation instance.\n");
        return 1;
    }

    int64_t x = 123456789;
    int64_t t = 10;
    int64_t y = sloth_permutation_mod_op(sp, x, t);

    printf("Original value: %lld\n", x);
    printf("Modified value: %lld\n", y);

    bool verification = sloth_permutation_mod_verif(sp, y, x, t);
    printf("Verification: %s\n", verification ? "true" : "false");

    sloth_permutation_free(sp);
    return 0;
}
