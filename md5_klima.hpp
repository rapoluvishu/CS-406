typedef unsigned int uint32;

extern uint32 t[64], s[64], m[16], shifts[32];

void initialise() {
	t[0] = 0xd76aa478;
	t[1] = 0xe8c7b756;
	t[2] = 0x242070db;
	t[3] = 0xc1bdceee;
	t[4] = 0xf57c0faf;
	t[5] = 0x4787c62a;
	t[6] = 0xa8304613;
	t[7] = 0xfd469501;
	t[8] = 0x698098d8;
	t[9] = 0x8b44f7af;
	t[10] = 0xffff5bb1;
	t[11] = 0x895cd7be;
	t[12] = 0x6b901122;
	t[13] = 0xfd987193;
	t[14] = 0xa679438e;
	t[15] = 0x49b40821;
	t[16] = 0xf61e2562;
	t[17] = 0xc040b340;
	t[18] = 0x265e5a51;
	t[19] = 0xe9b6c7aa;
	t[20] = 0xd62f105d;
	t[21] = 0x02441453;
	t[22] = 0xd8a1e681;
	t[23] = 0xe7d3fbc8;
	t[24] = 0x21e1cde6;
	t[25] = 0xc33707d6;
	t[26] = 0xf4d50d87;
	t[27] = 0x455a14ed;
	t[28] = 0xa9e3e905;
	t[29] = 0xfcefa3f8;
	t[30] = 0x676f02d9;
	t[31] = 0x8d2a4c8a;
	t[32] = 0xfffa3942;
	t[33] = 0x8771f681;
	t[34] = 0x6d9d6122;
	t[35] = 0xfde5380c;
	t[36] = 0xa4beea44;
	t[37] = 0x4bdecfa9;
	t[38] = 0xf6bb4b60;
	t[39] = 0xbebfbc70;
	t[40] = 0x289b7ec6;
	t[41] = 0xeaa127fa;
	t[42] = 0xd4ef3085;
	t[43] = 0x04881d05;
	t[44] = 0xd9d4d039;
	t[45] = 0xe6db99e5;
	t[46] = 0x1fa27cf8;
	t[47] = 0xc4ac5665;
	t[48] = 0xf4292244;
	t[49] = 0x432aff97;
	t[50] = 0xab9423a7;
	t[51] = 0xfc93a039;
	t[52] = 0x655b59c3;
	t[53] = 0x8f0ccc92;
	t[54] = 0xffeff47d;
	t[55] = 0x85845dd1;
	t[56] = 0x6fa87e4f;
	t[57] = 0xfe2ce6e0;
	t[58] = 0xa3014314;
	t[59] = 0x4e0811a1;
	t[60] = 0xf7537e82;
	t[61] = 0xbd3af235;
	t[62] = 0x2ad7d2bb;
	t[63] = 0xeb86d391;

	s[0] = 7;
	s[1] = 12;
	s[2] = 17;
	s[3] = 22;
	s[4] = 7;
	s[5] = 12;
	s[6] = 17;
	s[7] = 22;
	s[8] = 7;
	s[9] = 12;
	s[10] = 17;
	s[11] = 22;
	s[12] = 7;
	s[13] = 12;
	s[14] = 17;
	s[15] = 22;
	s[16] = 5;
	s[17] = 9;
	s[18] = 14;
	s[19] = 20;
	s[20] = 5;
	s[21] = 9;
	s[22] = 14;
	s[23] = 20;
	s[24] = 5;
	s[25] = 9;
	s[26] = 14;
	s[27] = 20;
	s[28] = 5;
	s[29] = 9;
	s[30] = 14;
	s[31] = 20;
	s[32] = 4;
	s[33] = 11;
	s[34] = 16;
	s[35] = 23;
	s[36] = 4;
	s[37] = 11;
	s[38] = 16;
	s[39] = 23;
	s[40] = 4;
	s[41] = 11;
	s[42] = 16;
	s[43] = 23;
	s[44] = 4;
	s[45] = 11;
	s[46] = 16;
	s[47] = 23;
	s[48] = 6;
	s[49] = 10;
	s[50] = 15;
	s[51] = 21;
	s[52] = 6;
	s[53] = 10;
	s[54] = 15;
	s[55] = 21;
	s[56] = 6;
	s[57] = 10;
	s[58] = 15;
	s[59] = 21;
	s[60] = 6;
	s[61] = 10;
	s[62] = 15;
	s[63] = 21;

	shifts[0] = 1;
	for(int i=1;i<32;i++)
	{
		shifts[i] = 2*shifts[i-1];
	}
}


int sigma(int operation)
{
	if(operation <= 16)
		return operation-1;
	else if(operation <= 32)
		return (5*operation - 4)%16;
	else if(operation <= 48)
		return (3*operation + 2)%16;
	else
		return (7*(operation-1))%16;
}
