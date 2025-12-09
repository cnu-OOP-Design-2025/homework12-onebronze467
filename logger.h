
#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <string>

class Logger {
private:
    static std::unique_ptr<Logger> instance;
    static std::mutex init_mtx;
    static std::mutex write_mtx;
    std::ofstream logFile;


public:
    Logger(const std::string& filename = "Test/output2.txt") {
        logFile.open(filename, std::ios::trunc);
        log("[Init] Logger started.");
    }
    ~Logger() {
        if (logFile.is_open()) {
            log("[Shutdown] Logger closed.");
            logFile.close();
        }
    }
    static Logger* getInstance(const std::string& filename = "Test/output2.txt") {
        std::lock_guard<std::mutex> lock(init_mtx);
        if (!instance) {
            instance.reset(new Logger(filename));
        }
        return instance.get();
    }

    void log(const std::string& message) {
        /* TODO */
        std::lock_guard<std::mutex> lock(write_mtx);
        logFile << message << std::endl;

    }

};

std::unique_ptr<Logger> Logger::instance;
std::mutex Logger::init_mtx;
std::mutex Logger::write_mtx;

