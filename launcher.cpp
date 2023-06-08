#include <cstdlib>
#include <sys/ioctl.h>
#include <string>

void setTerminalBufferSize(int columns, int rows) {
    std::string command = "stty cols " + std::to_string(columns) + " rows " + std::to_string(rows);
    std::system(command.c_str());
}

int getTerminalWidth() {
    struct winsize size;
    ioctl(1, TIOCGWINSZ, &size);
    return size.ws_col;
}

int getTerminalHeight() {
    struct winsize size;
    ioctl(1, TIOCGWINSZ, &size);
    return size.ws_row;
}

int main() {
    // Set the desired terminal size
    int columns = 12;
    int rows = 5;

    // Set the terminal buffer size to match the terminal size
    int terminalWidth = getTerminalWidth();
    int terminalHeight = getTerminalHeight();
    setTerminalBufferSize(terminalWidth, terminalHeight);

    // Launch the clock program
    std::string command = "gnome-terminal --geometry=" + std::to_string(columns) + "x" + std::to_string(rows) + " -- ./home/arctrect/Projects/cpp-projects/clock/clock";
    std::system(command.c_str());

    return 0;
}
