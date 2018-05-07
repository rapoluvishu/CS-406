#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "md5.hpp"
using namespace std;

uint32 t[64], s[64], m[16], shifts[32];
uint32 a[17], b[17], c[17], d[17];
uint32 mx[16], my[16];
time_t seed;

void md5_hash(bool x)
{
	if(x)
	{
		for(int i=0;i<4;i++)
		{
			MD5_STEP(FF,a[i],b[i],c[i],d[i],m[sigma(i*4+1)],t[i*4],s[i*4],a[i+1]);
			MD5_STEP(FF,d[i],a[i+1],b[i],c[i],m[sigma(i*4+2)],t[i*4+1],s[i*4+1],d[i+1]);
			MD5_STEP(FF,c[i],d[i+1],a[i+1],b[i],m[sigma(i*4+3)],t[i*4+2],s[i*4+2],c[i+1]);
			MD5_STEP(FF,b[i],c[i+1],d[i+1],a[i+1],m[sigma(i*4+4)],t[i*4+3],s[i*4+3],b[i+1]);
		}
	}

	for(int i=4;i<8;i++)
	{
		MD5_STEP(GG,a[i],b[i],c[i],d[i],m[sigma(i*4+1)],t[i*4],s[i*4],a[i+1]);
		MD5_STEP(GG,d[i],a[i+1],b[i],c[i],m[sigma(i*4+2)],t[i*4+1],s[i*4+1],d[i+1]);
		MD5_STEP(GG,c[i],d[i+1],a[i+1],b[i],m[sigma(i*4+3)],t[i*4+2],s[i*4+2],c[i+1]);
		MD5_STEP(GG,b[i],c[i+1],d[i+1],a[i+1],m[sigma(i*4+4)],t[i*4+3],s[i*4+3],b[i+1]);
	}

	for(int i=8;i<12;i++)
	{
		MD5_STEP(HH,a[i],b[i],c[i],d[i],m[sigma(i*4+1)],t[i*4],s[i*4],a[i+1]);
		MD5_STEP(HH,d[i],a[i+1],b[i],c[i],m[sigma(i*4+2)],t[i*4+1],s[i*4+1],d[i+1]);
		MD5_STEP(HH,c[i],d[i+1],a[i+1],b[i],m[sigma(i*4+3)],t[i*4+2],s[i*4+2],c[i+1]);
		MD5_STEP(HH,b[i],c[i+1],d[i+1],a[i+1],m[sigma(i*4+4)],t[i*4+3],s[i*4+3],b[i+1]);
	}

	for(int i=12;i<16;i++)
	{
		MD5_STEP(II,a[i],b[i],c[i],d[i],m[sigma(i*4+1)],t[i*4],s[i*4],a[i+1]);
		MD5_STEP(II,d[i],a[i+1],b[i],c[i],m[sigma(i*4+2)],t[i*4+1],s[i*4+1],d[i+1]);
		MD5_STEP(II,c[i],d[i+1],a[i+1],b[i],m[sigma(i*4+3)],t[i*4+2],s[i*4+2],c[i+1]);
		MD5_STEP(II,b[i],c[i+1],d[i+1],a[i+1],m[sigma(i*4+4)],t[i*4+3],s[i*4+3],b[i+1]);
	}
}


