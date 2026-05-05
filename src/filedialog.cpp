#include "filedialog.hpp"

// 1. Include PFD here (it will include windows.h internally)
#include "portable-file-dialogs.h"
#include <filesystem>

std::vector<std::string> AskForDirectoryFilename()
{
    auto selection = pfd::open_file("Select a file", ".",
                                    {"All Files", "*"})
                         .result();

    if (!selection.empty())
    {
        // 2. Convert the string path to a filesystem path object
        std::filesystem::path fullPath = selection[0];

        // 3. Extract the filename without the extension
        // Example: "C:/Users/Docs/data.txt" -> "data"
        std::string filename = fullPath.stem().string();

        // Optional: Extract the directory location
        std::string directory = fullPath.parent_path().string();
        return {directory, filename};
        // ig.setPath(directory, filename);
        // ig.generate();
    }

    return {};
}