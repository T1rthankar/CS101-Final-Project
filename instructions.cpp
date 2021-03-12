#include <simplecpp>
#include "lasso.h"
#include "instructions.h"
//We need lasso.h for the preprocessor constants it defines.

void instructions() {
    int center_y = 90;
    
    Text t1(WINDOW_X / 2, center_y, "Welcome to the Lasso Game!");
    
    center_y += textHeight() + 15;
    Text t2(WINDOW_X / 2, center_y, "In this game, the objective is to catch as many coins as you can! (But beware");

    center_y += textHeight() + 15;
    Text t3(WINDOW_X / 2, center_y, "the bombs, because catching them makes you lose 1 point!)");

    center_y += textHeight() + 15;
    Text t13(WINDOW_X / 2, center_y, "The golden circles are coins, and the black circles are bombs.");
    
    center_y += textHeight() + 30;
    Text t4(WINDOW_X / 2, center_y, "Here are the controls:");

    center_y += textHeight() + 15;
    Text t5(WINDOW_X / 2, center_y, "t : throw the Lasso");

    center_y += textHeight() + 15;
    Text t6(WINDOW_X / 2, center_y, "y : yank the Lasso");

    center_y += textHeight() + 15;
    Text t7(WINDOW_X / 2, center_y, "l : loop the Lasso");

    center_y += textHeight() + 15;
    Text t8(WINDOW_X / 2, center_y, "q : quit the game (while in the game)");

    center_y += textHeight() + 30;
    Text t9(WINDOW_X / 2, center_y, "[ : rotate the Lasso counter-clockwise");

    center_y += textHeight() + 15;
    Text t10(WINDOW_X / 2, center_y, "] : rotate the Lasso clockwise");

    center_y += textHeight() + 15;
    Text t11(WINDOW_X / 2, center_y, "= : increase the speed of the Lasso");

    center_y += textHeight() + 15;
    Text t12(WINDOW_X / 2, center_y, "- : decrease the speed of the Lasso");

    center_y += textHeight() + 30;
    Text t14(WINDOW_X / 2, center_y, "Press s to start the game, or e to exit.");

    bool waiting = true;
    while (waiting) {
        XEvent e;

        bool pendingEv = checkEvent(e);
        if(pendingEv) {
            char c = charFromEvent(e);
            switch (c) {
                case 's':
                    waiting = false;
                    break;
                case 'e':
                    exit(0);
                default:
                    break;
            }
        }
    }
    return;
}