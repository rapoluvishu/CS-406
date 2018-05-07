#include<iostream>
#include "md5.hpp"
using namespace std;

uint32 a[17], b[17], c[17], d[17];
uint32 aa0, aa1, bb0, bb1, cc0, cc1, dd0, dd1;
uint32 t[64], s[64], shifts[32];

void md5_hash(bool x, uint32 m[])
{


	for(int i=0;i<4;i++)
	{
		MD5_STEP(FF,a[i],b[i],c[i],d[i],m[sigma(i*4+1)],t[i*4],s[i*4],a[i+1]);
		MD5_STEP(FF,d[i],a[i+1],b[i],c[i],m[sigma(i*4+2)],t[i*4+1],s[i*4+1],d[i+1]);
		MD5_STEP(FF,c[i],d[i+1],a[i+1],b[i],m[sigma(i*4+3)],t[i*4+2],s[i*4+2],c[i+1]);
		MD5_STEP(FF,b[i],c[i+1],d[i+1],a[i+1],m[sigma(i*4+4)],t[i*4+3],s[i*4+3],b[i+1]);
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

	if(!x)
	{
		aa0 = a[16] + a[0];
		bb0 = b[16] + b[0];
		cc0 = c[16] + c[0];
		dd0 = d[16] + d[0];
		// cout<<aa0<<" "<<a[16]<<" "<<a[0]<<endl;
		// cout<<bb0<<" "<<b[16]<<" "<<b[0]<<endl;
		// cout<<cc0<<" "<<c[16]<<" "<<c[0]<<endl;
		// cout<<dd0<<" "<<d[16]<<" "<<d[0]<<endl;
	}
	else
	{
		aa1 = a[16] + a[0];
		bb1 = b[16] + b[0];
		cc1 = c[16] + c[0];
		dd1 = d[16] + d[0];
		// cout<<aa1<<" "<<a[16]<<" "<<a[0]<<endl;
		// cout<<bb1<<" "<<b[16]<<" "<<b[0]<<endl;
		// cout<<cc1<<" "<<c[16]<<" "<<c[0]<<endl;
		// cout<<dd1<<" "<<d[16]<<" "<<d[0]<<endl;

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
	if(pos_bit(c[16],32) != pos_bit(a[16],32)) return false;

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

bool conditions()
{
	if(c[1] != (c[1] & 0xFFF7F7BF)) return false;
	if(b[1] != (b[1] & 0x7f00000f) + 0x80080830 + (c[1] & 0x0077f780)) return false;
	if(a[2] != (a[2] & 0x01000000) + 0x88400025) return false;
	if(d[2] != 0x027fbc41 + (a[2] & 0x01000000)) return false;
	if(c[2] != 0x03fef820) return false;
	if(b[2] != (b[2] & 0x00605000) + 0x01910540) return false;
	if(a[3] != (a[3] & 0x00e04000) + 0xfb102f3d + (b[2] & 0x00001000)) return false;
	if(d[3] != (d[3] & 0x0f004e3c) + 0x701f9040) return false;
	if(c[3] != (c[3] & 0x0a100a3c) + 0x20e180c2 + (d[3] & 0x00004000)) return false;
	if(b[3] != (b[3] & 0x1cf00e7f) + 0x00081100 + (c[3] & 0x03000000)) return false;
	if(a[4] != (a[4] & 0x3cf01e77) + 0x410fe008) return false;
	if(d[4] != (d[4] & 0x1cf01e77) + 0x000be188) return false;
	if(c[4] != (c[4] & 0x80ff3f80) + 0x61008000) return false;
	if(b[4] != (b[4] & 0x03dfff88) + 0x20000000 + (c[4] & 0x80000000) + ((~c[4]) & 0x00200000)) return false;

	return true;
}

int main()
{
	initialise();
	uint32 m0[16], m1[16];
	for(int i=0;i<16;i++)
	{
		cin>>m0[i];
		m1[i] = m0[i];
	}
	
	m1[4] += shifts[31];
	m1[11] += (1<<15);
	m1[14] += shifts[31];
	
	for(int i=0;i<16;i++)
		cout<<m1[i] - m0[i]<<" ";
	cout<<endl;

	a[0] = 0x67452301;
	b[0] = 0xefcdab89;
	c[0] = 0x98badcfe;
	d[0] = 0x10325476;
	md5_hash(false,m0);
	a[0] = 0x67452301;
	b[0] = 0xefcdab89;
	c[0] = 0x98badcfe;
	d[0] = 0x10325476;
	md5_hash(true,m1);
	cout<<aa1 - aa0<<endl;
	cout<<bb1 - bb0<<endl;
	cout<<cc1 - cc0<<endl;
	cout<<dd1 - dd0<<endl;
}