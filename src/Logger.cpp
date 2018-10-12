//
// Created by khaled on 10/5/18.
//

#include <string>
#include <chrono>
#include <iomanip>
#include <iostream>
#include "../include/Logger.h"

Logger::Logger(const char* path) {
    this->path = path;
}

std::ofstream  Logger::openFile() {
    std::ofstream file(path, std::fstream::out | std::fstream::app);
    return file;
}

void Logger::closeFile(std::ofstream file) {
    file.flush();
    file.close();
}

void Logger::log(std::string message, Logger::Level level) {
    openFile();
    std::string timestamp = getDateTime();
    std::string prefix;

    switch (level) {
        case Level::INFO:
            prefix = " [INFO]:";
            break;
        case Level::WARNING:
            prefix = " [WARNING]:";
            break;
        case Level::ERROR:
            prefix = " [ERROR]:";
            break;
    }
    std::string logMessage = timestamp + ' ' + prefix + ' ' + message + '\n';

    std::ofstream file = openFile();
    file << logMessage;
    file.flush();
    file.close();
}

std::string Logger::getDateTime() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");

    return oss.str();
}

