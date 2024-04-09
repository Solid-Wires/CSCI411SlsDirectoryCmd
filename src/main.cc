#include "../inc/common.h"
using namespace std;

// Entry
//  Param 1: Directory to check (defaults to working directory)
int main(int argc, char *argv[]) {

    // Stat
    struct stat sb;

    // Directory to check
    const char* targetDir; // from unistd.h

    if (argc > 1) {
        // (optional) Manually provide the target directory from param
        targetDir = argv[1];

        // Check if this is a directory
        if (stat(targetDir, sb) == 0) {
            cout << "The given target directory does not exist." << endl;
            return -1;
        }
        cout << "Provided target dir: " << targetDir << endl;
    }
    else {
        // Use the current working directory if param not provided
        targetDir = get_current_dir_name();
        cout << "Current working dir: " << targetDir << endl;
    }

    return 0;
}
