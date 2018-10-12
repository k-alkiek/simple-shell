//
// Created by khaled on 10/5/18.
//

#ifndef SIMPLE_SHELL_LOGGER_H
#define SIMPLE_SHELL_LOGGER_H

#include <string>
#include <fstream>

class Logger {
public:
    Logger(const char* path);

    enum class Level { INFO, WARNING, ERROR };
    void log(std::string message, Logger::Level level);
private:
    std::ofstream openFile();
    void closeFile(std::ofstream file);
    const char* path;
    static std::string getDateTime();
};


#endif //SIMPLE_SHELL_LOGGER_H
