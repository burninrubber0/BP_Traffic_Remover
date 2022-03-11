Burnout Paradise Traffic Remover
=====

A small tool that permanently removes traffic from Burnout Paradise and Burnout Paradise Remastered by editing the TrafficData resource in B5TRAFFIC.BNDL.

Use [Noesis](https://richwhitehouse.com/index.php?content=inc_projects.php&showproject=91) with [DGIorio's Burnout Paradise Unpacker/Packer scripts](https://mega.nz/folder/9IkSVKyS#ariDuk-2b4e8vngMB7iZsA) to handle the bundle file. Run this tool on the extracted resource.

## Usage
This is a command-line application. There are currently no plans for a GUI version.
```
Usage: Traffic_Remover <platform> <input>
Valid platforms:
  PS3
  X360
  PC
  PS4
  NX
```

## Building
Requires [CMake](https://cmake.org/download) and [Qt](https://www.qt.io/download-qt-installer). Tested on CMake 3.21 and Qt 6.1.3 only. The path to your Qt installation must be added to the system environment variables under `CMAKE_PREFIX_PATH`.
```sh
$ mkdir build && cd build
$ cmake ..
$ cmake --build .
```
