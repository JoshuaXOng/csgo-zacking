external_header_dirs :=
additional_search_dirs :=
external_libs := -l mingw32
src_code := src/main.cpp

build: 
	g++ -municode ${external_header_dirs} ${additional_search_dirs} -o main ${src_code} ${external_libs}