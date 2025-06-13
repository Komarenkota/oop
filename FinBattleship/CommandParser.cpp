#include "CommandParser.hpp"
#include "FileWrapper.hpp"



CommandParser::CommandParser() {
    std::string filename = "Settings.dat";
    std::fstream file("Settings.dat");
    FileWrapper fileWrapper = FileWrapper(filename, std::ios::in);

    if (file.is_open()) {
        char key;
        std::string command;
        std::map<char, CommandType> tempBindings;
        std::set<CommandType> usedCommands;

        while (file >> key >> command) {
            CommandType cmd = stringToCommand(command);

            if (cmd == CommandType::Unknown) {
                commandBindings = {
                    {'f', CommandType::Fire},
                    {'s', CommandType::Save},
                    {'l', CommandType::Load},
                    {'a', CommandType::UseAbility},
                    {'p', CommandType::PutShip},
                    {'e', CommandType::Exit}
                };
                return;
            }

            if (usedCommands.count(cmd)) {
                commandBindings = {
                    {'f', CommandType::Fire},
                    {'s', CommandType::Save},
                    {'l', CommandType::Load},
                    {'a', CommandType::UseAbility},
                    {'p', CommandType::PutShip},
                    {'e', CommandType::Exit}
                };
                return;
            }

            if (tempBindings.find(key) != tempBindings.end()) {
                commandBindings = {
                    {'f', CommandType::Fire},
                    {'s', CommandType::Save},
                    {'l', CommandType::Load},
                    {'a', CommandType::UseAbility},
                    {'p', CommandType::PutShip},
                    {'e', CommandType::Exit}
                };
                return;
            }

            tempBindings[key] = cmd;
            usedCommands.insert(cmd);
        }

        commandBindings = tempBindings;
    } else {
        commandBindings = {
            {'s', CommandType::Save},
            {'f', CommandType::Fire},
            {'l', CommandType::Load},
            {'a', CommandType::UseAbility},
            {'p', CommandType::PutShip},
            {'e', CommandType::Exit}
        };
    }
}



Command CommandParser::parse(const std::string& input) {
    if (input.size() < 1) return {CommandType::Unknown, {}};
    char key = input[0];

    if (commandBindings.find(key) != commandBindings.end()) {
        CommandType type = commandBindings[key];
        std::vector<std::string> arguments;

        if (input.size() > 2) {
            std::istringstream iss(input.substr(2));
            std::string arg;
            while (iss >> arg) {
                arguments.push_back(arg);
            }
        }

        return {type, arguments};
    }

    return {CommandType::Unknown, {}};
}

std::string CommandParser::waitCommand(){
    std::string input;
    std::cout << "Enter command: ";
    std::getline(std::cin, input);
    return input;
}

CommandType CommandParser::stringToCommand(const std::string& command) {
    if (command == "PutShip") return CommandType::PutShip;
    if (command == "Fire") return CommandType::Fire;
    if (command == "Save") return CommandType::Save;
    if (command == "Load") return CommandType::Load;
    if (command == "UseAbility") return CommandType::UseAbility;
    if (command == "Exit") return CommandType::Exit;
    return CommandType::Unknown;
}