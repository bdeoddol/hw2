#include "book.h"
#include "util.h"
#include <set>
#include <string>

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

Book::Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string Author):      Product(category, name, price, qty) 
{
    ISBN_ = ISBN;
    author_ = Author;
    // convToLower(author_);
}



    //Returns the appropriate keywords that this product should be associated with
std::set<std::string> Book::keywords() const {
    //declare a set, we'll use the one returned by parseStringToWords() with the product name as an arg
    //break down the title into key words, lower case for case insensitive search
    std::set<std::string> searchTerms = parseStringToWords(convToLower(getName()));


    //insert extra data (ISBN, Author) into the key word set
    searchTerms.insert(ISBN_);
    //even authors can be made up of multiple terms as well
    std::string authorlowerCase = convToLower(author_);
    std::set<std::string> authorKeywords = parseStringToWords(authorlowerCase);
    std::set<std::string>::iterator t1;

    for(t1 = authorKeywords.begin(); t1 != authorKeywords.end(); ++t1){
        searchTerms.insert(*t1);
    }


    //return the set

    return searchTerms;
}

        // return name, price, quantity, categoryy, ISBN, Author
std::string Book::displayString() const{
    /*
    <name>
    Author: <author> ISBN: <isbn>
    <price> <quantity> left.
    
    */
    std::string retString;

    retString.append(getName());
    retString.push_back('\n');
    retString.append("Author: ");
    retString.append(getAuthor());
    retString.push_back(' ');
    retString.append("ISBN: ");
    retString.append(getISBN());
    retString.push_back('\n');
    retString.append(std::to_string(getPrice()));
    retString.push_back(' ');
    retString.append(std::to_string(getQty()));
    retString.push_back(' ');
    retString.append("left.");


    return retString;
}

        // Outputs the product info in the database format
void Book::dump(std::ostream& os) const{
    os << "book" << "\n" 
        << getName() << "\n" 
        << getPrice() << "\n" 
        << getQty() << "\n"
        << ISBN_ << "\n"
        << author_ << "\n";

}

std::string Book::getISBN() const{
    return ISBN_;
}

std::string Book::getAuthor() const{
    return author_;
}
