#include "mydatastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include <iostream>

void MyDataStore::addProduct(Product* p)
{
  products_.push_back(p);
  std::set<std::string> keywords = p->keywords();

  for(std::set<std::string>::iterator it = keywords.begin(); it!=keywords.end(); ++it)
  {
    index_[*it].insert(p);
  }
}

void MyDataStore::addUser(User* u)
{
  users_.push_back(u);

  std::string name = convToLower(u->getName());

  users_by_name[name] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& search_terms,int type) 
{


   prevResults_.clear();

  if (search_terms.empty())
  {
    return  prevResults_;
  }


  std::vector<std::string> lowered_terms;
  std::set<std::string> viewed;

  for(std::vector<std::string>::iterator it = search_terms.begin(); it!=search_terms.end(); ++it)
  {
    // lowered_term = convToLower(*it);
    // if(lowered_term not in viewed)
    // {
    //   add lowered_term to viewed
    //   add lowered_term to lowered_terms
    // }

    std::string lowered_term = convToLower(*it);
    if(viewed.find(lowered_term) == viewed.end())
    {
      viewed.insert(lowered_term);
      lowered_terms.push_back(lowered_term);
    }
  }


  std::set<Product*> result;

  if(type == 0)
  {
    bool initialized = false;  
   

    for(std::vector<std::string>::iterator it = lowered_terms.begin(); it!=lowered_terms.end(); ++it)
    {
      std::set<Product*> product_posts;
      std::unordered_map<std::string, std::set<Product*>>::const_iterator prod_it = index_.find(*it);

      if(prod_it != index_.end())
      { product_posts = prod_it->second;}
      else 
      { product_posts = std::set<Product*>();}

      if(initialized == false)
      {
        result = product_posts;
        initialized = true;
      }
      else
      {
        result = setIntersection(result, product_posts);
      }

      if(result.empty())
      {
        break;
      }
    }
  }
  else
  {
    for(std::vector<std::string>::iterator it = lowered_terms.begin(); it!=lowered_terms.end(); ++it)
    {
      std::set<Product*> product_posts;
      std::unordered_map<std::string, std::set<Product*>>::const_iterator prod_it = index_.find(*it);

      if(prod_it != index_.end())
      { product_posts = prod_it->second;}
      else 
      { product_posts = std::set<Product*>();}


      result = setUnion(result, product_posts);

    }
  }

  std::vector<Product*> hits; 

  for(std::vector<Product*>::iterator it = products_.begin(); it!=products_.end(); ++it)
    { 
      if(result.find(*it) != result.end())
      {
         hits.push_back(*it);
      }
    }

   prevResults_ = hits; 
  return  prevResults_;
}

void MyDataStore::add_to_cart(const std::string& uname,std::size_t hIndex)
{
  std::string name_key = convToLower(uname);

  if(users_by_name.find(name_key) == users_by_name.end())
  {
    std::cout<< "Invalid request"<< std::endl; 
    return; 
  }

  if(hIndex == 0 || hIndex > prevResults_.size())
  {
    std::cout<< "Invalid request"<< std::endl; 
    return; 
  }

  carts_[name_key].push_back(prevResults_[hIndex - 1]);
}

void MyDataStore::view_cart(const std::string& uname, std::ostream& os) const
{
  std::string name_key = convToLower(uname);
  
  if(users_by_name.find(name_key) == users_by_name.end())
  {
    os<< "Invalid username"<< std::endl; 
    return; 
  }

  std::unordered_map<std::string, std::deque<Product*>>::const_iterator it = carts_.find(name_key);

  if(it == carts_.end())
  {
    return; 
  }

  const std::deque<Product*>& result = it->second; 

  for(size_t i =0 ; i< result.size(); i++)
  {
    os<< "Item "<< (i+1) << std::endl; 
    os<< result[i]->displayString()<< std::endl; 
  }
}


void MyDataStore::buy_cart(const std::string& uname)
{
  std::string name_key = convToLower(uname);

  if(users_by_name.find(name_key) == users_by_name.end())
  {
    std::cout<< "Invalid username"<< std::endl; 
    return; 
  }

  User* cur_user = users_by_name[name_key];

  std::deque<Product*>& cur_cart =  carts_[name_key];

  std::deque<Product*> remaining_cart;

  for(std::deque<Product*>::iterator it = cur_cart.begin(); it!=cur_cart.end(); ++it)
    { 


      Product* p = *it; 
      
      double price = p->getPrice();
      bool available = (p->getQty() > 0);
      bool canBuy = ( cur_user->getBalance() >=  price);

      if (canBuy && available)
      {
        p->subtractQty(1);
        cur_user->deductAmount(price);
      }
      else
      {
        remaining_cart.push_back(*it);
      }
    }

    cur_cart = remaining_cart; 
}


void MyDataStore::setPrevResults(const std::vector<Product*>& hits)
{
  prevResults_.clear();
  for(size_t i =0; i< hits.size(); i++)
  {
    prevResults_.push_back(hits[i]);
  }



}



void MyDataStore::dump(std::ostream& os)
{
  os<< "<products>" << std::endl; 
  for(size_t i = 0;i< products_.size(); i++)
  {
    products_[i]->dump(os);
  }

  os <<"</products>"<<std::endl;


  os<< "<users>" << std::endl; 
  for(size_t i = 0;i< users_.size(); i++)
  {
    users_[i]->dump(os);
  }

  os <<"</users>"<<std::endl;


}


MyDataStore::~MyDataStore()
{
  for(std::size_t i = 0; i<products_.size(); i++)
  {
    delete products_[i];
  }

  for( std::size_t i =0;i< users_.size(); i++)
  {
    delete users_[i];
  }

  users_.clear();

  index_.clear();
  carts_.clear();
  users_by_name.clear();
  prevResults_.clear();

}
