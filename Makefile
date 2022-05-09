external_header_dirs := -I ./dependencies/FTXUI-master/include/
additional_search_dirs := -L ./dependencies/FTXUI-master/build/
external_libs := -l mingw32 -l ftxui-component -l ftxui-dom -l ftxui-screen
src_code := src/main.cpp

build: 
	g++ -municode ${external_header_dirs} ${additional_search_dirs} -o main ${src_code} ${external_libs}