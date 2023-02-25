#pragma once

#include <string>
#include <fstream>

#include "../../Utils/Headers/Constants.h"

class ClientConfig {
public:
	ClientConfig(const std::string& filename);

	bool is_full() const noexcept;

	const std::string& get_username() const noexcept;

	void set_username(const std::string& username);

	const client_id& get_client_id() const noexcept;

	void set_client_id(const client_id& client_id);

	const std::string& get_public_key() noexcept;

	void set_public_key(const std::string& public_key);

	const std::string& get_private_key() noexcept;

private:
	bool is_full_;
	std::fstream file_;
	std::string username_;
	client_id client_id_;
	std::string private_key_;
	std::string public_key_;
};