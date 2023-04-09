# slothvdf-gcc
Sloth Pseudo-VDF high-performance version in C.

## Building

Compile and build the project using CMake. Open a terminal in the project folder and run the following commands:

```sh
sudo apt-get install -y cmake build-essential
sudo apt-get install libgmp-dev
mkdir build
cd build
cmake ..
make
```

For macOS:

```sh
brew install cmake
brew install libgmp-dev
mkdir build
cd build
cmake ..
make
```

After compiling and building the project, you should have an executable named sloth_permutation_example in the build folder. Run the compiled program by executing the following command:

```sh
./sloth_permutation_example
```

You should see output similar to the following:

```yaml
Original value: 123456789
Modified value: 14685083385528342811
Verification: true
```
