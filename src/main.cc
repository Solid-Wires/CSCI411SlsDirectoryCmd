#include "../inc/common.h"
using namespace std;

// Entry
//  Param 1: Directory to check (defaults to working directory)
int main(int argc, char *argv[]) {
    // Directory to check
    string targetDir = get_current_dir_name(); // from unistd.h
    if (argc > 1) {
        // Manually provide the target directory from param
        targetDir = argv[1];
    }

    cout << targetDir << endl;
    return 0;
}
