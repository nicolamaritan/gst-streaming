# video-streamer
## Summary
Application demo and for video streaming on GStreamer.

Currently supporting Linux on X11.

## Usage
### Screen Sharing
#### Linux
```
$ ./sender -i _local-ip-address_  # On sender system
$ ./receiver                      # On receiver system
```

## Installation
Install GStreamer following https://gstreamer.freedesktop.org/documentation/installing/index.html?gi-language=c.

### Linux
Create build directory.
```
$ mkdir build
```

Enter build directory.
```
$ cd build
```

Run:
```
$ cmake ..
$ make
```
