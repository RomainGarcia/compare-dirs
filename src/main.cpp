#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>
#include "md5/md5.h"

std::string getMD5Hash(const std::string& filePath, MD5& md5)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open file '" << filePath << "'" << std::endl;
        return "FILE ERROR";
    }

    std::stringstream ss;
    ss << file.rdbuf();

    md5(ss.str());

    return md5.getHash();
}

std::unordered_map<std::string, std::string> browse(const std::string& directory)
{
    MD5 md5;
    std::unordered_map<std::string, std::string> files(1000);

    if (!std::filesystem::exists(directory))
    {
        std::cerr << "Error: Directory '" << directory << "' does not exist" << std::endl;
        return files;
    }

    for (const auto & entry : std::filesystem::recursive_directory_iterator(directory.c_str())) {
        if (!entry.is_directory()) {
            std::string cleanPath = entry.path().string();
            cleanPath.erase(0, directory.length());
            files.emplace(cleanPath, getMD5Hash(entry.path().string(), md5));
        }
    }

    return files;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <path_original_directory> <path_directory_to_check_for> [-a]" << std::endl;
        std::cout << "" << std::endl;
        std::cout << " - path_original_directory: original path <> [-a]" << std::endl;
        std::cout << " - path_directory_to_check_for: path to check if there is differences with the previous path" << std::endl;
        std::cout << " - -a: (optional) if present display all of the results instead of only the differences" << std::endl;
        return 1;
    }

    std::string pathOriginal = argv[1];
    std::string pathEdited = argv[2];
    bool displayAll = argc == 4;

    std::unordered_map<std::string, std::string> filesOriginal = browse(pathOriginal);
    std::unordered_map<std::string, std::string> filesEdited = browse(pathEdited);

    std::vector<std::string> resultEdited;
    resultEdited.reserve(100);
    std::vector<std::string> resultNotFound;
    resultNotFound.reserve(100);
    std::vector<std::string> resultOther;
    resultOther.reserve(displayAll ? filesEdited.size() : 0);

    for (const auto& [fileName, hash] : filesEdited) {
        if (filesOriginal.contains(fileName) && hash != filesOriginal[fileName]) {
            resultEdited.emplace_back(fileName);
        } else if (!filesOriginal.contains(fileName)) {
            resultNotFound.emplace_back(fileName);
        } else if (displayAll) {
            resultOther.emplace_back(fileName);
        }
    }

    for (const auto& fileName : resultOther) {
        std::cout << "File not modified: " << fileName << '\n';
    }

    for (const auto& fileName : resultNotFound) {
        std::cout << "File not present in original directory: " << fileName << '\n';
    }

    for (const auto& fileName : resultEdited) {
        std::cout << "File modified: " << fileName << '\n';
    }

    if (resultNotFound.empty() && resultEdited.empty()) {
        std::cout << "No differences found" << '\n';
    }

    std::cout << '\n';

    std::cout << "Files in original directory: " << filesOriginal.size() << std::endl;
    std::cout << "Files in edited directory: " << filesEdited.size() << std::endl;
    std::cout << "Edited files found: " << resultEdited.size() << std::endl;
    std::cout << "Files not found: " << resultNotFound.size() << std::endl;

    return 0;
}