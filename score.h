#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

/**
 * To store the scores, we will have a simple plaintext file on the user's
 * computer called scores.txt, and it will store one name and the
 * corresponding score. (To support the same name having multiple scores,
 * we will use multimaps to construct the high score map from the
 * plaintext file. For example, the file could contain something like
 * this:
 * 
 * Tirthankar 10
 * Tirthankar 7
 * Tirthankar 5
 * Justin 3
 * Justin 1
 * 
 * Though it may not be very efficient, I've decided to construct the vector
 * from the file every time the game is played and a high score is made.
 */

class Score {
    using ScorePair = std::pair<std::string, int>;
    using ScoreVector = std::vector<ScorePair>;

    ScoreVector vector;

    bool exists_test(const std::string &filename) {
        //This will be used internally to check if "scores.txt" exists. If it
        //does, we'll read from that, and if it doesn't, we'll make that file
        //and store data there.        
        std::ifstream f(filename.c_str());
        return f.good();
    }

    ScorePair extract_data(std::string str) {
        //Takes a string with two pieces of data, data1 and data2 that are
        //separated by a space and returns the std::pair {data1, data2}
        std::string data1, data2;

        std::size_t index = str.find(' ');
        data1 = str.substr(0, index);
        data2 = str.substr(index + 1);

        ScorePair p{data1, std::stoi(data2)};
        return p;
    }

    public:
        Score() {
            vector = ScoreVector();
        }

        std::size_t size() {
            //This function is needed because vector is a private member, so
            //vector.size() cannot be called from outside the class.
            return vector.size();
        }

        void trunc() {
            //Truncates the vector to a max. size of 10 because we will
            //only store the top 10 high scores in the text file.
            vector.resize(10);
        }

        void display_high_scores(std::string filename);

        void insert(std::string name, int score);
        bool readFile(std::string filename);
        void writeFile(std::string filename);

        std::string get_name(int index) {
            return std::get<0>(vector.at(index));

        }

        int get_score(int index) {
            return std::get<1>(vector.at(index));
        }
};