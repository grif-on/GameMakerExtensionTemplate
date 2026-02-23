# GameMaker Extension Template

Template for GameMaker C++ Extension.

# How to use

- Copy/clone this repo.
- Follow Multiplatform build steps or per platform ones.
- Open `./TestProject/TestProject.yyp`.
- And run the game. You should see output of example functions.

# Build

### Multiplatform (CMake + PowerShell)

- First time -
```
cmake -B "out"
```
- Everytime after C++ code changes -
```
cmake --build "out" --config Release; Copy-Item "./out/Release/ExampleExtension.dll" "./TestProject/extensions/TestExtension/ExampleExtension.dll" -Force
```

Note - If you want to add new .cpp files, make sure to add them in `add_library()` inside `./CMakeLists.txt` and re-run `cmake -B "out"`.

### Windows Desktop

- Use `./ExampleExtension.sln` in Visual Studio.

### Linux

- Use the `build_linux.sh` shell script.

### Mac OS X

- Use ExampleExtension.xcodeproj and XCode to build.

### Other platforms

- Check out:
  - `./build_emscripten.sh`
  - `./ExampleExtension.xcodeproj`
  - `./ExampleExtensionUWP`