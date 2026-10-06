# Verification of the refactoring

The codebase was cleaned up and deduplicated without changing what it computes.
This file records how that was checked, and what could not be checked.

## Method

Every program was built and run twice — once from the original sources, once
from the refactored ones — and the resulting bitmaps were compared byte for
byte with `md5sum`.

Two adjustments were needed to make the comparison meaningful:

- **`CercleApollonius` sizes its starting circles at random**, seeded from the
  clock, so no two runs agree. For the comparison only, the seed was pinned to
  a constant in both trees.
- **Rendering is slow by construction.** `GrosseImage` performs a seek, a write
  and a flush per pixel, so a single 3000×3000 render takes minutes. For the
  comparison, both trees were built against a drop-in replacement that keeps the
  pixel array in RAM and writes the file once, through the same header writer
  and in the same byte order. It was validated against the real implementation
  first: on `SierpinskiTriangle` both produce the identical file
  `6a8d01effd64ef923451eeaf1f18a7c6`. `CercleDeFord` was additionally checked
  against the real implementation end to end, because it is the one program
  that writes outside the image bounds (see below).

## Floating point

The programs must be compiled with IEEE-correct double arithmetic, which is why
the Makefile passes `-msse2 -mfpmath=sse`.

`Segment::dessine` and `Cercle::dessine` rasterise by comparing accumulated
`double` values. On 32-bit x86 the default x87 unit keeps intermediates in
80-bit registers, so those comparisons can see more precision than a `double`
carries, and which pixels get lit depends on how the compiler happened to
allocate registers. The original sources show this directly: built at `-O0`
they draw one image, built at `-O2` with x87 they draw a slightly different one
— about 2000 pixels out of 18 500 on the Alga L-system.

The original makefiles passed no `-O` flag, so the images committed to the
original repository are the `-O0` ones. Forcing SSE arithmetic reproduces those
exactly at any optimisation level, and makes the output stable:

| Flags | Original sources | Refactored sources |
|---|---|---|
| `-O0` | `55eac965…` | `55eac965…` |
| `-O2 -msse2 -mfpmath=sse` | `55eac965…` | `55eac965…` |
| `-O2 -ffloat-store` | `55eac965…` | `55eac965…` |
| `-O2` (x87, unstable) | `bb9629f8…` | `55eac965…` |

*(Alga L-system, `Images/LsystemAlgue.bmp`.)*

## Results

All seventeen outputs are **byte-identical** before and after the refactoring,
built with `-std=c++11 -O2 -msse2 -mfpmath=sse`.

The third column compares against the bitmaps that were committed to the
original repository, which is a stronger check: it shows the refactored code
still reproduces the images the project was actually reported with.

| Output | before = after | = image committed originally |
|---|:---:|:---:|
| `test.bmp` | yes | yes |
| `SierpinskiTriangle.bmp` | yes | yes |
| `SierpinskiTapis.bmp` | yes | yes |
| `FloconDeKoch.bmp` | yes | yes |
| `Mandelbrot.bmp` | yes | yes |
| `LsystemAlgue.bmp` | yes | yes |
| `LsystemArbreSimple.bmp` | yes | yes |
| `LsystemBrindille.bmp` | yes | yes |
| `LsystemDragon.bmp` | yes | yes |
| `LsystemFleche.bmp` | yes | yes |
| `LsystemHerbe.bmp` | yes | yes |
| `LsystemLiane.bmp` | yes | yes |
| `LsystemRameau.bmp` | yes | yes |
| `LsystemSavane.bmp` | yes | yes |
| `LsystemTriangle.bmp` | yes | yes |
| `CercleDeFord.bmp` | yes | no — see below |
| `CercleApolloniusAleatoire.bmp` | yes, at a fixed seed | not applicable — random |

The box-counting measurement was also re-run end to end on the Koch snowflake
(`enregistrementData()` in `Fractales/FloconDeKoch.cpp`). It produces data files
identical to the originals, and identical to the ones committed in the
repository — so the reported dimension of **1.2608** is reproducible from this
code.

## Not verified

These are stated so they are not mistaken for checked results.

1. **`Images/CercleApollonius.bmp`** — the non-random gasket. No default code
   path produces it; it needs a commented-out block in
   `Fractales/CercleApollonius.cpp` to be switched back on. Not regenerated, so
   not compared. The `assets/` copy is the originally committed image.

2. **`Images/FloconDeKochEdge.bmp`** — nothing in the sources writes this
   filename, in either version. Its provenance is unknown; the `assets/` copy is
   the originally committed image.

3. **`CercleDeFord.bmp` against the originally committed image.** Before and
   after agree, so the refactoring is clean, but both differ from the committed
   file by 65 pixels out of a million. Re-running the *original, unmodified*
   sources reproduces that same 65-pixel difference, so the committed image
   predates the current `CercleDeFord.cpp`. This is pre-existing, not a
   regression.

   Separately, this program writes 32 pixels outside the image bounds.
   `GrosseImage::set` does not range-check, so those writes land at whatever
   offset the arithmetic produces. It is the only program that does this.

4. **`Images/Julia.bmp`.** The original sources could only produce it by editing
   two lines, so there is no "before" behaviour to preserve; running it is a new
   capability (`./Mandelbrot_Julia.exe julia`). What it produces differs from the
   committed image by 5 pixels out of 400 000, at the escape-radius boundary —
   visually identical, but not bit-identical.

5. **`enregistrementData()` in `Lsystem/Test/TestLsystemRameau.cpp`.** Not
   re-run: it renders the L-system six times on a 4001×4001 canvas, which takes
   hours. It uses the same shared helpers as the Koch version, which *was*
   verified, but it has not itself been executed.

6. **`Lsystem/Test/regressionLineaire.R`.** This script was rewritten rather
   than preserved: the original pointed at absolute paths on one machine, read
   filenames that do not exist in the repository, and called `LINREG`/`regplot`,
   which are not part of base R — it could not run as it stood. The replacement
   uses `lm()` and relative paths. R was not available on the machine used here,
   so **the script has not been executed**. The regression it performs was
   checked independently and gives 1.2608 (R² = 0.985) for the Koch snowflake
   and 1.1575 (R² = 0.997) for the Branchlet, matching the reported figures.

7. **Other toolchains.** Everything was built and run with MinGW g++ 6.3.0
   (32-bit) on Windows 11. The sources are platform-neutral and should build
   elsewhere, but no other compiler, standard library or architecture was tried.

## Known defects left in place

Found while refactoring, and deliberately *not* changed, because fixing them
would alter the output:

- `Triangle::dessine` bounds its column loop with `getNombreLignes()` instead of
  `getNombreColonnes()`. Harmless here only because every image it draws on is
  square.
- `GrosseImage::set` performs no bounds check, as described above.
- The first box-counting sample is taken at scale 0, so the recorded `log(s)` is
  `-inf`. The R script reads it back as `log(1) = 0`, which is what the original
  analysis did.

Defects that were removed, because they were unreachable and so could not change
any output:

- `Complexe::operator+(double)` and `operator-(double)` shadowed the member `a`
  with the parameter, making `operator-` always return `0` for the real part.
  Neither was ever called.
- `Cercle(Point, double)` passed its own uninitialised `color` member to the
  base constructor, and left `plein` uninitialised. Never called.
- `Regles()` left `suivant` uninitialised while `aUnsuivant()` compared it
  against `NULL`. Never reached through that constructor.
- Two leaks in `Cercle::apolloniusNouveauxCercles`: one array allocated and
  never used, one allocated and immediately overwritten.
