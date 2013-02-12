//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


//[ hello_world_client_main
/*`
  This is a part of the 'Hello World' example.  We create a client
  object and make a single HTTP request.  If we use make this request
  to the `hello_world_server`, then the output is simply "Hello,
  World!".
 */
#include "tempodb/Client.h"
#include <boost/network/message.hpp>
#include <iostream>


namespace http = boost::network::http;
namespace network = boost::network;


int
main(int argc, char *argv[]) {

    try {
        Client client("4bf5848729ad400cb63774abc7aa32fa", "5c65b7c5bddb4b8c9400f012f59f357d", "http://api-staging.tempo-db.com");

        HttpResponse response = client.ping();
        std::cout << body(response) << std::endl;

        // HttpResponse response2 = client.listSeries("Basic NGJmNTg0ODcyOWFkNDAwY2I2Mzc3NGFiYzdhYTMyZmE6NWM2NWI3YzViZGRiNGI4Yzk0MDBmMDEyZjU5ZjM1N2Q=");
        // HttpResponse response2 = client.listSeries();
        // std::cout << headers(response2)["Status Code"] << std::endl;
        // for(headers(response2)::container_type::iterator it = headers(response2)::container_type.begin(); it != headers(response2)::container_type.end(); ++it)
        // {
        //   std::out << *it << std::endl;
        // }
        //

        std::vector<Series> slist = client.listSeries();
        for(int i = 0; i < slist.size(); i++)
        {
          std::cout << slist[i].toString() << std::endl;
        }

        std::cout << std::endl;

        Series s = client.getSeries("38f7efc590364368a8732427d6e838ba");

        std::cout << s.toString() << std::endl;

        for(int i = 0; i < s.tags.size(); i++)
          std::cout << s.tags[i] << std::endl;

        for(MapSS::iterator ci = s.attributes.begin(); ci != s.attributes.end(); ++ci)
          std::cout << ci->first << " : " << ci->second << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
//]
