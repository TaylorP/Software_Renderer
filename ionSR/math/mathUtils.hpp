//
// Taylor Petrick
//

#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

#define PI 3.14159265f

#define min3(a,b,c) ({__typeof__ (a) _a = (a); \
                    __typeof__ (b) _b = (b); \
                    __typeof__ (c) _c = (c); \
                    (_a < _b) ? (_a < _c ? _a : _c) : (_b < _c ? _b : _c);})

#define max3(a,b,c) ({__typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
__typeof__ (c) _c = (c); \
(_a > _b) ? (_a > _c ? _a : _c) : (_b > _c ? _b : _c);})

#define min(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a < _b ? _a : _b; })

#define max(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a > _b ? _a : _b; })


#endif