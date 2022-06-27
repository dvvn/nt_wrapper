#include <gtest/gtest.h>
#include <ntw/sys/handles.hpp>

TEST(ntdll, system_handles)
{
    std::vector<uint8_t>                  arr(0x1000000);
    auto res =  ntw::sys::system_handles(arr);
    EXPECT_TRUE(res.success());
    if (res.success()) {
        for(auto& handle : *res) {
            if (handle.pid == (uint16_t)NtCurrentProcessId()) {
                std::cout << handle.pid << std::endl;
            }
        }
    }
}
