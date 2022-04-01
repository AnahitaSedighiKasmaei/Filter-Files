
//*********************************************************
//
//      Written by: Anahita Sedighikasmaei
//
//*********************************************************

#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

char** extensions;
int extensionsLength = 0;

///******************************************************************************************************************
///  This method gets the  extension part of the file for filtering the files, base on the input extensions
///******************************************************************************************************************

const char *get_filename_ext(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}
///******************************************************************************************************************
/// This method prints the list of files in the output to show
/// The input extensions were saved in extensions and will be shown if they were found
///******************************************************************************************************************
static int show( const char *fpath, const struct stat *sb,
                 int tflag, struct FTW *ftwbuf)
{

    for(int i = 0; i < extensionsLength; i++)
    {
        if (strcmp(get_filename_ext(fpath), extensions[i])==0)
        {
            printf("%-3s %2d %7jd   %-40s %d %s\n",
                   (tflag == FTW_D) ?   "d"   : (tflag == FTW_DNR) ? "dnr" :
                   (tflag == FTW_DP) ?  "dp"  : (tflag == FTW_F) ?   "f" :
                   (tflag == FTW_NS) ?  "ns"  : (tflag == FTW_SL) ?  "sl" :
                   (tflag == FTW_SLN) ? "sln" : "???",
                   ftwbuf->level, (intmax_t) sb->st_size,
                   fpath, ftwbuf->base, fpath + ftwbuf->base);
        }

    }
    return 0;

}

///******************************************************************************************************************
/// we should check the input arguments
/// we can get 3 types of args
/// 1- Extensions: they located in arg[1] (Mandatory)
/// 2- Delimiter: "-t" is located in arg[2] (Optional)
/// 3- Path: the path is located in arg[3] (Optional)
/// when delimiter(-t) is detected then the other args would be path address

///******************************************************************************************************************
int main( int argc, char *argv[] )
{
// Thw default path if the path is not entered would be "."
    char *path= ".";

    if (argc == 1)
    {
        printf("\nPlease enter file extensions as arguments.\n\n");
        return 0;
    }
// memory allocation is setting here base on extensions
    extensions = malloc(1 * sizeof(*extensions));

    bool isPathArg = false;
    for (int i = 1; i < argc; i++)
    {

        if (strcmp(argv[i], "-t")==0)
        {
            isPathArg = true;
            continue;
        }
        if (isPathArg)
        {
            // the input path would set here if "-t" char was entered
            path = argv[i];
            isPathArg = false;
        }
        else
        {
            extensionsLength++;
            // here we extending the array size based on input arguments with realloc function
            if (extensionsLength > 1) {
                extensions = realloc(extensions, extensionsLength * sizeof(*extensions));
            }
            extensions[extensionsLength-1] = argv[i];
        }
    }
    printf("\nFinding files in: %s\n=========================================\n", path);
    nftw(path, show, 20, 0); //FTW_F | FTW_DEPTH | FTW_PHYS | FTW_CHDIR

    return 0;
}
