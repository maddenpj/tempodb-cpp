#include "tempodb/Client.h"

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include <sstream>

#include <boost/foreach.hpp>

using namespace TempoDB;

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
  std::cout << os.str() << std::endl;
  req << boost::network::header("Authorization", "Basic " + os.str());
}



std::vector<Series> Client::listSeries()
{
  String url = apiUrl + "/v1/series";
  HttpResponse response = execute(url, "GET");

  PTree pt = jsonToPTree(body(response));

  std::vector<Series> vec;
  for(PTree::iterator it = pt.begin(); it != pt.end(); ++it)
  {
    vec.push_back(Series::fromPTree(it->second));
  }
  return vec;
}

Series Client::getSeries(const String& id)
{
  String url = apiUrl + "/v1/series/id/" + id + "/";
  HttpResponse res = execute(url, "GET");
  return Series::fromJson(body(res));
}

Series Client::getSeriesByKey(const String& key)
{
  String url = apiUrl + "/v1/series/key/" + key + "/";
  HttpResponse res = execute(url, "GET");
  return Series::fromJson(body(res));
}

HttpResponse Client::execute(const String& url, const String method, const String& body)
{
  HttpRequest request(url);
  request << boost::network::body(body);

  addBasicAuth(request);

  HttpResponse res;
  if(method == "GET") {
    res = httpClient.get(request);
  } else if(method == "POST") {
    res = httpClient.post(request);
  }
  return res;
}
