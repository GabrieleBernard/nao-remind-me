# nao-remind-me
Simple time-manager and scheduler with option to be queried by a NAO robot

## How to build
1. Clone the repository.
2. Go to the directory `nao-remind-me/libs` and execute the script: `./build_dependencies.sh` that'll clone the [C++ REST SDK](https://github.com/Microsoft/cpprestsdk) repository and will build the static version of the library.
3. Go to the directory `nao-remind-me` and type the following commands:
   ```
   $ mkdir build
   $ cd build
   $ cmake ..
   $ make
   ```
4. In the `build` directory you should see the executable files.
