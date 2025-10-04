#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>


 
Book::Book(const std::string& name,
              double price, 
              int qty,
              const std::string& isbn,
              const std::string& author
            ): Product("book", name, price, qty), 
            isbn_(isbn),
            author_(author)
{
}


std::set<std::string> Book::keywords() const
{
  std::set<std::string> result; 

  std::set<std::string> s1 = parseStringToWords(convToLower(name_));
  std::set<std::string> s2 = parseStringToWords(convToLower(author_));

  result = setUnion(s1,s2);
  result.insert(convToLower(isbn_));

  return result;
}



void Book::dump(std::ostream& os) const{
  Product::dump(os);
  os<< isbn_ <<"\n" << author_ << "\n";
}




std::string Book::displayString() const
{

  std::ostringstream oss;
  oss<<getName() <<"\n"
    <<"Author: "<< author_ <<" ISBN: "<<isbn_ <<"\n"
    << std::fixed<< std::setprecision(2) 
    << getPrice() << " "<<getQty()<< " left.";
  return oss.str();
} 

