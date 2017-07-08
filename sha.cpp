#include <stdio.h>
#include <string.h>
#include "sha.h"
#include "sha_sysc.h"

/* initialize the SHA digest */

void sha_init(SHA_INFO *sha_info)
{
    sha_info->digest[0] = 0x67452301L;
    sha_info->digest[1] = 0xefcdab89L;
    sha_info->digest[2] = 0x98badcfeL;
    sha_info->digest[3] = 0x10325476L;
    sha_info->digest[4] = 0xc3d2e1f0L;
    sha_info->count_lo = 0L;
    sha_info->count_hi = 0L;
}

/* finish computing the SHA digest */

void sha_final(SHA_INFO *sha_info)
{
    int count;
    LONG lo_bit_count, hi_bit_count;

    lo_bit_count = sha_info->count_lo;
    hi_bit_count = sha_info->count_hi;
    count = (int) ((lo_bit_count >> 3) & 0x3f);
    ((BYTE *) sha_info->data)[count++] = 0x80;
    if (count > 56) {
	memset((BYTE *) &sha_info->data + count, 0, 64 - count);
#ifdef LITTLE_ENDIAN
	byte_reverse(sha_info->data, SHA_BLOCKSIZE);
#endif /* LITTLE_ENDIAN */
	sha_transform(sha_info);
	memset(&sha_info->data, 0, 56);
    } else {
	memset((BYTE *) &sha_info->data + count, 0, 56 - count);
    }
#ifdef LITTLE_ENDIAN
    byte_reverse(sha_info->data, SHA_BLOCKSIZE);
#endif /* LITTLE_ENDIAN */
    sha_info->data[14] = hi_bit_count;
    sha_info->data[15] = lo_bit_count;
    sha_transform(sha_info);
}

/* compute the SHA digest of a FILE stream */

#define BLOCK_SIZE	8192

void sha_stream(SHA_INFO *sha_info, FILE *fin)
{
    int i;
    BYTE data[BLOCK_SIZE];

    sha_init(sha_info);
    while ((i = fread(data, 1, BLOCK_SIZE, fin)) > 0) {
	sha_update(sha_info, data, i);
    }
    sha_final(sha_info);
}

/* print a SHA digest */

void sha_print(SHA_INFO *sha_info)
{
    printf("%08lx %08lx %08lx %08lx %08lx\n",
	sha_info->digest[0], sha_info->digest[1], sha_info->digest[2],
	sha_info->digest[3], sha_info->digest[4]);
}
