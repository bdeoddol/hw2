    #include "datastore.h"
    #include "util.h"
    #include <set>
    #include <map>


    MyDataStore::~MyDataStore(){
        //delete all allocated product elements in storeProducts
      for(std::set<Product*>::iterator t1 = storeProducts.begin(); t1 != storeProducts.end(); ++t1){
        delete (*t1);
      }
      //delete all allocated user elements in storeUsers
      for(std::set<User*>::iterator t2 = storeUsers.begin(); t2 != storeUsers.end(); ++t2){
        delete (*t2);
      }

      
    }


    void MyDataStore::addProduct(Product* p) {
        storeProducts.insert(p);

        std::set<std::string> keyWords = p->keywords();
        
        //as we add products, we add all keywords of the product to a map, this keyword will be mapped to a set of all products that use this keyword. 
        //we must check for two cases, the keyword doesn't exist and we must make a new addition
        //or the keyword exists, where we will add the product to the accompany set of products
        for(std::set<std::string>::iterator t1 = keyWords.begin(); t1 != keyWords.end(); ++t1){
            //for each keyword found in the  product, we add the product to them
            std::map<std::string, std::set<Product*>>::iterator t2 = keyMap.find(*t1);
            if(t2 != keyMap.end()){
            //if the keyword in the map already exists, add the product into the set of products that map to keyword
                t2->second.insert(p);
            }
            else{
             //if keyword does not already exist, create a index for that keyword and map the product in a product set to that keyword

                std::set<Product*> newProdSet;
                newProdSet.insert(p);
                keyMap.insert(std::make_pair(*t1, newProdSet));
            }
        }
        return;
    }

    void MyDataStore::addUser(User* u) {
        storeUsers.insert(u);

        return;
    }

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
        std::map<std::string, std::set<Product*>>::iterator t1;
        std::set<Product*>::iterator t2;
        std::vector<Product*> retVec;
        std::set<Product*> firstSet; //this is the initial set we use to start us off in both search types
        if(type == 0){
            //AND must include all hits that contain ALL search terms
            //To find a common set of products shared across all terms, i would need an initial set to work with. I'll loop thru the terms and check if they exist on the map of all potential keywords. Upon the evaluateing any element of the vector, if i do not find a matching term, then it implies that this term cannot used in ALL search terms, simply break out func early if this is the case. If i DO find a matching term, i'll save the product set mapped to that term and move on to the next. 

            
            
            t1 = keyMap.find(terms[0]);
            if(t1 != keyMap.end()){
                firstSet = t1->second;
                //we start off our setIntersection with an initial set
                for(int i = 1; i < static_cast<int>(terms.size()); i++){
                    //for each term in vec, find intersection of remaining terms product sets
                    t1 = keyMap.find(convToLower(terms[i]));

                    if(t1 != keyMap.end()){
                        firstSet = setIntersection(firstSet,t1->second);
                    }
                    else{
                        //if t1 cannot find a term within the map of all possible keywords, it must mean that there exists a 
                        //term in the vector that does not match ANY product in the database, thus invalid search result
                        return retVec;
                    }
                }
            }
            else{
                //if we couldn't find a term in the map, break out early
                return retVec;
            }

            //by the end of the loop, firstSet will a set that has common product[s] shared across all sets of each term index.
            //we can store all these products within a vector by iterating
            for(t2 = firstSet.begin(); t2 != firstSet.end(); ++t2){
                retVec.push_back(*t2);
            }
            return retVec;
        }
        else if(type == 1){
            //OR must include ANY hits that contain the search terms
            //we can achieve this by looking up each term, then union all their product sets to find all products that contains any of the terms in the vec
            // to union a all valid product sets, i need to have an initial set to begin.so i would need to check with each term in the vector until i find one. If i don't find one at all, then it must mean that the terms given to me do not yield any valid search. If i do find one along the way, i'll save this product set that is paired with the term in the map, and begin performing setunion for the rest of the terms if they exist on the map

            bool foundInitialset = 0;
            for(int i = 0; i < static_cast<int>(terms.size()); i++){
                //search for a term in our map
                t1 = keyMap.find(convToLower(terms[i]));
                if(t1 != keyMap.end() && foundInitialset == false){
                    //if we found a term and this is our first found set
                    firstSet = t1->second;
                    foundInitialset = 1;
                }
                else if(t1 != keyMap.end() && foundInitialset == true){
                    //if we found a matching term to go with out initial/other set
                    firstSet = setUnion(firstSet, t1->second);
                }
            }

            if(foundInitialset == false){
                return retVec;
            }

            //convert set into a vector
            for(t2 = firstSet.begin(); t2 != firstSet.end(); ++t2){
                retVec.push_back(*t2);
            }
        }

      return retVec;
    }

    /**
     * Reproduce the database file from the current Products and User values
     */
    void MyDataStore::dump(std::ostream& ofile){
        //begin with products, then do users. 

        std::set<Product*>::iterator t1;
        std::set<User*>::iterator t2;
        ofile << "<products>" << std::endl;
        for(t1 = storeProducts.begin(); t1 != storeProducts.end(); ++t1){
            (*t1)->dump(ofile);
        }
        ofile << "</products>" << std::endl;
        ofile << "<users>" << std::endl;
        for(t2 = storeUsers.begin(); t2 != storeUsers.end(); ++t2){
            (*t2)->dump(ofile);
        }
        ofile << "</users>" << std::endl;

    }


User* MyDataStore::findUser(std::string username) const{
    std::set<User*>::iterator t1;
    User* retUser = nullptr;

    for(t1 = storeUsers.begin(); t1 != storeUsers.end(); ++t1){
        if (convToLower((*t1)->getName()) == convToLower(username)){
        //convert the User's name and username arg to lower case so that we compare lower-case to lower-case usernames only
            retUser = *t1;
            return retUser;
        }
    }

    //return null if user is never found
    return retUser;
}

void MyDataStore::addtoUsersCart(std::string username, std::vector<Product*>& lastSearch, int index){
    //we need to find the specific user given their username
    //provided indices are offset by one, subtract index arg by 1 to get zerobased indexing
    //search linearly

    User* userPtr;
    if(index-1 >= 0 && index-1 < static_cast<int>(lastSearch.size())){
        //ensure indexing is valid
        userPtr = findUser(username);
        if(userPtr != nullptr){
            userPtr->addToCart(lastSearch[index-1]);
            return;
        }
    }

    std::cout << "Invalid request" << std::endl;
    return;
}

void MyDataStore::dumpUserCart(std::string username, std::ostream& os) const{
    User* userPtr;
    userPtr = findUser(username);
    if(userPtr != nullptr){
        userPtr->dumpCartContent(os);
        return;
    }

    //user name was never found
    os << "Invalid username" << std::endl;
    return;
}

void MyDataStore::buyUserCart(std::string username){
    User* userPtr;
    userPtr = findUser(username);
    if(userPtr != nullptr){
        userPtr->buyCart();
        return;
    }

    std::cout << "Invalid username" << std::endl;
    return;
}