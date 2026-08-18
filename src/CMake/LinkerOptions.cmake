################################################################################
# Global linker options
################################################################################
foreach(cfg IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER "${cfg}" CFG)

    set(CMAKE_EXE_LINKER_FLAGS_${CFG} "")
    set(CMAKE_MODULE_LINKER_FLAGS_${CFG} "")
    set(CMAKE_SHARED_LINKER_FLAGS_${CFG} "")
    set(CMAKE_STATIC_LINKER_FLAGS_${CFG} "")
endforeach()

################################################################################
# Incremental linking
################################################################################
set(INCREMENTAL_LINKING_ENABLED OFF)
if(ENABLE_INCREMENTAL_LINKING)
    if(MSVC)
        if(NOT ENABLE_IPO)
            set(INCREMENTAL_LINKING_ENABLED ON)
            message(WARNING "Incremental linking enabled")
            add_link_options(
                /INCREMENTAL
            )
        else()
            message(WARNING "Incremental linking disabled (IPO/LTO is enabled)")
            add_link_options(
                /INCREMENTAL:NO
            )
        endif()
    else()
        message(WARNING "Incremental linking is only supported with MSVC; option ignored")
    endif()
endif()

if(INCREMENTAL_LINKING_ENABLED)
    add_link_options(
        /OPT:NOREF
        /OPT:NOICF
    )
else()
    add_link_options(
        /OPT:REF
        /OPT:ICF
    )
endif()
