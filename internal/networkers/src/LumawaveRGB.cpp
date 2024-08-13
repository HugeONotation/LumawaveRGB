#include "LumawaveRGB.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <span>

#include <boost/asio.hpp>

namespace lwrgb {

    struct Client_connection {
        std::vector<std::array<std::uint8_t, 3>> buffer;



        boost::asio::ip::tcp::socket socket;
    };

    std::string_view verify_server_config(const Server_config& config) {
        if (config.use_ipv6) {
            if (config.ip6_address[0] == 0 || config.ip6_address[1] == 0) {
                return "ipv6 address not initialized";
            }
        } else {
            if (config.ip4_address == 0) {
                return "ipv4 address not initialized";
            }
        }

        if (config.port < 1024) {
            return "Invalid port specified";
        }

        return "";
    }

    std::string_view run_server(const Server_config& config) {
        std::string_view result = verify_server_config(config);
        if (!result.empty()) {
            return result;
        }

        using namespace boost::asio;
        using namespace boost::asio::ip;

        try {
            io_context ctx{};

            tcp::resolver res{ctx};

            std::string host = std::to_string(config.ip4_address); // This isn't correct lol
            std::string port = std::to_string(config.port);
            tcp::resolver::results_type endpoints = res.resolve(host, port);

            tcp::socket socket{ctx};
            boost::asio::connect(socket, endpoints);

            while (true) {
                //TODO: Populate buffer with RGB strip colors
                std::string buffer{"Hello, World!"};

                boost::asio::write(socket, boost::asio::buffer(buffer));
            }
        } catch (std::exception& e) {
            //TODO: Do proper error handling
            std::cerr << "Exception: " << e.what() << std::endl;
        }

        return {};
    }

    void client_session(boost::asio::ip::tcp::socket socket) {
        try {
            while (true) {
                char data[4 * 1024];

                boost::system::error_code error;

                std::size_t length = socket.read_some(boost::asio::buffer(data), error);

                std::cout << std::string_view{data, length} << std::endl;

                //TODO: Utilize data read from buffer

                if (error == boost::asio::error::eof) {
                    break; // Connection closed by server
                } else if (error) {
                    throw boost::system::system_error(error);
                }

                //boost::asio::write(socket, boost::asio::buffer(data, length));
            }
        } catch (std::exception& e) {
            //TODO: Do proper error handling
            std::cerr << "Exception in thread: " << e.what() << std::endl;
        }
    }

    std::string_view verify_client_config(const Client_config& config) {
        if (config.use_ipv6) {
            if (config.ip6_address[0] == 0 || config.ip6_address[1] == 0) {
                return "ipv6 address not initialized";
            }
        } else {
            if (config.ip4_address == 0) {
                return "ipv4 address not initialized";
            }
        }

        if (config.port < 1024) {
            return "Invalid port specified";
        }

        return "";
    }

    std::string_view run_client(const Client_config& config) {
        std::string_view result = verify_client_config(config);
        if (!result.empty()) {
            return result;
        }

        using namespace boost::asio;
        using namespace boost::asio::ip;

        io_context ctx;
        tcp::acceptor acc{ctx, tcp::endpoint{config.use_ipv6 ? tcp::v6() : tcp::v4(), config.port}};

        while (true) {
            tcp::socket socket{ctx};
            acc.accept(socket);

            std::thread{client_session, std::move(socket)}.detach();
        }

        return {};
    }

}
