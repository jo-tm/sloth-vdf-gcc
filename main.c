#include <stdio.h>
#include <gmp.h>
#include "sloth_permutation.h"

int main() {
    SlothPermutation* sp = sloth_permutation_new();

    mpz_t t, x, y;
    mpz_init_set_ui(t, 100);
    mpz_init_set_str(x, "12345678901234567890", 10);
    mpz_init(y);

    sloth_permutation_mod_op(sp, y, x, t);

    printf("Generated proof: ");
    mpz_out_str(stdout, 10, y);
    printf("\n");

    bool is_valid = sloth_permutation_mod_verif(sp, y, x, t);
    printf("Verification result: %s\n", is_valid ? "True" : "False");

    mpz_clear(t);
    mpz_clear(x);
    mpz_clear(y);
    sloth_permutation_free(sp);

    return 0;
}