void after_round1()
{
	if(pos_bit(a[5],16) != pos_bit(b[4],16))
	{
		m[1] += ((1<<(16-6))*(pos_bit(d[1],16+7)==0 ? 1 : -1));
		MD5_STEP(FF,d[0],a[0+1],b[0],c[0],m[sigma(0*4+2)],t[0*4+1],s[0*4+1],d[0+1]);
		m[2] = RS((c[1]-d[1]),17) - c[0] - FF(d[1],a[1],b[0]) - t[2];
		m[3] = RS((b[1]-c[1]),22) - b[0] - FF(c[1],d[1],a[1]) - t[3];
		m[4] = RS((a[2]-b[1]),7) - a[1] - FF(b[1],c[1],d[1]) - t[4];
		m[5] = RS((d[2]-a[1]),12) - d[1] - FF(a[2],b[1],c[1]) - t[5];
	}

	MD5_STEP(GG,a[4],b[4],c[4],d[4],m[sigma(4*4+1)],t[4*4],s[4*4],a[4+1]);

	if(pos_bit(a[5],18) != 0)
	{
		m[1] += ((1<<(18-6))*(pos_bit(d[1],18+7)==0 ? 1 : -1));
		MD5_STEP(FF,d[0],a[0+1],b[0],c[0],m[sigma(0*4+2)],t[0*4+1],s[0*4+1],d[0+1]);
		m[2] = RS((c[1]-d[1]),17) - c[0] - FF(d[1],a[1],b[0]) - t[2];
		m[3] = RS((b[1]-c[1]),22) - b[0] - FF(c[1],d[1],a[1]) - t[3];
		m[4] = RS((a[2]-b[1]),7) - a[1] - FF(b[1],c[1],d[1]) - t[4];
		m[5] = RS((d[2]-a[1]),12) - d[1] - FF(a[2],b[1],c[1]) - t[5];
	}

	MD5_STEP(GG,a[4],b[4],c[4],d[4],m[sigma(4*4+1)],t[4*4],s[4*4],a[4+1]);

	if(pos_bit(a[5],32) != 0)
	{
		m[1] += ((1<<(32-6))*(pos_bit(d[1],32+7-32)==0 ? 1 : -1));
		MD5_STEP(FF,d[0],a[0+1],b[0],c[0],m[sigma(0*4+2)],t[0*4+1],s[0*4+1],d[0+1]);
		m[2] = RS((c[1]-d[1]),17) - c[0] - FF(d[1],a[1],b[0]) - t[2];
		m[3] = RS((b[1]-c[1]),22) - b[0] - FF(c[1],d[1],a[1]) - t[3];
		m[4] = RS((a[2]-b[1]),7) - a[1] - FF(b[1],c[1],d[1]) - t[4];
		m[5] = RS((d[2]-a[1]),12) - d[1] - FF(a[2],b[1],c[1]) - t[5];
	}

	MD5_STEP(GG,a[4],b[4],c[4],d[4],m[sigma(4*4+1)],t[4*4],s[4*4],a[4+1]);

	if(pos_bit(a[5],4) != pos_bit(b[4],4))
	{
		m[1] += ((1<<(4-6+32))*(pos_bit(d[1],4+7)==0 ? 1 : -1));
		MD5_STEP(FF,d[0],a[0+1],b[0],c[0],m[sigma(0*4+2)],t[0*4+1],s[0*4+1],d[0+1]);
		m[2] = RS((c[1]-d[1]),17) - c[0] - FF(d[1],a[1],b[0]) - t[2];
		m[3] = RS((b[1]-c[1]),22) - b[0] - FF(c[1],d[1],a[1]) - t[3];
		m[4] = RS((a[2]-b[1]),7) - a[1] - FF(b[1],c[1],d[1]) - t[4];
		m[5] = RS((d[2]-a[1]),12) - d[1] - FF(a[2],b[1],c[1]) - t[5];
	}

	MD5_STEP(GG,a[4],b[4],c[4],d[4],m[sigma(4*4+1)],t[4*4],s[4*4],a[4+1]);
	MD5_STEP(GG,d[4],a[4+1],b[4],c[4],m[sigma(4*4+2)],t[4*4+1],s[4*4+1],d[4+1]);

	if(pos_bit(d[5],32) != 0)
	{		
		m[2] += (1<<6);
		MD5_STEP(FF,c[0],d[0+1],a[0+1],b[0],m[sigma(0*4+3)],t[0*4+2],s[0*4+2],c[0+1]);
		b[1] += (1<<22);
		m[3] = RS((b[1]-c[1]),22) - b[0] - FF(c[1],d[1],a[1]) - t[3];
		m[4] = RS((a[2]-b[1]),7) - a[1] - FF(b[1],c[1],d[1]) - t[4];
		m[5] = RS((d[2]-a[1]),12) - d[1] - FF(a[2],b[1],c[1]) - t[5];
		m[6] -= (1<<22);
		m[7] = RS((b[2]-c[2]),22) - b[1] - FF(c[2],d[2],a[2]) - t[7];
	}

	MD5_STEP(GG,d[4],a[4+1],b[4],c[4],m[sigma(4*4+2)],t[4*4+1],s[4*4+1],d[4+1]);
	MD5_STEP(GG,c[4],d[4+1],a[4+1],b[4],m[sigma(4*4+3)],t[4*4+2],s[4*4+2],c[4+1]);

	if(pos_bit(c[5],18) != 0)
	{
		m[9] += (1<<23);
		MD5_STEP(FF,d[2],a[2+1],b[2],c[2],m[sigma(2*4+2)],t[2*4+1],s[2*4+1],d[2+1]);
		m[10] = RS((c[3]-d[3]),17) - c[2] - FF(d[3],a[3],b[2]) - t[10];
		m[11] -= (1<<3);
		m[12] = RS((a[4]-b[3]),7) - a[3] - FF(b[3],c[3],d[3]) - t[12];
		m[13] = RS((d[4]-a[4]),12) - d[3] - FF(a[4],b[3],c[3]) - t[13];
	}

	MD5_STEP(GG,c[4],d[4+1],a[4+1],b[4],m[sigma(4*4+3)],t[4*4+2],s[4*4+2],c[4+1]);

	if(pos_bit(c[5],32) != 0)
	{
		m[12] += (1<<5);
		MD5_STEP(FF,a[3],b[3],c[3],d[3],m[sigma(3*4+1)],t[3*4],s[3*4],a[3+1]);
		m[13] = RS((d[4]-a[4]),12) - d[3] - FF(a[4],b[3],c[3]) - t[13];
		m[14] = RS((c[4]-d[4]),17) - c[3] - FF(d[4],a[4],b[3]) - t[14];
		b[4] += ((1<<22) - (1<<17));
		m[15] = RS((b[4]-c[4]),22) - b[3] - FF(c[4],d[4],a[4]) - t[15];
	}

	MD5_STEP(GG,c[4],d[4+1],a[4+1],b[4],m[sigma(4*4+3)],t[4*4+2],s[4*4+2],c[4+1]);
	MD5_STEP(GG,b[4],c[4+1],d[4+1],a[4+1],m[sigma(4*4+4)],t[4*4+3],s[4*4+3],b[4+1]);

	if(pos_bit(b[5],32) != 0)
	{
		m[12] += (1<<31);
		MD5_STEP(FF,a[3],b[3],c[3],d[3],m[sigma(3*4+1)],t[3*4],s[3*4],a[3+1]);
		m[13] = RS((d[4]-a[4]),12) - d[3] - FF(a[4],b[3],c[3]) - t[13];
		m[14] = RS((c[4]-d[4]),17) - c[3] - FF(d[4],a[4],b[3]) - t[14];
		b[4] -= (1<<11);
		m[15] = RS((b[4]-c[4]),22) - b[3] - FF(c[4],d[4],a[4]) - t[15];
	}

	MD5_STEP(GG,b[4],c[4+1],d[4+1],a[4+1],m[sigma(4*4+4)],t[4*4+3],s[4*4+3],b[4+1]);
	MD5_STEP(GG,a[5],b[5],c[5],d[5],m[sigma(5*4+1)],t[5*4],s[5*4],a[5+1]);

	if(pos_bit(a[6],18) != pos_bit(b[5],18))
	{
		m[12] -= (1<<25);
		MD5_STEP(FF,a[3],b[3],c[3],d[3],m[sigma(3*4+1)],t[3*4],s[3*4],a[3+1]);
		m[13] = RS((d[4]-a[4]),12) - d[3] - FF(a[4],b[3],c[3]) - t[13];
		m[14] = RS((c[4]-d[4]),17) - c[3] - FF(d[4],a[4],b[3]) - t[14];
		m[15] = RS((b[4]-c[4]),22) - b[3] - FF(c[4],d[4],a[4]) - t[15];
		m[1] += 1;
		m[2] = RS((c[1]-d[1]),17) - c[0] - FF(d[1],a[1],b[0]) - t[2];
		m[3] = RS((b[1]-c[1]),22) - b[0] - FF(c[1],d[1],a[1]) - t[3];
		m[4] = RS((a[2]-b[1]),7) - a[1] - FF(b[1],c[1],d[1]) - t[4];
		MD5_STEP(FF,d[0],a[0+1],b[0],c[0],m[sigma(0*4+2)],t[0*4+1],s[0*4+1],d[0+1]);
	}

	MD5_STEP(GG,a[5],b[5],c[5],d[5],m[sigma(5*4+1)],t[5*4],s[5*4],a[5+1]);

	if(pos_bit(a[6],32) != 0)
	{
		m[3] += (1<<4);
		MD5_STEP(FF,b[0],c[0+1],d[0+1],a[0+1],m[sigma(0*4+4)],t[0*4+3],s[0*4+3],b[0+1]);
		m[4] = RS((a[2]-b[1]),7) - a[1] - FF(b[1],c[1],d[1]) - t[4];
		m[5] -= (1<<26);
		m[7] -= (1<<26);
	}

	MD5_STEP(GG,a[5],b[5],c[5],d[5],m[sigma(5*4+1)],t[5*4],s[5*4],a[5+1]);
	MD5_STEP(GG,d[5],a[5+1],b[5],c[5],m[sigma(5*4+2)],t[5*4+1],s[5*4+1],d[5+1]);

	if(pos_bit(d[6],32) != 0)
	{
		m[8] += (1<<15);
		MD5_STEP(FF,a[2],b[2],c[2],d[2],m[sigma(2*4+1)],t[2*4],s[2*4],a[2+1]);
		m[9] = RS((d[3]-a[3]),12) - d[2] - FF(a[3],b[2],c[2]) - t[9];
		m[10] -= (1<<22);
		m[12] = RS((a[4]-b[3]),7) - a[3] - FF(b[3],c[3],d[3]) - t[12];
	}

	MD5_STEP(GG,d[5],a[5+1],b[5],c[5],m[sigma(5*4+2)],t[5*4+1],s[5*4+1],d[5+1]);
	MD5_STEP(GG,c[5],d[5+1],a[5+1],b[5],m[sigma(5*4+3)],t[5*4+2],s[5*4+2],c[5+1]);

	if(pos_bit(c[6],32) != 0)
	{
		m[10] += (1<<12);
		MD5_STEP(FF,c[2],d[2+1],a[2+1],b[2],m[sigma(2*4+3)],t[2*4+2],s[2*4+2],c[2+1]);
		m[11] -= (1<<7);
		m[12] = RS((a[4]-b[3]),7) - a[3] - FF(b[3],c[3],d[3]) - t[12];
		m[13] = RS((d[4]-a[4]),12) - d[3] - FF(a[4],b[3],c[3]) - t[13];
		m[14] += (1<<22 - 1<<29);
		m[15] -= (1<<7 + 1<<17);
		MD5_STEP(FF,c[3],d[3+1],a[3+1],b[3],m[sigma(3*4+3)],t[3*4+2],s[3*4+2],c[3+1]);
	}
}


