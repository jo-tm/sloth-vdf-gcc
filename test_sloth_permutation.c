#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gmp.h>
#include "sloth_permutation.h"

#define HEX(x) #x

// Block time tests

void test_vdf01() {
    SlothPermutation* sloth = sloth_permutation_new();
    sloth_permutation_set_prime(sloth, "23");

    mpz_t x, t, y;
    mpz_inits(x, t, y, NULL);

    mpz_set_ui(x, 10);
    mpz_mod(x, x, sloth->p);
    mpz_set_ui(t, 50);

    sloth_permutation_generate_proof_vdf(sloth, y, t, x);
    bool verified = sloth_permutation_verify_proof_vdf(sloth, t, x, y);
    gmp_printf("[VDF01] generate and verify, small: %d\n", verified);

    mpz_clears(x, t, y, NULL);
    sloth_permutation_free(sloth);
}

void test_vdf02() {
    SlothPermutation* sloth = sloth_permutation_new();
    sloth_permutation_set_prime(sloth, HEX(73237431696005972674723595250817150843));

    mpz_t x, t, y;
    mpz_inits(x, t, y, NULL);

    mpz_set_str(x, "808080818080808080818080", 16);
    mpz_mod(x, x, sloth->p);
    mpz_set_ui(t, 2000);

    sloth_permutation_generate_proof_vdf(sloth, y, t, x);
    bool verified = sloth_permutation_verify_proof_vdf(sloth, t, x, y);
    gmp_printf("[VDF02] generate and verify, medium: %d\n", verified);

    mpz_clears(x, t, y, NULL);
    sloth_permutation_free(sloth);
}

void test_vdf03() {
    SlothPermutation* sloth = sloth_permutation_new();

    mpz_t x, y;
    mpz_inits(x, y, NULL);

    mpz_set_ui(x, 0x789acdef);
    mpz_mul_2exp(x, x, 32);
    mpz_add_ui(x, x, 0x06543210);

    sloth_permutation_write_big_int_to_buffer(sloth, y, x, 8);
    sloth_permutation_read_big_int_from_buffer(sloth, x, y);

    bool equal = (mpz_cmp(x, y) == 0);
    gmp_printf("[VDF03] bigint export/import from buffers: %d\n", equal);

    mpz_clears(x, y, NULL);
    sloth_permutation_free(sloth);
}

void test_vdf04() {
    SlothPermutation* sloth = sloth_permutation_new();
    mpz_t x, y;
    mpz_inits(x, y, NULL);

    sloth_permutation_set_ui(sloth->p, 0);
    mpz_setbit(sloth->p, 512);
    mpz_nextprime(sloth->p, sloth->p);

    mpz_set_ui(x, 0x789acdef);
    mpz_mul_2exp(x, x, 32);
    mpz_add_ui(x, x, 0x06543210);

    sloth_permutation_write_big_int_to_buffer(sloth, y, x, 8);
    sloth_permutation_read_big_int_from_buffer(sloth, x, y, 8);

    bool equal = (mpz_cmp(x, y) == 0);
    gmp_printf("[VDF04] bigint export/import from buffers of arbitrary size = 64: %d\n", equal);

    mpz_clears(x, y, NULL);
    sloth_permutation_free(sloth);
}

void test_vdf05() {
    SlothPermutation* sloth = sloth_permutation_new();
    mpz_t x, y;
    mpz_inits(x, y, NULL);

    mpz_set_ui(x, 0x789acdef);
    mpz_mul_2exp(x, x, 32);
    mpz_add_ui(x, x, 0x06543210);

    sloth_permutation_write_big_int_to_buffer(sloth, y, x, 8);
    sloth_permutation_read_big_int_from_buffer(sloth, x, y);

    bool equal = (mpz_cmp(x, y) == 0);
    gmp_printf("[VDF05] bigint export/import from buffers: %d\n", equal);

    mpz_clears(x, y, NULL);
    sloth_permutation_free(sloth);
}

void test_vdf06() {
    SlothPermutation* sp = sloth_permutation_new();

    mpz_t x, y;
    mpz_inits(x, y, NULL);

    mpz_set_ui(x, 0x789acdef);
    mpz_mul_2exp(x, x, 32);
    mpz_add_ui(x, x, 0x06543210);

    sloth_permutation_write_big_int_to_buffer(sp, y, x, 8);
    sloth_permutation_read_big_int_from_buffer(sp, x, y, 8);

    bool equal = (mpz_cmp(x, y) == 0);
    gmp_printf("[VDF06] bigint export/import from buffers of arbitrary size = 64: %d\n", equal);

    mpz_clears(x, y, NULL);
    sloth_permutation_free(sp);
}

void test_vdf07() {
    SlothPermutation* sloth = sloth_permutation_new();
    sloth_permutation_set_prime(sloth, HEX(73237431696005972674723595250817150843));
    mpz_t x, t, y;
    mpz_inits(x, t, y, NULL);

    mpz_set_str(x, "808080818080808080818080", 16);
    sloth_permutation_mod_op(sloth, t, x, y);
    mpz_set_ui(y, 2000);

    sloth_permutation_generate_proof_vdf(sloth, y, t, x);
    bool verified = sloth_permutation_verify_proof_vdf(sloth, y, t, x);
    gmp_printf("[VDF07] generate and verify, medium: %d\n", verified);

    mpz_clears(x, t, y, NULL);
    sloth_permutation_free(sloth);
}

void test_vdf08() {
    SlothPermutation* sloth = sloth_permutation_new();
    mpz_t x, y, t;
    mpz_inits(x, y, t, NULL);

    // Choose a prime p and a number x less than p
    sloth_permutation_set_prime(sloth, "73237431696005972674723595250817150843");
    mpz_set_str(x, "808080818080808080818080", 16);
    sloth_permutation_mod(sloth, x, x, sloth->p);

    // Calculate y = x^2 mod p using sloth_permutation_mod_op
    sloth_permutation_mod_op(sloth, y, x, x);

    // Verify that y is a quadratic residue modulo p
    bool is_residue = sloth_permutation_quad_res(sloth, y);
    gmp_printf("[VDF08] verify quadratic residue: %d\n", is_residue);

    // Verify that y is the correct square root of x^2 mod p using sloth_permutation_sqrt_mod_p_verify
    bool verified = sloth_permutation_sqrt_mod_p_verify(sloth, t, y, sloth->p);
    gmp_printf("[VDF08] verify square root: %d\n", verified);

    sloth_permutation_free(sloth);
    mpz_clears(x, y, t, NULL);
}

void test_vdf09() {
    SlothPermutation* sloth = sloth_permutation_new();
    sloth_permutation_set_prime(sloth, HEX(73237431696005972674723595250817150843));

    mpz_t x, t, y;
    mpz_inits(x, t, y, NULL);

    mpz_set_str(x, "808080818080808080818080", 16);
    sloth_permutation_mod_op(sloth, x, x, sloth->p);
    mpz_set_ui(t, 2000);

    sloth_permutation_mod_sqrt_op(sloth, y, x);
    sloth_permutation_mod_op(sloth, y, y, t);

    bool verified = sloth_permutation_mod_verif(sloth, t, x, y);
    gmp_printf("[VDF09] verify, small: %d\n", verified);

    sloth_permutation_free(sloth);
    mpz_clears(x, t, y, NULL);
}
