#include "../inc/common.h"
using namespace std;

// Function prototypes here
const char* TagDirectory(unsigned char d_type);
string DisplayPerms(mode_t st_mode);

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

        // I tried my best to format it, still ended up looking weird in the terminal on Seed's low res screen.\
        //  But this appears to be functionally complete, so I'll just leave this the way it is to not break anything.
        *ss << left << setfill(' ');
        *ss << setw(6) << TagDirectory(dp->d_type);
        *ss << setw(12) << DisplayPerms(sb.st_mode);
        *ss << setw(16) << dp->d_name;
        *ss << setw(6) << sb.st_size;
        *ss << setw(24) << ctime(&sb.st_mtime);
        *ss << endl;
    }
    // Done listing the dir
    closedir(dir);
    // Then the string stream should contain the output stream that was performed while reading the directory.
}

// If the given type is a directory according to dirent.h, return the DIR tag
//  Otherwise, return an empty string.
//  Param 1: d_type, type of the file, as an unsigned char from dirent
const char* TagDirectory(unsigned char d_type) {
    switch(d_type) {
        case DT_DIR:
            return "DIR";
    }
    return "";
}

// Display all permissions that the user/owner, group, and others have with this file, in that order.
// Note that most of these permission bits are only available in Linux's OS. Windows seems to only know user perm bits.
//  Param 1: st_mode, the various state bits of the file from stat that describes the file type and permission information
string DisplayPerms(mode_t st_mode) {
    // The output string is 9 characters long.
    //  Any bits that are not present are left as dashes.
    char permFlags[10] = "---------"; 
    
    // Check permissions for user/owner
    if (st_mode & S_IRUSR) { // User read perm bit
        permFlags[0] = 'r';
    }
    if (st_mode & S_IWUSR) { // User write perm bit
        permFlags[1] = 'w';
    }
    if (st_mode & S_IXUSR) { // User exec/search perm bit
        permFlags[2] = 'x';
    }

    // Check permissions for group
    if (st_mode & S_IRGRP) { // Group read perm bit
        permFlags[3] = 'r';
    }
    if (st_mode & S_IWGRP) { // Group write perm bit
        permFlags[4] = 'w';
    }
    if (st_mode & S_IXGRP) { // Group exec/search perm bit
        permFlags[5] = 'x';
    }

    // Check permissions for others
    if (st_mode & S_IROTH) { // Others read perm bit
        permFlags[6] = 'r';
    }
    if (st_mode & S_IWOTH) { // Others write perm bit
        permFlags[7] = 'w';
    }
    if (st_mode & S_IXOTH) { // Others exec/search perm bit
        permFlags[8] = 'x';
    }
    
    return (string)permFlags;
}
