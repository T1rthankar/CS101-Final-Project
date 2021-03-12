#include "score.h"

bool Score::readFile(std::string filename) {
    if (exists_test(filename)) {
        std::ifstream f(filename);
        
        std::string data; //We'll put the contents of the file in
        //here, line by line, and then store the username and
        //high score in name and score.
        std::string name;

        while (std::getline(f, data)) {
            vector.push_back(extract_data(data));
        }

        f.close();
        return true;
    } else {
        return false;
    }
}

void Score::insert(std::string name, int score) {
    ScorePair p{name, score};
    
    vector.push_back(p);

    //Using a lambda function as the Comparator function
    std::stable_sort(vector.begin(), vector.end(),
        [](const ScorePair &left, const ScorePair &right) {
            return left.second > right.second;
        }
    );
    /**
     * The idea here is that if use a stable sort, then people with the same
     * score and names will be preserved in the original order. By appending
     * the latest score at the very end of the vector, we are giving it the
     * lowest priority in the stable sort (given that the score is low enough
     * for that to matter.)
    */

    //We resize the vector (if necessary)
    if (vector.size() > 10) {
        trunc();
    }
}

void Score::writeFile(std::string filename) {
    std::ofstream f(filename);
    //Even though it would make more sense to add to the file rather than
    //flushing it and rewriting it, the performance penalty won't be too
    //big because we just store 10 high scores.
    for (std::size_t i = 0; i < vector.size(); i++) {
        f << get_name(i) << " " << get_score(i) << std::endl;
    }

    f.close();
}

void Score::display_high_scores(std::string filename) {
    if (!exists_test(filename)) {
        std::cout << "No high scores have been logged yet.\n" << std::endl;
        std::cout << "Your score has been recorded. You are Rank 1 in the list of recorded high scores." << std::endl;
    } else {
        if (vector.size() == 0) {
            //We need to do it like this to prevent multiple calls to the function from adding the
            //data from the text file multiple times.
            readFile(filename);
        }
        
        std::size_t max_name_length = get_name(0).size();
        for (std::size_t i = 0; i < vector.size(); i++) {
            if (get_name(i).size() > max_name_length) {
                max_name_length = get_name(i).size();
            }
        }
        //This is to find the maximum name length in the list of stored high scores.
        
        std::cout << "No.\t" << std::setw(max_name_length) << std::left << "Name" << "\tScore" << std::endl;
        for (std::size_t i = 0; i < vector.size(); i++) {
            std::cout << i + 1 << ".\t" << std::setw(max_name_length) << std::left << get_name(i) << "\t" << get_score(i) << std::endl;
        }
    }
}