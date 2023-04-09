#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <gmp.h>

#include "sloth_permutation.h"

#define HEX(x) #x

// Block time tests

void test_vdf01() {
  SlothPermutation sloth;
  mpz_init_set_ui(sloth.p, 23);
  mpz_t x, t, y;
  mpz_inits(x, t, y, NULL);

  mpz_set_ui(x, 10);
  mpz_mod(x, x, sloth.p);
  mpz_set_ui(t, 50);

  sloth.generate_proof_vdf(y, t, x);
  bool verified = sloth.verify_proof_vdf(t, x, y);
  gmp_printf("[VDF01] generate and verify, small: %d\n", verified);

  mpz_clears(x, t, y, sloth.p, NULL);
}

void test_vdf02() {
  SlothPermutation sloth;
  mpz_init_set_str(sloth.p, HEX(73237431696005972674723595250817150843), 10);
  mpz_t x, t, y;
  mpz_inits(x, t, y, NULL);

  mpz_set_str(x, "808080818080808080818080", 16);
  mpz_mod(x, x, sloth.p);
  mpz_set_ui(t, 2000);

  sloth.generate_proof_vdf(y, t, x);
  bool verified = sloth.verify_proof_vdf(t, x, y);
  gmp_printf("[VDF02] generate and verify, medium: %d\n", verified);

  mpz_clears(x, t, y, sloth.p, NULL);
}

void test_vdf03() {
  SlothPermutation sloth;
  mpz_t x, y;
  mpz_inits(x, y, NULL);

  mpz_set_ui(x, 0x789acdef);
  mpz_mul_2exp(x, x, 32);
  mpz_add_ui(x, x, 0x06543210);

  sloth.write_big_int_to_buffer(y, x, 8);
  sloth.read_big_int_from_buffer(x, y);

  bool equal = (mpz_cmp(x, y) == 0);
  gmp_printf("[VDF03] bigint export/import from buffers: %d\n", equal);

  mpz_clears(x, y, NULL);
}

void test_vdf04() {
  SlothPermutation sloth;
  mpz_t x, y;
  mpz_inits(x, y, NULL);

  mpz_set_ui(x, 0x789acdef);
  mpz_mul_2exp(x, x, 32);
  mpz_add_ui(x, x, 0x06543210);

  sloth.write_big_int_to_buffer(y, x, 8);
  sloth.read_big_int_from_buffer(x, y, 8);

  bool equal = (mpz_cmp(x, y) == 0);
  gmp_printf("[VDF04] bigint export/import from buffers of arbitrary size = 64: %d\n", equal);

  mpz_clears(x, y, NULL);
}

void test_vdf05() {
  SlothPermutation sloth;
  mpz_t x, y;
  mpz_inits(x, y, NULL);
  mpz_set_ui(x, 0x789acdef);
  mpz_mul_2exp(x, x, 32);
  mpz_add_ui(x, x, 0x06543210);
  mpz_mul_2exp(x, x, 64);
  mpz_add(x, x, x);

  sloth.write_big_int_to_buffer(y, x, 16);
  sloth.read_big_int_from_buffer(x, y, 16);

  bool equal = (mpz_cmp(x, y) == 0);
  gmp_printf("[VDF05] bigint export/import from buffers of arbitrary size = 128: %d\n", equal);

  mpz_clears(x, y, NULL);
}

void test_vdf06() {
  SlothPermutation sloth;
  mpz_t challenge, t, proof;
  mpz_inits(challenge, t, proof, NULL);
  mpz_set_str(challenge, "137010851887946622574152571239132315287", 10);
  mpz_set_ui(t, 200);

  sloth.set_prime("297010851887946822574352571639152315287");
  sloth.generate_buffer_proof_vdf(proof, t, challenge, 16);
  bool verified = sloth.verify_buffer_proof_vdf(t, challenge, proof, 16);
  gmp_printf("[VDF06] bigint export/import from buffers of arbitrary size = 128 bits and VDF test: %d\n", verified);

  mpz_clears(challenge, t, proof, NULL);
}

void test_vdf07() {
  SlothPermutation sloth;
  mpz_t challenge, t, proof;
  mpz_inits(challenge, t, proof, NULL);
  mpz_set_str(challenge, "c8774beca835214089860e8b01157c6c883c70f4a25e83d190b577f7f56bcfd3", 16);
  mpz_set_ui(t, 200);

  sloth.set_prime("64106875808534963770974826322234655855469213855659218736479077548818158667371");
  sloth.generate_buffer_proof_vdf(proof, t, challenge, 32);
  bool verified = sloth.verify_buffer_proof_vdf(t, challenge, proof, 32);
  gmp_printf("[VDF07] bigint export/import from buffers of arbitrary size = 256 bits and VDF test: %d\n", verified);

  mpz_clears(challenge, t, proof, NULL);
}

void test_vdf08() {
  SlothPermutation sloth;
  mpz_t challenge, t, proof;
  mpz_inits(challenge, t, proof, NULL);
  mpz_set_str(challenge, "137010851887946622574152571239132315287", 10);
  mpz_set_ui(t, 200);

  sloth.set_prime("297010851887946822574352571639152315287");
  sloth.generate_buffer_proof_vdf(proof, t, challenge, 16);
  bool verified = sloth.verify_buffer_proof_vdf(t, challenge, proof, 16);
  gmp_printf("[VDF08] bigint export/import from buffers of arbitrary size = 128 bits and VDF test: %d\n", verified);

  mpz_clears(challenge, t, proof, NULL);
}

void test_vdf09() {
  SlothPermutation sloth;
  mpz_t challenge, t, proof;
  mpz_inits(challenge, t, proof, NULL);

  mpz_set_str(challenge, HEX(c8774beca835214089860e8b01157c6c883c70f4a25e83d190b577f7f56bcfd3), 16);
  mpz_set_ui(t, 200);

  // 256 bits prime
  mpz_set_str(sloth.p, HEX(64106875808534963770974826322234655855469213855659218736479077548818158667371), 10);

  sloth.generate_buffer_proof_vdf(proof, t, challenge, 32);
  bool verified = sloth.verify_buffer_proof_vdf(t, challenge, proof, 32);
  gmp_printf("[VDF09] bigint export/import from buffers of arbitrary size = 256 bits and VDF test many steps: %d\n", verified);

  mpz_clears(challenge, t, proof, sloth.p, NULL);
}
