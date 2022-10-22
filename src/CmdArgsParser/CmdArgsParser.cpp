#include "CmdArgsParser.hpp"

#include <stdexcept>
#include <sstream>

CmdArgsParser::CmdArgsParser(int argc, char* argv[]) {
    for (std::size_t i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            auto [command, args] = Parse(argv[i], "-");
            parsed_commands_.push_back(command);
        } else {
            parsed_args_.push_back(argv[i]);
        }
    }
}

const std::vector<Command>& CmdArgsParser::GetParsedCommands() const {
    return parsed_commands_;
}

const std::vector<std::string> CmdArgsParser::GetParsedArgs(std::size_t count) {
    if (cur_args_getted_count_ + count > parsed_args_.size()) {
        throw std::runtime_error("cur_args_getted_count_ + count > parsed_args_.size()");
    }

    std::vector<std::string> ret;
    for (std::size_t i = cur_args_getted_count_; i < cur_args_getted_count_ + count; ++i) {
        ret.push_back(parsed_args_[i]);
    }

    cur_args_getted_count_ += count;
    return ret;
}

std::tuple<Command, std::string> Parse(std::string line, std::string del_prefix) {
    if (!del_prefix.empty()) {
        if (line.length() < del_prefix.length() || line.substr(0, del_prefix.length()) != del_prefix) {
            throw std::runtime_error("Incorrect command" + line);
        }

        line = line.substr(del_prefix.length(), line.length());
    }

    std::stringstream line_in(line);
    
    Command command;
    {
        std::string command_str;
        line_in >> command_str;

        command = COMMANDS_MAP.at(command_str);
    }

    std::string args;
    {
        std::string arg_str;
        while (line_in >> arg_str) {
            args += arg_str + " ";
        }
    }

    if (!args.empty()) {
        args.pop_back();
    }
    
    return {command, args};
}