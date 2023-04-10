#include <stdio.h>
#include <assert.h>
#include "sloth_permutation.h"

void test_vdf01() {
    SlothPermutation sp;
    sloth_permutation_init(&sp, 23);

    mpz_t x, y;
    mpz_init_set_ui(x, 10);
    mpz_mod(x, x, sp.p);

    size_t t = 50;

    sloth_generate_proof_vdf(&sp, y, x, t);
    bool verified = sloth_verify_proof_vdf(&sp, y, x, t);

    assert(verified);

    mpz_clear(x);
    mpz_clear(y);
    sloth_permutation_clear(&sp);
}

void test_vdf02() {
    SlothPermutation sp;
    sloth_permutation_init_from_str(&sp, "73237431696005972674723595250817150843");

    mpz_t x, y;
    mpz_init_set_str(x, "808080818080808080818080", 10);
    mpz_mod(x, x, sp.p);

    size_t t = 2000;

    sloth_generate_proof_vdf(&sp, y, x, t);
    bool verified = sloth_verify_proof_vdf(&sp, y, x, t);

    assert(verified);

    mpz_clear(x);
    mpz_clear(y);
    sloth_permutation_clear(&sp);
}

void test_vdf04() {
    mpz_t x, y;
    mpz_init_set_ui(x, 0x789acdef);
    mpz_mul_2exp(x, x, 32);
    mpz_add_ui(x, x, 0x06543210);

    uint8_t arr[8];

    writeBigUIntLE(x, arr, 8, 0);
    readBigUIntLE(y, arr, 8, 0);

    assert(mpz_cmp(x, y) == 0);

    mpz_clear(x);
    mpz_clear(y);
}

void test_vdf05() {
    mpz_t x, y;
    mpz_init_set_ui(x, 0x789acdef);
    mpz_mul_2exp(x, x, 32);
    mpz_add_ui(x, x, 0x06543210);
    mpz_add(x, x, mpz_mul_2exp(x, x, 64));

    uint8_t arr[16];

    writeBigUIntLE(x, arr, 16, 0);
    readBigUIntLE(y, arr, 16, 0);

    assert(mpz_cmp(x, y) == 0);

    mpz_clear(x);
    mpz_clear(y);
}

void test_vdf06() {
    // Implement test case VDF06 here
}

void test_vdf07() {
    // Implement test case VDF07 here
}

void test_vdf08() {
    // Implement test case VDF08 here
}

void test_vdf09() {
    // Implement test case VDF09 here
}

void test_vdf09b() {
    // Implement test case VDF09b here
}

int main() {
    test_vdf01();
    test_vdf02();
    test_vdf04();
    test_vdf05();
    // Add calls to the other test functions here
    printf("All tests passed.\n");
    return 0;
}
