#pragma once
#include "../detail/common.hpp"
#include "../result.hpp"
namespace ntw::sys {
    enum class ver_enum {
        windows_ancient     = 0,
        windows_xp          = 51,
        windows_server_2003 = 52,
        windows_vista       = 60,
        windows_7           = 61,
        windows_8           = 62,
        windows_8_1         = 63,
        windows_10          = 100,
        windows_new         = (std::numeric_limits<int>::max)()
    };

    template<typename T>
    struct version {
        uint32_t os_version_info_size;
        uint32_t major_version;
        uint32_t minor_version;
        uint32_t build_number;
        uint32_t platform_id;
        T        ver[128]; // Maintenance string for PSS usage
        uint16_t service_pack_major;
        uint16_t service_pack_minor;
        uint16_t suite_mask;
        uint8_t  product_type;
        uint8_t  reserved;
        NTW_INLINE ver_enum to_ver_enum() noexcept;
    };


    NTW_INLINE ntw::result<version<wchar_t>> sys_ver();
} // namespace ntw::sys

#include "impl/version.inl"