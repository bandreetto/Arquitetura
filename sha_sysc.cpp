#include "systemc.h"
#include "sha_sysc.h"

SC_MODULE (sha_systemc) {

	sc_in<bool> exec;

	//Transform
	sc_in<LONG> digest[5];
	sc_in<LONG> data[16];

	sc_out<LONG> digest_out[5];

	//Byte Reverse
	sc_in<LONG> buffer[16];
	sc_in<int> counter;

	sc_out<LONG> buffer_out[16];

	void transform() {
		if (exec.read()) {
			int i;
			LONG temp, A, B, C, D, E, W[80];

			for (i = 0; i < 16; ++i) {
				W[i] = data[i].read();
			}
			for (i = 16; i < 80; ++i) {
				W[i] = W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16];
#ifdef USE_MODIFIED_SHA
				W[i] = ROT32(W[i], 1);
#endif /* USE_MODIFIED_SHA */
			}
			A = digest[0].read();
			B = digest[1].read();
			C = digest[2].read();
			D = digest[3].read();
			E = digest[4].read();

#ifdef UNROLL_LOOPS
			FUNC(1, 0); FUNC(1, 1); FUNC(1, 2); FUNC(1, 3); FUNC(1, 4);
			FUNC(1, 5); FUNC(1, 6); FUNC(1, 7); FUNC(1, 8); FUNC(1, 9);
			FUNC(1,10); FUNC(1,11); FUNC(1,12); FUNC(1,13); FUNC(1,14);
			FUNC(1,15); FUNC(1,16); FUNC(1,17); FUNC(1,18); FUNC(1,19);

			FUNC(2,20); FUNC(2,21); FUNC(2,22); FUNC(2,23); FUNC(2,24);
			FUNC(2,25); FUNC(2,26); FUNC(2,27); FUNC(2,28); FUNC(2,29);
			FUNC(2,30); FUNC(2,31); FUNC(2,32); FUNC(2,33); FUNC(2,34);
			FUNC(2,35); FUNC(2,36); FUNC(2,37); FUNC(2,38); FUNC(2,39);

			FUNC(3,40); FUNC(3,41); FUNC(3,42); FUNC(3,43); FUNC(3,44);
			FUNC(3,45); FUNC(3,46); FUNC(3,47); FUNC(3,48); FUNC(3,49);
			FUNC(3,50); FUNC(3,51); FUNC(3,52); FUNC(3,53); FUNC(3,54);
			FUNC(3,55); FUNC(3,56); FUNC(3,57); FUNC(3,58); FUNC(3,59);

			FUNC(4,60); FUNC(4,61); FUNC(4,62); FUNC(4,63); FUNC(4,64);
			FUNC(4,65); FUNC(4,66); FUNC(4,67); FUNC(4,68); FUNC(4,69);
			FUNC(4,70); FUNC(4,71); FUNC(4,72); FUNC(4,73); FUNC(4,74);
			FUNC(4,75); FUNC(4,76); FUNC(4,77); FUNC(4,78); FUNC(4,79);
#else /* !UNROLL_LOOPS */
			for (i = 0 ; i < 20; ++i) FUNC(1, i);
			for (i = 20; i < 40; ++i) FUNC(2, i);
			for (i = 40; i < 60; ++i) FUNC(3, i);
			for (i = 60; i < 80; ++i) FUNC(4, i);
#endif /* !UNROLL_LOOPS */
			digest_out[0].write(digest[0].read() + A);
			digest_out[1].write(digest[1].read() + B);
			digest_out[2].write(digest[2].read() + C);
			digest_out[3].write(digest[3].read() + D);
			digest_out[4].write(digest[4].read() + E);
		}
	}

//#ifdef LITTLE_ENDIAN
	void byte_reverse() {
		if (exec.read()) {
			int i, count;
			BYTE ct[4], *cp;
			LONG *data = (LONG *) malloc(sizeof(LONG) * 16);

			count = counter.read()/sizeof(LONG);
			for (int i = 0; i < 16; i++)
				data[i] = buffer[i].read();
			cp = (BYTE *) data;
			for (i = 0; i < count; ++i) {
				ct[0] = cp[0];
				ct[1] = cp[1];
				ct[2] = cp[2];
				ct[3] = cp[3];
				cp[0] = ct[3];
				cp[1] = ct[2];
				cp[2] = ct[1];
				cp[3] = ct[0];
				cp += sizeof(LONG);
			}
			data = (LONG *) cp;
			for (int i = 0; i < 16; i++)
				buffer_out[i].write(data[i]);
		}
	}
//#endif /* LITTLE_ENDIAN */

	SC_CTOR(sha_systemc) {
		SC_METHOD(transform);
			sensitive << exec;
		SC_METHOD(byte_reverse);
			sensitive << exec;
	}
};
