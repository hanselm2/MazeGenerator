TEST_SQUARE_MAZE_EXE = testsquaremaze
TEST_SQUARE_MAZE_OBJS = main.o maze.o dsets.o rgbapixel.o png.o

CXX = g++
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
CXX_OPTS = -c -g -O0 -Wfatal-errors -Werror $(WARNINGS)

.PHONY: all clean

all: $(TEST_DSETS_EXE) $(TEST_SQUARE_MAZE_EXE)

clean:
	-rm *.o $(TEST_DSETS_EXE) $(TEST_SQUARE_MAZE_EXE) 2>/dev/null

tidy:
	-rm -rf doc

$(TEST_DSETS_EXE): $(TEST_DSETS_OBJS)
	$(CXX) -o $@ $^

$(TEST_SQUARE_MAZE_EXE): $(TEST_SQUARE_MAZE_OBJS)
	$(CXX) $^ -lpng -o $@

main.o: main.cpp dsets.o maze.o png.o
	$(CXX) $(CXX_OPTS) $<

dsets.o: dsets.cpp dsets.h
	$(CXX) $(CXX_OPTS) $<

maze.o: maze.cpp maze.h dsets.o
	$(CXX) $(CXX_OPTS) $<

png.o: png.cpp png.h
	$(CXX) $(CXX_OPTS) $<

rgbapixel.o: rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXX_OPTS) $<
