#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "../../Utils/Headers/Constants.h"

class TransferConfig {
public:
	TransferConfig(const std::string& filename);

	const std::string& get_server_address() const noexcept;

	const std::string& get_server_port() const noexcept;

	const std::string& get_username() const noexcept;

	const std::vector<std::string>& get_files() const noexcept;

private:
	std::fstream file_;
	std::string server_address_;
	std::string server_port_;
	std::string username_;
	std::vector<std::string> files_;
};
