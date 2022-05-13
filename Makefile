target := c++17

external_header_dirs := -I ./dependencies/FTXUI-master/include/ -I dependencies/SDL2/include/
additional_search_dirs := -L ./dependencies/FTXUI-master/build/ -L dependencies/SDL2/lib/
external_libs := -l mingw32 -lgdi32 -l ftxui-component -l ftxui-dom -l ftxui-screen -l SDL2main -l SDL2
src_code := src/main.cpp

build: 
	i686-w64-mingw32-g++ -std=${target} -municode ${external_header_dirs} ${additional_search_dirs} -o main ${src_code} ${external_libs}
