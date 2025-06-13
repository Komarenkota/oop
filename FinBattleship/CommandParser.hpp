#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string.h>
#include <sstream>
#include <set>
#include <algorithm>

enum CommandType{
        Fire,
        Save,
        Load,
        UseAbility,
        PutShip,
        Exit,
        Unknown
};

struct Command {
    CommandType type;
    std::vector<std::string> arguments;
};

class CommandParser {
public:
    CommandParser();
    Command parse(const std::string& input);
    std::string waitCommand();

private:
    std::map<char, CommandType> commandBindings;
    CommandType stringToCommand(const std::string& command);
};

#endif