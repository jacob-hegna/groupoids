#ifndef __PARSER_H__
#define __PARSER_H__

#include "groupoid.h"
#include <istream>

GroupoidPtr parse_groupoid(std::istream& in);

std::vector<GroupoidPtr> parse_groupoid_list(std::istream& in);

#endif // __PARSER_H_