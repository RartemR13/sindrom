#include "Executer.hpp"

#include <iostream>
#include <sstream>
#include <exception>
#include <random>
#include <iterator>
#include <set>

#include "../../submodules/colorcode/colorcode/colorcode.h"

Executer::Executer(CmdArgsParser& args_parser) :
    args_parser_(args_parser),
    cur_path_(std::filesystem::current_path())
{}

void Executer::Start() {
    auto parsed_commands = args_parser_.GetParsedCommands();
    if (parsed_commands.empty()) {
        do {
            WriteCurPath();

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
    case Command::CUT:
        Cut(args_line);
        break;
    case Command::EXIT:
        break;
    case Command::SCALE:
        Scale(args_line);
        break;
    case Command::IMPROVE_DEFINITION:
        ImpoveDefinition();
        break;
    case Command::GAUSS:
        Gauss();
        break;
    case Command::MEDIAN:
        Median();
        break;
    case Command::MAKE_GREY:
        MakeGrey();
        break;
    case Command::EDGE_DETECTION:
        EdgeDetection(args_line);
        break;
    case Command::VINIET:
        Viniet(args_line);
        break;
    case Command::UNDO:
        Undo();
        break;
    case Command::LS:
        Ls();
        break;
    case Command::CLEAR:
        Clear();
        break;
    case Command::CD:
        Cd(args_line);
        break;
    }
}

void Executer::Load(std::string args_line) {
    if (picture_) {
        story_.push_back(picture_.value());
    }

    picture_ = SindromPicture(cur_path_.string() + "/" + args_line);
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

    story_.push_back(picture_.value());
    picture_->ReplaceColor(from, to);
}

void Executer::Negative() {
    if (!picture_) {
        throw std::runtime_error("Image was not load");
    }

    story_.push_back(picture_.value());
    picture_->Negative();
}

void Executer::Save(std::string args_line) {
    if (!picture_) {
        throw std::runtime_error("Image was not load");
    }

    picture_->Save(cur_path_.string() + "/" + args_line);
}

void Executer::Cut(std::string args_line) {
    if (!picture_) {
        throw std::runtime_error("Image was not load");
    }

    std::size_t x, y, dx, dy;
    std::stringstream args(args_line);
    if (!(args >> x >> y >> dx >> dy)) {
        throw std::invalid_argument("Bad args, Cut");
    }

    story_.push_back(picture_.value());
    picture_->SetStorage(picture_->Cut(x, y, dx, dy).GetStorage());
}

void Executer::Scale(std::string args_line) {
    if (!picture_) {
        throw std::runtime_error("Image was not load");
    }

    std::size_t new_x, new_y;
    std::stringstream args(args_line);
    if (!(args >> new_x >> new_y)) {
        throw std::invalid_argument("Bad args, Scale");
    }

    story_.push_back(picture_.value());
    picture_->Scale(new_x, new_y);
}

void Executer::ImpoveDefinition() {
    if (!picture_) {
        throw std::runtime_error("Image was not load");
    }

    story_.push_back(picture_.value());
    picture_->ImproveDefinition();
}

void Executer::Gauss() {
    if (!picture_) {
        throw std::runtime_error("Image was not load");
    }

    story_.push_back(picture_.value());
    picture_->Gauss();
}

void Executer::Median() {
    if (!picture_) {
        throw std::runtime_error("Image was not load");
    }

    story_.push_back(picture_.value());
    picture_->Median();
}

void Executer::MakeGrey() {
    if (!picture_) {
        throw std::runtime_error("Image was not load");
    }

    story_.push_back(picture_.value());
    picture_->MakeGrey();
}

void Executer::EdgeDetection(std::string args_line) {
    if (!picture_) {
        throw std::runtime_error("Image was not load");
    }

    std::size_t thres_hold;
    std::stringstream args(args_line);

    if (!(args >> thres_hold) || thres_hold > 255) {
        throw std::invalid_argument("Bad args, edge_detection thres hold");
    }

    story_.push_back(picture_.value());
    picture_->EdgeDetection(static_cast<std::uint8_t>(thres_hold));
}

void Executer::Viniet(std::string args_line) {
    if (!picture_) {
        throw std::runtime_error("Image was not load");
    }

    std::size_t viniet_koef;
    std::stringstream args(args_line);

    if (!(args >> viniet_koef)) {
        throw std::invalid_argument("Bad args, viniet viniet_koef");
    }

    story_.push_back(picture_.value());
    picture_->Viniet(viniet_koef);
}

void Executer::Undo() {
    if (story_.empty()) {
        return;
    }

    picture_ = story_.back();
    story_.pop_back();
}

void Executer::Ls() {
    std::cout << colorcode::fore(colorcode::COLOR_BLUE)
              << ". .. ";

    for (auto dir_entry : std::filesystem::directory_iterator(cur_path_)) {
        if (dir_entry.is_directory()) {
            std::cout << colorcode::fore(colorcode::COLOR_BLUE);
        } else if (dir_entry.path().extension() == ".bmp") {
            std::cout << colorcode::fore(colorcode::COLOR_MAGENTA);
        } else {
            std::cout << colorcode::fore(colorcode::COLOR_DEFAULT);
        }
        std::cout << dir_entry.path().filename().string() << " ";
    }
    
    std::cout << colorcode::fore(colorcode::COLOR_DEFAULT);
    std::cout << std::endl;
}



const std::vector<std::string> LIFE_STATUS_STRINGS = {
    #include "BeginPhrases.hpp"
};

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

void Executer::WriteCurPath() {
    std::cout << colorcode::fore(colorcode::COLOR_DARK_RED)
              << *select_randomly(LIFE_STATUS_STRINGS.begin(), LIFE_STATUS_STRINGS.end())
        
              << colorcode::fore(colorcode::COLOR_BLUE) 
              << " ? "

              << colorcode::fore(colorcode::COLOR_YELLOW) 
              << cur_path_.string()

              << colorcode::fore(colorcode::COLOR_GREEN)
              << " > "

              << colorcode::fore(colorcode::COLOR_DEFAULT);
}

void Executer::Clear() {
    std::system("clear");
}

void Executer::Cd(std::string args_line) {
    if (args_line == ".") {
        return;
    }

    if (args_line == "..") {
        cur_path_ = cur_path_.parent_path();
        return;
    }

    for (auto dir_component : std::filesystem::recursive_directory_iterator(cur_path_)) {
        if (dir_component.path().string() == cur_path_.string() + "/" + args_line && dir_component.is_directory()) {
            cur_path_ += "/" + args_line;
            return;
        }
    }

    if (std::filesystem::directory_entry(std::filesystem::path(args_line)).is_directory()) {
        cur_path_ = std::filesystem::path(args_line);
        return;
    }

    throw std::invalid_argument("Incorrect directory " + args_line);
}