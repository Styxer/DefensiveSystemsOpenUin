#pragma once

#include <array>

//The client version as 
constexpr uint8_t client_version = 3;

//The length of a client ID.
constexpr uint8_t client_id_length = 16;

//Maximum length of the username.
constexpr size_t max_username_length = 255;

//Maximum length of a file_name.
constexpr size_t max_filename_length = 255;

//Amount of retries to do for the CRC check.
constexpr size_t crc_retry_count = 4;

//Client configuration file_name  
constexpr char CLIENT_CONFIG_FILENAME[] = "me.info";

//Transfer configuration file_name 
constexpr char TRANSFER_CONFIG_FILENAME[] = "transfer.info";

//the client ID.
using client_id = std::array<uint8_t, client_id_length>;

//the username
using username = std::array<uint8_t, max_username_length>;

//the file_name
using filename = std::array<uint8_t, max_filename_length>;
