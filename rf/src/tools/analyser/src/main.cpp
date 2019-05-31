#include <boost/algorithm/string/predicate.hpp>
#include <fstream>
#include <iostream>
#include <vector>

void print_usage(const char *app_name) {
    std::cerr << std::string{app_name} << " <filename of grc output>\n";
    return;
}

bool has_metadata(const char c){
    return 0 != (c & 0xfe);
}
bool is_start_of_data(const char c){
    return (c&0xfe) == 0x06;
}

void trim_string(std::string& building){
    if(30 == building.size()){
        building.erase(0,10);
    }
}

int main(const int argc, const char *argv[]) {

    if (argc != 2) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    const auto fname = std::string{argv[1]};
    std::cout << "Using file " << fname << "\n";

    auto dfile = std::ifstream(fname, std::ios_base::in | std::ios_base::binary);
    if (!dfile) {
        std::cerr << "Unable to open file " << fname << "\n";
        return EXIT_FAILURE;
    }

    char c{' '};
    auto aggregation = uint8_t{};
    auto data_collection = std::vector<uint8_t>{};
    auto count = 0;
    auto building = std::string{};

    enum class state { finding_preamble, in_data, finding_rx_freq, finding_data, found };
    auto current_state = state::finding_preamble;

    while (dfile.read(&c, 1)) {
        switch(current_state){
            case state::finding_preamble: {
                    const auto letter = std::isprint(c);
                    if(letter){ 
                        building += c;
                        trim_string(building);
                        if(boost::algorithm::ends_with(building, "preamble")){
                            count = 0;
                            aggregation = 0;
                            data_collection.clear();
                            current_state = state::finding_data;
                        }
                    }
                }
                break;
            case state::finding_data:{
                    if(is_start_of_data(c)){    
                        current_state = state::in_data;
                        aggregation = 0;
                        count = 0;
                    }                
                }
                break;
            case state::finding_rx_freq:{
                    const auto letter = std::isprint(c);
                    if(letter){ 
                        building += c;
                        trim_string(building);
                        if(boost::algorithm::ends_with(building, "rx_freq")){
                            count = 0;
                            aggregation = 0;
                            data_collection.clear();
                            current_state = state::finding_data;
                        }
                    }
                }
                break;
            case state::in_data:{
                    if(has_metadata(c)){
                        current_state = state::finding_rx_freq;
                    }else{
                        if(8 == count){
                            data_collection.push_back(aggregation);
                            constexpr auto packet_len = 26;
                            if(data_collection.size() == packet_len){
                                current_state = state::found;
                            }
                            aggregation = c;
                            count = 1;
                        }else{
                            aggregation <<= 1;
                            aggregation |= (0x01 & c);
                            ++count;
                        }
                    }
                }
                break;
           case state::found:{
                    std::cout << "Packet:\t";
                    for(const auto& c: data_collection){
                        if(std::isprint(c)){
                            std::cout << c;
                        } else {
                          std::cout << std::hex << std::showbase << static_cast<int>(c) << std::dec;
                        }
                        std::cout << " ";
                    }
                    std::cout << "\n";
                    current_state = state::finding_preamble;
                }
                break;
            default: break; 
        }
    }
    
    std::cout << "Done reading file\n";
    return EXIT_SUCCESS;
}
