#include <iostream>
#include <fstream>

void print_usage(const char* app_name){
    std::cerr << std::string{app_name} << " <filename of grc output>\n";
    return;
}

int main(const int argc, const char* argv[]){
    
    if(argc != 2){
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    const auto fname = std::string{argv[1]};
    std::cout << "Using file " << fname << "\n";

    auto dfile = std::ifstream(fname, std::ios_base::in | std::ios_base::binary);
    if(!dfile){
        std::cerr << "Unable to open file " << fname << "\n";
        return EXIT_FAILURE;
    }

    char c;
    while(dfile.read(&c,1)){
        const auto unpacked_data = static_cast<uint8_t>(c);
        const auto meta_mask = ~0x01;
        const auto meta_data = meta_mask & unpacked_data;
        if(0 != meta_data){
            std::cout << "Tag found\n";
        }
    }
    std::cout << "Done reading file\n";
    return EXIT_SUCCESS;
}
