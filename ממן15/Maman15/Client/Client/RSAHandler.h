#pragma once
#include <osrng.h>
#include <rsa.h>
#include <string>
#include <cstddef>

static constexpr unsigned int key_size = 160;
static constexpr unsigned int bits = 1024;
static constexpr unsigned int block_size = 128;

CryptoPP::AutoSeededRandomPool rng_;
CryptoPP::RSA::PrivateKey privateKey_;