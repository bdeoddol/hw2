#ifndef MOVIE_H
#define MOVIE_H
#include <set>
#include "product.h"


        // a product has a
        //     name
        //     price
        //     quantity
        //     category (string)

        // a movie has a 
        //     Genre
        //     Rating
class Movie : public Product
{
    public:
        Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
        // ~Movie();

        // Returns the appropriate keywords that this product should be associated with
        std::set<std::string> keywords() const;
        // return name, price, quantity, categoryy, ISBN, Author
        std::string displayString() const;
        // Outputs the product info in the database format
        void dump(std::ostream& os) const;

        std::string getRating() const;
        std::string getGenre() const;


    private:
    std::string rating_;
    std::string genre_;

}; 



#endif