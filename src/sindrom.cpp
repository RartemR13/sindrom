#include <iostream>

#include "SindromPicture/SindromPicture.hpp"
#include "CmdArgsParser/CmdArgsParser.hpp"

int main(int argc, char* argv[]) {
    CmdArgsParser cmd_parser(argc, argv);
    SindromPicture picture("kaneki.bmp");

    for (const auto& command : cmd_parser.GetParsedCommands()) {
        switch (command) {
            case CmdArgsParser::Command::NEGATIVE:
            {
                cmd_parser.GetParsedArgs(0);
                picture.Negative();
                break;
            }
            case CmdArgsParser::Command::REPLACE_COLOR:
            {
                auto args = cmd_parser.GetParsedArgs(8);
                
                RGBquad from{static_cast<std::uint8_t>(std::stoul(args[0])),
                             static_cast<std::uint8_t>(std::stoul(args[1])),
                             static_cast<std::uint8_t>(std::stoul(args[2])),
                             static_cast<std::uint8_t>(std::stoul(args[3]))};

                RGBquad to  {static_cast<std::uint8_t>(std::stoul(args[4])),
                             static_cast<std::uint8_t>(std::stoul(args[5])),
                             static_cast<std::uint8_t>(std::stoul(args[6])),
                             static_cast<std::uint8_t>(std::stoul(args[7]))};

                picture.ReplaceColor(from, to);
                break;
            }
            default:
                break;
        }
    }

    picture.Save("sosi.bmp");
}