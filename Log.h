#ifndef XMLWRAPPER_LOG_H
#define XMLWRAPPER_LOG_H

#ifdef DEBUG

#ifndef LOG_DEBUG
#include <iostream>
#define LOG_DEBUG(X) std::cout << __FILE__ <<":" << __LINE__ <<"\t"\
<< X << std::endl;
#endif

#else // ifdef DEBUG

#ifndef LOG_DEBUG
#define LOG_DEBUG(X)
#endif

#endif

#endif  //XMLWRAPPER_LOG_H
