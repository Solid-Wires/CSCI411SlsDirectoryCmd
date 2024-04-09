#include "../inc/common.h"
using namespace std;

// Entry
//  Param 1: Directory to check
//      If not provided, check the working directory
int main(int argc, char *argv[]) {
    // Directory to check (defaults to working directory)
    string listDir = get_current_dir_name(); // from unistd.h
    if (argc > 1) {
        listDir = argv[1];
    }

    cout << listDir << endl;
    return 0;
}
