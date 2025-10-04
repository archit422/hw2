#include <iostream>
#include <sstream>
#include <cctype>
#include <string>
#include <set>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{

  //keywords in a common case so that searching is easy and case-insensitive
  
  set<std::string> result;

  string raw_words = convToLower(rawWords);

  size_t raw_words_len = raw_words.size();

  char c; 
  std::string buffer;

  for(size_t i = 0; i<raw_words_len; i++)
  {
    c = raw_words[i];
    if(isalnum(static_cast<unsigned char>(c)))
    {
      buffer.push_back(c);
    }
    else 
    {
      if(buffer.length() >=2)
      {
        result.insert(buffer);
      }
      buffer.clear();
    }
  }

  if(buffer.length() >=2)
    {
      result.insert(buffer);
      buffer.clear();
    }



return result;



  //For the product name, book author, and clothing brand we define a 
  //keyword to be any string of 2 or more characters. If such a word has 
  //punctuation it should be split at each punctuation character and the 
  //resulting substrings (of 2 or more characters) should be used as keywords.


  //For other keywords (book ISBN and movie genre) no punctuation or 
  //size analysis is necessary and it should be used verbatim as a 
  //keyword.

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
