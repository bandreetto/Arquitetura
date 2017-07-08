#ifndef SHA_SYSC_H
#define SHA_SYSC_H

#include "sha.h"

void sha_transform(SHA_INFO *);
void byte_reverse(LONG *, int);
void sha_update(SHA_INFO *, BYTE *, int);

#endif /* SHA_SYSC_H */
