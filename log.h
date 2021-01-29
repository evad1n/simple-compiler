#if !defined(LOGGING_H)
#define LOGGING_H

#include <iostream>

#if !defined(LOGGING)
#define LOGGING 0
#endif // LOGGING

#if LOGGING
#define LOG(X) std::cout << X << std::endl;
#else 
#define LOG(X) ;
#endif

#endif // DEBUG_H
