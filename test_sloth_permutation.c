#include <assert.h>
#include <gmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sloth_permutation.h"



void test_vdf01_generate_and_verify_small() {
    SlothPermutation* sp = sloth_permutation_new();
    mpz_t x, t, y;
    bool verified;

    mpz_init_set_ui(x, 10);
    mpz_init_set_ui(t, 50);
    mpz_init(y);

    mpz_mod(x, x, sp->p);

    sloth_generate_proof_vdf(sp, y, x, t);
    verified = sloth_verify_proof_vdf(sp, y, x, t);

    assert(verified);

    mpz_clear(x);
    mpz_clear(t);
    mpz_clear(y);
    sloth_permutation_free(sp);
}

void test_vdf02_generate_and_verify_medium() {
    SlothPermutation* sp = sloth_permutation_new();
    mpz_t x, t, y;
    bool verified;

    mpz_init_set_str(x, "808080818080808080818080", 10);
    mpz_init_set_str(sp->p, "73237431696005972674723595250817150843", 10);
    mpz_init_set_ui(t, 2000);
    mpz_init(y);

    mpz_mod(x, x, sp->p);

    sloth_generate_proof_vdf(sp, t, x, y);
    verified = sloth_verify_proof_vdf(sp, y, x, t);

    assert(verified);

    mpz_clear(x);
    mpz_clear(t);
    mpz_clear(y);

    sloth_permutation_free(sp);
}

void test_vdf03_bigint_export_import_from_buffers() {
    mpz_t x, y;
    uint8_t buffer[16];

    mpz_init_set_ui(x, 0x789acdef);
    mpz_mul_2exp(x, x, 32);
    mpz_add_ui(x, x, 0x06543210);
    mpz_init(y);

    write_biguint_le_mpz(x, buffer, 8);
    read_biguint_le_mpz(buffer, 8, y);

    assert(mpz_cmp(x, y) == 0);

    mpz_clear(x);
    mpz_clear(y);
}

void test_vdf04_bigint_export_import_from_buffers_arbitrary_size_64() {
    SlothPermutation *sp = sloth_permutation_new();
    uint64_t x = ((uint64_t)0x789acdef << 32) + (uint64_t)0x06543210;
    uint64_t y;
    uint8_t buffer[8];

    write_biguint_le(x, buffer, 8);
    y = read_biguint_le(buffer, 8);

    assert(x == y);

    sloth_permutation_free(sp);
}

void test_vdf05_bigint_export_import_from_buffers_arbitrary_size_128() {
    SlothPermutation *sp = sloth_permutation_new();
    mpz_t x, y;
    uint8_t buffer[16];

    mpz_init_set_ui(x, 0x789acdef);
    mpz_mul_2exp(x, x, 32);
    mpz_add_ui(x, x, 0x06543210);
    mpz_init(y);

    mpz_mul_2exp(x, x, 64);

    write_biguint_le_mpz(x, buffer, 16);
    read_biguint_le_mpz(buffer, 16, y);

    assert(mpz_cmp(x, y) == 0);

    mpz_clear(x);
    mpz_clear(y);

    sloth_permutation_free(sp);
}

