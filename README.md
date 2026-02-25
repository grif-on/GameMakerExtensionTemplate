# GameMaker Extension Template

Start making your new C++ GameMaker extension in a few clicks, while leaving all renaming deuties to automation!

# How to use

- Copy/clone this repo.
- Install [PowerShell 7](https://github.com/PowerShell/PowerShell/releases) (or just use old one that preinstalled on windows).
- Run `./rename_extension.ps1`.
  - It will replace all "GameMakerExtensionTemplate" strings/names for this repo files with your own name (thus changing .dll/.so/.dylib output filenames and even VisualStudio/Xcode project names).
- Follow Multiplatform build steps (recomended) or per platform ones.
- Open `./TestProject/TestProject.yyp`.
- And run the game.
  - You should see that example functions are working.
- Code, compile, test, repeat :)
- Once you feel that extension are ready, just use GameMakers local package creation tool to transfer extension asset from TestProject in to your game project.

# Building an extension

### Multiplatform (CMake + PowerShell)

- First time -
```
cmake -B "out"
```
- Everytime after C++ code changes -
```
cmake --build "out" --config Release; Copy-Item "./out/Release/GameMakerExtensionTemplate.dll" "./TestProject/extensions/GameMakerExtensionTemplate/GameMakerExtensionTemplate.dll" -Force
```

Note - If you want to add new .cpp files, make sure to add them in `add_library()` arguments inside `./CMakeLists.txt` and re-run `cmake -B "out"`.

### Windows Desktop

- Use `./GameMakerExtensionTemplate.sln` in VisualStudio.

### Linux

- Use the `./build_linux.sh` shell script.

### Mac OS X

- Use `./GameMakerExtensionTemplate.xcodeproj/` in XCode.

### HTML5

- Check out `./GameMakerExtensionTemplate.js`.

It have nothing to do with C++ though, it is here just as an example on how to make JS proxy file for C++ extension ¯\\\_(ツ)\_/¯

### Other platforms

- Check out:
  - `./build_emscripten.sh` (GX.games)
  - `./GameMakerExtensionTemplateUWP/`
  - `./WinPhone/`