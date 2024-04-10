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
        char* f_type;
        char* f_perms;
        char* f_name;
        int f_size;
        char* last_modified;
    };

    // Open the directory with dirent.h
    struct dirent *dp; // Information we retrieve from readdir
    DIR *dir = opendir(path); // The provided dir
    while (dp = readdir(dir)) { // Read each file in this given dir
        // Retrieve what is needed to be described
        finfo i;
        i.f_type = dp->d_type;
        i.f_name = dp->d_name;
        *ss << i.f_type << '\t' << i.f_name << '\t' << endl;
    }
    // Done listing the dir
    closedir(dir);
}
