# Builds every fractal program.
#
# The seventeen near-identical per-program makefiles this replaces all did the
# same thing, so the recipe is written once and the programs are listed as data.
#
# Run from this directory. Programs write their image into ../Images, which the
# `all` target creates.
#
#   make                    build everything
#   make FloconDeKoch.exe   build one program
#   make run-FloconDeKoch   build it and run it
#   make clean              remove objects and executables
#
# Override the compiler if g++ is not on PATH:
#   make CXX="C:/MinGW/bin/g++"

# Plain "=" rather than "?=": make predefines CC and CXX, so "?=" would never
# take effect. A command-line "make CXX=..." still overrides this.
CXX = g++
LINK = $(CXX)

# -msse2 -mfpmath=sse matters for reproducibility, not for speed. On 32-bit x86
# the default x87 unit keeps intermediate results in 80-bit registers, so a
# double expression can carry more precision than a double should. Segment and
# Cercle rasterise by comparing accumulated doubles, so which pixels they light
# up then depends on how the compiler happened to allocate registers, and the
# same source gives different images at -O0 and -O2. Forcing SSE arithmetic
# keeps every intermediate at true double precision, which makes the output
# identical across optimisation levels.
CXXFLAGS = -std=c++11 -O2 -msse2 -mfpmath=sse -I.

# --- programs -----------------------------------------------------------------

FRACTALES = Test SierpinskiTriangle SierpinskiTapis CercleDeFord CercleApollonius \
            Mandelbrot_Julia FloconDeKoch

LSYSTEMES = Algue ArbreSimple Brindille Dragon Fleche Herbe Liane Rameau Savane Triangle

LSYSTEME_EXES = $(addprefix TestLsystem,$(addsuffix .exe,$(LSYSTEMES)))
EXES = $(addsuffix .exe,$(FRACTALES)) $(LSYSTEME_EXES)

# --- shared objects -----------------------------------------------------------

COMMUN    = GrosseImage.o OutilsCreationImage.o
GEOMETRIE = $(COMMUN) Point.o
SYMBOLES  = Lsystem.o SymboleX.o SymboleY.o SymboleF.o SymboleCf.o SymboleCo.o \
            SymboleMoins.o SymbolePlus.o
NOYAU_LS  = $(COMMUN) $(SYMBOLES)

all: $(EXES)

../Images:
	mkdir -p ../Images

# --- compilation --------------------------------------------------------------

Point.o: ../Point.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

GrosseImage.o: ../GrosseImage.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

OutilsCreationImage.o: ../OutilsCreationImage.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Lsystem.o: ../Lsystem/Lsystem.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Symbole%.o: ../Lsystem/Symbole/Symbole%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Lsystem%.o: ../Lsystem/Lsystem%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

TestLsystem%.o: ../Lsystem/Test/TestLsystem%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: ../Fractales/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- linking ------------------------------------------------------------------

Mandelbrot_Julia.exe: Mandelbrot_Julia.o $(COMMUN) | ../Images
	$(LINK) $^ -o $@

Test.exe SierpinskiTriangle.exe SierpinskiTapis.exe CercleDeFord.exe CercleApollonius.exe FloconDeKoch.exe: %.exe: %.o $(GEOMETRIE) | ../Images
	$(LINK) $^ -o $@

$(LSYSTEME_EXES): TestLsystem%.exe: TestLsystem%.o Lsystem%.o $(NOYAU_LS) | ../Images
	$(LINK) $^ -o $@

# --- running ------------------------------------------------------------------

run-%: %.exe
	./$<

clean:
	rm -f *.o *.exe

.PHONY: all clean
.PRECIOUS: %.o
