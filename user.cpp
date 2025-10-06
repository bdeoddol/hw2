#include "user.h"
#include "product.h"
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1)
{

}
User::User(std::string name, double balance, int type) :
    name_(name), balance_(balance), type_(type)
{

}

User::~User()
{

}


std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
    os << name_ << " "  << balance_ << " " << type_ << endl;
}

void User::addToCart(Product* p){
    cart_.push_back(p);

    return;
}

void User::dumpCartContent(std::ostream& os){
    for(int i = 0;  i < static_cast<int>(cart_.size()); i++){
        os << "Item " << i << endl;
        os << cart_[i]->displayString() << "\n";
    }
    return;
}

void User::buyCart(){
    std::deque<Product*>::iterator t1;
    for(int i = 0; i < static_cast<int>(cart_.size()); i++){
        if((cart_[i]->getPrice() <= getBalance()) && (cart_[i]->getQty() > 0)){
            cart_[i]->subtractQty(1);
            deductAmount(cart_[i]->getPrice());
            cart_.erase(cart_.begin() + i); //erase at i-th position of cart from the beginning
            i--; //because we erased in a DEQUE, everything is shifted over 1 left so we have to bring the i-tracker bacck 1 so it moves on to the correct next item.
        }
        
    }
}
