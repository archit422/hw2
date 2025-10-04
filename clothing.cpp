#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iomanip>


 
Clothing::Clothing(const std::string& name,
              double price, 
              int qty,const std::string& size,
              const std::string& brand
              
            ): Product("clothing", name, price, qty), 
            brand_(brand),size_(size)
{
}


std::set<std::string> Clothing::keywords() const
{
  std::set<std::string> result; 

  std::set<std::string> s1 = parseStringToWords(convToLower(name_));
  std::set<std::string> s2 = parseStringToWords(convToLower(brand_));

  result = setUnion(s1,s2);

  return result;
}


void Clothing::dump(std::ostream& os) const{
  Product::dump(os);
  os<< size_ <<"\n" 
    << brand_ << "\n";
}



std::string Clothing::displayString() const
{

  std::ostringstream oss;
  oss<<getName() <<"\n"
    <<"Size: "<< size_ << " Brand: "<<brand_ <<"\n"
    << std::fixed<< std::setprecision(2) 
    << getPrice() << " "<<getQty()<< " left.";
  return oss.str();
} 

