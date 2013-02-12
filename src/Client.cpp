#include "tempodb/Client.h"

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include <sstream>

#include <boost/foreach.hpp>


HttpResponse Client::ping()
{
  String url = apiUrl + "/ping";

  std::cout << "hitting: " << url << std::endl;

  HttpRequest request(url);

  return httpClient.get(request);
}

void Client::addBasicAuth(HttpRequest& req)
{
  using namespace boost::archive::iterators;
  typedef base64_from_binary<transform_width<const char *, 6, 8 > > base64_text;

  std::string auth = apiKey + ":" + apiSecret;
  std::stringstream os;
  std::copy(
      base64_text(auth.c_str()),
      base64_text(auth.c_str() + auth.size()),
      boost::archive::iterators::ostream_iterator<char>(os)
  );

  req << boost::network::header("Authorization", "Basic " + os.str());
}

std::vector<Series> Client::listSeries()
{
  String url = apiUrl + "/v1/series";
  HttpRequest request(url);
  std::cout << "hitting: " << url << std::endl;
  addBasicAuth(request);
  HttpResponse response = httpClient.get(request);

  PTree pt = jsonToPTree(body(response));
  std::cout << body(response) << std::endl;

  // std::cout << pt.front() << std::endl;
  // for(PTree::iterator pi = pt.begin(); pi != pt.end(); ++pi)
  // {
  //   std
  // }
  std::cout << "asdf"  << std::endl;
}

Series Client::getSeries(String id)
{
  String url = apiUrl + "/v1/series/id/" + id + "/";
  HttpRequest request(url);
  std::cout << "hitting: " << url << std::endl;
  addBasicAuth(request);
  HttpResponse res = httpClient.get(request);
  return Series::fromJson(body(res));

}
