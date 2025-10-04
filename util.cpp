#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  
    std::set<std::string>subStrings; //declare a set of substrings
    
    stringstream parseWords(rawWords);
    std::string keyWord;
    std::string buildWord;
    
    //ex: Men's Fitted Shirt -> Men Fitted Shirt
    //ex: Data Abstraction & Problem Solving with C++ -? Data Abstraction Problem Solving with C++
    //ex: J. Crew

    while(parseWords >> keyWord){
         
        if(keyWord.size() >= 2){ //if the keyword is greater than or equal to 2, process each char in keyword for punc
            for(int i = 0; i < static_cast<int>(keyWord.size()); i++){ //build the keyword, char by char, process each char for punc
                if(ispunct(keyWord[i])){ 
                    //if punc found, check if built keyword is >=2 chars, if true, insert into set, clear string to build the next portion of keyWord.
                    //if not found, keep building keyword. 
                    if(buildWord.size() >= 2){
                        subStrings.insert(buildWord);
                        buildWord.clear();
                    }
                    else{
                        buildWord.clear();
                    }
                }

                else{
                    buildWord.push_back(keyWord[i]);
                }

            }

            if(buildWord.size() >= 2){
                //if no punc found, or reach end of keyWord without punc. check if the curr built word >=2, insert if true
                subStrings.insert(buildWord);
            }

        }
    }

    return subStrings;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
