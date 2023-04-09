#ifndef SLOTH_PERMUTATION_H
#define SLOTH_PERMUTATION_H

#include <stdbool.h>
#include <gmp.h>

typedef struct SlothPermutation SlothPermutation;

SlothPermutation* sloth_permutation_new(void);
void sloth_permutation_free(SlothPermutation* sp);

bool sloth_permutation_sqrt_mod_p_verify(SlothPermutation* sp, mpz_t y, mpz_t x, mpz_t p);
void sloth_permutation_mod(SlothPermutation* sp, mpz_t result, mpz_t x, mpz_t y);
void sloth_permutation_fast_pow(SlothPermutation* sp, mpz_t result, mpz_t base, mpz_t exponent, mpz_t modulus);
bool sloth_permutation_quad_res(SlothPermutation* sp, mpz_t x);
void sloth_permutation_mod_sqrt_op(SlothPermutation* sp, mpz_t result, mpz_t x);
void sloth_permutation_mod_op(SlothPermutation* sp, mpz_t result, mpz_t x, mpz_t t);
bool sloth_permutation_mod_verif(SlothPermutation* sp, mpz_t y, mpz_t x, mpz_t t);

#endif // SLOTH_PERMUTATION_H
