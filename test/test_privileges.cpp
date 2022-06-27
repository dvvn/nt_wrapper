#include <gtest/gtest.h>
#include <ntw/ob/token.hpp>

TEST(ntdll, adjust_privileges)
{
    const auto tok = ntw::ob::token::open(
        ntw::ob::process_ref{}, ntw::ob::token_access{}.adjust_privileges().query());
    const auto res = tok->adjust_privilege(ntw::ob::privilege::debug().enable());
    EXPECT_TRUE(res.success());
}
