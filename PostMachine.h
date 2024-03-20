#ifndef POSTMACHINE_H
#define POSTMACHINE_H

#include <vector>
#include <string>

class PostMachine {
public:
    PostMachine(bool state, std::vector<char> ribbon_list, int carriage);
    bool get_state();
    std::vector<char> get_ribbon_list();
    int get_carriage();
    std::pair<std::vector<char>, int> command_function(char current_command);
    std::string error_message;

private:
    bool state;
    std::vector<char> ribbon_list;
    int carriage;
    bool can_do_command(char current_command);
    void ribbon_extension();
};

#endif // POSTMACHINE_H
