#ifndef _TEMPODB_SERIES_H_
#define _TEMPODB_SERIES_H_

#include "tempodb/JSON.h"


namespace TempoDB
{

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

    static Series fromJson(const String &json);
    static Series fromPTree(PTree& pt);

    String toJson() const;
};

}

#endif
