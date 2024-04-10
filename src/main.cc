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
        cout << "Provided target path: " << targetDir << endl;
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
    switch (sb.st_mode & S_IFMT) {
        case S_IFDIR: // Directory
            stringstream ss('');
            cout << "This is a directory" << endl;
            break;
        default: // Anything
            // Just print out the path of whatever is there (this is what ls does)
            cout << targetDir << endl;
            break;
    }

    return 0;
}
