#include "Document.hpp"

bool checkExtensions(const std::string &filename, const std::vector<std::string> &extensions) {
    // Vérifier que l'extension du fichier est bien une des extensions autorisées
    std::string extension = filename.substr(filename.find_last_of(".") + 1);
    for (const std::string &ext : extensions) {
        if (ext != extension) {
            return false;
        }
    }
    return true;
}

void removeEmptyLines(std::string &content)
{
    // Supprimer les lignes vides
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