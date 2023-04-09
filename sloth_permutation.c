#include "sloth_permutation.h"
#include <stdlib.h>

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

void sloth_generate_proof_vdf(SlothPermutation* sp, mpz_t result, mpz_t x, mpz_t t) {
    mpz_mod(x, x, sp->p);
    for (mpz_t i; mpz_cmp(i, t) < 0; mpz_add_ui(i, i, 1)) {
        sloth_permutation_mod_sqrt_op(sp, x, x);
    }
    mpz_set(result, x);
}

bool sloth_verify_proof_vdf(SlothPermutation* sp, mpz_t y, mpz_t x, mpz_t t) {
    mpz_mod(x, x, sp->p);
    for (mpz_t i; mpz_cmp(i, t) < 0; mpz_add_ui(i, i, 1)) {
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
    uint8_t first = buffer[offset];
    uint8_t last = buffer[offset + 7];
    if (first == NULL || last == NULL) {
        perror("Out of bounds");
        return NULL;
    }
    uint64_t lo = (uint64_t)first +
            ((uint64_t)buffer[++offset] << 8) +
            ((uint64_t)buffer[++offset] << 16) +
            ((uint64_t)buffer[++offset] << 24);

    uint64_t hi = (uint64_t)buffer[++offset] +
            ((uint64_t)buffer[++offset] << 8) +
            ((uint64_t)buffer[++offset] << 16) +
            ((uint64_t)last << 24);

    mpz_t result;
    mpz_init(result);
    mpz_set_ui(result, lo);
    mpz_addmul_ui(result, result, (uint64_t)1 << 32);
    mpz_add_ui(result, result, hi);

    SlothPermutation* sp = sloth_permutation_new();
    sloth_permutation_set_from_bigint(sp, result);

    return sp;
}

void write_biguint64_le(SlothPermutation *sp, mpz_t x, uint8_t *buffer, size_t offset) {
    uint8_t first = buffer[offset];
    uint8_t last = buffer[offset + 7];
    if (first == '\0' || last == '\0') {
        printf("Out of bounds\n");
        exit(1);
    }

    mpz_t y, big256, big8, temp;
    mpz_inits(y, big256, big8, temp, NULL);

    mpz_set(y, x);
    mpz_set_ui(big256, 256);
    mpz_set_ui(big8, 8);

    for (int i = 0; i < 8; i++) {
        mpz_mod(temp, y, big256);
        buffer[offset + i] = mpz_get_ui(temp);
        mpz_fdiv_q(y, y, big256);
    }

    mpz_clears(y, big256, big8, temp, NULL);
}


