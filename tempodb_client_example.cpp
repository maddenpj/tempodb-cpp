#include "tempodb/Client.h"
#include <boost/network/message.hpp>
#include <iostream>

typedef TempoDB::Series Series;

int main(int argc, char *argv[]) {

  TempoDB::Client client("4bf5848729ad400cb63774abc7aa32fa", "5c65b7c5bddb4b8c9400f012f59f357d", "http://api-staging.tempo-db.com");

  // std::vector<Series> slist = client.listSeries();
  // std::cout << "Printing: " << slist.size() << std::endl;
  // for(int i = 0; i < slist.size(); i++)
  // {
  //   std::cout << slist[i].toString() << std::endl;
  // }

  // std::cout << std::endl;

  // Series sbykey = client.getSeriesByKey("demo-series");
  // std::cout << sbykey.toString() << std::endl;

  Series s = client.getSeries("38f7efc590364368a8732427d6e838ba");
  std::cout << s.toString() << std::endl;

  s.toJson();

  // for(int i = 0; i < s.tags.size(); i++)
  //   std::cout << s.tags[i] << std::endl;

  for(MapSS::iterator ci = s.attributes.begin(); ci != s.attributes.end(); ++ci)
    std::cout << ci->first << " : " << ci->second << std::endl;


  return 0;
}
