#!/bin/bash

RESTSDK_VERSION="v2.9.1"
DEFAULT_LIB_DIRECTORY_PATH="."
BUILD_PACKAGES="build-essential git cmake zlib1g-dev libboost-all-dev libssl1.0-dev"

libDir=${1:-$DEFAULT_LIB_DIRECTORY_PATH}

install_build_deps() {
  sudo apt update
  sudo apt install --yes $BUILD_PACKAGES
}

install_cpprestsdk(){
	restsdkDir="$libDir/cpprestsdk"
	restsdkBuildDir="$restsdkDir/build.release"
   
   if [ -d "$restsdkDir" ]; then
      rm -rf "$restsdkDir"
   fi
   
	git clone https://github.com/Microsoft/cpprestsdk.git "$restsdkDir"
	(cd $restsdkDir && git checkout tags/$RESTSDK_VERSION -b $RESTSDK_VERSION)
	mkdir "$restsdkBuildDir"
	(cd "$restsdkBuildDir" && cmake ../Release -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DBUILD_TESTS=OFF -DBUILD_SAMPLES=OFF)
	(cd "$restsdkBuildDir" && make)
}

mkdir -p "$libDir"
install_build_deps
install_cpprestsdk
