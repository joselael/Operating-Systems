#include <stdlib.h>
#include <unistd.h>
//#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <assert.h>

void worker_process(unsigned numChapters, unsigned numHW, unsigned numStudents, int* grades[]) {
    unsigned score = 0;
    pid_t child = fork();

    if (!child) {
        for (unsigned i = 0; i < numStudents; ++i) {
            if (!numChapters)
                score += grades[i][numHW];
            else if (numChapters == 1)
                score += grades[i][numHW + numChapters + 1];
        }

        float average = ((float) score) / numStudents;
        printf("For chapter %d, HW %d, the average is: %f\n", numChapters + 1, numHW + 1, average);
        exit(child);
    }
    waitpid(child, NULL, 0);

}

void manager_process(unsigned numChapters, unsigned numHW, unsigned numStudents, unsigned *grades) {
    pid_t child = fork();

    if (!child) {
        for (unsigned i = 0; i < numHW; ++i)
            worker_process(numChapters, i, numStudents, grades);
        exit(manager_process);
    }
    waitpid(child, NULL, 0);
}

int main(int argc, char *argv[]) {
    int buffer;
    unsigned numHW, numStudents = 10, numChapters;

    FILE *source = fopen(argv[1], "r");
    if (!source) {
        perror("fopen()");
        return EXIT_FAILURE;
    }

    printf("Enter number of chapters: ");
    scanf("%d", &numChapters);
    assert(numChapters > 1);
    printf("Enter number of home-works: ");
    scanf("%d", &numHW);
    assert(numHW >= 1);

    unsigned grades[numStudents][numHW * numChapters];

    for (unsigned i = 0; i < numStudents; ++i)
        for (unsigned j = 0; j < numChapters * numHW; ++j) {
            fscanf(source, "%d", &buffer);
            grades[i][j] = buffer;
        }

    for (unsigned i = 0; i < numChapters; ++i)
        manager_process(i, numHW, numStudents, grades);

    fclose(source);
    return EXIT_SUCCESS;
}