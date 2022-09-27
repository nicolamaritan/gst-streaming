cmake_minimum_required(VERSION 3.22)

project(video-streamer)

# To use pkg_check_modules
find_package(PkgConfig REQUIRED)

# Check for gstreamer-1.0
pkg_check_modules(GSTLIBS REQUIRED
        gstreamer-1.0
        #gobject-2.0
        #glib-2.0
        #gstreamer-sdp-1.0
        #gstreamer-pbutils-1.0
        #gstreamer-check-1.0
)


# include_directories(
#         include
#         /usr/include/glib-2.0
#         /usr/lib64/glib-2.0/include
#         /usr/include/gstreamer-1.0
#         /usr/include/gio-unix-2.0)

add_library(screen
        src/screen.c
        include/screen.h)

add_library(sender_parse
        src/sender_parse.c
        include/sender_parse.h)   

add_executable(sender
    src/sender.c
    src/screen.c
    src/sender_parse.c)

target_link_libraries(sender
    screen
    ${GSTLIBS_LIBRARIES}
    sender_parse)

# Include GSTLIBS dirs to sender and screen
target_include_directories(sender PUBLIC ${GSTLIBS_INCLUDE_DIRS})
target_include_directories(screen PUBLIC ${GSTLIBS_INCLUDE_DIRS})