void test_vdf06_bigint_export_import_from_buffers_arbitrary_size_128_and_vdf_test() {
    SlothPermutation* sp = sloth_permutation_new();
    uint8_t challenge[16] = {0x13, 0x70, 0x10, 0x85, 0x18, 0x87, 0x94, 0x66, 0x22, 0x57, 0x41, 0x52, 0x57, 0x12, 0x39, 0x13};
    uint8_t proof[16], proof2[16], proof3[16], proof4[16], proof5[16];

    mpz_init_set_str(sp->p, "297010851887946822574352571639152315287", 10);
    mpz_init_set_ui(sp->t, 200);

    sloth_permutation_set_prime(sp->p);

    generate_buffer_proof_vdf(sp->t, challenge, 16, proof);
    assert(verify_buffer_proof_vdf(sp->t, challenge, proof, 16));

    memcpy(challenge, proof, 16);
    generate_buffer_proof_vdf(sp->t, challenge, 16, proof2);
    assert(verify_buffer_proof_vdf(sp->t, challenge, proof2, 16));

    memcpy(challenge, proof2, 16);
    generate_buffer_proof_vdf(sp->t, challenge, 16, proof3);
    assert(verify_buffer_proof_vdf(sp->t, challenge, proof3, 16));

    memcpy(challenge, proof3, 16);
    generate_buffer_proof_vdf(sp->t, challenge, 16, proof4);
    assert(verify_buffer_proof_vdf(sp->t, challenge, proof4, 16));

    memcpy(challenge, proof4, 16);
    generate_buffer_proof_vdf(sp->t, challenge, 16, proof5);
    assert(verify_buffer_proof_vdf(sp->t, challenge, proof5, 16));

    assert(memcmp(proof, proof2, 16) != 0);
    assert(memcmp(proof, proof3, 16) != 0);
    assert(memcmp(proof, proof4, 16) != 0);
    assert(memcmp(proof, proof5, 16) != 0);
    assert(memcmp(proof2, proof3, 16) != 0);
    assert(memcmp(proof2, proof4, 16) != 0);
    assert(memcmp(proof2, proof5, 16) != 0);
    assert(memcmp(proof3, proof4, 16) != 0);
    assert(memcmp(proof3, proof5, 16) != 0);
    assert(memcmp(proof4, proof5, 16) != 0);

    sloth_permutation_free(sp);
}

void test_vdf07_bigint_export_import_from_buffers_arbitrary_size_256_and_vdf_test() {
    mpz_t p, t;
    uint8_t challenge[32] = {0xc8, 0x77, 0x4b, 0xec, 0xa8, 0x35, 0x21, 0x40, 0x89, 0x86, 0x0e, 0x8b, 0x01, 0x15, 0x7c, 0x6c, 0x88, 0x3c, 0x70, 0xf4, 0xa2, 0x5e, 0x83, 0xd1, 0x90, 0xb5, 0x77, 0xf7, 0xf5, 0x6b, 0xcf, 0xd3};
    uint8_t proof[32], proof2[32], proof3[32], proof4[32], proof5[32];

    mpz_init_set_str(p, "64106875808534963770974826322234655855469213855659218736479077548818158667371", 10);
    mpz_init_set_ui(t, 200);

    SlothPermutation* sp = sloth_permutation_new(p);
    sloth_permutation_set_prime(sp, p);

    generate_buffer_proof_vdf(t, challenge, 32, proof);
    assert(verify_buffer_proof_vdf(sp, t, challenge, proof, 32));

    memcpy(challenge, proof, 32);
    generate_buffer_proof_vdf(t, challenge, 32, proof2);
    assert(verify_buffer_proof_vdf(sp, t, challenge, proof2, 32));

    memcpy(challenge, proof2, 32);
    generate_buffer_proof_vdf(t, challenge, 32, proof3);
    assert(verify_buffer_proof_vdf(sp, t, challenge, proof3, 32));

    memcpy(challenge, proof3, 32);
    generate_buffer_proof_vdf(t, challenge, 32, proof4);
    assert(verify_buffer_proof_vdf(sp, t, challenge, proof4, 32));

    memcpy(challenge, proof4, 32);
    generate_buffer_proof_vdf(t, challenge, 32, proof5);
    assert(verify_buffer_proof_vdf(sp, t, challenge, proof5, 32));

    assert(memcmp(proof, proof2, 32) != 0);
    assert(memcmp(proof, proof3, 32) != 0);
    assert(memcmp(proof, proof4, 32) != 0);
    assert(memcmp(proof, proof5, 32) != 0);
    assert(memcmp(proof2, proof3, 32) != 0);
    assert(memcmp(proof2, proof4, 32) != 0);
    assert(memcmp(proof2, proof5, 32) != 0);
    assert(memcmp(proof3, proof4, 32) != 0);
    assert(memcmp(proof3, proof5, 32) != 0);
    assert(memcmp(proof4, proof5, 32) != 0);

    sloth_permutation_free(sp);
    mpz_clear(p);
    mpz_clear(t);
}

