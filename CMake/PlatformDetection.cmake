
if(WIN32)
    message(STATUS "Platform Windows detected.")
    add_definitions(-DRL_PLATFORM_WINDOWS)
elseif(APPLE)
    message(STATUS "Platform MacOS detected.")
    add_definitions(-DRL_PLATFORM_MACOS)
elseif(UNIX AND NOT APPLE)
    message(STATUS "Platform Linux detected.")
    add_definitions(-DRL_PLATFORM_LINUX)
elseif(ANDROID)
    message(STATUS "Platform Android detected.")
    add_definitions(-DRL_PLATFORM_ANDROID)
elseif(IOS)
    message(STATUS "Platform IOS detected.")
    add_definitions(-DRL_PLATFORM_IOS)
else()
    message(FATAL_ERROR "Platform Detection could not Identify your current Platform.")
endif()
