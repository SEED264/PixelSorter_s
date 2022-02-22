#!/bin/sh

if [ $# -gt 0 ]; then
    mode=$1
else
    mode="default"
fi

# Move current directory to build directory
script_dir=`dirname $0`
build_dir=$script_dir"/build"
if [ ! -e $build_dir ]; then
    echo "Build dir doesn't exists."
    echo "Creating build dir."
    mkdir -p $script_dir"/build"
fi
cd $script_dir"/build"

# Install dir
cmake_install_path=""

# Lua dirs
lua_include_dir=""
lua_library_dir=""

# Launch cmake
case $mode in
"msvc")
    cmake_prefix_path=""

    cmake .. -G"Visual Studio 16 2019" -A Win32 \
        -DCMAKE_PREFIX_PATH=$cmake_prefix_path \
        -DCMAKE_INSTALL_PREFIX=$cmake_install_path \
        -DLUA_INCLUDE_DIR=$lua_include_dir \
        -DLUA_LIBRARY_DIR=$lua_library_dir
;;

"msys")
    cmake_prefix_path=""

    cmake .. -G"MSYS Makefiles" \
        -DCMAKE_PREFIX_PATH=$cmake_prefix_path \
        -DCMAKE_INSTALL_PREFIX=$cmake_install_path\
        -DLUA_INCLUDE_DIR=$lua_include_dir \
        -DLUA_LIBRARY_DIR=$lua_library_dir
;;

"ninja")
    cmake_prefix_path=""

    cmake .. -G"Ninja" \
        -DCMAKE_PREFIX_PATH=$cmake_prefix_path \
        -DCMAKE_INSTALL_PREFIX=$cmake_install_path\
        -DLUA_INCLUDE_DIR=$lua_include_dir \
        -DLUA_LIBRARY_DIR=$lua_library_dir
;;

"clean")
    current_dir_name=`basename \`pwd\``
    if [ $current_dir_name = "build" ]; then
        rm -rf *
    fi
;;

*)
    echo "Error : Invalid option"
;;
esac