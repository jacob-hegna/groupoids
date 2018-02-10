#include "parser.h"

#include <iostream>
#include <istream>
#include <sstream>

/* We expect to receive input formatted like the following 6-groupoid:
 * * | 0 1 2 3 4 5 
 * --+------------
 * 0 | 2 4 1 1 3 1 
 * 1 | 2 1 3 1 2 3 
 * 2 | 2 5 5 2 0 1 
 * 3 | 3 5 3 2 5 2 
 * 4 | 0 1 0 5 0 3 
 * 5 | 5 1 2 1 4 4 
 */

// internal helper function that parses the groupoid table
GroupoidPtr parse_groupoid_string(std::vector<std::string> gpd_str) {
    std::vector<std::vector<uint>> table;
    for(auto& line : gpd_str) {
        // skip the first line
        if(line.at(0) == '*' || line.at(0) == '-') {
            continue;
        }

        std::vector<uint> row;
        std::stringstream line_ss(line.substr(4, line.length()));
        uint token;
        while(line_ss >> token) {
            row.push_back(token);
        }

        table.push_back(row);
    }

    bool valid_table = true;
    if(table.empty() || table.size() != table.at(0).size()) {
        valid_table = false;
    } else {
        for(auto& row : table) {
            // do we even have the right sized rows...
            if(row.size() != table.at(0).size()) {
                valid_table = false;
                break;
            }
            for(auto& ele : row) {
                // valid multiplication?
                if(ele >= row.size()) {
                    valid_table = false;
                    break;
                }
            }
        }
    }
    
    if(valid_table) {
        return Groupoid::from_vector(table);
    } else {
        return nullptr;
    } 
}

GroupoidPtr parse_groupoid(std::istream& in) {
    if(!in.good()) {
        return nullptr;
    }

    std::string line;
    std::vector<std::string> lines;
    while(std::getline(in, line)) {
        lines.push_back(line);
    }
    
    return parse_groupoid_string(lines);
}

std::vector<GroupoidPtr> parse_groupoid_list(std::istream& in) {
    if(!in.good()) {
        return {};
    }

    std::vector<GroupoidPtr> groupoids;

    std::string line;
    std::vector<std::string> lines;
    while(std::getline(in, line)) {
        if(line.empty()) {
            auto gpd = parse_groupoid_string(lines);
            if(gpd != nullptr) {
                groupoids.push_back(gpd);
            }
            lines.clear();
            continue;
        }

        if(line.at(0) == '*') {
            lines.clear();
        }

        lines.push_back(line);
    }

    return groupoids;
}