#include "Document.hpp"

bool checkExtensions(const std::string& filename, const std::vector<std::string>& extensions) {
    std::string extension = filename.substr(filename.find_last_of(".") + 1);
    for (const std::string& ext : extensions) {
        if (ext == extension) {
            return true;
        }
    }
    return false;
}

void removeEmptyLines(std::string& content) {
    std::istringstream contentStream(content);
    std::ostringstream resultStream;
    std::string line;
    
    while (std::getline(contentStream, line)) {
        if (!line.empty()) {
            resultStream << line << "\n";
        }
    }
    
    content = resultStream.str();
}
