#include "../inc/common.h"
using namespace std;

// Entry
//  Param 1: Directory to check (defaults to working directory)
int main(int argc, char *argv[]) {

    // Stat (path stats)
    struct stat sb;

    // Directory to check
    const char* targetDir;

    // Check first arg
    if (argc > 1) {
        // (optional) Manually provide the target directory from param
        targetDir = argv[1];
        cout << "Provided target dir: " << targetDir << endl;
    }
    else {
        // Use the current working directory if param not provided
        targetDir = get_current_dir_name(); // from unistd.h
        cout << "Current working dir: " << targetDir << endl;
    }
    // Check if this path exists (and retrieve path stats)
    if (stat(targetDir, &sb) == -1) {
        cout << "The given target directory does not exist." << endl;
        return -1;
    }

    // Check if this path is a directory
    // TODO: What to do if it's a linked file?
    switch (sb.st_mode & S_IFMT) {
        case S_IFDIR: // Directory
            // Do directory stuff
            cout << "This is a directory" << endl;
            break;
        case S_IFREG: // Regular File
            // Just print out the file
            cout << "This is a file" << endl;
            break;
        default:
            // Anything else is unsupported
            cout << "Unsupported" << endl;
            break;
    }

    return 0;
}
