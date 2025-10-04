#include "product.h"
#include <string>
#include <set>
#include <ostream>


class Clothing: public Product{

  public:

  Clothing(
    const std::string& name,
    double price,
    int qty,
    const std::string& size,
    const std::string& brand
    );

    std::set<std::string> keywords() const; 
    std::string displayString() const override; 
    void dump(std::ostream& os) const; 

  private:
    std::string brand_;
    std::string size_;
};
