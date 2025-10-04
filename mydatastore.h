  //searching, adding products and users, 
 //saving the database
#include "datastore.h"
#include "product.h"
#include "user.h"
#include <vector>
#include <string>
#include <set>
#include <ostream>
#include <deque>
#include <unordered_map>


class MyDataStore: public DataStore
{
  public:

  //add products
  //add users 
  //search product

  void addProduct(Product* p) override;
  void addUser(User* u) override;
  std::vector<Product*> search(std::vector<std::string>& search_terms,int type)override ;
  void dump(std::ostream&) override;
  void add_to_cart(const std::string& uname,std::size_t hIndex);
  void view_cart(const std::string& uname, std::ostream& os) const;
  void buy_cart(const std::string& uname);
  void setPrevResults(const std::vector<Product*>& hits);
  virtual ~MyDataStore();
  
  private:
  std::vector<Product*> products_;
  std::vector<User*> users_;
  std::unordered_map<std::string, std::set<Product*>> index_;
  std::unordered_map<std::string, std::deque<Product*>> carts_;
  std::unordered_map<std::string, User*> users_by_name;

  std::vector<Product*> prevResults_;
};