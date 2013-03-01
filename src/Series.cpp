#include "tempodb/Series.h"
#include "tempodb/JSON.h"

#include <istream>
#include <sstream>

#include <boost/foreach.hpp>

#include <iostream>

using namespace TempoDB;

Series Series::fromJson(const String& json)
{
  PTree pt = jsonToPTree(json);
  return Series::fromPTree(pt);
}

Series Series::fromPTree(PTree& pt)
{
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

String Series::toJson() const
{
  PTree pt;
  pt.put("id", id);
  pt.put("key", key);

  BOOST_FOREACH(const std::string tag, tags)
    pt.put("tags", tag);

  BOOST_FOREACH(const MapSS::value_type &attr, attributes) {
    PTree attribute;
    attribute.put(attr.first, attr.second);
    print(attribute);
    pt.put("attributes", attribute.data());
  }
  print(pt);

  String json = ptreeToJson(pt);
  std::cout << json << std::endl;
  return "";

}
