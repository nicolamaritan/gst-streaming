cmake_minimum_required(VERSION 3.22)

project(video-streamer)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTLIBS REQUIRED
        gobject-2.0
        glib-2.0
        gstreamer-sdp-1.0
        gstreamer-pbutils-1.0
        gstreamer-check-1.0)


include_directories(
        include
        /usr/include/glib-2.0
        /usr/lib64/glib-2.0/include
        /usr/include/gstreamer-1.0
        /usr/include/gio-unix-2.0)

add_library(screen
        src/screen.c
        include/screen.h)


add_executable( video_streamer
    src/main.c
    src/screen.c)

target_link_libraries(video_streamer
    screen
    ${GSTLIBS_LIBRARIES})

    
