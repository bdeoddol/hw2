#include "clothing.h"
#include "util.h"
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
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand): Product(category, name, price, qty) 
{
    
    size_ = size;
    brand_ = brand;
    // convToLower(brand_);

}



    //Returns the appropriate keywords that this product should be associated with
std::set<std::string> Clothing::keywords() const {
    //declare a set, we'll use the one returned by parseStringToWords() with the product name as an arg
    //break down the title into key words case insensitive
    std::set<std::string> searchTerms = parseStringToWords(convToLower(getName()));


    //insert extra data (brand) into the key word set
    //BRANDS CAN INCLUDE PUNCTUATION, changed implementation, and to lowercase for case insensitive search
    std::string brandLowerCase = convToLower(brand_);
    std::set<std::string> brandKeywords = parseStringToWords(brandLowerCase);
    std::set<std::string>::iterator t1;

    for(t1 = brandKeywords.begin(); t1 != brandKeywords.end(); ++t1){
        searchTerms.insert(*t1);
    }   

    //return the set
    return searchTerms;
}

        // return name, price, quantity, categoryy, size, brand
std::string Clothing::displayString() const{
    /*
    <name>
    Size: <size> Brand: <brand>
    <price> <quantity> left.
    
    */
    std::string retString;

    retString.append(getName());
    retString.push_back('\n');
    retString.append("Size: ");
    retString.append(getSize());
    retString.push_back(' ');
    retString.append("Brand: ");
    retString.append(getBrand());
    retString.push_back('\n');
    retString.append(std::to_string(getPrice()));
    retString.push_back(' ');
    retString.append(std::to_string(getQty()));
    retString.push_back(' ');
    retString.append("left.");


    return retString;
}

        // Outputs the product info in the database format
void Clothing::dump(std::ostream& os) const{
    os << "clothing" << "\n" 
        << getName() << "\n" 
        << getPrice() << "\n" 
        << getQty() << "\n"
        << size_ << "\n"
        << brand_ << "\n"; 

}

std::string Clothing::getSize() const{
    return size_;
}

std::string Clothing::getBrand() const{
    return brand_;
}

