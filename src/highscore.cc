#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <cstdio>
#include "highscore.h"

Highscore::Highscore()
    : filename{}, level_name{}, current_highscore{} {}

//Loads relevant score from file.
void Highscore::load_highscore()
{
    std::ifstream score_file(filename);
    std::string line;
    while (getline(score_file, line))
    {
        std::vector<std::string> lvl_time{};
        std::string section;
        std::stringstream ss(line);

        while (getline(ss, section, '|'))
        { lvl_time.push_back(section); }

        if (lvl_time.size() > 0 && lvl_time.at(0) == level_name)
        {
            if (lvl_time.size() > 1)
            { current_highscore = stoi(lvl_time.at(1)); }
        }
    }
    score_file.close();
}

//Replaces relevant score in file.
void Highscore::save_highscore(int new_score)
{
    std::ifstream file_in(filename);
    std::ofstream file_out("./tempscore.txt");

    std::string line;
    bool found{false};

    while (getline(file_in, line))
    {
        std::vector<std::string> sections{};
        std::string section;
        std::stringstream ss(line);

        while (getline(ss, section, '|'))
        { sections.push_back(section); }

        if (sections.size() > 0)
        {
            if (sections.at(0) == level_name)
            {
                found = true;
                if (new_score < current_highscore)
                {
                    line = level_name + "|" + std::to_string(new_score);
                }
            }
            line += "\n";
            file_out << line;
        }
    }
    if (!found)
    {
        std::string output{level_name + "|" + std::to_string(1000) + "\n"};
        file_out << output;
    }

    unlink(filename.c_str());
    if (std::rename("./tempscore.txt", filename.c_str()))
    { std::cout << "Can't rename file!" << std::endl; }

    file_in.close();
    file_out.close();
}

int Highscore::get_highscore()
{
    return current_highscore;
}

void Highscore::set_filename(std::string input)
{
    filename = input;
}

void Highscore::set_level_name(std::string input)
{
    level_name = input;
}
