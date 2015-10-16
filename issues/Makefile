
CXX = g++-4.9
CXXFLAGS = -std=c++11 -DNDEBUG -O2


all: programs

src/lists.o: src/lists.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

src/date.o: src/date.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

src/section_data.o: src/section_data.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

src/toc_diff.o: src/toc_diff.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

bin/make_lists: src/lists.o src/date.o
	${CXX} ${CXXFLAGS} -o $@ src/lists.o src/date.o

bin/make_section_data: src/section_data.o
	${CXX} ${CXXFLAGS} -o $@ $?

bin/make_toc_diff: src/toc_diff.o
	${CXX} ${CXXFLAGS} -o $@ $?


programs: bin/make_lists bin/make_section_data bin/make_toc_diff


lists: programs
	./bin/make_lists


clean:
	rm -f src/*.o
	rm -f bin/make_lists
	rm -f bin/make_section_data
	rm -f bin/make_toc_diff