inline bool verify_single()
{
	if(pos_bit(a[5],4) != pos_bit(b[4],4)) return false;
	if(pos_bit(a[5],16) != pos_bit(b[4],16)) return false;
	if(pos_bit(a[5],18) != 0) return false;
	if(pos_bit(a[5],32) != 0) return false;
	if(pos_bit(d[5],18) != 1) return false;
	if(pos_bit(d[5],30) != pos_bit(a[5],30)) return false;
	if(pos_bit(d[5],32) != 0) return false;
	if(pos_bit(c[5],18) != 0) return false;
	if(pos_bit(c[5],32) != 0) return false;
	if(pos_bit(b[5],32) != 0) return false;
	if(pos_bit(a[6],18) != pos_bit(b[5],18)) return false;
	if(pos_bit(a[6],32) != 0) return false;
	if(pos_bit(d[6],32) != 0) return false;
	if(pos_bit(c[6],32) != 0) return false;
	if(pos_bit(b[6],32) != 1) return false;
	if(pos_bit( HH(d[9],a[9],b[8]) , 32 ) != 0) return false;
	if(pos_bit(b[12],32) != pos_bit(d[12],32)) return false;
	if(pos_bit(a[13],32) != pos_bit(c[12],32)) return false;
	if(pos_bit(d[13],32) == pos_bit(b[12],32)) return false;
	if(pos_bit(c[13],32) != pos_bit(a[13],32)) return false;
	if(pos_bit(b[13],32) != pos_bit(d[13],32)) return false;
	if(pos_bit(a[14],32) != pos_bit(c[13],32)) return false;
	if(pos_bit(d[14],32) != pos_bit(b[13],32)) return false;
	if(pos_bit(c[14],32) != pos_bit(a[14],32)) return false;
	if(pos_bit(b[14],32) != pos_bit(d[14],32)) return false;
	if(pos_bit(a[15],32) != pos_bit(c[14],32)) return false;
	if(pos_bit(d[15],32) != pos_bit(b[14],32)) return false;
	if(pos_bit(c[15],32) != pos_bit(a[15],32)) return false;
	if(pos_bit(b[15],26) != 0) return false;
	if(pos_bit(b[15],32) == pos_bit(d[15],32)) return false;
	if(pos_bit(a[16],26) != 1) return false;
	if(pos_bit(a[16],27) != 0) return false;
	if(pos_bit(a[16],32) != pos_bit(c[15],32)) return false;
	if(pos_bit(d[16],32) != pos_bit(b[15],32)) return false;
	if(pos_bit(c[16],32) != pos_bit(d[16],32)) return false;

	uint32 aa0=a[16]+a[0];
	uint32 bb0=b[16]+b[0];
	uint32 cc0=c[16]+c[0];
	uint32 dd0=d[16]+d[0];

	if(pos_bit(dd0,26) != 0) return false;
	if(pos_bit(cc0,26) != 1) return false;
	if(pos_bit(cc0,27) != 0) return false;
	if(pos_bit(cc0,32) != pos_bit(dd0,32)) return false;
	if(pos_bit(bb0,26) != 0) return false;
	if(pos_bit(bb0,27) != 0) return false;
	if(pos_bit(bb0,6) != 0) return false;
	if(pos_bit(bb0,32) != pos_bit(cc0,32)) return false;

	return true;
}

