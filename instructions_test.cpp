#include <simplecpp>
#include "lasso.h"
#include "instructions.h"


main_program {
    initCanvas("Lasso", WINDOW_X, WINDOW_Y);
    instructions();
    wait(1);
}