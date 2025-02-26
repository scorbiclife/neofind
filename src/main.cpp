#include <cinttypes>
#include <tuple>
#include <iostream>

/**
 * Each cell consists of bits that represent the state at each phase.
 */
using Cell = uint16_t;

/**
 * The possible populations of the following bottom three neighbors.
 *  xx xx xx
 *  xx    xx
 *  sw sc se
 *
 * If the population could be zero at a specific phase,
 * `(std::get<0>(populations) >> phase) & 0x1` should be on.
 * Same for the other possible values.
 */
using TripletPopulationSet = std::tuple<Cell, Cell, Cell, Cell>;

/**
 * Given the a cell (cc) and its top and middle five neighbors,
 * calculate the possible populations of the bottom three neighbors.
 */
using InferenceFunction =
    std::function<TripletPopulationSet (
            Cell nw, Cell nc, Cell ne,
            Cell cw, Cell cc, Cell ce,
            int period)>;

/**
 * Inference function for conway's game of life.
 */
inline TripletPopulationSet inferConwaylife(
        Cell nw, Cell nc, Cell ne,
        Cell cw, Cell cc, Cell ce,
        int period) {
    // First, get the population of the following five neighbors:
    //   nw nc ne
    //   cw    ce
    //   xx xx xx
    //
    // We calculate each bit of the sum using bitwise manipulation.
    
    // ones place
    Cell s1 = nw ^ nc ^ ne ^ cw ^ ce;

    // twos place
    // CGoL-specific optimization:
    // The following calculates whether at least two of the five neighbors are on.
    // This gives wrong results when the cell has >= 4 neighbors,
    // but it doesn't matter because the next state is always off due to overpopulation,
    // so it doesn't affect the possible sums of the three cells in the south.
    Cell s2 =
        ((nw | nc | ne) & (cw | ce))
        | (nw & nc)
        | (nw & ne)
        | (nc & ne)
        | (cw & ce);

    // fours place
    // This calculates whether at least four of the five neighbors are on.
    Cell s4 =
        (nw & nc & ne & (cw | ce))
        | (nw & (nc | ne) & cw & ce)
        | (nc & ne & cw & ce);

    // Second, given the population of the aformentioned five neighbors
    // and the next phase of the center cell, 
    // calculate the possible populations of the southmost three cells.
    // The following magic formulas are derived manually from a Karnaugh map
    Cell nextPhase = (cc >> 1) | ((cc & 0x1) << (period - 1));
    Cell periodMask = (1 << period) - 1;
    Cell canHavePopZero = ((s4 | (~s2) | (~s1 & ~cc)) ^ nextPhase) & periodMask;
    Cell canHavePopOne = ((s4 | ~(s1 ^ s2) | (s1 & ~cc)) ^ nextPhase) & periodMask;
    Cell canHavePopTwo = ((s4 | s2 | (~s1 & ~cc)) ^ nextPhase) & periodMask;
    Cell canHavePopThree = ((s4 | s2 | s1) ^ nextPhase) & periodMask;
    return std::make_tuple(canHavePopZero, canHavePopOne, canHavePopTwo, canHavePopThree);
}

/**
 * TODO:
 * convert this to a test that compares the results with
 * a more straightforward but slower algorithm.
 *
 * I prefer making things easier to test,
 * but magic black box bit manipulations like this are literally
 * the opposite of "easier to test".
 * The best thing I could come up with was printing out every case
 * and skimming manually.
 */
void debugConwaylifeInference() {
    InferenceFunction conwaylife = inferConwaylife;
    // handle every distinct interesting case
    for (int nw = 0; nw < 2; ++nw)
    for (int nc = 0; nc < 2; ++nc)
    for (int ne = 0; ne < 2; ++ne)
    for (int cw = 0; cw < 2; ++cw)
    for (int cc = 0; cc < 4; ++cc) // for the center cell, also consider the next state
    for (int ce = 0; ce < 2; ++ce) {
        auto [pop0, pop1, pop2, pop3] = conwaylife(nw, nc, ne, cw, cc, ce, 2);
        std::cout
            << nw << nc << ne << '\n'
            << cw << cc << ce << '\n'
            << (pop0 & 1) << (pop1 & 1) << (pop2 & 1) << (pop3 & 1) << "\n\n";
    }
}

int main() {
    return 0;
}


