#include "../inc/common.h"
using namespace std;

// Entry
//  Param 1: Directory to check (defaults to working directory)
int main(int argc, char *argv[]) {
    // Directory to check
    string targetDir = get_current_dir_name(); // from unistd.h
    if (argc > 1) {
        // (optional) Manually provide the target directory from param
        targetDir = argv[1];

        // Check if this is a directory
        if (!filesystem.exists(targetDir)) {
            cout << "The given target directory does not exist." << endl;
            return -1;
        }
        cout << "Provided target dir: " << targetDir << endl;
    }
    else {
        // Print the current working directory if param not provided
        cout << "Current working dir: " << targetDir << endl;
    }

    return 0;
}
