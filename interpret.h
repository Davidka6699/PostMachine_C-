#ifndef INTERPRET_H
#define INTERPRET_H

#include <ncurses.h>
#include <vector>
#include <string>
#include "PostMachine.h"

class Interpret {
public:
    Interpret();
    void run();

private:
    PostMachine postMachine;
    std::vector<std::string> commandList;
    std::vector<char> firstRibbonList;
    int carriage;
    bool correctStep(int step);
    bool correctInputRibbon(std::vector<char> ribbon);
    void start();
};

#endif // INTERPRET_H
