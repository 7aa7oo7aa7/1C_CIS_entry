#include <iostream>
#include <fstream>

int get_vertex_num() {
    std::cout << "Enter vertex number: ";
    size_t vertex_num = 0;
    std::cin >> vertex_num;
    return vertex_num;
}

std::vector<std::vector<int>> read_data() {
    std::fstream file;
    file.open("./png_data", std::ios::in);
    char pixel;
    std::vector<std::vector<int>> png_data;
    png_data.push_back(std::vector<int>());
    while (true) {
        file >> pixel;
        if (pixel == '\n') {
            png_data.push_back(std::vector<int>());
        } else if (pixel == '\0') {
            png_data.pop_back();
            break;
        } else if (pixel == '0' || pixel == '1') {
            png_data.back().push_back(pixel - '0');   
        }
    }
    file.close();
    return png_data;
}
