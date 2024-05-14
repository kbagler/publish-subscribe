# publish-subscribe

# Table of Contents

* [Build](#build)
    * [Dependencies](#dependencies)
    * [Running cmake](#running-cmake)
    * [Building](#building)
* [Running Unit Tests](#running-unit-tests)
* [Code Coverage](#code-coverage)

## Build
### Dependencies
  - CMake 3.16.3
  - C++17 compatible compiler (build tested with g++ 9.4.0) 

### Running cmake
Navigate to the root of the project directory and then issue the following commands:
1. `mkdir build` (Creates a build directory)
2. `cd build` (Switches into the build directory)
3. `cmake ..` (Actually runs cmake)

This will create all of the necessary build files for 'Release' build type. If
you want to have a Code Coverage information (see [Code
Coverage](#code-coverage)), 'Debug' type build is needed to be used. In order
to create files for 'Debug' build, run:
```
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

### Building
After cmake was run, issue the command:
```
make
```
After the successful build, all of the binaries can be found in `bin/` directory
inside the build directory.

## Running Unit Tests
Unit test can be run either by issuing the command:
```
make test
```
or by running `publish-subscribe-test` binary from `bin/` directory.

## Code Coverage
### Dependencies
  - lcov 1.14
  - gcovr 4.2

After the Unit Tests were run, Code Coverage information can be created by
running the command:
```
make coverage
```
Please note that creating Code Coverage information requires 'Debug' build
type, see [Running cmake](#running-cmake).

After running `make coverage`, the Code Coverage information can be found in
`coverage/` directory. Coverage information in user friendly .html format is
available by opening `coverage/html/index.html` file in your web browser.
Coverage information in text format is present in `coverage/txt/` directory.

