#include <gtest/gtest.h>
#include <ntw/sys/version.hpp>

TEST(ntdll, sys_ver) {
	auto result = ntw::sys::sys_ver();
    result.and_then([](decltype(result) ver) { 
		EXPECT_TRUE(ver->to_ver_enum() != ntw::sys::ver_enum::windows_ancient);
    });
}

TEST(ntdll, sys_ver_from_peb) {
    auto result = ntw::sys::sys_ver_from_peb();
    result.and_then([](decltype(result) ver) {
        EXPECT_TRUE(ver->to_ver_enum() != ntw::sys::ver_enum::windows_ancient);
    });
}