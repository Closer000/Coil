# Coil: A minimalist grid-based snake game built with raylib and C

## About:

Coil is a small desktop Snake game.The snake moves cell by cell on a 50x50 grid.
Just like classic Snake game, you can eat food to grow and raise your score,avoid the walls and your own body.
When you reach the target score, you win!

It is built as a learning project: plain C11, raylib for windowing and rendering, CMake for the build and vcpkg for dependencies.

## Features:

- Grid-based movement with frame-rate independent stepping
- Three difficulty presets (target score 20 / 50 / 100)
- Real-time score display
- Win and game-over screens with instant restart
- Optional test grid overlay for debugging
- Custom window icon; assets are bundled with the build

## Controls:

| Action | Key |
| --- | --- |
| Move | W / A / S / D |
| Menu | Mouse |
| Restart (After win or game over) | R |
| Quit | ESC |

## Download:

Prebuilt Windows builds are available on the [Releases](../../releases) page.

Download the latest `Coil-v1.0-win64.zip`, extract it, and run `Coil.exe`.
Keep `raylib.dll`, `glfw3.dll` and the files from `assets` next to the executable.

## Build from Source:

### Requirements:

- Windows 10/11
- Visual Studio 2022 or 2026 with the MSVC toolchain
- CMake 3.25 or newer(4.3+ if you use the `Visual Studio 18 2026` generator)
- vcpkg

### Steps:

1. Install raylib with vcpkg:`vcpkg install raylib:x64-windows`
2. Set the environment variable `COIL_VCPKG_ROOT` to your vcpkg root, for example 'D:\vcpkg'
3. Configure: `cmake --preset vs2026`
4. Build: `cmake --build --preset vs2026-release`

The executable is written to `out/build/vs2026/Release`.
The build copies the assets and required DLLs next to it.

You can also open the repository folder directly in Visual Studio; it reads 'CMakePresets.json'

### Troubleshooting:

- **Could not find raylib** - make sure `COIL_VCPKG_ROOT` points to a vcpkg installation that has raylib built for the `x64-windows` triplet.
- **LNK2019: unresolved external symbol WinMain** - the `/ENTRY:mainCRTStartup` linking option is missing: `CMakeLists.txt` sets it for MSVC.
- **The window icon is missing** - `SnakeIcon.png` must be next to executable. The build copies it from `assets/`.

## Project Structure:

- src/Code: C sources
- src/Head: headers 
- assets/: runtime assets
- resources/: Windows resources(icon, .rc)

## Development Log

See [docs/DEVLOG.md](docs/DEVLOG.md) for the development history and [CHANGELOG.md](CHANGELOG.md) for version notes.

## License

MIT. See [LICENSE](LICENSE).

## Acknowledgements

- [raylib](https://www.raylib.com/) - simple and easy-to-use game programming library
- [vcpkg](https://vcpkg.io/) - C/C++ package manager