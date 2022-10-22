#include "Executer.hpp"

#include <iostream>
#include <sstream>
#include <exception>

Executer::Executer(CmdArgsParser& args_parser) :
    args_parser_(args_parser)
{}

void Executer::Start() {
    auto parsed_commands = args_parser_.GetParsedCommands();
    if (parsed_commands.empty()) {
        do {
            std::string line;
            if (!std::getline(std::cin, line)) {
                throw std::runtime_error("EOF!");
            }

            auto [command, args_line] = Parse(line);
            if (command == Command::EXIT) {
                break;
            }
            try {
                Execute(command, args_line);
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        } while (true);
    } else {
        for (const auto& parsed_command : parsed_commands) {
            auto args = args_parser_.GetParsedArgs(CommandArgsCount[static_cast<std::size_t>(parsed_command)]);
            std::stringstream to_args_line;
            for (const auto& arg : args) {
                to_args_line << arg + " ";
            }

            std::string args_line = to_args_line.str();
            if (!args_line.empty()) {
                args_line.pop_back();
            }

            Execute(parsed_command, args_line);
        }
    }
}

void Executer::Execute(Command command, std::string args_line) {
    switch (command)
    {
    case Command::LOAD:
        Load(args_line);
        break;
    case Command::REPLACE_COLOR:
        ReplaceColor(args_line);
        break;
    case Command::SAVE:
        Save(args_line);
        break;
    case Command::NEGATIVE:
        Negative();
        break;
    case Command::EXIT:
        break;
    }
}

void Executer::Load(std::string args_line) {
    picture_ = SindromPicture(args_line);
}

void Executer::ReplaceColor(std::string args_line) {
    if (!picture_) {
        throw std::runtime_error("Image was not load");
    }

    std::stringstream args(args_line);

    RGBquad from, to;
    if (!(args >> from)) {
        throw std::invalid_argument("Bad args, replace_color from");
    }

    if (!(args >> to)) {
        throw std::invalid_argument("Bad args, replace_color to");
    }

    picture_->ReplaceColor(from, to);
}

void Executer::Negative() {
    if (!picture_) {
        throw std::runtime_error("Image was not load");
    }

    picture_->Negative();
}

void Executer::Save(std::string args_line) {
    if (!picture_) {
        throw std::runtime_error("Image was not load");
    }

    picture_->Save(args_line);
}