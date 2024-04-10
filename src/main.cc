#include "../inc/common.h"
using namespace std;

// Entry
//  Optional Param 1: Directory to check (defaults to working directory)
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
        cout << "The given target directory cannot be found." << endl;
        return -1;
    }

    // Check if this path is a directory
    switch (sb.st_mode & S_IFMT) { // S_IFMT bit Looks specifically into the file type
        case S_IFDIR: // Directory bit
            {
                // Start a string stream, write contents of information into it, then
                //  print out the string stream.
                stringstream ss;
                WriteDirContents(targetDir, &ss);
                cout << ss.str();
                break;
            }
        default: // Anything
            // Just print out the path of whatever is there (this is what ls does)
            cout << targetDir << endl;
            break;
    }

    return 0;
}
