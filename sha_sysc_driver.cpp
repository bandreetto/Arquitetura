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

	// Open VCD file
//	sc_trace_file *wf = sc_create_vcd_trace_file("counter");
	// Dump the desired signals
//	sc_trace(wf, data, "data");
//	sc_trace(wf, digest, "digest");
//	sc_trace(wf, digest_out, "digest_out");

	cout << "TESTE DE CODIGO\nDADOS: ";
	for(int i = 0; i < 16; i++) {
		cout << data[i].read();
	}
	cout << "\n";
	transform.transform();

	return 0;
}
