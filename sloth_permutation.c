#include "sloth_permutation.h"
#include <stdlib.h>
#include <stdio.h>

SlothPermutation* sloth_permutation_new(void) {
    SlothPermutation* sp = malloc(sizeof(SlothPermutation));
    if (!sp) {
        return NULL;
    }
    mpz_init_set_str(sp->p, "170082004324204494273811327264862981553264701145937538369570764779791492622392118654022654452947093285873855529044371650895045691292912712699015605832276411308653107069798639938826015099738961427172366594187783204437869906954750443653318078358839409699824714551430573905637228307966826784684174483831608534979", 10);
    return sp;
}

void sloth_permutation_set_prime(SlothPermutation* sp, const char* prime_str) {
    mpz_init_set_str(sp->p, prime_str, 10);
}

void sloth_permutation_free(SlothPermutation* sp) {
    if (sp) {
        mpz_clear(sp->p);
        free(sp);
    }
}

bool sloth_permutation_sqrt_mod_p_verify(SlothPermutation* sp, mpz_t y, mpz_t x, mpz_t p) {
    mpz_t temp;
    mpz_init(temp);
    mpz_powm_ui(temp, y, 2, p);
    bool result = mpz_cmp(temp, x) == 0;
    mpz_clear(temp);
    return result;
}

void sloth_permutation_mod(SlothPermutation* sp, mpz_t result, mpz_t x, mpz_t y) {
    mpz_tdiv_r(result, x, y);
}

void sloth_permutation_fast_pow(SlothPermutation* sp, mpz_t result, mpz_t base, mpz_t exponent, mpz_t modulus) {
    mpz_powm(result, base, exponent, modulus);
}

bool sloth_permutation_quad_res(SlothPermutation* sp, mpz_t x) {
    mpz_t temp;
    mpz_init(temp);
    mpz_sub_ui(temp, sp->p, 1);
    mpz_tdiv_q_ui(temp, temp, 2);
    sloth_permutation_fast_pow
(sp, temp, x, temp, sp->p);
    bool result = mpz_cmp_ui(temp, 1) == 0;
    mpz_clear(temp);
    return result;
}

void sloth_permutation_mod_sqrt_op(SlothPermutation* sp, mpz_t result, mpz_t x) {
    mpz_t temp;
    mpz_init(temp);
    if (sloth_permutation_quad_res(sp, x)) {
        mpz_add_ui(temp, sp->p, 1);
        mpz_tdiv_q_ui(temp, temp, 4);
        sloth_permutation_fast_pow(sp, result, x, temp, sp->p);
    } else {
        mpz_sub(temp, sp->p, x);
        mpz_mod(temp, temp, sp->p);
        mpz_add_ui(temp, sp->p, 1);
        mpz_tdiv_q_ui(temp, temp, 4);
        sloth_permutation_fast_pow(sp, result, temp, temp, sp->p);
    }
    mpz_clear(temp);
}

void sloth_generate_proof_vdf(SlothPermutation* sp, mpz_t result, mpz_t x, size_t t) {
    mpz_mod(x, x, sp->p);
    for (size_t i = 0; i < t; i++) {
        sloth_permutation_mod_sqrt_op(sp, x, x);
    }
    mpz_set(result, x);
}

bool sloth_verify_proof_vdf(SlothPermutation* sp, mpz_t y, mpz_t x, size_t t) {
    mpz_mod(x, x, sp->p);
    for (size_t i = 0; i < t; i++) {
        mpz_powm_ui(y, y, 2, sp->p);
    }
    if (!sloth_permutation_quad_res(sp, y)) {
        mpz_sub(y, sp->p, y);
        mpz_mod(y, y, sp->p);
    }
    bool result = mpz_cmp(x, y) == 0 || mpz_cmp(x, y) == mpz_cmp(sp->p, y);
    return result;
}
// I/O

#include <stdint.h>
#include <stdlib.h>

SlothPermutation* read_biguint64_le(uint8_t* buffer, int offset) {
    SlothPermutation* sp = sloth_permutation_new();
    if (!sp) {
        return NULL;
    }
    mpz_set_ui(sp->p, 0);
    mpz_import(sp->p, 8, -1, sizeof(buffer[0]), 0, 0, buffer + offset);
    return sp;
}

void write_biguint64_le(SlothPermutation *sp, mpz_t x, uint8_t *buffer, size_t offset) {
    mpz_export(buffer + offset, NULL, -1, sizeof(buffer[0]), 0, 0, x);
}

SlothPermutation* read_biguint_le(const uint8_t* buffer, size_t byte_len, size_t offset) {
    SlothPermutation* sp = sloth_permutation_new();
    if (!sp) {
        return NULL;
    }
    mpz_set_ui(sp->p, 0);
    mpz_import(sp->p, byte_len, -1, sizeof(buffer[0]), 0, 0, buffer + offset);
    return sp;
}

void write_biguint_le(SlothPermutation* sp, mpz_t x, uint8_t* buffer, int byte_len, int offset) {
    mpz_export(buffer + offset, NULL, -1, sizeof(buffer[0]), 0, 0, x);
}

void sloth_permutation_set_from_bigint(SlothPermutation* sp, mpz_t p) {
    mpz_init_set(sp->p, p);
}

uint8_t* generate_buffer_proof_vdf(SlothPermutation* sp, const uint8_t* x, size_t byte_len, size_t t) {
    uint8_t* ret = calloc(byte_len, sizeof(uint8_t));
    if (!ret) {
        return NULL;
    }
    mpz_t x_mpz, mod_op_res;
    mpz_init(x_mpz);
    mpz_init(mod_op_res);
    SlothPermutation_read_biguint_le(sp, x_mpz, x, byte_len, 0);
    SlothPermutation_mod_op(sp, mod_op_res, x_mpz, t);
    SlothPermutation_write_biguint_le(sp, mod_op_res, ret, byte_len, 0);
    mpz_clear(x_mpz);
    mpz_clear(mod_op_res);
    return ret;
}

bool verify_buffer_proof_vdf(SlothPermutation* sp, uint8_t* x, uint8_t* y, size_t byte_len, size_t t) {
    mpz_t x_mpz, y_mpz;
    mpz_init(x_mpz);
    mpz_init(y_mpz);
    SlothPermutation_read_biguint_le(sp, x_mpz, x, byte_len, 0);
    SlothPermutation_read_biguint_le(sp, y_mpz, y, byte_len, 0);
    bool result = SlothPermutation_mod_verif(sp, y_mpz, x_mpz, t);
    mpz_clear(x_mpz);
    mpz_clear(y_mpz);
    return result;
}

