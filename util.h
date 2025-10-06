#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{ 
        //method was dervied from https://en.cppreference.com/w/cpp/algorithm/set_intersection.html
    /*
    ex:
    A = {1, 2, 3}, 
    B = {2, 3, 4}

    A = {1, 2},
    B = {3, 4}
    
    A = {1, 2},
    B = {1, 2, 3, 4}
    */

    std::set<T> Intersect;
    //declare two iterators, for s1 and s2
    typename std::set<T>::iterator t1 = s1.begin();
    typename std::set<T>::iterator t2 = s2.begin(); 

    while(t1 != s1.end() && t2 != s2.end()){
        if(*t1 == *t2){
            //if elements found in both set, insert and increment
            Intersect.insert(*t1);
            ++t1;
            ++t2;
        }
        //always increment the smaller of the 2 elements compared between 2 sets. 
        else if(*t1 < *t2){
            ++t1;
        }
        else{
            ++t2;
        }
    }
    return Intersect;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    //method derived from http://en.cppreference.com/w/cpp/algorithm/set_union.html
    std::set<T> Union;

    //declare two iterators, for s1 and s2
    typename std::set<T>::iterator t1 = s1.begin();
    typename std::set<T>::iterator t2 = s2.begin(); 

    while(t1 != s1.end() && t2 != s2.end()){
        //given two sets. I will start by comparing which set's initial element is smaller and increment while comparing with the initial element of the 2nd set. When i find that the 2nd set element is smaller, ill begin incrementing the 2nd set.

        //Basically only insert element and incremenet on the set has the smaller element when comparing.
        if(*t1 < *t2){
            Union.insert(*t1);
            ++t1;
        }
        else if(*t2 < *t1){
            Union.insert(*t2);
            ++t2;
        }
        else if( *t1 == *t2){
            Union.insert(*t1);
            ++t1;
            ++t2;
        }
    }

    while(t1 != s1.end()){
        //if s2 is finished but s1 still hasn't reached the end, dump the rest
        Union.insert(*t1);
        ++t1;
    }

    while(t2 != s2.end()){
        //if s1 is finished but s2 still hasn't reached the end, dump the rest
        Union.insert(*t2);
        ++t2;
    }

    return Union;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
