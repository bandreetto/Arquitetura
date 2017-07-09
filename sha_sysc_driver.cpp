#include "systemc.h"
#include "sha_sysc.cpp"

void print(char *tag, sc_signal<LONG> a[], int size) {
	cout << tag;
	for(int i = 0; i < size; i++) cout << (char)a[i].read();
	cout << endl;
}

int sc_main(int argc, char* argv[])
{
	sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);

	//Exec
	sc_signal<bool> exec;

	//Transform
	sc_signal<LONG> digest[5];
	sc_signal<LONG> data[16];

	sc_signal<LONG> digest_out[5];

	//Byte Reverse
	sc_signal<LONG> buffer[16];
	sc_signal<int> counter;

	sc_signal<LONG> buffer_out[16];

	//Associating signals to ports
	sha_systemc coprocessor("COPROCESSOR");
	coprocessor.exec(exec);
	coprocessor.counter(counter);
	for(int i = 0; i < 16; i++) {
		coprocessor.data[i](data[i]);
		coprocessor.buffer[i](buffer[i]);
		coprocessor.buffer_out[i](buffer_out[i]);
	}
	for(int i = 0; i < 5; i++) {
		coprocessor.digest[i](digest[i]);
		coprocessor.digest_out[i](digest_out[i]);
	}

	//Tracing
//	sc_trace_file *wf = sc_create_vcd_trace_file("sc_start");
//	sc_trace(wf, coprocessor.data, "data");
//	sc_trace(wf, coprocessor.digest, "digest");
//	sc_trace(wf, coprocessor.digest_out, "digest_out");
//	sc_trace(wf, coprocessor.buffer, "buffer");
//	sc_trace(wf, coprocessor.buffer_out, "buffer_out");

	sc_start(0);
	char texto[17] = "Teste do SystemC";
	for(int i = 0; i < 16; i++) {
		data[i] = (LONG) texto[i];
		buffer[i] = i+48;
	}

	digest[0] = 0x67452301L;
	digest[1] = 0xefcdab89L;
	digest[2] = 0x98badcfeL;
	digest[3] = 0x10325476L;
	digest[4] = 0xc3d2e1f0L;

	counter = 8*sizeof(LONG);

	exec = 0;
	sc_start(1);
	print("DATA: ", data, 16);
	print("DIGEST: ", digest, 5);
	print("DIGEST_OUT: ", digest_out, 5);
	print("BUFFER: ", buffer, 16);
	print("BUFFER_OUT: ", buffer_out, 16);

	exec = 1;
	sc_start(1);
	print("DATA: ", data, 16);
	print("DIGEST: ", digest, 5);
	print("DIGEST_OUT: ", digest_out, 5);
	print("BUFFER: ", buffer, 16);
	print("BUFFER_OUT: ", buffer_out, 16);

//	sc_close_vcd_trace_file(wf);
	return 0;
}
