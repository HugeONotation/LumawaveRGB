#ifndef LUMAWAVERGB_LUMAWAVERGB_HPP
#define LUMAWAVERGB_LUMAWAVERGB_HPP

#include <cstdint>
#include <array>
#include <string_view>

namespace lwrgb {

    struct Server_config {
        std::uint32_t ip4_address{};
        std::array<std::uint64_t, 2> ip6_address{};

        std::uint16_t port = 0;

        bool use_ipv6 = false;
    };

    ///
    /// \param config Configuration for LumawaveRGB server
    /// \return String containing error messages. An empty
    /// string indicates success.
    std::string_view run_server(const Server_config& config);



    struct Client_config {
        std::uint32_t ip4_address{};
        std::array<std::uint64_t, 2> ip6_address{};

        std::uint16_t port = 0;

        bool use_ipv6 = false;
    };

    ///
    /// \param config Configuration for LumawaveRGB client
    /// \return String containing error messages. An empty
    /// string indicates success.
    std::string_view run_client(const Client_config& config);

}

#endif //LUMAWAVERGB_LUMAWAVERGB_HPP