void test_vdf08_generate_and_verify_large() {
    mpz_t x, p, t, y;
    bool verified;

    mpz_init_set_str(x, "1234567890987654321012345678909876543210123456789098765432101234567890987654321", 10);
    mpz_init_set_str(p, "32317006071311007300714876688669951960444102669715484032130345427524655138867", 10);
    mpz_init_set_ui(t, 100000);

    sloth_permutation* sp = sloth_permutation_new();
    sloth_permutation_set_prime(sp, p);

    mpz_mod(x, x, p);

    sloth_generate_proof_vdf(sp, t, x, y);
    verified = sloth_verify_proof_vdf(sp, t, x, y);

    assert(verified);

    sloth_permutation_free(sp);

    mpz_clear(x);
    mpz_clear(p);
    mpz_clear(t);
    mpz_clear(y);
}

void test_vdf09_bigint_export_import_from_buffers_arbitrary_size_256_and_vdf_test_many_steps() {
    mpz_t challenge, p, t, proof;
    mpz_init_set_str(challenge, "c8774beca835214089860e8b01157c6c883c70f4a25e83d190b577f7f56bcfd3", 16);
    mpz_init_set_str(p, "64106875808534963770974826322234655855469213855659218736479077548818158667371", 10);
    mpz_init_set_ui(t, 200);

    sloth_permutation_set_prime(p);

    mpz_init(proof);

    int buffer_size = 32;
    uint8_t challenge_buffer[buffer_size];
    uint8_t proof_buffer[buffer_size];

    mpz_export(challenge_buffer, NULL, 1, sizeof(uint8_t), 0, 0, challenge);
    generate_proof_vdf_buffer(t, challenge_buffer, proof_buffer, buffer_size);
    assert(verify_proof_vdf_buffer(t, challenge_buffer, proof_buffer, buffer_size));

    mpz_clear(challenge);
    mpz_clear(p);
    mpz_clear(t);
    mpz_clear(proof);

    printf("Test case VDF09 passed.\n");
}


int main() {
    printf("Running VDF01 test...\n");
    test_vdf01_generate_and_verify_small();
    printf("VDF01 test passed.\n");
    
    printf("Running VDF02 test...\n");
    test_vdf02_generate_and_verify_medium();
    printf("VDF02 test passed.\n");
    
    printf("Running VDF03 test...\n");
    test_vdf03_bigint_export_import_from_buffers();
    printf("VDF03 test passed.\n");

    printf("Running VDF04 test...\n");
    test_vdf04_bigint_export_import_from_buffers_arbitrary_size_64();
    printf("VDF04 test passed.\n");

    printf("Running VDF05 test...\n");
    test_vdf05_bigint_export_import_from_buffers_arbitrary_size_128();
    printf("VDF05 test passed.\n");

    printf("Running VDF06 test...\n");
    test_vdf06_bigint_export_import_from_buffers_arbitrary_size_128_and_vdf_test();
    printf("VDF06 test passed.\n");

    printf("Running VDF07 test...\n");
    test_vdf07_bigint_export_import_from_buffers_arbitrary_size_256_and_vdf_test();
    printf("VDF07 test passed.\n");

    printf("Running VDF08 test...\n");
    test_vdf08_bigint_export_import_from_buffers_arbitrary_size_128_and_vdf_test();
    printf("VDF08 test passed.\n");

    printf("Running VDF09 test...\n");
    test_vdf09_bigint_export_import_from_buffers_arbitrary_size_256_and_vdf_test_many_steps();
    printf("VDF09 test passed.\n");
    
    printf("All tests passed.\n");
    return 0;
}
