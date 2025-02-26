#ifndef NEOFIND_COMMON
#define NEOFIND_COMMON

#include <cinttypes>
#include <tuple>
#include <functional>

/**
 * Each cell consists of bits that represent the state at each phase.
 */
using Cell = uint16_t;


/**
 * A data structure that can contain a set of populations of
 * at most three neighbors.
 *
 * We use this, for example, to save the possible populations
 * of the southmost three neighbors.
 */
class PopSet {

private:
    Cell canHavePop0;
    Cell canHavePop1;
    Cell canHavePop2;
    Cell canHavePop3;

public:
    PopSet(int period __attribute__((unused)), Cell pop0, Cell pop1, Cell pop2, Cell pop3) {
        canHavePop0 = pop0;
        canHavePop1 = pop1;
        canHavePop2 = pop2;
        canHavePop3 = pop3;
    }

    std::tuple<Cell, Cell, Cell, Cell> destructure() {
        return std::make_tuple(canHavePop0, canHavePop1, canHavePop2, canHavePop3);
    }

    bool operator==(PopSet other) const {
        return canHavePop0 == other.canHavePop0
            && canHavePop1 == other.canHavePop1
            && canHavePop2 == other.canHavePop2
            && canHavePop3 == other.canHavePop3;
    }
};


/**
 * Given the a cell (cc) and its top and middle five neighbors,
 * calculate the possible populations of the bottom three neighbors.
 */
using InferenceFunction =
    std::function<
        PopSet (
                int period,
                Cell nw, Cell nc, Cell ne,
                Cell cw, Cell cc, Cell ce)>;

#endif

