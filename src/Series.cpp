#include "tempodb/Series.h"
#include "tempodb/JSON.h"

#include <istream>
#include <sstream>

#include <boost/foreach.hpp>

#include <iostream>

Series Series::fromJson(String json)
{
  PTree pt = jsonToPTree(json);

  Series s;

  s.id = pt.get<String>("id");
  s.key = pt.get<String>("key");

  BOOST_FOREACH(PTree::value_type &v,
      pt.get_child("tags"))
    s.tags.push_back(v.second.data());

  BOOST_FOREACH(PTree::value_type &v,
      pt.get_child("attributes"))
    s.attributes[v.first.data()] = v.second.data();

  return s;
}
