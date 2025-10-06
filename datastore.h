#ifndef DATASTORE_H
#define DATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"

/**
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 *
 * DO NOT EDIT
 */


class DataStore {
public:
    virtual ~DataStore() { }

    /**
     * Adds a product to the data store
     */
    virtual void addProduct(Product* p) = 0;

    /**
     * Adds a user to the data store
     */
    virtual void addUser(User* u) = 0;

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type) = 0;

    /**
     * Reproduce the database file from the current Products and User values
     */
    virtual void dump(std::ostream& ofile) = 0;


};

// Implement a derived DataStore class called MyDataStore in mydatastore.h and mydatastore.cpp. It is here that you will implement the core functionality of your program: searching, adding products and users, saving the database, etc. (For search you can use the setIntersection and setUnion) functions in util.h. This class is likely where you should store products and users in some fashion. Again we recommend compiling this file separately as well after you write the core functionality. You may need to add to it or modify it later as you work through other design aspects but make sure it can compile now even just using empty “dummy” function implementations. This derived class may define non-virtual functions to do other specific commands that the menu supports. It might be a good idea to have one member function in this class that corresponds to and performs each command from the menu options. You should not modify datastore.h.


class MyDataStore : public DataStore {
    public:
         void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
        void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
        std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
         void dump(std::ostream& ofile);

        //iterates thru set of storeUsers to find a user given their username
        User* findUser(std::string username) const;

        void addtoUsersCart(std::string username, std::vector<Product*>& lastSearch, int index);
        void dumpUserCart(std::string username, std::ostream& os) const;
        void buyUserCart(std::string username);

    private:
        std::set<Product*> storeProducts;
        std::set<User*> storeUsers;
        std::map<std::string, std::set<Product*>> keyMap;

};

#endif
