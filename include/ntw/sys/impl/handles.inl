#pragma once
#include "../handles.hpp"

namespace ntw::sys {

    template<class Range>
    NTW_INLINE ntw::result<std::span<handle_information>>
               system_handles(Range&& buffer, ulong_t* returned /*= nullptr*/)
    {
        const auto  first  = detail::unfancy(detail::adl_begin(buffer));
        const auto  size   = static_cast<ulong_t>(detail::range_byte_size(buffer));
        ntw::status status = NTW_SYSCALL(NtQuerySystemInformation)(
            SystemHandleInformation, first, size, returned);

        std::span<handle_information> r{
            reinterpret_cast<handle_information*>(first + sizeof(uint32_t)),
            *reinterpret_cast<uint32_t*>(first)
        };
        return { status, r };
    }
} // namespace ntw::sys