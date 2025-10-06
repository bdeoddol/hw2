#ifndef CLOTHING_H
#define CLOTHING_H
#include <set>
#include "product.h"


        // a product has a
        //     name
        //     price
        //     quantity
        //     category (string)

        // a Clothing has a 
        //     Size
        //     Brand
class Clothing : public Product
{
    public:
        Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
        // ~Clothing();

        // Returns the appropriate keywords that this product should be associated with
        std::set<std::string> keywords() const;
        // return name, price, quantity, categoryy, ISBN, Author
        std::string displayString() const;
        // Outputs the product info in the database format
        void dump(std::ostream& os) const;

        std::string getSize() const;
        std::string getBrand() const;

    private:
    std::string size_;
    std::string brand_;

}; 



#endif