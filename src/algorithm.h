#ifndef __GROUPOID_SR_H_
#define __GROUPOID_SR_H_

#include "groupoid.h"
#include <ostream>

namespace Algorithm {
    bool check_sr(GroupoidPtr gpd, GroupoidPtr algo_tb = nullptr);

    void sr_graph(GroupoidPtr, std::ostream& out, bool rho = true);
};

#endif