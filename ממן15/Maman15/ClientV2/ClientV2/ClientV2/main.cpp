#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/format.hpp>

#include "./Utils/Headers/Constants.h"

#include "./Config/Headers/TransferConfig.h"
#include "./config/Headers/ClientConfig.h"

#include "./User/Header/User.h"

using boost::asio::ip::tcp;
using namespace boost;

int main(void) {
    try {       

        TransferConfig transfer_config(transfer_config_filename);
        ClientConfig client_config(client_config_filename);
        client_config.set_username(transfer_config.get_username());
        
        tcp::iostream tcp_stream;
        tcp_stream.connect(transfer_config.get_server_address(), transfer_config.get_server_port());

        User user(client_config);
        user.sign_up(tcp_stream);
        user.do_key_exchange(tcp_stream);

        for (auto filename : transfer_config.get_files()) {
            std::cout << "Uploading " << filename << "..." << std::endl;
            user.upload_file(tcp_stream, filename);
        }

        tcp_stream.close();
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}