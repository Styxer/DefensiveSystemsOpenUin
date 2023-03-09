#pragma once

#include <array>

// The client 
constexpr uint8_t client_version = 3;

//The length of a client ID
constexpr uint8_t client_id_length = 16;

//Maximum length of the user_name
constexpr size_t max_username_length = 255;

//Maximum length of a file_name
constexpr size_t max_filename_length = 255;

//Amount of retries to do for the CRC check, 
constexpr size_t crc_retry_count = 4;

//Client configuration file_name
constexpr char client_config_filename[] = "me.info";

//Transfer configuration file_name 
constexpr char transfer_config_filename[] = "transfer.info";

// Type indicating the client ID to 
using client_id = std::array<uint8_t, client_id_length>;

//Type indicating the user_name to 
using user_name = std::array<uint8_t, max_username_length>;

// * Type indicating the file_name to 
using file_name = std::array<uint8_t, max_filename_length>;
