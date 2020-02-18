//
// Created by vellhe on 2020-02-10.
//

#include "GlobalValues.h"
namespace global{

    const int DBCode::OK = 0;
    const int DBCode::ERR = -1;

    const int DBCode::QUERY_ERR = -1001;
    const int DBCode::QUERY_RET_EMPTY = 1001;

    const int DBCode::CONN_INIT_ERR = -2001;
    const int DBCode::CONN_ERR = -2002;
    const int DBCode::CONN_CHARSET_ERR = -2003;
}