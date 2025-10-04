#include "product.h"
#include <string>
#include <set>
#include <ostream>


class Movie: public Product{

  public:

  Movie(
    const std::string& name,
    double price,
    int qty,
    const std::string& genre,
    const std::string& rating);

    std::set<std::string> keywords() const; 
    std::string displayString() const override; 
    void dump(std::ostream& os) const; 

  private:
    std::string genre_;
    std::string rating_;
};
