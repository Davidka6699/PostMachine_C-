#include "PostMachine.h"

PostMachine::PostMachine(bool state, std::vector<char> ribbon_list, int carriage) {
    this->state = state;
    this->ribbon_list = ribbon_list;
    this->carriage = carriage;
}

bool PostMachine::get_state() {
    return state;
}

std::vector<char> PostMachine::get_ribbon_list() {
    return ribbon_list;
}

int PostMachine::get_carriage() {
    return carriage;
}

bool PostMachine::can_do_command(char current_command) {
    if (ribbon_list[carriage] == '1' && current_command == 'V')
        return false;
    else if (ribbon_list[carriage] == '0' && current_command == 'X')
        return false;
    else if (current_command != 'V' && current_command != 'X')
        return false;
    else
        return true;
}

void PostMachine::ribbon_extension() {
    if (carriage == ribbon_list.size() - 1) {
        for (int i = 0; i < 33; i++)
            ribbon_list.push_back('0');
    } else if (carriage == 0) {
        std::vector<char> temp(33, '0');
        ribbon_list.insert(ribbon_list.begin(), temp.begin(), temp.end());
        carriage = 30;
    }
}

std::pair<std::vector<char>, int> PostMachine::command_function(char current_command) {
    if (current_command == 'V' && can_do_command(current_command)) {
        ribbon_list[carriage] = '1';
        return {ribbon_list, carriage};
    } else if (current_command == 'X' && can_do_command(current_command)) {
        ribbon_list[carriage] = '0';
        return {ribbon_list, carriage};
    } else if (current_command == '>') {
        if (carriage == ribbon_list.size() - 1)
            ribbon_extension();
        carriage++;
        return {ribbon_list, carriage};
    } else if (current_command == '<') {
        if (carriage == 0) {
            ribbon_extension();
        } else {
            carriage--;
        }
        return {ribbon_list, carriage};
    } else if (current_command == 's') {
        error_message = "Программа окончила свое выполнение без ошибок";
        return {{}, -1};
    } else if (current_command == '?') {
        if (ribbon_list[carriage] == '1')
            return {{}, 22};
        else
            return {{}, 11};
    } else {
        error_message = "Программа не может окончить свое выполнение в связи с ошибкой";
        return {{}, -1};
    }
}
