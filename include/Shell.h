//
// Created by khaled on 10/5/18.
//

#ifndef SIMPLE_SHELL_SHELL_H
#define SIMPLE_SHELL_SHELL_H

#include <string>
#include <vector>
#include "Logger.h"

class Shell {
public:
    Shell();
    void start();

private:
    void welcome();
    std::vector<std::string> getInput();
    void shellLoop();
    void shellExecute(std::vector<std::string> args);
    static void sigchldHandler(int sig);
    void cd(char* path);
    void printPrompt();

    std::string pwd();
    std::string userName;
    char hostName[50];

    static Logger logger;
};



#endif //SIMPLE_SHELL_SHELL_H
