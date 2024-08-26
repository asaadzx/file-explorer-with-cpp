## C++ File Explorer
This is a simple C++ console-based file explorer that allows you to navigate directories, view their contents, and create new directories within the current directory.

Features
View Directory Contents: List all files and subdirectories in the current directory.
Navigate Directories: Move into subdirectories or go up to parent directories.
Create New Directories: Easily create new directories within the current path.
Libraries Used
The project utilizes the following C++ standard libraries:

<iostream>: Handles input and output operations.
<filesystem>: Provides access to file system operations such as navigating directories and checking file types. Requires C++17 or later.
<vector>: Used for managing lists of directory entries (although not directly utilized in this example, it's included for potential future enhancements).
<fstream>: Handles file creation and manipulation.
<string>: Manages text strings, particularly for user input and file or directory names.
Code Overview
1. View Directory Contents
cpp
Copy code
void view_Directory(const std::filesystem::path& path) {
    std::cout << "Contents of " << path << ":\n";
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        std::cout << (entry.is_directory() ? "[DIR]" : "    ")
                << entry.path().filename().string() << '\n';
    }
}
This function lists all files and directories in the specified path. Directories are marked with [DIR].

2. Create a New Directory
cpp
Copy code
void create_File(const std::filesystem::path& path) {
    std::ofstream file(path);
    if (file.is_open()) {
        std::cout << "File created successfully: " << path.filename().string() << '\n';
    } else {
        std::cout << "Failed to create file:" << path.filename().string() << '\n';
    }
    file.close();
}
This function creates a new directory within the specified path.

3. Main Program Loop
cpp
Copy code
int main() 
{
    std::filesystem::path current_path = std::filesystem::current_path();

    while (true) 
    {
        view_Directory(current_path);

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
This loop:

Displays the contents of the current directory.
Accepts user input to navigate, create directories, or exit the program.
How to Compile and Run
Ensure you have a C++17 compatible compiler. For example, with g++, you can check the version:

bash
Copy code
g++ --version
Compile the Program:

bash
Copy code
g++ -std=c++17 -o file_explorer file_explorer.cpp
Run the Program:

bash
Copy code
./file_explorer
Future Enhancements
File Creation: Add functionality to create files, not just directories.
File Deletion: Enable users to delete files and directories.
File Viewing: Implement a feature to read and display file contents.
