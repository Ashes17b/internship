#include "logger.h"

int main() {
    Logger *logger = new Logger();

    logger->log("Console", 1, "IP address: ", "192.168.1.1", " has been blocked, port= ", "8.8.8.8");

    return 0;
}