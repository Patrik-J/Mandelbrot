#include "filedialog.hpp"

#include "portable-file-dialogs.h"
#include <filesystem>

std::vector<std::string> AskForDirectoryFilename()
{
    auto selection = pfd::open_file("Select a file", ".",
                                    {"All Files", "*"})
                         .result();

    if (!selection.empty())
    {
        std::filesystem::path fullPath = selection[0];

        std::string filename = fullPath.stem().string();

        std::string directory = fullPath.parent_path().string();
        return {directory, filename};
    }

    return {};
}