bool verify_multi()
{
	if(pos_bit(b[5],32) != 0) if(pos_bit(d[5],12) != pos_bit(a[5],12)) return false;
	if(pos_bit(c[6],32) != 0) if(pos_bit(a[5],8) != pos_bit(b[4],8)) return false;

	return verify_single();
}

void single_msg_modification()
{
	
	//single message modification

	MD5_STEP(FF,a[0],b[0],c[0],d[0],m[sigma(0*4+1)],t[0*4],s[0*4],a[0+1]);

	//for d1
	MD5_STEP(FF,d[0],a[0+1],b[0],c[0],m[sigma(0*4+2)],t[0*4+1],s[0*4+1],d[0+1]);
	d[1] =  single_bit_modification(d[1], 0, 11); //extra
	d[1] = single_bit_modification(d[1], 0, 13); //extra
	MD5_REVERSE_STEP(d[0],a[0+1],b[0],c[0],m[sigma(0*4+2)],t[0*4+1],s[0*4+1],d[0+1]);

	//for c1
	MD5_STEP(FF,c[0],d[0+1],a[0+1],b[0],m[sigma(0*4+3)],t[0*4+2],s[0*4+2],c[0+1]);
	c[1] = (c[1] & 0xFFF7F7BF);
	c[1] =  single_bit_modification(c[1], 0, 23); //extra
	MD5_REVERSE_STEP(c[0],d[0+1],a[0+1],b[0],m[sigma(0*4+3)],t[0*4+2],s[0*4+2],c[0+1]);
	
	//for b1
	MD5_STEP(FF,b[0],c[0+1],d[0+1],a[0+1],m[sigma(0*4+4)],t[0*4+3],s[0*4+3],b[0+1]);
	b[1] = (b[1] & 0xFF7FFFBF) | 0x80080800;
	b[1] =  single_bit_modification(b[1], pos_bit(c[1],8), 8);
	b[1] =  single_bit_modification(b[1], pos_bit(c[1],9), 9);
	b[1] =  single_bit_modification(b[1], pos_bit(c[1],10), 10);
	b[1] =  single_bit_modification(b[1], pos_bit(c[1],11), 11);
	b[1] =  single_bit_modification(b[1], pos_bit(c[1],13), 13);
	b[1] =  single_bit_modification(b[1], pos_bit(c[1],14), 14);
	b[1] =  single_bit_modification(b[1], pos_bit(c[1],15), 15);
	b[1] =  single_bit_modification(b[1], pos_bit(c[1],16), 16);
	b[1] =  single_bit_modification(b[1], pos_bit(c[1],17), 17);
	b[1] =  single_bit_modification(b[1], pos_bit(c[1],18), 18);
	b[1] =  single_bit_modification(b[1], pos_bit(c[1],19), 19);
	b[1] =  single_bit_modification(b[1], pos_bit(c[1],21), 21);
	b[1] =  single_bit_modification(b[1], pos_bit(c[1],22), 22);
	b[1] =  single_bit_modification(b[1], pos_bit(c[1],23), 23);
	b[1] =  single_bit_modification(b[1], 0, 27); //extra
	MD5_REVERSE_STEP(b[0],c[0+1],d[0+1],a[0+1],m[sigma(0*4+4)],t[0*4+3],s[0*4+3],b[0+1]);
	
	//for a2
	MD5_STEP(FF,a[1],b[1],c[1],d[1],m[sigma(1*4+1)],t[1*4],s[1*4],a[1+1]);
	a[2] = (a[2] & 0xFD40003F) | 0x88400025;
	a[2] =  single_bit_modification(a[2], 1, 27);//extra
	MD5_REVERSE_STEP(a[1],b[1],c[1],d[1],m[sigma(1*4+1)],t[1*4],s[1*4],a[1+1]);

	//for d2
	MD5_STEP(FF,d[1],a[1+1],b[1],c[1],m[sigma(1*4+2)],t[1*4+1],s[1*4+1],d[1+1]);
	d[2] = (d[2] & 0x777FBC5B) | 0x27FBC41;
	d[2] =  single_bit_modification(d[2], pos_bit(a[2],2), 2);
	d[2] =  single_bit_modification(d[2], pos_bit(a[2],4), 4);
	d[2] =  single_bit_modification(d[2], pos_bit(a[2],5), 5);
	d[2] =  single_bit_modification(d[2], pos_bit(a[2],25), 25);
	d[2] =  single_bit_modification(d[2], pos_bit(a[2],27), 27);
	d[2] =  single_bit_modification(d[2], pos_bit(a[2],29), 29);
	d[2] =  single_bit_modification(d[2], pos_bit(a[2],30), 30);
	d[2] =  single_bit_modification(d[2], pos_bit(a[2],31), 31);
	MD5_REVERSE_STEP(d[1],a[1+1],b[1],c[1],m[sigma(1*4+2)],t[1*4+1],s[1*4+1],d[1+1]);
	
	//for c2
	MD5_STEP(FF,c[1],d[1+1],a[1+1],b[1],m[sigma(1*4+3)],t[1*4+2],s[1*4+2],c[1+1]);
	c[2] = 0x3FEF820;
	MD5_REVERSE_STEP(c[1],d[1+1],a[1+1],b[1],m[sigma(1*4+3)],t[1*4+2],s[1*4+2],c[1+1]);
	
	//for b2
	MD5_STEP(FF,b[1],c[1+1],d[1+1],a[1+1],m[sigma(1*4+4)],t[1*4+3],s[1*4+3],b[1+1]);
	b[2] = (b[2] & 0x1F15540) | 0x1910540;
	MD5_REVERSE_STEP(b[1],c[1+1],d[1+1],a[1+1],m[sigma(1*4+4)],t[1*4+3],s[1*4+3],b[1+1]);	

	//for a3
	MD5_STEP(FF,a[2],b[2],c[2],d[2],m[sigma(2*4+1)],t[2*4],s[2*4],a[2+1]);
	a[3] = (a[3] & 0xFBF07F3D) | 0xFB102F3D;
	a[3] =  single_bit_modification(a[3], pos_bit(b[2],13), 13);
	a[3] =  single_bit_modification(a[3], 0, 23); //extra
	MD5_REVERSE_STEP(a[2],b[2],c[2],d[2],m[sigma(2*4+1)],t[2*4],s[2*4],a[2+1]);

	//for d3
	MD5_STEP(FF,d[2],a[2+1],b[2],c[2],m[sigma(2*4+2)],t[2*4+1],s[2*4+1],d[2+1]);
	d[3] = (d[3] & 0x7F7FDE7C) | 0x401F9040;
	d[3] =  single_bit_modification(d[3], 0, 4); //extra
	d[3] =  single_bit_modification(d[3], 1, 23); //extra
	d[3] =  single_bit_modification(d[3], pos_bit(a[3],30), 30); //extra
	MD5_REVERSE_STEP(d[2],a[2+1],b[2],c[2],m[sigma(2*4+2)],t[2*4+1],s[2*4+1],d[2+1]);

	//for c3
	MD5_STEP(FF,c[2],d[2+1],a[2+1],b[2],m[sigma(2*4+3)],t[2*4+2],s[2*4+2],c[2+1]);
	c[3] = (c[3] & 0x3FF1CEFE) | 0x180C2;
	c[3] =  single_bit_modification(c[3], pos_bit(d[3],15), 15);
	c[3] =  single_bit_modification(c[3], 1, 4); //extra
	c[3] =  single_bit_modification(c[3], 1, 23); //extra
	c[3] =  single_bit_modification(c[3], 0, 30); //extra
	MD5_REVERSE_STEP(c[2],d[2+1],a[2+1],b[2],m[sigma(2*4+3)],t[2*4+2],s[2*4+2],c[2+1]);

	//for b3
	MD5_STEP(FF,b[2],c[2+1],d[2+1],a[2+1],m[sigma(2*4+4)],t[2*4+3],s[2*4+3],b[2+1]);
	b[3] = (b[3] & 0x3FF81F7F) | 0x81100;
	b[3] =  single_bit_modification(b[3], pos_bit(c[3],25), 25);
	b[3] =  single_bit_modification(b[3], pos_bit(c[3],26), 26);
	MD5_REVERSE_STEP(b[2],c[2+1],d[2+1],a[2+1],m[sigma(2*4+4)],t[2*4+3],s[2*4+3],b[2+1]);

	//for a4
	MD5_STEP(FF,a[3],b[3],c[3],d[3],m[sigma(3*4+1)],t[3*4],s[3*4],a[3+1]);
	a[4] = (a[4] & 0x7DFFFE7F) | 0x410FE008;
	a[4] =  single_bit_modification(a[4], 1, 1); //extra
	a[4] =  single_bit_modification(a[4], 0, 7); //extra
	a[4] =  single_bit_modification(a[4], 0, 13); //extra
	MD5_REVERSE_STEP(a[3],b[3],c[3],d[3],m[sigma(3*4+1)],t[3*4],s[3*4],a[3+1]);

	//for d4
	MD5_STEP(FF,d[3],a[3+1],b[3],c[3],m[sigma(3*4+2)],t[3*4+1],s[3*4+1],d[3+1]);
	d[4] = (d[4] & 0x5CFBFFFF) | 0xBE188;
	d[4] =  single_bit_modification(d[4], 0, 12); //extra
	d[4] =  single_bit_modification(d[4], 1, 21); //extra
	d[4] =  single_bit_modification(d[4], 0, 23); //extra
	MD5_REVERSE_STEP(d[3],a[3+1],b[3],c[3],m[sigma(3*4+2)],t[3*4+1],s[3*4+1],d[3+1]);
}

