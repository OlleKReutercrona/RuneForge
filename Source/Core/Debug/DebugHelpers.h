#pragma once
#include <cassert>

#ifdef _DEBUG

#define ASSERT_MSG(cond, msg) \
    do { \
        if (!(cond)) { \
            assert(!("ERROR: " msg )); \
        } \
    } while(0)


#else // NOTE: Remember to define Macro's inside #else also.

#define ASSERT_MSG(cond, msg) ((void)0)

#endif