#include "server.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>

std::string fileName() {
    std::time_t current_time = std::time(nullptr);
    std::tm* local = std::localtime(&current_time);

    std::ostringstream oss;
    oss << (local->tm_year + 1900)
        << std::setfill('0') << std::setw(2) << (local->tm_mon + 1)
        << std::setfill('0') << std::setw(2) << local->tm_mday << "_"
        << std::setfill('0') << std::setw(2) << local->tm_hour
        << std::setfill('0') << std::setw(2) << local->tm_min
        << std::setfill('0') << std::setw(2) << local->tm_sec;

    return oss.str();
}

std::string Server::downloadFile(std::string link, std::string format) {
    std::string filename = fileName() + "." + format;
    std::string absolutePath = "/home/jame/Projects/Youload/downloads/" + filename;

    std::string command;
    if (format == "mp3") {
        command = "yt-dlp -x --audio-format mp3 -o \"" + absolutePath + "\" \"" + link + "\"";
    } else {
        command = "yt-dlp --merge-output-format mp4 -o \"" + absolutePath + "\" \"" + link + "\"";
    }

    std::cout << "Running command: " << command << std::endl;

    int result = std::system(command.c_str());

    if (result == 0) {
        std::cout << "Download complete in server!" << std::endl;
        return filename;
    } else {
        std::cerr << "Error to run yt-dlp" << std::endl;
        return "";
    }
}
