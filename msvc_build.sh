#!/bin/sh

shopt -s nocasematch

mode="default"
config="Release"
for OPT in "$@"
do
    case $OPT in
        debug|release)
            config=$OPT
        ;;
        build|rebuild|install)
            mode=$OPT
        ;;
    esac
done

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
    MSBuild.exe ./ALL_BUILD.vcxproj -t:Build -p:Configuration=$config -p:Platform="Win32" -v:m -nologo
;;

"rebuild")
    MSBuild.exe ./ALL_BUILD.vcxproj -t:Rebuild -p:Configuration=$config -p:Platform="Win32" -v:m -nologo
;;

"install")
    MSBuild.exe ./INSTALL.vcxproj -t:Build -p:Configuration=$config -p:Platform="Win32" -v:m -nologo
;;

*)
    echo "Error : Invalid option"
;;
esac