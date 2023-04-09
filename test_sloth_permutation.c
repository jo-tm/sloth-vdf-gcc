#include <stdio.h>
#include <string.h>
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

void test_VDF02() {
    mpz_t x, y;
    mpz_init_set_str(x, "808080818080808080818080", 10);
    mpz_init(y);

    mpz_t p;
    mpz_init_set_str(p, "73237431696005972674723595250817150843", 10);

    sloth_permutation_set_prime(p);

    uint64_t t = 2000;

    generate_proof_vdf(t, x, y);
    assert(verify_proof_vdf(t, x, y));
}

void test_VDF03() {
    mpz_t x, y;
    mpz_init_set_ui(x, 0x789acdef);
    mpz_mul_2exp(x, x, 32);
    mpz_add_ui(x, x, 0x06543210);
    mpz_init(y);

    uint8_t buf[8];

    write_big_uint64_le(x, buf);
    read_big_uint64_le(y, buf);

    assert(mpz_cmp(x, y) == 0);
}

void test_VDF04() {
    mpz_t x, y;
    mpz_init_set_ui(x, 0x789acdef);
    mpz_mul_2exp(x, x, 32);
    mpz_add_ui(x, x, 0x06543210);
    mpz_init(y);

    uint8_t buf[8];

    write_big_uint_le(x, buf, 8);
    read_big_uint_le(y, buf, 8);

    assert(mpz_cmp(x, y) == 0);
}

void test_VDF05() {
    mpz_t x, y;
    mpz_init_set_ui(x, 0x789acdef);
    mpz_mul_2exp(x, x, 32);
    mpz_add_ui(x, x, 0x06543210);
    mpz_mul_2exp(x, x, 64);
    mpz_init(y);

    uint8_t buf[16];

    write_big_uint_le(x, buf, 16);
    read_big_uint_le(y, buf, 16);

    assert(mpz_cmp(x, y) == 0);
}

void test_VDF06() {
    uint8_t challenge[16] = {0x13, 0x70, 0x10, 0x85, 0x18, 0x87, 0x94, 0x66, 0x22, 0x57, 0x41, 0x52, 0x57, 0x12, 0x39, 0x13};
    mpz_t p;
    mpz_init_set_str(p, "297010851887946822574352571639152315287", 10);
    sloth_permutation_set_prime(p);

    uint64_t t = 200;

    for (int i = 0; i < 5; ++i) {
        uint8_t proof[16];
        generate_buffer_proof_vdf(t, challenge, proof, 
16);
        assert(verify_buffer_proof_vdf(t, challenge, proof, 16));
        memcpy(challenge, proof, 16);
    }
}

void test_VDF07() {
    uint8_t challenge[32] = {0xc8, 0x77, 0x4b, 0xec, 0xa8, 0x35, 0x21, 0x40, 0x89, 0x86, 0x0e, 0x8b, 0x01, 0x15, 0x7c, 0x6c, 0x88, 0x3c, 0x70, 0xf4, 0xa2, 0x5e, 0x83, 0xd1, 0x90, 0xb5, 0x77, 0xf7, 0xf5, 0x6b, 0xcf, 0xd3};
    mpz_t p;
    mpz_init_set_str(p, "64106875808534963770974826322234655855469213855659218736479077548818158667371", 10);
    sloth_permutation_set_prime(p);

    uint64_t t = 200;

    for (int i = 0; i < 5; ++i) {
        uint8_t proof[32];
        generate_buffer_proof_vdf(t, challenge, proof, 32);
        assert(verify_buffer_proof_vdf(t, challenge, proof, 32));
        memcpy(challenge, proof, 32);
    }
}

void test_VDF08() {
    uint8_t challenge[16] = {0x13, 0x70, 0x10, 0x85, 0x18, 0x87, 0x94, 0x66, 0x22, 0x57, 0x41, 0x52, 0x57, 0x12, 0x39, 0x13};
    mpz_t p;
    mpz_init_set_str(p, "297010851887946822574352571639152315287", 10);
    sloth_permutation_set_prime(p);

    uint64_t t = 200;

    uint8_t proof[16];
    generate_buffer_proof_vdf(t, challenge, proof, 16);
    assert(verify_buffer_proof_vdf(t, challenge, proof, 16));
}

void test_VDF09() {
    mpz_t challenge;
    mpz_init_set_str(challenge, "64528909272528537054813745700492621300445458085274430251275671551785582282347", 10);
    mpz_t p;
    mpz_init_set_str(p, "64106875808534963770974826322234655855469213855659218736479077548818158667371", 10);
    sloth_permutation_set_prime(p);

    uint64_t t = 10;

    for (int i = 0; i < 8; ++i) {
        mpz_add_ui(challenge, challenge, 1);
        mpz_mul_2exp(challenge, challenge, 252);

        mpz_t proof;
        mpz_init(proof);
        generate_proof_vdf(t, challenge, proof);
        assert(verify_proof_vdf(t, challenge, proof));
    }
}

int main() {
    test_VDF01();
    test_VDF02();
    test_VDF03();
    test_VDF04();
