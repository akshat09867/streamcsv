#include "streamcsv/mapped_file.hpp"

#include <algorithm>
#include <exception>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    if(argc<2){
        cerr<<"Usage: streamcsv <file_path>\n";
        return 1;
    }
    try{
        streamcsv::Mappedfile file(argv[1]);
        string_view content= file.view();
        const auto newlines = count(content.begin(), content.end(), '\n');
        std::cout << "Mapped " << file.size() << " bytes | Lines: " << newlines << '\n';
    }
    catch (const std::exception& ex) {
            std::cerr << "Error: " << ex.what() << '\n';
            return 1;
        }
        return 0;
}
