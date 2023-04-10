#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "sloth_permutation.h"

void test_vdf01() {
    SlothPermutation sp;
    sloth_permutation_set_prime(&sp, "23");

    mpz_t x, y;
    mpz_init_set_ui(x, 10);
    mpz_mod(x, x, sp.p);

    size_t t = 50;

    sloth_generate_proof_vdf(&sp, y, x, t);
    bool verified = sloth_verify_proof_vdf(&sp, y, x, t);

    assert(verified);

    mpz_clear(x);
    mpz_clear(y);
    mpz_clear(sp.p);
}

void test_vdf02() {
    SlothPermutation sp;
    sloth_permutation_set_prime(&sp, "73237431696005972674723595250817150843");

    mpz_t x, y;
    mpz_init_set_str(x, "808080818080808080818080", 10);
    mpz_mod(x, x, sp.p);

    size_t t = 2000;

    sloth_generate_proof_vdf(&sp, y, x, t);
    bool verified = sloth_verify_proof_vdf(&sp, y, x, t);

    assert(verified);

    mpz_clear(x);
    mpz_clear(y);
    mpz_clear(sp.p);
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
    mpz_t x, y, temp;
    mpz_init_set_ui(x, 0x789acdef);
    mpz_mul_2exp(x, x, 32);
    mpz_add_ui(x, x, 0x06543210);

    mpz_init(temp);
    mpz_mul_2exp(temp, x, 64);
    mpz_add(x, x, temp);

    uint8_t arr[16];

    writeBigUIntLE(x, arr, 16, 0);
    readBigUIntLE(y, arr, 16, 0);

    assert(mpz_cmp(x, y) == 0);

    mpz_clear(x);
    mpz_clear(y);
    mpz_clear(temp);
}

void test_vdf06() {
    SlothPermutation sp;
    sloth_permutation_set_prime(&sp, "297010851887946822574352571639152315287");

    uint8_t challenge[16] = {0x13, 0x70, 0x10, 0x85, 0x18, 0x87, 0x94, 0x66, 0x22, 0x57, 0x41, 0x52, 0x57, 0x12, 0x39, 0x13};
    size_t t = 200;

    uint8_t proof[16], proof2[16], proof3[16], proof4[16], proof5[16];

    sloth_generate_buffer_proof_vdf(&sp, proof, challenge, t, 16);
    assert(sloth_verify_buffer_proof_vdf(&sp, proof, challenge, t, 16));

    memcpy(challenge, proof, 16);

    sloth_generate_buffer_proof_vdf(&sp, proof2, challenge, t, 16);
    assert(sloth_verify_buffer_proof_vdf(&sp, proof2, challenge, t, 16));

    // Add more iterations as required

    assert(memcmp(proof, proof2, (unsigned long) 16) != 0);
    // Add additional memcmp assertions as needed

    mpz_clear(sp.p);
}

void test_vdf07() {
    SlothPermutation sp;
    sloth_permutation_set_prime(&sp, "64106875808534963770974826322234655855469213855659218736479077548818158667371");

    uint8_t challenge[32] = {0xc8, 0x77, 0x4b, 0xec, 0xa8, 0x35, 0x21, 0x40, 0x89, 0x86, 0x0e, 0x8b, 0x01, 0x15, 0x7c, 0x6c, 0x88, 0x3c, 0x70, 0xf4, 0xa2, 0x5e, 0x83, 0xd1, 0x90, 0xb5, 0x77, 0xf7, 0xf5, 0x6b, 0xcf, 0xd3};
    size_t t = 200;

    uint8_t proof[32], proof2[32], proof3[32], proof4[32], proof5[32];

    sloth_generate_buffer_proof_vdf(&sp, proof, challenge, t, 32);
    assert(sloth_verify_buffer_proof_vdf(&sp, proof, challenge, t, 32));

    memcpy(challenge, proof, 32);

    sloth_generate_buffer_proof_vdf(&sp, proof2, challenge, t, 32);
    assert(sloth_verify_buffer_proof_vdf(&sp, proof2, challenge, t, 32));

    // Add more iterations as required

    assert(memcmp(proof, proof2, (unsigned long) 32) != 0);
    // Add additional memcmp assertions as needed

    mpz_clear(sp.p);
}

void test_vdf08() {
    // Implement test case VDF08 here
}

void test_vdf09() {
    // Implement test case VDF09 here
}

int main() {
    test_vdf01();
    test_vdf02();
    test_vdf04();
    test_vdf05();
    test_vdf06();
    test_vdf07();
    // Add calls to the other test functions here
    printf("All tests passed.\n");
    return 0;
}
