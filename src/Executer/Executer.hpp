#pragma once

#include <optional>

#include "../SindromPicture/SindromPicture.hpp"
#include "../CmdArgsParser/CmdArgsParser.hpp"

class Executer {
public:
    Executer(CmdArgsParser& args_parser);
    void Start();
private:
    void Execute(Command command, std::string args_line);

    void Negative();
    void ReplaceColor(std::string);
    void Load(std::string);
    void Save(std::string);
    void Cut(std::string);
    void Scale(std::string);
    void ImpoveDefinition();
    void Gauss();
    void Median();
    void MakeGrey();

    CmdArgsParser& args_parser_;
    std::optional<SindromPicture> picture_;
};