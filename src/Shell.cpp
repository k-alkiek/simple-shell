//
// Created by khaled on 10/5/18.
//

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <array>

#include "../include/Shell.h"

using namespace std;

// Create Logger
string loggerPath = (string(getenv("PWD")) + "/shell-logs");
Logger Shell::logger = Logger(loggerPath.c_str());

Shell::Shell() {
    userName = getenv("USER");
    gethostname(hostName, 50);
    logger.log("------ Started Shell -------", Logger::Level::INFO);

}

void Shell::start() {
    welcome();
    shellLoop();
}

void Shell::welcome() {
    string splashText {
            "                                      _.-''|''-._\n"
            "                                   .-'     |     `-.\n"
            " __ _                 _          .'\\       |       /`.     __ _          _ _\n"
            "/ _(_)_ __ ___  _ __ | | ___   .'   \\      |      /   `.  / _\\ |__   ___| | |\n"
            "\\ \\| | '_ ` _ \\| '_ \\| |/ _ \\  \\     \\     |     /     /  \\ \\| '_ \\ / _ \\ | |\n"
            "_\\ \\ | | | | | | |_) | |  __/   `\\    \\    |    /    /'   _\\ \\ | | |  __/ | |\n"
            "\\__/_|_| |_| |_| .__/|_|\\___|     `\\   \\   |   /   /'     \\__/_| |_|\\___|_|_|\n"
            "               |_|                  `\\  \\  |  /  /'\n"
            "                                   _.-`\\ \\ | / /'-._\n"
            "                                  {_____`\\\\|//'_____}\n"
            "                                          `-'"
    };

    cout << splashText << endl;
}

vector<string> Shell::getInput() {
    string line;
    getline(cin, line);
    istringstream iss(line);

    vector<string> tokens;
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));

    return tokens;
}

void Shell::shellLoop() {


    while (true) {
        printPrompt();
        vector<string> input = getInput();
        if (input.size() == 0) continue;
        else if (input[0] == "q" || input[0] == "exit" || input[0] == "quit") {
            logger.log("------ Shell Exit Gracefully -------", Logger::Level::INFO);
            return;
        }
        else if (input[0] == "cd" && input.size() > 1) cd((char*)input[1].c_str());
        else shellExecute(input);
    }
}

void Shell::shellExecute(vector<string> args) {
    vector<char *> argc;
    for (auto const& a : args) {
        argc.emplace_back(const_cast<char *>(a.c_str()));
    }
    argc.push_back(NULL);

    bool isBackgroundProcess = std::find(args.begin(), args.end(), "&") != args.end();

    int pid = fork();
    signal(SIGCHLD, Shell::sigchldHandler);
    if (pid == 0) {     // Child process

        execvp(argc[0], argc.data());
    }
    else {        // Parent process
        if (!isBackgroundProcess) {
            wait(NULL);
        }
    }
}

void Shell::printPrompt() {
    cout << userName << '@' << hostName << ":" << pwd() << " >";
}

void Shell::cd(char *path) {
    if (chdir(path)) {
        char wd[1024];
        getcwd(wd, sizeof(wd));

    }
}

string Shell::pwd() {
    char temp[1024];
    return ( getcwd(temp, 1024) ? std::string( temp ) : std::string("") );
}

void Shell::sigchldHandler(int sig) {
    int status;
    waitpid(-1, &status, WNOHANG);
    logger.log("Child process was terminated " + to_string(status), Logger::Level::INFO);
}
