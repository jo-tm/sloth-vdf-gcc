#include "sloth_permutation.h"
#include <stdlib.h>

struct SlothPermutation {
    int64_t p;
};

SlothPermutation* sloth_permutation_new(void) {
    SlothPermutation* sp = malloc(sizeof(SlothPermutation));
    if (!sp) {
        return NULL;
    }
    sp->p = 170082004324204494273811327264862981553264701145937538369570764779791492622392118654022654452947093285873855529044371650895045691292912712699015605832276411308653107069798639938826015099738961427172366594187783204437869906954750443653318078358839409699824714551430573905637228307966826784684174483831608534979;
    return sp;
}

void sloth_permutation_free(SlothPermutation* sp) {
    if (sp) {
        free(sp);
    }
}

bool sloth_permutation_sqrt_mod_p_verify(SlothPermutation* sp, int64_t y, int64_t x, int64_t p) {
    int64_t temp = (y * y) % p;
    if (temp != (x % p)) {
        return false;
    } else {
        return true;
    }
}

int64_t sloth_permutation_mod(SlothPermutation* sp, int64_t x, int64_t y) {
    return (x - (x / y * y));
}

int64_t sloth_permutation_fast_pow(SlothPermutation* sp, int64_t base, int64_t exponent, int64_t modulus) {
    if (modulus == 1) return 0;
    int64_t result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent / 2;
        base = (base * base) % modulus;
    }
    return result;
}

bool sloth_permutation_quad_res(SlothPermutation* sp, int64_t x) {
    return sloth_permutation_fast_pow(sp, x, (sp->p - 1) / 2, sp->p) == 1;
}

int64_t sloth_permutation_mod_sqrt_op(SlothPermutation* sp, int64_t x) {
    int64_t y;
    if (sloth_permutation_quad_res(sp, x)) {
        y = sloth_permutation_fast_pow(sp, x, (sp->p + 1) / 4, sp->p);
    } else {
        x = (sp->p - x) % sp->p;
        y = sloth_permutation_fast_pow(sp, x, (sp->p + 1) / 4, sp->p);
    }
    return y;
}

int64_t sloth_permutation_mod_op(SlothPermutation* sp, int64_t x, int64_t t) {
    x = x % sp->p;
    for (int64_t i = 0; i < t; i++) {
        x = sloth_permutation_mod_sqrt_op(sp, x);
    }
    return x;
}

bool sloth_permutation_mod_verif(SlothPermutation* sp, int64_t y, int64_t x, int64_t t) {
    x = x % sp->p
    for (int64_t i = 0; i < t; i++) {
        y = (y * y) % sp->p;
    }
    if (!sloth_permutation_quad_res(sp, y)) {
        y = (sp->p - y) % sp->p;
    }
    if ((x % sp->p) == y || ((sp->p - x) % sp->p) == y) {
        return true;
    } else {
        return false;
    }
}

int64_t sloth_permutation_generateProofVDF(SlothPermutation* sp, int64_t t, int64_t x) {
    return sloth_permutation_mod_op(sp, x, t);
}

bool sloth_permutation_verifyProofVDF(SlothPermutation* sp, int64_t t, int64_t x, int64_t y) {
    return sloth_permutation_mod_verif(sp, y, x, t);
}
