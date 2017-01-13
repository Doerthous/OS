#ifndef _SPSNPRINTF_H_
#define _SPSNPRINTF_H_

#include <sptypes.h>
#include <spstddef.h>
#include <spstdarg.h>
#include <spstring.h>

int snprintf(char * buf, u32 size, const char * fmt, ...);

#endif // _SPSNPRINTF_H_ 
