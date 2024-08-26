#include <iostream> //add all libr
#include <filesystem>
#include <vector>
#include <fstream>
#include <string>

// make func to show all directory contents

void veiw_Directory(const std::filesystem::path& path) {
    std::cout << "Contents of " << path << ":\n";
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        std::cout << (entry.is_directory() ? "[DIR]" : "    ")
                << entry.path().filename().string() << '\n';
    }
}
// make func to create file 

void create_File(const std::filesystem::path& path) {
    std::ofstream file(path);
    if (file.is_open()) {
        std::cout << "File created successfully: " << path.filename().string() << '\n';
    } else {
        std::cout << "Failed to create file:" << path.filename().string() << '\n';
    }
    file.close();
}

int main() 
{
    std::filesystem::path current_path = std::filesystem::current_path();

    while (true) 
    {
        veiw_Directory(current_path);

        std::cout << "\nEnter a directory to navigate into (or '<<' to go up, 'exit' to quit, 'mkdir' to make a new directory): ";
        std::string user_Input;
        std::cin >> user_Input;

        if (user_Input == "exit") {
            break;
        } else if (user_Input == "mkdir"){
            std::cout << "Enter a directory name: ";
            std::string dir_name;
            std::cin >> dir_name;
            create_File(current_path / dir_name);
        } else if (user_Input == "<<") {
            current_path = current_path.parent_path();
        } else {
            std::filesystem::path new_path = current_path / user_Input;
            if (std::filesystem::exists(new_path) && std::filesystem::is_directory(new_path)) {
                current_path = new_path;
            } else {
                std::cout << "Invalid directory.\n";
            }
        }
    }

    return 0;
}