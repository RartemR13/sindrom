#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <map>

//---------------------------------------------------
enum class Command {
    LOAD,
    SAVE,
    NEGATIVE,
    REPLACE_COLOR,
    EXIT
};

const std::size_t CommandArgsCount[] =
{
    //LOAD = 
        1,
    //SAVE = 
        1,
    //NEGATIVE = 
        0,
    //REPLACE_COLOR = 
        8,
    //EXIT = 
        0
};

const std::map<std::string, Command> COMMANDS_MAP{
    {"load", Command::LOAD},
    {"save", Command::SAVE},
    {"negative", Command::NEGATIVE},
    {"replace_color", Command::REPLACE_COLOR},
    {"exit", Command::EXIT}
};
std::tuple<Command, std::string> Parse(std::string, std::string = "");
//---------------------------------------------------

class CmdArgsParser {
public:
    CmdArgsParser(int argc, char* argv[]);
    const std::vector<Command>& GetParsedCommands() const;
    const std::vector<std::string> GetParsedArgs(std::size_t count);

    CmdArgsParser() = delete;
    CmdArgsParser(const CmdArgsParser&) = delete;
    ~CmdArgsParser() = default;

private:
    std::vector<Command> parsed_commands_;

    std::vector<char*> parsed_args_;
    std::size_t cur_args_getted_count_ = 0;
};
