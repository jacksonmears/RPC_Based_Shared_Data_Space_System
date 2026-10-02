#include "../include/arg_parser.hpp"



int char_found(const std::string& str)
{
    for (char c : str) 
    {
        if (!std::isdigit(static_cast<unsigned char>(c))) 
        {
            return 1; 
        }
    }
    return 0; 
}

int number_found(const std::string& str) 
{
    for (char c : str) 
    {
        if (std::isdigit(static_cast<unsigned char>(c))) 
        {
            return 1; 
        }
    }
    return 0; 
}

