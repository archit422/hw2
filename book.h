#include "product.h"
#include <string>
#include <set>
#include <ostream>



class Book: public Product{

  public:

  Book(
    const std::string& name,
    double price,
    int qty,
    const std::string& isbn,
    const std::string& author);

    std::set<std::string> keywords() const; 
    std::string displayString() const override; 
    void dump(std::ostream& os) const; 

  private:
    std::string isbn_;
    std::string author_;
};
