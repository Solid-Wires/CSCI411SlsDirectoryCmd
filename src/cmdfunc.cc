#include "../inc/common.h"
using namespace std;

// Main function of the command that writes the contents of everything in a directory into a string stream.
//  Parameters:
//      path - The path of the directory to list contents.
//  Returns:
//      ss - the string stream reference to write the output into.
void WriteDirContents(const char* path, stringstream *ss) {

    // Custom struct describing information about each listed file
    struct finfo {
        const char* f_isdir;
        const char* f_perms;
        const char* f_name;
        int f_size;
        const char* last_modified;
    };

    // Open the directory with dirent.h
    struct dirent *dp; // Information we retrieve from readdir
    DIR *dir = opendir(path); // The provided dir
    while (dp = readdir(dir)) { // Read each file in this given dir
        // Retrieve what is needed to be described
        finfo i;
        switch(dp->d_type) {
            case DT_DIR:
                // If this is a directory, tag this as a DIR
                i.f_isdir = "DIR";
                break;
            default:
                i.f_isdir = "";
        }
        i.f_name = dp->d_name;
        *ss << i.f_isdir << '\t' << i.f_name << '\t' << endl;
    }
    // Done listing the dir
    closedir(dir);
}
