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


add_executable( video_streamer
    src/main.c
    src/screen.c)

target_link_libraries(video_streamer
    screen
    ${GSTLIBS_LIBRARIES})

# Include GSTLIBS dirs to video_streamer and screen
target_include_directories(video_streamer PUBLIC ${GSTLIBS_INCLUDE_DIRS})
target_include_directories(screen PUBLIC ${GSTLIBS_INCLUDE_DIRS})