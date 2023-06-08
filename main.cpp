#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <thread>
#include <ncurses.h>
#include <csignal>
#include <regex>

bool shouldExit = false;

void signalHandler(int signal) {
    shouldExit = true;
}

void centerText(const std::string& text, int terminalHeight, std::string position) {

    int padding;
    if (position == "top")
    {
        padding = 0;
        
    } else {
        padding = (terminalHeight - 1) / 2;
    }
    int row = padding;
    int col = (COLS - text.length()) / 2;
    mvprintw(row, col, "%s", text.c_str());
}

std::string getCurrentTime() {
    auto currentTime =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm* localTime = std::localtime(&currentTime);
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour << ":"
        << std::setfill('0') << std::setw(2) << minute << ":"
        << std::setfill('0') << std::setw(2) << second;

    return oss.str();
}

void displayClock()
{
    initscr();
    curs_set(0);

    while (!shouldExit) {
        std::string timeString = getCurrentTime();

        clear();
        box(stdscr, 0, 0);
        centerText("Clock", LINES, "top");
        centerText(timeString, LINES, "other");
        refresh();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    curs_set(1);
    endwin();
}

int main() {
    signal(SIGTERM, signalHandler);
    displayClock();

    return 0;
}

