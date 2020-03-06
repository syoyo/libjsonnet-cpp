# libjsonnet-cpp

Embed jsonnet https://github.com/google/jsonnet for your C++11 application.
Code is grabbed from jsonnet repo.

https://github.com/google/jsonnet

## Why

jsonnet++ requires the generation of std.jsonnet.h, which causes build error on some platform and when cross-compiling.

libjsonnet-cpp is a self-contained mobule and does not require third_party libraries and external program execution to embed it to your C++11 application.

## Supported Platform

* [ ] Linux 64bit
* [ ] Android arm64-v8a
* [ ] macOS
* [ ] Visual Studio 2017 or later

## Build

### Linux, macOS


### MSVC

## For developer

### How to sync with jsonnet repo.

* Copy C++ related files in the following folder at jsonnet repo
  * `include`, `core`, `cpp`
* Generate std.stdlib.h in jsonnet repo, then copy it to `core` folder.

## TODO

* [ ] `add_submobule` ready CMakeFile.

## License

libjsonnet-cpp is licensed under Apache 2.0 License.

### Third party licenses

* jsonnet: Apache 2.0 License.
* md5: See `third_party/md5/LICENSE` for details
* json.hpp: MIT license. https://github.com/nlohmann/json
