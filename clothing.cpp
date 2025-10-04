#include "clothing.h"
#include "hw2Util.h"
#include <set>

/*
    a product has a
        name
        price
        quantity
        category (string)

        a book has a
            ISBN
            Author

        a movie has a 
            Genre
            Rating
        a clothing has a
            size
            brand


Books: the words in the author’s name should be searchable keywords as well as the book’s ISBN number
Clothing: the words in the brand should be searchable keywords
Movie: the movie’s genre should be a searchable keyword

*/
// Product(const std::string category, const std::string name, double price, int qty);
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand):Product(category, name, price, qty) 
{
    size_ = size;
    brand_ = brand;

}



    //Returns the appropriate keywords that this product should be associated with
std::set<std::string> Clothing::keywords() const {
    //declare a set, we'll use the one returned by parseStringToWords() with the product name as an arg
    //break down the title into key words
    std::set<std::string> searchTerms = parseStringToWords(getName());


    //insert extra data (brand) into the key word set
    //BRANDS CAN INCLUDE PUNCTUATION, changed implementation
    std::set<std::string> brandKeywords = parseStringToWords(brand_);
    std::set<std::string>::iterator t1;

    for(t1 = brandKeywords.begin(); t1 != brandKeywords.end(); ++t1){
        searchTerms.insert(*t1);
    }   

    //return the set
    return searchTerms;
}

        // return name, price, quantity, categoryy, size, brand
std::string Clothing::displayString() const{
        //declare a new set
    std::set<std::string> searchTerms = this->keywords();
        //declare an iterator for a set
    std::set<std::string>::iterator t1;
        //declare string to be returned
    std::string retString;


        //use iterator to iterate thru set of keywords found by keywords()
    for(std::set<std::string>::iterator t1 = searchTerms.begin(); t1 != searchTerms.end(); ++t1){
        //for each term in the set, append keyWord to string
        retString.append(*t1);
        retString.push_back(' ');

    }

    return retString;
}

        // Outputs the product info in the database format
void Clothing::dump(std::ostream& os) const{
    os << "clothing" << "\n" 
        << getName() << "\n" 
        << getPrice() << "\n" 
        << getQty() << "\n"
        << size_ << "\n"
        << brand_ << "\n" << std::endl;  

}

