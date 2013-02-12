#ifndef _TEMPODB_JSON_H_
#define _TEMPODB_JSON_H_

#include "tempodb/STL.h"

#include <istream>
#include <sstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

typedef boost::property_tree::ptree PTree;

inline PTree jsonToPTree(String json)
{
  using boost::property_tree::ptree;
  ptree pt;
  std::stringbuf buf(json);
  std::istream in(&buf);
  read_json(in, pt);
  return pt;
}







#endif
