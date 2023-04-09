#include <stdio.h>
#include <assert.h>
#include "sloth_permutation.h"

void test_VDF01() {
    mpz_t x, y;
    mpz_init_set_ui(x, 10);
    mpz_init(y);

    mpz_t p;
    mpz_init_set_ui(p, 23);

    sloth_permutation_set_prime(p);

    uint64_t t = 50;

    generate_proof_vdf(t, x, y);
    assert(verify_proof_vdf(t, x, y));
}

// ... other tests ...

int main(int argc, char **argv) {
    test_VDF01();
    // ... call other test functions ...
    printf("All tests passed.\n");
    return 0;
}
