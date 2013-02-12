#ifndef _TEMPODB_CLIENT_H_
#define _TEMPODB_CLIENT_H_

#include <boost/network/protocol/http/client.hpp>
#include <iostream>

#include "tempodb/JSON.h"
#include "tempodb/STL.h"
#include "tempodb/Series.h"

namespace http = boost::network::http;

typedef http::client::response HttpResponse;
typedef http::client::request HttpRequest;

class Client
{
  private:
    http::client httpClient;
    String apiKey;
    String apiSecret;
    String apiUrl;
    int port;
    bool secure;
    String version;

    void addBasicAuth(HttpRequest& req);


  public:
    Client(String _apiKey, String _apiSecret, String _apiUrl, int _port = 443, bool _secure = true, String _version = "v1") :
      apiKey(_apiKey), apiSecret(_apiSecret), apiUrl(_apiUrl), port(_port), secure(_secure), version(_version), httpClient() { }

    HttpResponse ping();

    std::vector<Series> listSeries();

    Series getSeries(String id);
};




#endif


