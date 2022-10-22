#include "CmdArgsParser.hpp"

#include <stdexcept>

CmdArgsParser::CmdArgsParser(int argc, char* argv[]) {
    if (argc <= 1) {
        throw std::invalid_argument("argc <= 1");
    }

    for (std::size_t i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            auto cur_command = static_cast<std::string>(argv[i]);
            if (cur_command == "-negative") {
                parsed_commands_.push_back(Command::NEGATIVE);
            } else if (cur_command == "-replace_color") {
                parsed_commands_.push_back(Command::REPLACE_COLOR);
            } else if (cur_command == "-load") {
                parsed_commands_.push_back(Command::LOAD);
            } else if (cur_command == "-save") {
                parsed_commands_.push_back(Command::SAVE);                
            } else {
                throw std::invalid_argument("incorrect command name: " + cur_command);
            }
        } else {
            parsed_args_.push_back(argv[i]);
        }
    }
}

const std::vector<CmdArgsParser::Command>& CmdArgsParser::GetParsedCommands() const {
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