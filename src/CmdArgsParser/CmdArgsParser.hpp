#pragma once

#include <vector>
#include <string>

class CmdArgsParser {
public:
    enum class Command {
        NEGATIVE,
        REPLACE_COLOR
    };

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