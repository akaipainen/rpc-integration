// #include <cstdlib>
#include <iostream>
// #include <getopt.h>
// #include <string>
// #include <fstream>
// #include <bitset>
// #include <sstream>
// #include <vector>

// #include "nlohmann/json.hpp"

// #include "event.h"
// #include "event_builder.h"
// #include "histogram_builder.h"
// #include "histograms.h"
// #include "utils.h"

#include "loader.h"
#include "reconstructor.h"
#include "analysis_manager.h"

#include "simple_task.h"
#include "time_difference_from_average.h"
#include "time_difference_vs_distance.h"
#include "isolate_noise.h"

#include <TTree.h>

// using json = nlohmann::json;

void print_help() {
    std::cout << "Usage: ./gen_tree config_file num_packets" << std::endl;
    exit(1);
}

int main(int argc, char *argv[]) {
    Loader *loader = new Loader();
    loader->open("official_leading.root");
    TTree *tree = new TTree("tree", "Tree info");

    Reconstructor rec;
    rec.set_input_file(argv[1]);
    rec.set_pair_mode(false);
    rec.set_tree(*tree);
    rec.add_noise(169);
    rec.add_noise(233);
    rec.run();

    AnalysisManager mgr;
    mgr.init(tree);
    // mgr.add_task(new SimpleTask());
    mgr.add_task(new TimeDifferenceFromAverage());
    mgr.add_task(new TimeDifferenceVsDistance());
    // mgr.add_task(new IsolateNoise());
    mgr.run();

    loader->write();

    delete loader;

    return 0;
}