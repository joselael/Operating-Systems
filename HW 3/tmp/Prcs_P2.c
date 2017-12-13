#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char *sourceFile = argv[1];
    char *destination1File = argv[2], *destination2File = argv[3];
    int sourceID, destination1ID, destination2ID, sourceSize;


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
    //char data2[sourceSize];
    // printf("Source file is %d bytes\n", sourceSize);

    // try to create the copy file
    destination1ID = open(destination1File, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (destination1ID < 0) {
        printf("open() failed with error [%s]\n", strerror(errno));
        return 1;
    }

    destination2ID = open(destination2File, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (destination2ID < 0) {
        printf("open() failed with error [%s]\n", strerror(errno));
        return 1;
    }

    // char xyz[] = "XYZ";
    // try to read all the contents of the source file
    bool eof = false;
    unsigned bytesRead = 0;
    while (!eof) {

        /* Changing 1s to As in 100 characters read */
        {
            if (read(sourceID, data, 100) != 100) {
                if(bytesRead < sourceSize - 100) {
                    printf("(A) Could not copy file. Error [%s]\n", strerror(errno));
                    return 1;
                }
            }

            // change all 1s to As
            for (unsigned loopIndex = 0, dataIndex = 0; loopIndex < 100; loopIndex++, dataIndex++)
                if (data[dataIndex] == '1')
                    data[dataIndex] = 'A';
            bytesRead += 100;
            // write the data into the destination file

            if (write(destination1ID, data, 100) != 100) {
                if(bytesRead < sourceSize) {
                    printf("Could not write to destination1. Error [%s]\n", strerror(errno));
                    return 1;
                }
            }
        }

        /* Chaning 2s to Bs in 50 characters read */
        {
            if (read(sourceID, data, 50) != 50) {
                if(bytesRead < sourceSize - 50) {
                    printf("(B) Could not copy file. Error [%s]\n", strerror(errno));
                    return 1;
                }
            }

            // change all 2s to Bs
            for (unsigned loopIndex = 0, dataIndex = 0; loopIndex < 50; loopIndex++, dataIndex++)
                if (data[dataIndex] == '2')
                    data[dataIndex] = 'B';
            bytesRead += 50;


            if (write(destination2ID, data, 50) != 50) {
                if (bytesRead < sourceSize) {
                    printf("Could not write to destination2. Error [%s]\n", strerror(errno));
                    return 1;
                }
            }
        }


        if (bytesRead >= sourceSize)
            eof = true;

       //printf("Bytes read: %u\n", bytesRead);
    }
    close(sourceID);
    close(destination1ID);
    close(destination2ID);

    return EXIT_SUCCESS;
}
