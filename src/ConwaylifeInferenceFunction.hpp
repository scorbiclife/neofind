#ifndef NEOFIND_CONWAYLIFEINFERENCEFUNCTION
#define NEOFIND_CONWAYLIFEINFERENCEFUNCTION

#include "common.hpp"

/**
 * Inference function for conway's game of life.
 */
inline PopSet inferConwaylife(
        int period,
        Cell nw, Cell nc, Cell ne,
        Cell cw, Cell cc, Cell ce) {
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
    return PopSet(period, canHavePopZero, canHavePopOne, canHavePopTwo, canHavePopThree);
}

#endif
