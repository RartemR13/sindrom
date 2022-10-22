#include <iostream>
#include <optional>

#include "CmdArgsParser/CmdArgsParser.hpp"
#include "Executer/Executer.hpp"

int main(int argc, char* argv[]) {
    CmdArgsParser cmd_parser(argc, argv);
    Executer executer(cmd_parser);

    executer.Start();
}