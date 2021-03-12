#include <iostream>
#include "score.h"

int main() {
    Score sc;

    std::string filename = "test_scores.txt";
    
    sc.display_high_scores(filename);

    std::cout << std::endl;
    
    sc.insert("Abel", 9000);

    for (std::size_t i = 0; i < sc.size(); i++) {
        std::cout << sc.get_name(i) << " " << sc.get_score(i) << std::endl;
    }

    std::cout << std::endl;

    sc.display_high_scores(filename);
}