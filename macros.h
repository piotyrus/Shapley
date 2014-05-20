#ifndef __MACROS_H__
#define __MACROS_H__

#define MAX(a,b) \
({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
            _a > _b ? _a : _b; })

#define MIN(a,b) \
({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
            _a < _b ? _a : _b; })


#endif /*__MACROS_H__*/
