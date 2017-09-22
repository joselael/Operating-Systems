#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    char *sourceFile = argv[1];
    char *destinationFile = argv[2];
    int sourceID, destinationID, sourceSize;


    //printf("%s is %s\n", "Source file", sourceFile);
    //printf("%s is %s\n", "Destination file", destinationFile);

    // try to open the file
    sourceID = open(sourceFile, O_RDONLY);
    if (sourceID < 0) {
        printf("open() failed with error [%s]\n", strerror(errno));
        perror("open");
        return 1;
    }

    // get the size in bytes of the source file
    struct stat st;
    stat(sourceFile, &st);
    sourceSize = st.st_size;
    char data[sourceSize];

    // printf("Source file is %d bytes\n", sourceSize);

    // try to create the copy file
    destinationID = open(destinationFile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (destinationID < 0) {
        printf("open() failed with error [%s]\n", strerror(errno));
        return 1;
    }

    char xyz[] = "XYZ";
    // try to read all the contents of the source file
    bool eof = false;
    unsigned bytesRead = 0;
    while (!eof) {
        if (read(sourceID, data, 100) != 100) {
            printf("Could not copy file. Error [%s]\n", strerror(errno));
            return 1;
        }


        // change all 1s to As
        for (unsigned i = 0; i < 100; i++)
            if (data[i] == '1')
                data[i] = 'A';

        bytesRead += 100;

        // write the data into the destination file
        if (write(destinationID, data, 100) != 100) {
            printf("Could not write to file. Error [%s]\n", strerror(errno));
            return 1;
        }


        if (write(destinationID, xyz, 3) != 3) {
            printf("Could not write to file. Error [%s]\n", strerror(errno));
            return 1;
        }

        if (bytesRead >= sourceSize)
            eof = true;
    }
    close(sourceID);
    close(destinationID);

    return EXIT_SUCCESS;
}
