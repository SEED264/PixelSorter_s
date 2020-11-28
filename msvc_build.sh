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

case $mode in
"build")
    MSBuild.exe ./ALL_BUILD.vcxproj -t:Build -p:Configuration=Release -p:Platform="Win32" -v:m -nologo
;;

"rebuild")
    MSBuild.exe ./ALL_BUILD.vcxproj -t:Rebuild -p:Configuration=Release -p:Platform="Win32" -v:m -nologo
;;

"install")
    MSBuild.exe ./INSTALL.vcxproj -t:Build -p:Configuration=Release -p:Platform="Win32" -v:m -nologo
;;

*)
    echo "Error : Invalid option"
;;
esac