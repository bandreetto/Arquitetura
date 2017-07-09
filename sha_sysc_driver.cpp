#include "systemc.h"
#include "sha_sysc.cpp"

int sc_main(int argc, char* argv[])
{
	sc_signal<LONG> digest[5];
	sc_signal<LONG> data[16];

	sc_signal<LONG> digest_out[5];

	sha_transform transform("TRANSFORM");

	char texto[16] = "Hello World!";
	for(int i = 0; i < 16; i++) {
		transform.data[i](data[i]);
		data[i] = (LONG) texto[i];
	}
	for(int i = 0; i < 5; i++) {
		transform.digest[i](digest[i]);
		transform.digest_out[i](digest_out[i]);
	}
	digest[0] = 0x67452301L;
	digest[1] = 0xefcdab89L;
	digest[2] = 0x98badcfeL;
	digest[3] = 0x10325476L;
	digest[4] = 0xc3d2e1f0L;

	cout << "TESTE DE CODIFO\nDATA: ";
	for(int i = 0; i < 16; i++) {
		cout << (LONG) texto[i];
	}
	cout << "\n";
	transform.transform();

	return 0;
}
