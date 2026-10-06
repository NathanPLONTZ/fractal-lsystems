# Dependencies

This is a C++ project with no third-party libraries, so there is no
`requirements.txt`, `package.json` or similar manifest to install from. The
build manifest is `Makefile/Makefile`; everything below is what has to exist on
the machine first.

## Required

| Tool | Version used | Notes |
|---|---|---|
| C++ compiler | MinGW g++ 6.3.0 | Any C++11 compiler. `-msse2 -mfpmath=sse` must be supported; see VERIFICATION.md for why it matters. |
| `make` | GNU make 3.82 (`mingw32-make`) | Pattern rules and `$(addprefix ...)` are used, so BSD make will not do. |

Standard library only: `<fstream>`, `<vector>`, `<string>`, `<cmath>`,
`<complex>`, `<sstream>`, `<iomanip>`, `<cstdio>`, `<cstdlib>`, `<ctime>`.
No image library — the BMP writer is part of the project.

## Optional

| Tool | Used for |
|---|---|
| R (base only) | `Lsystem/Test/regressionLineaire.R`, which fits the fractal dimension from the recorded samples. Uses `lm()`; no packages needed. |

## Build

```sh
cd Makefile
make
```

If `g++` is not on `PATH`:

```sh
make CXX="C:/MinGW/bin/g++"
```
