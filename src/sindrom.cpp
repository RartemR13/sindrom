#include <iostream>
#include <optional>

#include "SindromPicture/SindromPicture.hpp"
#include "CmdArgsParser/CmdArgsParser.hpp"

int main(int argc, char* argv[]) {
    CmdArgsParser cmd_parser(argc, argv);

    std::optional<SindromPicture> picture;

    for (const auto& command : cmd_parser.GetParsedCommands()) {
        switch (command) {
            case CmdArgsParser::Command::LOAD:
            {
                auto args = cmd_parser.GetParsedArgs(1);
                picture = SindromPicture(args.front());
                break;
            }
            case CmdArgsParser::Command::SAVE:
            {
                if (!picture) {
                    throw std::invalid_argument("Image has not been load");
                }

                auto args = cmd_parser.GetParsedArgs(1);
                picture->Save(args.front());
                break;
            }
            case CmdArgsParser::Command::NEGATIVE:
            {
                if (!picture) {
                    throw std::invalid_argument("Image has not been load");
                }
                
                picture->Negative();
                break;
            }
            case CmdArgsParser::Command::REPLACE_COLOR:
            {
                if (!picture) {
                    throw std::invalid_argument("Image has not been load");
                }

                auto args = cmd_parser.GetParsedArgs(8);
                
                RGBquad from{static_cast<std::uint8_t>(std::stoul(args[0])),
                             static_cast<std::uint8_t>(std::stoul(args[1])),
                             static_cast<std::uint8_t>(std::stoul(args[2])),
                             static_cast<std::uint8_t>(std::stoul(args[3]))};

                RGBquad to  {static_cast<std::uint8_t>(std::stoul(args[4])),
                             static_cast<std::uint8_t>(std::stoul(args[5])),
                             static_cast<std::uint8_t>(std::stoul(args[6])),
                             static_cast<std::uint8_t>(std::stoul(args[7]))};

                picture->ReplaceColor(from, to);
                break;
            }
            default:
                break;
        }
    }
}