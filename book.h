#ifndef BOOK_H
#define BOOK_H
#include <set>
#include "product.h"


    // a product has a
    //     name
    //     price
    //     quantity
    //     category (string)

    //     a book has a
    //         ISBN
    //         Author

class Book : public Product
{
    public:
        Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string Author);
        // ~Book();

        // Returns the appropriate keywords that this product should be associated with
        std::set<std::string> keywords() const;
        // return name, price, quantity, categoryy, ISBN, Author
        std::string displayString() const;
        // Outputs the product info in the database format
        void dump(std::ostream& os) const;

        std::string getISBN() const;
        std::string getAuthor() const;

    private:
    std::string ISBN_;
    std::string author_;

}; 



#endif