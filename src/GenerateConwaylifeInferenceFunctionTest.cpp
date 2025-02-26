#include "common.hpp"
#include "ConwaylifeInferenceFunction.hpp"

#include <iostream>

void generateConwaylifeInferenceTestCode() {
    InferenceFunction conwaylife = inferConwaylife;
    // handle every distinct interesting case
    for (int nw = 0; nw < 2; ++nw)
    for (int nc = 0; nc < 2; ++nc)
    for (int ne = 0; ne < 2; ++ne)
    for (int cw = 0; cw < 2; ++cw)
    for (int cc = 0; cc < 4; ++cc) // for the center cell, also consider the next state
    for (int ce = 0; ce < 2; ++ce) {
        auto popSet = conwaylife(2, nw, nc, ne, cw, cc, ce);
        auto [pop0, pop1, pop2, pop3] = popSet.destructure();
        std::cout
            << "EXPECT_EQ("
                << "conwaylife("
                    << 2 << ", "
                    << nw << ", " << nc << ", " << ne << ", "
                    << cw << ", " << cc << ", " << ce << ")"
                << ", "
                << "PopSet("
                    << 2 << ", "
                    << pop0 << ", "
                    << pop1 << ", "
                    << pop2 << ", "
                    << pop3 << ")"
                << ");\n";
    }
}

int main() {
    generateConwaylifeInferenceTestCode();
    return 0;
}
