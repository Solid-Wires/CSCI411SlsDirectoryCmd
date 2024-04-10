#include "../inc/common.h"
using namespace std;

// Function prototypes here
const char* TagDirectory(unsigned char d_type);
string DisplayPerms(struct stat *sb);

// Main function of the command that writes the contents of everything in a directory into a string stream.
//  Parameters:
//      path - The path of the directory to list contents.
//  Returns:
//      ss - the string stream reference to write the output into.
void WriteDirContents(const char* path, stringstream *ss) {

    // Open the directory with dirent.h
    struct dirent *dp; // Information we retrieve from readdir
    DIR *dir = opendir(path); // The provided dir
    while (dp = readdir(dir)) { // Read each file in this given dir
        // Retrieve what is needed to be described
        //  And write it into the stream
        string targetPath((string)path + '/' + dp->d_name); // Stat requires a path to the file. Luckily, we already kind of know it here
        struct stat sb;
        stat(targetPath.c_str(), &sb); // Could use lstat, but the example seems to just use stat
        *ss << TagDirectory(dp->d_type) << '\t' << DisplayPerms(&sb) << '\t' << dp->d_name << '\t' << sb.st_size << '\t' << ctime(&sb.st_mtime) << endl;
    }
    // Done listing the dir
    closedir(dir);
}

// If the given type is a directory according to dirent.h, return the DIR tag
//  Otherwise, return an empty string
const char* TagDirectory(unsigned char d_type) {
    switch(d_type) {
        case DT_DIR:
            return "DIR";
    }
    return "";
}

// Display all permissions that the user/owner, group, and others have with this file, in that order.
string DisplayPerms(struct stat *sb) {
    // The output string is 9 characters long.
    char permFlags[10] = "---------"; 
    
    // Check permissions for user/owner
    switch(sb->st_mode & S_IRWXU) {
        case S_IRUSR:
            permFlags[0] = 'r';
        case S_IWUSR:
            permFlags[1] = 'w';
        case S_IXUSR:
            permFlags[2] = 'x';
    }
    // Check permissions for group
    switch(sb->st_mode & S_IRWXG) {
        case S_IRGRP:
            permFlags[3] = 'r';
        case S_IWGRP:
            permFlags[4] = 'w';
        case S_IXGRP:
            permFlags[5] = 'x';
    }
    // Check permissions for others
    switch(sb->st_mode & S_IRWXO) {
        case S_IROTH:
            permFlags[6] = 'r';
        case S_IWOTH:
            permFlags[7] = 'w';
        case S_IXOTH:
            permFlags[8] = 'x';
    }
    return (string)permFlags;
}
