#include <gtest/gtest.h>
#include <ntw/sys/processes.hpp>
#pragma comment(lib, "ntdll.lib")
#include <iostream>

TEST(ntdll, query_extended_process_info) { 
	std::vector<uint8_t> arr(0x100000);
    auto processes = ntw::sys::processes_ex(arr);
    EXPECT_TRUE(processes.success()) << processes.code();
	for (auto& p : *processes) {
        if(p.id < 10)
            continue;
        if (p.id == (uintptr_t)NtCurrentProcessId()) {
            EXPECT_TRUE(p.image_name.empty() == false);
            for(auto& t : p.extended_threads()) {
                EXPECT_TRUE(t.thread_info.id != 0);
                EXPECT_TRUE(t.win32_start_address != 0);
            }
        }
	}
}

TEST(ntdll, query_process_info)
{
    std::vector<uint8_t> arr(0x100000);
    auto                 processes = ntw::sys::processes(arr);
    EXPECT_TRUE(processes.success());
    for(auto& p : *processes) {
        if(p.id == (uintptr_t)NtCurrentProcessId()) {
            EXPECT_TRUE(p.image_name.empty() == false);
            for(auto& t : p.threads()) {
                EXPECT_TRUE(t.id != 0);
            }
        }
    }
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}