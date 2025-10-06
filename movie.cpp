#include "movie.h"
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
Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating):   Product(category, name, price, qty) 
{

    genre_ = genre;
    rating_ = rating;
    // convToLower(genre_);
}



    //Returns the appropriate keywords that this product should be associated with
std::set<std::string> Movie::keywords() const {
    //declare a set, we'll use the one returned by parseStringToWords() with the product name as an arg
    //break down the title into key words lower case for case insensitive search
    std::set<std::string> searchTerms = parseStringToWords(convToLower(getName()));


    //insert extra data (genre) into the key word set, lower case for case insensitive search
    std::string genreLowerCase = convToLower(genre_);
    searchTerms.insert(genreLowerCase);

    //return the set

    return searchTerms;
}

        // return name, price, quantity, categoryy, genre, rating
std::string Movie::displayString() const{
    /*
    <name>
    Genre: <genre> Rating: <rating>
    <price> <quantity> left.
    
    */
    std::string retString;

    retString.append(getName());
    retString.push_back('\n');
    retString.append("Genre: ");
    retString.append(getGenre());
    retString.push_back(' ');
    retString.append("Rating: ");
    retString.append(getRating());
    retString.push_back('\n');
    retString.append(std::to_string(getPrice()));
    retString.push_back(' ');
    retString.append(std::to_string(getQty()));
    retString.push_back(' ');
    retString.append("left.");


    return retString;
}

        // Outputs the product info in the database format
void Movie::dump(std::ostream& os) const{
    os << "movie" << "\n" 
        << getName() << "\n" 
        << getPrice() << "\n" 
        << getQty() << "\n"
        << getGenre() << "\n"
        << getRating() << "\n";  

}

std::string Movie::getRating() const{
    return rating_;
}

std::string Movie::getGenre() const{
    return genre_;
}



