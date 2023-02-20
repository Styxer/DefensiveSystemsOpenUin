#pragma once
#include <osrng.h>
#include <rsa.h>

using namespace CryptoPP;

static constexpr unsigned int key_size = 160;
static constexpr unsigned int bits = 1024;
static constexpr unsigned int block_size = 128;

AutoSeededRandomPool rng_;
