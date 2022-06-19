#include <ntw/sys/pool_tags.hpp>
#define WIN32_NO_STATUS
#include <catch2/catch.hpp>

#pragma comment(lib, "ntdll.lib")

TEST_CASE("system pool tags list")
{
    std::vector<std::uint8_t> arr(0x100000);
    auto                      tags = ntw::sys::pool_tags(arr);
    REQUIRE(tags);
    for(auto& t : *tags) {
        ;
    }
}