# sloth-vdf-gcc
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
Generated proof: 162949938008000040363510076671725537478825197145029107763660641737067617049504042810537455813286617354359441947774021734710529883446950702179202821436558543249945005874767098449940513505759016612112615571539306689756914470822154600079684000520431008956057031752584120574418366552954124322232955819107965612972
Verification result: True
```

## Testing

And then run the tests:

```
ctest
```

## Performance

## Performance

Approx 1000 steps per second on a Macbook Pro Intel for the 1024 bits version.

