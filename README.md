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

## Server API
The server API accepts following HTTP GET requests:
- `http://<host_ip>:6502/v1/nao-remind-me/api/ping`
- `http://<host_ip>:6502/v1/nao-remind-me/api/entries`
- `http://<host_ip>:6502/v1/nao-remind-me/api/entries/length`
- `http://<host_ip>:6502/v1/nao-remind-me/api/entries/#` where `#` is the position of the agenda entries
Modify the `agenda-server/agenda-server.cpp` file to edit the server response. 

## Runtime environment
Use either of these operating systems:
- [Debian with Raspberry Pi Desktop](https://www.raspberrypi.org/downloads/raspberry-pi-desktop/)
- [Raspbian](https://www.raspberrypi.org/downloads/raspbian/)
- [Customized Raspbian and Raspberry Pi Desktop images](https://github.com/rainerum-robotics-rpi/raspbian-mods/releases/latest)

## Sources
Components of this software were taken from following projects:
- [Modern C++ micro-service implementation + REST API](https://medium.com/audelabs/modern-c-micro-service-implementation-rest-api-b499ffeaf898)
- [Sample micro-service in C++](https://github.com/ivanmejiarocha/micro-service)
- [Microsoft C++ REST SDK](https://github.com/Microsoft/cpprestsdk)
- [Agenda from K. Delugan](https://github.com/BisUmTo/ITI/tree/9561692d27169b37db2b9779196e22fc7dc9450f/3%20-%20Terza/Informatica/Vacanze%20Natale/Agenda)
- [Pololu DRV8835 dual motor driver kit for Raspberry Pi B+](https://github.com/pololu/drv8835-motor-driver-rpi)
- [WiringPi](http://wiringpi.com/)
