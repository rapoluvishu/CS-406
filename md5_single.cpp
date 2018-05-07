#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "md5.hpp"
using namespace std;

uint32 t[64], s[64], m[16], shifts[32];
uint32 a[17], b[17], c[17], d[17];
uint32 mx[16];
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
	else 
	{
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
}

bool verify_single()
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

void msg_modification()
{
	
	//single message modification

	MD5_STEP(FF,a[0],b[0],c[0],d[0],m[sigma(0*4+1)],t[0*4],s[0*4],a[0+1]);

	//for d1
	MD5_STEP(FF,d[0],a[0+1],b[0],c[0],m[sigma(0*4+2)],t[0*4+1],s[0*4+1],d[0+1]);
	MD5_REVERSE_STEP(d[0],a[0+1],b[0],c[0],m[sigma(0*4+2)],t[0*4+1],s[0*4+1],d[0+1]);

	//for c1
	MD5_STEP(FF,c[0],d[0+1],a[0+1],b[0],m[sigma(0*4+3)],t[0*4+2],s[0*4+2],c[0+1]);
	c[1] = (c[1] & 0xFFF7F7BF);
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
	MD5_REVERSE_STEP(b[0],c[0+1],d[0+1],a[0+1],m[sigma(0*4+4)],t[0*4+3],s[0*4+3],b[0+1]);
	
	//for a2
	MD5_STEP(FF,a[1],b[1],c[1],d[1],m[sigma(1*4+1)],t[1*4],s[1*4],a[1+1]);
	a[2] = (a[2] & 0xFD40003F) | 0x88400025;
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
	MD5_REVERSE_STEP(a[2],b[2],c[2],d[2],m[sigma(2*4+1)],t[2*4],s[2*4],a[2+1]);

	//for d3
	MD5_STEP(FF,d[2],a[2+1],b[2],c[2],m[sigma(2*4+2)],t[2*4+1],s[2*4+1],d[2+1]);
	d[3] = (d[3] & 0x7F7FDE7C) | 0x401F9040;
	MD5_REVERSE_STEP(d[2],a[2+1],b[2],c[2],m[sigma(2*4+2)],t[2*4+1],s[2*4+1],d[2+1]);

	//for c3
	MD5_STEP(FF,c[2],d[2+1],a[2+1],b[2],m[sigma(2*4+3)],t[2*4+2],s[2*4+2],c[2+1]);
	c[3] = (c[3] & 0x3FF1CEFE) | 0x180C2;
	c[3] =  single_bit_modification(c[3], pos_bit(d[3],15), 15);
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
	MD5_REVERSE_STEP(a[3],b[3],c[3],d[3],m[sigma(3*4+1)],t[3*4],s[3*4],a[3+1]);

	//for d4
	MD5_STEP(FF,d[3],a[3+1],b[3],c[3],m[sigma(3*4+2)],t[3*4+1],s[3*4+1],d[3+1]);
	d[4] = (d[4] & 0x5CFBFFFF) | 0xBE188;
	MD5_REVERSE_STEP(d[3],a[3+1],b[3],c[3],m[sigma(3*4+2)],t[3*4+1],s[3*4+1],d[3+1]);

}

void single_msg_modification()
{
	seed = time(0);
	srand (seed);
	for(int i=0;i<14;i++)
	{
		m[i] = uint32(rand());
	}
	md5_hash(true);
	msg_modification();
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
		MD5_REVERSE_STEP(c[3],d[3+1],a[3+1],b[3],m[sigma(3*4+3)],t[3*4+2],s[3*4+2],c[3+1]);

		//for b4
		MD5_STEP(FF,b[3],c[3+1],d[3+1],a[3+1],m[sigma(3*4+4)],t[3*4+3],s[3*4+3],b[3+1]);
		b[4] = (b[4] & 0x7FFFFFFF) | 0x20000000;
		MD5_REVERSE_STEP(b[3],c[3+1],d[3+1],a[3+1],m[sigma(3*4+4)],t[3*4+3],s[3*4+3],b[3+1]);

		mx[14] = m[14];
		mx[15] = m[15];
		md5_hash(false);
	}while(!verify_single());
}


int main()
{

	initialise();
	a[0] = 0x67452301;
	b[0] = 0xefcdab89;
	c[0] = 0x98badcfe;
	d[0] = 0x10325476;
	
	single_msg_modification();
	for(int i=0;i<16;i++)
		cout<<m[i]<<endl;
	cout<<endl;

	cout<<"Seed is " <<seed<<endl;

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
}