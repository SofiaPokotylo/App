all: App

App: cmake-build-debug/CMakeFiles/App.dir/main.cpp.obj cmake-build-debug/libsearch_library.a
	g++ -lm -o App cmake-build-debug/CMakeFiles/App.dir/main.cpp.obj -L. cmake-build-debug/libsearch_library.a
cmake-build-debug/CMakeFiles/App.dir/main.cpp.obj: main.cpp
	g++ -c main.cpp
cmake-build-debug/CMakeFiles/App.dir/search.cpp.obj: search.cpp search.h
	g++ -c search.cpp search.h

cmake-build-debug/libsearch_library.a: search.cpp search.h
	ar rcs cmake-build-debug/libsearch_library.a cmake-build-debug/CMakeFiles/App.dir/search.cpp.obj

libs: cmake-build-debug/libsearch_library.a

clean:
	rm -f cmake-build-debug/libsearch_library.a cmake-build-debug/CMakeFiles/App.dir/main.cpp.obj cmake-build-debug/CMakeFiles/App.dir/search.cpp.obj