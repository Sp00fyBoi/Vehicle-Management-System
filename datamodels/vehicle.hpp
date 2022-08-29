#pragma once

#include <string>
#include <stdlib.h>
#include "../datastructures/date.hpp"

using namespace std;

class Vehicle
{
public:
    std::string modelname, vtype;
    unsigned int price;
    Date lastImportDate;

    Vehicle()
    {
        this->price = 0;
    }

    Vehicle(std::string modelname, unsigned int price, std::string vtype)
    {
        this->modelname = modelname;
        this->price = price;
        this->vtype = vtype;
    }

    Vehicle(std::string s)
    {
        this->modelname = s.substr(0, s.find(" "));
        s.erase(0, s.find(" ") + 1);

        this->price = std::stoi(s.substr(0, s.find(" ")));
        s.erase(0, s.find(" ") + 1);

        this->vtype = s.substr(0, s.find(" "));
        s.erase(0, s.find(" ") + 1);

        this->lastImportDate = Date(s.substr(0, s.find(" ")));
        s.erase(0, s.find(" ") + 1);
    }

    string Serialize()
    {
        string s = modelname + " " + to_string(price) + " " + vtype + " " + string(lastImportDate);
        return s;
    }
};
