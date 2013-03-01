#ifndef _TEMPODB_JSON_H_
#define _TEMPODB_JSON_H_

#include "tempodb/STL.h"

#include <istream>
#include <sstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

typedef boost::property_tree::ptree PTree;

inline PTree jsonToPTree(const String& json)
{
  PTree pt;
  std::stringbuf buf(json);
  std::istream in(&buf);
  read_json(in, pt);
  return pt;
}

inline String ptreeToJson(const PTree& ptree)
{
  std::ostringstream out;
  write_json(out, ptree);
  return out.str();
}

inline void print(PTree const& pt)
{
  PTree::const_iterator end = pt.end();
  for (PTree::const_iterator it = pt.begin(); it != end; ++it) {
    std::cout << it->first << ": " << it->second.get_value<std::string>() << std::endl;
    print(it->second);
  }
}





#endif
