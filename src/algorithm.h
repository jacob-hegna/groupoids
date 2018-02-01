#ifndef __GROUPOID_SR_H_
#define __GROUPOID_SR_H_

#include "Groupoid.h"

namespace Algorithm {
    bool check_sr(GroupoidPtr gpd, GroupoidPtr algo_tb = nullptr);

    void sr_graph(GroupoidPtr, std::string filename);
};

#endif