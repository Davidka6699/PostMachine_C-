#include "interpret.h"

Interpret::Interpret() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
}

void Interpret::run() {
    printw("Post Machine Interpretator\n");
    printw("Enter program commands (one per line, press Ctrl+D to finish):\n");
    std::string command;
    while (getline(std::cin, command)) {
        commandList.push_back(command);
    }
    printw("Enter initial tape state (0s and 1s, press Enter to finish):\n");
    std::string ribbon;
    getline(std::cin, ribbon);
    for (char c : ribbon) {
        firstRibbonList.push_back(c);
    }
    firstRibbonList.insert(firstRibbonList.begin(), 30, '0');
    firstRibbonList.insert(firstRibbonList.end(), 30, '0');
    carriage = firstRibbonList.size() / 2;
    start();
    getch();
    endwin();
}

bool Interpret::correctStep(int step) {
    if (step <= 0 || step > commandList.size())
        return false;
    return true;
}

bool Interpret::correctInputRibbon(std::vector<char> ribbon) {
    for (char c : ribbon) {
        if (c != '0' && c != '1')
            return false;
    }
    return true;
}

void Interpret::start() {
    bool work = true;
    int step = 1;
    int iter = 0;
    int maxIter = 300;
    std::vector<char> currentRibbon;

    if (correctInputRibbon(firstRibbonList)) {
        postMachine = PostMachine(true, firstRibbonList, carriage);
        while (work && iter <= maxIter) {
            if (correctStep(step)) {
                char currentCommand = commandList[step - 1][0];
                std::pair<std::vector<char>, int> ex = postMachine.command_function(currentCommand);
                if (ex.second != -1) {
                    currentRibbon = ex.first;
                    carriage = ex.second;
                    clear();
                    printw("Tape: ");
                    for (int i = carriage - 24; i < carriage + 25; i++) {
                        printw("%c ", currentRibbon[i]);
                    }
                    printw("\nCommand %d: %s\n", step, commandList[step - 1].c_str());
                } else if (ex.second == -2) {
                    printw("-------------------------------------------------------------------------------------------------\n");
                    printw("Program cannot complete its execution due to an error\n");
                    printw("-------------------------------------------------------------------------------------------------\n");
                    work = false;
                } else if (ex.second == -3) {
                    printw("-------------------------------------------------------------------------------------------------\n");
                    printw("Program completed its execution without errors\n");
                    printw("-------------------------------------------------------------------------------------------------\n");
                    work = false;
                }
                iter++;
                step = std::stoi(commandList[step - 1].substr(1));
            } else {
                printw("-------------------------------------------------------------------------------------------------\n");
                printw("Program refers to a nonexistent command\n");
                printw("-------------------------------------------------------------------------------------------------\n");
                work = false;
            }
            if (iter > maxIter) {
                printw("-------------------------------------------------------------------------------------------------\n");
                printw("Program got into a loop and exceeded the allowable number of steps. Rewrite the program so that it executes in no more than 300 steps\n");
                printw("Or you added/subtracted numbers\n");
                printw("-------------------------------------------------------------------------------------------------\n");
                work = false;
            }
        }
    } else {
        printw("-------------------------------------------------------------------------------------------------\n");
        printw("Incorrect initial tape state input\n");
        printw("-------------------------------------------------------------------------------------------------\n");
        work = false;
    }
}
