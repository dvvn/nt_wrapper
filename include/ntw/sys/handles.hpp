#pragma once
#include "../detail/common.hpp"
#include "../result.hpp"
namespace ntw::sys {
    struct handle_information {
        uint16_t pid;
        uint16_t creator_back_trace_index;
        uint8_t  object_type_index;
        uint8_t  handle_attributes;
        uint16_t handle_value;
        void*    object;
        uint32_t granted_access;
    };

    template<class Range>
    NTW_INLINE ntw::result<std::span<handle_information>>
               system_handles(Range&& buffer, ulong_t* returned = nullptr);
} // namespace ntw::sys

#include "impl/handles.inl"