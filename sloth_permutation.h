#ifndef SLOTH_PERMUTATION_H
#define SLOTH_PERMUTATION_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct SlothPermutation SlothPermutation;

SlothPermutation* sloth_permutation_new(void);
void sloth_permutation_free(SlothPermutation* sp);

bool sloth_permutation_sqrt_mod_p_verify(SlothPermutation* sp, int64_t y, int64_t x, int64_t p);
int64_t sloth_permutation_mod(SlothPermutation* sp, int64_t x, int64_t y);
int64_t sloth_permutation_fast_pow(SlothPermutation* sp, int64_t base, int64_t exponent, int64_t modulus);
bool sloth_permutation_quad_res(SlothPermutation* sp, int64_t x);
int64_t sloth_permutation_mod_sqrt_op(SlothPermutation* sp, int64_t x);
int64_t sloth_permutation_mod_op(SlothPermutation* sp, int64_t x, int64_t t);
bool sloth_permutation_mod_verif(SlothPermutation* sp, int64_t y, int64_t x, int64_t t);

#endif // SLOTH_PERMUTATION_H
