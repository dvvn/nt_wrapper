#pragma once
#include "../version.hpp"

namespace ntw::sys {

    
    template<typename T>
    NTW_INLINE ntw::sys::ver_enum ntw::sys::version<T>::to_ver_enum() noexcept
    {
        if(major_version == 5 && minor_version < 1 || major_version < 5) {
            return ver_enum::windows_ancient;
        }
        else if(major_version == 5 && minor_version == 1) {
            return ver_enum::windows_xp;
        }
        else if(major_version == 5 && minor_version == 2) {
            return ver_enum::windows_server_2003;
        }
        else if(major_version == 6 && minor_version == 0) {
            return ver_enum::windows_vista;
        }
        else if(major_version == 6 && minor_version == 1) {
            return ver_enum::windows_7;
        }
        else if(major_version == 6 && minor_version == 2) {
            return ver_enum::windows_8;
        }
        else if(major_version == 6 && minor_version == 3) {
            return ver_enum::windows_8_1;
        }
        else if(major_version == 10 && minor_version == 0) {
            return ver_enum::windows_10;
        }
        else if(major_version == 10 && minor_version > 0 || major_version > 10) {
            return ver_enum::windows_new;
        }
        return ver_enum::windows_ancient;
    }

    NTW_INLINE ntw::result<version<wchar_t>> sys_ver()
    {
        version<wchar_t> ver = {sizeof(version<wchar_t>), 0, 0 };
        ntw::status      status = 
        NTW_SYSCALL(RtlGetVersion)(reinterpret_cast<PRTL_OSVERSIONINFOEXW>(&ver));
        return { status, ver };
    }

    NTW_INLINE ntw::result<version<wchar_t>> sys_ver_from_peb() {
        version<wchar_t> ver = { sizeof(version<wchar_t>),
                                 NtCurrentPeb()->OSMajorVersion,
                                 NtCurrentPeb()->OSMinorVersion };
        return { ntw::status{ STATUS_SUCCESS }, ver };
    }
} // namespace ntw::sys