#ifndef _TEMPODB_SERIES_H_
#define _TEMPODB_SERIES_H_

#include "tempodb/STL.h"


class Series
{
  public:
    String id;
    String key;
    String name;
    VecS tags;
    MapSS attributes;

    Series() {}


    String toString()
    {
      return "Series(" + id + " , " + key + ")";
    }

    static Series fromJson(String json);
};

#endif
