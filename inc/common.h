#pragma once

// Includes
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sstream>
#include <types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

// Function prototypes
void WriteDirContents(const char* path, std::stringstream *ss);
