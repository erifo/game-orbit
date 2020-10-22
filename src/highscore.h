#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>

class Highscore
{
    private:
    /*! Private variables. 
        Contains datatypes.
    */
        std::string filename;
        std::string level_name;
        int current_highscore;

    public:
    /*! Public function variables. 
	    Constructor for highscore and getters and setters for highscore class. 
	*/
        Highscore();
        void load_highscore();
        void save_highscore(int new_score);
        
    /*! Getters. */
        int get_highscore();

    /*! Setters. */
        void set_filename(std::string input);
        void set_level_name(std::string input);
};

#endif