#include "config.h"

u8 sbox[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

void Sbox() {
	cout << "hex |";
	for (int i = 0; i < 16; i++) 
		cout << hex << "  " << i << " |";
	cout << "\n";
	int tmp = 0;
	for (int i = 0; i < 16; i++) {
		cout << "  " << i << " | " ;
		for (int j = 0; j < 16; j++) 
			cout << hex << setfill('0') << setw(2) << (int) sbox[tmp++] << " | ";
		cout << "\n";
	}
}

void vypis(vec_GF2E a) {
	for (int i = 0; ; i+=4) {
		if (i > 15) {
			i -= 15;
			cout << "\n";
		}
		int tmp = 0;
		if (a[i].LoopHole().xrep.length())
			tmp = a[i].LoopHole().xrep[0];
		cout << hex << setfill('0') << setw(2) << tmp << ", ";
		if (i == 15) break;
	}
	cout << "\n\n";
}

vec_GF2E set_GF2E(stringstream& src) {
	vec_GF2E dst;
	dst.SetLength(16);

	for (int i = 0; i < 16; i++) {
		int tmp = 0;
		src >> tmp;
		if (tmp) {
			dst[i].LoopHole().SetLength(1);
			dst[i].LoopHole().xrep[0] = tmp;
		}
	}

	return dst;
}

void SubBytes(vec_GF2E& text) {
	for (int i = 0; i < 16; i++) {
		int tmp = 0;
		if (text[i].LoopHole().xrep.length() != 0)
			tmp = text[i].LoopHole().xrep[0];

		int res = sbox[tmp];
		if (res != 0) {
			text[i].LoopHole().SetLength(1);
			text[i].LoopHole().xrep[0] = res;
		}
		else
			text[i] = 0;
	}

	cout << "After SubBytes:\n";
	vypis(text);
}

void ShiftRows(vec_GF2E& text) {
	GF2E tmp;
	tmp = text[1];
	text[1] = text[5];
	text[5] = text[9];
	text[9] = text[13];
	text[13] = tmp;
	tmp = text[2];
	text[2] = text[10];
	text[10] = tmp;
	tmp = text[6];
	text[6] = text[14];
	text[14] = tmp;
	tmp = text[3];
	text[3] = text[15];
	text[15] = text[11];
	text[11] = text[7];
	text[7] = tmp;

	cout << "After ShiftRows:\n";
	vypis(text);
}

void MixColumns(vec_GF2E& text) {
	vec_GF2E res;
	res.SetLength(16);

	GF2E a, b, c;
	a.LoopHole().SetLength(1);
	a.LoopHole().xrep[0] = 0x01;
	b.LoopHole().SetLength(1);
	b.LoopHole().xrep[0] = 0x02;
	c.LoopHole().SetLength(1);
	c.LoopHole().xrep[0] = 0x03;

	for (int i = 0; i < 16; i+=4) {
		res[i+0] = b * text[i] + c * text[i+1] + a * text[i+2] + a * text[i+3];
		res[i+1] = a * text[i] + b * text[i+1] + c * text[i+2] + a * text[i+3];
		res[i+2] = a * text[i] + a * text[i+1] + b * text[i+2] + c * text[i+3];
		res[i+3] = c * text[i] + a * text[i+1] + a * text[i+2] + b * text[i+3];
	}

	text = res;

	cout << "After MixColumns:\n";
	vypis(text);
}

void AddRoundKey(vec_GF2E& text, vec_GF2E& key) {
	text += key;

	cout << "After AddRoundKey:\n";
	vypis(text);
}

void KeySchedule(vec_GF2E& key, int j) {
	u8 rcon[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36};

	vec_GF2E res;
	res.SetLength(16);
	for (int i = 0; i < 16; i++) {
		res[i] = 1;
	}

	res[0].LoopHole().xrep[0] = sbox[key[13].LoopHole().xrep[0]] ^ key[0].LoopHole().xrep[0] ^ rcon[j];
	res[1].LoopHole().xrep[0] = sbox[key[14].LoopHole().xrep[0]] ^ key[1].LoopHole().xrep[0];
	res[2].LoopHole().xrep[0] = sbox[key[15].LoopHole().xrep[0]] ^ key[2].LoopHole().xrep[0];
	res[3].LoopHole().xrep[0] = sbox[key[12].LoopHole().xrep[0]] ^ key[3].LoopHole().xrep[0];

	for (int i = 4; i < 16; i++) 
		res[i].LoopHole().xrep[0] = res[i-4].LoopHole().xrep[0] ^ key[i].LoopHole().xrep[0];

	key = res;

	cout << "After KeySchedule:\n";
	vypis(key);
}

void AES() {
	GF2X mod;
	BuildSparseIrred(mod, 8);
	GF2E::init(mod);

	cout << "mod: " << hex << mod.xrep[0] << endl;
	string plaintext = "32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34";
	string       key = "2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c";
	stringstream s;
	s << hex << plaintext << " " << key;

	vec_GF2E text = set_GF2E(s);
	cout << "Plaintext:\n";
	vypis(text);

	vec_GF2E round_key = set_GF2E(s);
	cout << "Cipher Key:\n";
	vypis(round_key);

	AddRoundKey(text, round_key);

	for (int i = 0; i < 9; i++) {
		SubBytes(text);
		ShiftRows(text);
		MixColumns(text);
		KeySchedule(round_key,i);
		AddRoundKey(text, round_key);
	}

	SubBytes(text);
	ShiftRows(text);
	KeySchedule(round_key,9);
	AddRoundKey(text, round_key);
}

void (*NKS[2])() = { Sbox,
					 AES,
};