#ifndef _SEARCH_H_
#define _SEARCH_H_
#include <tuple>
#define ENTRY_TUPLE tuple<char*,char*,char*,char*>
#define TUPLE_LIST ENTRY_TUPLE*
using namespace std;

ENTRY_TUPLE SearchIn(TUPLE_LIST entries, int len);

#endif