#include "../inc/common.h"
using namespace std;

// Function prototypes here
const char* TagDirectory(unsigned char d_type);

// Main function of the command that writes the contents of everything in a directory into a string stream.
//  Parameters:
//      path - The path of the directory to list contents.
//  Returns:
//      ss - the string stream reference to write the output into.
void WriteDirContents(const char* path, stringstream *ss) {

    // Custom struct describing information about each listed file
    struct finfo {
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
        i.f_name = dp->d_name;
        *ss << TagDirectory(dp->d_type) << '\t' << i.f_name << '\t' << endl;
    }
    // Done listing the dir
    closedir(dir);
}

// If the given type is a directory according to dirent.h, return the DIR tag
//  Otherwise, return an empty string
const char* TagDirectory(unsigned char d_type) {
    switch(dp->d_type) {
        case DT_DIR:
            return "DIR";
    }
    return "";
}
