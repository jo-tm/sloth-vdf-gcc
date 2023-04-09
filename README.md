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
Generated proof: 22383899008472923248342558038716577855249973925404630427668835255378090204398816111162687681292957371508730615056143258971547850805904084134819505260484717656828958962637003535630706560598176646251163304431089118507669354429155138397269397175019030837678969513371946863750726557534365492946093843219227319359
Verification result: True
```
