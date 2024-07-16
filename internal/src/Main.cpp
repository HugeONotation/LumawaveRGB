#include <iostream>
#include <string_view>

#include "LumawaveRGB.hpp"

int main(int argc, char* argv[]) {
    using namespace lwrgb;

    if (argc < 2) {
        std::cout << "Pass either -client or -server to the program." << std::endl;
        return EXIT_FAILURE;
    }

    //TODO: Parse configurations from command line input

    if (std::string_view{argv[1]} == "-client") {
        //TODO: Create configuration by other means
        Client_config config;
        config.ip4_address = 0x7F000001; // 127.0.0.1
        config.use_ipv6 = false;
        config.port = 20157;

        std::string_view result = run_client(config);
        if (!result.empty()) {
            std::cout << "Error encountered! See STDERR" << std::endl;
            std::cerr << result << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    if (std::string_view{argv[1]} == "-server") {
        //TODO: Create configuration by other means
        Server_config config;
        config.ip4_address = 0x7F000001; // 127.0.0.1
        config.use_ipv6 = false;
        config.port = 20157;

        std::string_view result = run_server(config);
        if (!result.empty()) {
            std::cout << "Error encountered! See STDERR" << std::endl;
            std::cerr << result << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    std::cout << "Second argument not recognized" << std::endl;
    return EXIT_FAILURE;
}
