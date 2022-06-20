#include <gtest/gtest.h>
#include <ntw/ob/process.hpp>
#include <ntw/info/memory.hpp>

void log_mem(ntw::memory::basic_info& mbi)
{
    std::cout << std::hex << mbi.base << "|" << mbi.size
              << "|" << mbi.allocation_base
              << "|" 
              << (mbi.protect.accessible() ? "" : "NOACCESS")
              << (mbi.protect.readable() ? "R" : "")
              << (mbi.protect.writeable() ? "W" : "")
              << (mbi.protect.executeable() ? "X" : "")
              << (mbi.protect.guarded() ? "G" : "") << "|"
              << (mbi.is_image() ? "IMAGE|" : "") << (mbi.is_mapped() ? "MAP|" : "")
              << (mbi.is_free() ? "FREE|" : "");
    std::cout << std::endl;
}

TEST(ntdll, memory)
{
    auto mem = ntw::ob::process_ref{}.query_mem<ntw::memory::basic_info>(0);
    bool find_main_module = false;
    while(true) {
        if(!mem)
            break;
        if (mem->base == reinterpret_cast<uintptr_t>(GetModuleHandleA(NULL))) {
            EXPECT_TRUE(mem->size != 0);
            find_main_module = true;
        }
        log_mem(*mem);
        mem = ntw::ob::process_ref{}.query_mem<ntw::memory::basic_info>(mem->end());
    }
    EXPECT_TRUE(find_main_module);
}