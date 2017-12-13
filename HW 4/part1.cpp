#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <numeric>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t child;
    std::string input, args;
    std::vector<std::string> words;

    while (true) {
        std::cout << "Input command(s): ";
        getline(std::cin, input);
        fflush(stdin);

        std::istringstream iss(input);
        std::copy(std::istream_iterator<std::string>(iss),
                  std::istream_iterator<std::string>(),
                  std::back_inserter(words));

        unsigned i = 1;
        for (; i < words.size(); i++)
            argv[i] = strdup(words[i].c_str());
        argv[i] = NULL;

        if (strcmp("quit", words[0].c_str()) == 0)
            return EXIT_SUCCESS;

        child = fork();

        if (child == 0) {
            execvp(words[0].c_str(), &argv[0]);
            std::cout << "Execvp failed!" << std::endl;
        }
        waitpid(child, NULL, 0);
        words.clear();
    }

    return EXIT_SUCCESS;
}
