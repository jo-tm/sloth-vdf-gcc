#include <stdio.h>
#include <gmp.h>
#include "sloth_permutation.h"

int main() {
    SlothPermutation* sp = sloth_permutation_new();

    mpz_t x, y;
    size_t t = 1000;
    mpz_init_set_str(x, "12345678901234567890", 10);
    mpz_init(y);

    sloth_generate_proof_vdf(sp, y, x, t);

    printf("Generated proof: ");
    mpz_out_str(stdout, 10, y);
    printf("\n");

    bool is_valid = sloth_verify_proof_vdf(sp, y, x, t);
    printf("Verification result: %s\n", is_valid ? "True" : "False");

    mpz_clear(x);
    mpz_clear(y);
    sloth_permutation_free(sp);

    return 0;
}