void multi_msg_modification()
{
	seed = time(0);
	srand (seed);
	for(int i=0;i<14;i++)
	{
		m[i] = uint32(rand());
	}

	md5_hash(true);
	single_msg_modification();

	for(int i=0;i<14;i++) 
	{
		mx[i] = m[i];
	}
	do
	{
		for(int i=0;i<14;i++) 
		{
			m[i] = mx[i];
		}

		m[14] = uint32(rand());
		m[15] = uint32(rand());
		//for c4
		MD5_STEP(FF,c[3],d[3+1],a[3+1],b[3],m[sigma(3*4+3)],t[3*4+2],s[3*4+2],c[3+1]);
		c[4] = (c[4] & 0x7DFFFFF7) | 0x21008000;
		c[4] =  single_bit_modification(c[4], 0, 8); //extra
		c[4] =  single_bit_modification(c[4], 1, 12); //extra
		c[4] =  single_bit_modification(c[4], 1, 18); //extra
		c[4] =  single_bit_modification(c[4], 1, 23); //extra
		MD5_REVERSE_STEP(c[3],d[3+1],a[3+1],b[3],m[sigma(3*4+3)],t[3*4+2],s[3*4+2],c[3+1]);

		//for b4
		MD5_STEP(FF,b[3],c[3+1],d[3+1],a[3+1],m[sigma(3*4+4)],t[3*4+3],s[3*4+3],b[3+1]);
		b[4] = (b[4] & 0x7FFFFFFF) | 0x20000000;
		b[4] =  single_bit_modification(b[4], 1, 4); //extra
		b[4] =  single_bit_modification(b[4], 1, 12); //extra
		b[4] =  single_bit_modification(b[4], 1, 18); //extra
		b[4] =  single_bit_modification(b[4], 0, 23); //extra
		MD5_REVERSE_STEP(b[3],c[3+1],d[3+1],a[3+1],m[sigma(3*4+4)],t[3*4+3],s[3*4+3],b[3+1]);

		mx[14] = m[14];
		mx[15] = m[15];

		md5_hash(false);
		after_round1();
		md5_hash(false);
	}while(!verify_multi());
}


int main()
{

	initialise();
	a[0] = 0x67452301;
	b[0] = 0xefcdab89;
	c[0] = 0x98badcfe;
	d[0] = 0x10325476;
	
	multi_msg_modification();

	for(int i=0;i<16;i++)
		cout<<m[i]<<endl;
	cout<<endl;

	cout<<"Seed is "<<seed<<endl;

	for(int i=0;i<=16;i++)
	{
		cout<< i<<endl;
		cout<<"   a d c b"<<endl;
		for(int j=0;j<32;j++)
		{
			if(j<9) cout<<"0";
			cout<< j+1 << " " << ((a[i]&(1<<j))>>j) << " " << ((d[i]&(1<<j))>>j) << " " << ((c[i]&(1<<j))>>j) << " " << ((b[i]&(1<<j))>>j)<<endl;
		}
		cout<<endl;
	}

	cout<<verify_single()<<endl;
}