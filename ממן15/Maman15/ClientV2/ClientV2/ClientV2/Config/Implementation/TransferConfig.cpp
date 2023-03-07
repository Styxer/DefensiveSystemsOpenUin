#include <stdexcept>

#include "../../Utils/Headers/Constants.h"

#include "../Headers/TransferConfig.h"

TransferConfig::TransferConfig(const std::string& filename) : file_(filename), server_address_(), server_port_(), username_({ 0 }), files_() {
    if (!this->file_.is_open()) {
        throw std::runtime_error::runtime_error("Missing transfer config!");
    }

    std::getline(this->file_, this->server_address_, ':');
    std::getline(this->file_, this->server_port_);
    std::getline(this->file_, this->username_);
    if (this->username_.size() > max_username_length) {
        throw std::runtime_error::runtime_error("Username too long!");
    }

    for (std::string file_name; std::getline(this->file_, file_name); ) {
        if (file_name.size() > max_filename_length) {
            throw std::runtime_error::runtime_error("Filename too long!");
        }

        this->files_.push_back(file_name);
    }
}

const std::string& TransferConfig::get_server_address() const noexcept {
    return this->server_address_;
}

const std::string& TransferConfig::get_server_port() const noexcept {
    return this->server_port_;
}

const std::string& TransferConfig::get_username() const noexcept {
    return this->username_;
}

const std::vector<std::string>& TransferConfig::get_files() const noexcept {
    return this->files_;
}
