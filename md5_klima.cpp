#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "md5_klima.hpp"
using namespace std;

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define RL(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#define RR(x, n) (((x) >> (n)) | ((x) << (32-(n))))

uint32 t[64], s[64], m[16], shifts[32];
uint32 a0, b0, c0, d0;
uint32 Q[65];
uint32 mx[16], my[16];

uint32 md5_step(int i)
{
	if( i<= 32) return Q[i-1] + RL( G(Q[i-1], Q[i-2], Q[i-3]) + Q[i-4] + m[sigma(i)] + t[i-1] , s[i-1]);
	if( i<= 48) return Q[i-1] + RL( H(Q[i-1], Q[i-2], Q[i-3]) + Q[i-4] + m[sigma(i)] + t[i-1] , s[i-1]);
	return Q[i-1] + RL( I(Q[i-1], Q[i-2], Q[i-3]) + Q[i-4] + m[sigma(i)] + t[i-1] , s[i-1]);
}

void md5_hash()
{
	for(int i=21; i<= 64; i++) Q[i] = md5_step(i);
}

int pos_bit(uint32 num, int pos)
{
	return (num & shifts[pos-1]) != 0;
}

bool verify()
{
	if(pos_bit(Q[21],18) != pos_bit(Q[20],18)) return false;
	if(pos_bit(Q[21],32) != 0) return false;
	if(pos_bit(Q[22],32) != 0) return false;
	if(pos_bit(Q[23],32) != 0) return false;
	if(pos_bit(Q[24],32) != 1) return false;
	if(pos_bit(H(Q[34],Q[33],Q[32]) , 32 ) != 0) return false;
	if(pos_bit(Q[48],32) != pos_bit(Q[46],32)) return false;
	if(pos_bit(Q[49],32) != pos_bit(Q[47],32)) return false;
	if(pos_bit(Q[50],32) == pos_bit(Q[48],32)) return false;
	if(pos_bit(Q[51],32) != pos_bit(Q[49],32)) return false;
	if(pos_bit(Q[52],32) != pos_bit(Q[50],32)) return false;
	if(pos_bit(Q[53],32) != pos_bit(Q[51],32)) return false;
	if(pos_bit(Q[54],32) != pos_bit(Q[52],32)) return false;
	if(pos_bit(Q[55],32) != pos_bit(Q[53],32)) return false;
	if(pos_bit(Q[56],32) != pos_bit(Q[54],32)) return false;
	if(pos_bit(Q[57],32) != pos_bit(Q[55],32)) return false;
	if(pos_bit(Q[58],32) != pos_bit(Q[56],32)) return false;
	if(pos_bit(Q[59],32) != pos_bit(Q[57],32)) return false;
	if(pos_bit(Q[60],26) != 0) return false;
	if(pos_bit(Q[60],32) == pos_bit(Q[58],32)) return false;
	if(pos_bit(Q[61],26) != 1) return false;
	if(pos_bit(Q[61],27) != 0) return false;
	if(pos_bit(Q[61],32) != pos_bit(Q[59],32)) return false;
	if(pos_bit(Q[62],32) != pos_bit(Q[60],32)) return false;
	if(pos_bit(Q[63],32) != pos_bit(Q[62],32)) return false;

	uint32 aa0=Q[61]+a0;
	uint32 bb0=Q[64]+b0;
	uint32 cc0=Q[63]+c0;
	uint32 dd0=Q[62]+d0;

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

void collision()
{
	while(true)
	{
		Q[ 3] = (uint32(rand()) & 0xFFF7F7BF);
		Q[ 4] = (uint32(rand()) & 0x7f00000f) + 0x80080830 + (Q[3] & 0x0077f780);
		Q[ 5] = (uint32(rand()) & 0x01000000) + 0x88400025;
		Q[ 6] = 0x027fbc41 + (Q[ 5] & 0x01000000);
		Q[ 7] = 0x03fef820;
		Q[ 8] = (uint32(rand()) & 0x00605000) + 0x01910540;
		Q[ 9] = (uint32(rand()) & 0x00e04000) + 0xfb102f3d + (Q[ 8] & 0x00001000);
		Q[10] = (uint32(rand()) & 0x0f004e3c) + 0x701f9040;
		Q[11] = (uint32(rand()) & 0x0a100a3c) + 0x20e180c2 + (Q[10] & 0x00004000);
		Q[12] = (uint32(rand()) & 0x1cf00e7f) + 0x00081100 + (Q[11] & 0x03000000);
		Q[13] = (uint32(rand()) & 0x3cf01e77) + 0x410fe008;
		Q[14] = (uint32(rand()) & 0x1cf01e77) + 0x000be188;
		Q[15] = (uint32(rand()) & 0x80ff3f80) + 0x61008000;
		Q[16] = (uint32(rand()) & 0x03dfff88) + 0x20000000 + (Q[15] & 0x80000000) + ((~Q[15]) & 0x00200000);

		m[ 6]=RR(Q[7 ]-Q[6 ],17)-F(Q[6 ],Q[5 ],Q[4 ])-Q[3 ]-0xa8304613;
		m[ 7]=RR(Q[8 ]-Q[7 ],22)-F(Q[7 ],Q[6 ],Q[5 ])-Q[4 ]-0xfd469501;
		m[ 8]=RR(Q[9 ]-Q[8 ], 7)-F(Q[8 ],Q[7 ],Q[6 ])-Q[5 ]-0x698098d8;
		m[ 9]=RR(Q[10]-Q[9 ],12)-F(Q[9 ],Q[8 ],Q[7 ])-Q[6 ]-0x8b44f7af;
		m[10]=RR(Q[11]-Q[10],17)-F(Q[10],Q[9 ],Q[8 ])-Q[7 ]-0xffff5bb1;
		m[11]=RR(Q[12]-Q[11],22)-F(Q[11],Q[10],Q[9 ])-Q[8 ]-0x895cd7be;
		m[12]=RR(Q[13]-Q[12], 7)-F(Q[12],Q[11],Q[10])-Q[9 ]-0x6b901122;
		m[13]=RR(Q[14]-Q[13],12)-F(Q[13],Q[12],Q[11])-Q[10]-0xfd987193;
		m[14]=RR(Q[15]-Q[14],17)-F(Q[14],Q[13],Q[12])-Q[11]-0xa679438e;
		m[15]=RR(Q[16]-Q[15],22)-F(Q[15],Q[14],Q[13])-Q[12]-0x49b40821;

		while(true)
		{
			Q[17] = (uint32(rand()) & 0x3ffd7ff7) + 0x40000000 + (Q[16] & 0x80008008);
			Q[18] = Q[17]+RL(G(Q[17],Q[16],Q[15])+Q[14]+m[6 ]+0xc040b340, 9);
			Q[19] = Q[18]+RL(G(Q[18],Q[17],Q[16])+Q[15]+m[11]+0x265e5a51,14);

			if(pos_bit(Q[18],18) != 1) continue;
			if(pos_bit(Q[18],30) != pos_bit(Q[17],30)) continue;
			if(pos_bit(Q[18],32) != 0) continue;
			if(pos_bit(Q[19],18) != 0) continue;
			if(pos_bit(Q[19],32) != 0) continue;

			break;
		}

		m[ 1] = RR(Q[17]-Q[16], 5)-G(Q[16],Q[15],Q[14])-Q[13]-0xf61e2562;
		uint32 Z;
		if(pos_bit(Q[19],32) == 0)
		{
			 Q[20] = 0;
			 Z = 2*((1<<30) - 1) + 1;
		}
		else
		{
			 Q[20] = (1<<31);
			 // Z = (1<<32) - 1;
			 cout<<"Error"<<endl;
		}

		for(;Q[20] <= Z;Q[20]++)
		{
			//cout<<Q[20]<<endl;
			m[ 0] = RR(Q[20]-Q[19],20)-G(Q[19],Q[18],Q[17])-Q[16]-0xe9b6c7aa;
			Q[ 1] = b0 + RL(F(b0, c0, d0) + a0 + m[0]+ 0xd76aa478, 7);
			Q[ 2] = Q[1] + RL(F(Q[1], b0, c0) +  d0 + m[1] + 0xe8c7b756,12);
			m[ 2] = RR(Q[3]-Q[2],17)-F(Q[2],Q[1],b0)- c0 - 0x242070db;
			m[ 3] = RR(Q[4]-Q[3],22)-F(Q[3],Q[2],Q[1])- b0 - 0xc1bdceee;
			m[ 4] = RR(Q[5]-Q[4], 7)-F(Q[4],Q[3],Q[2])-Q[1] - 0xf57c0faf;
			m[ 5] = RR(Q[6]-Q[5],12)-F(Q[5],Q[4],Q[3])-Q[2] - 0x4787c62a;

			md5_hash();
			if(verify()) break;
		}

		if(Q[20] > Z) continue;
		break;
	}
}

int main()
{
	/*time_t seed = time(0);
	cout<<seed<<endl;
	srand (1525464394);*/
	a0 = 0x67452301;
	b0 = 0xefcdab89;
	c0 = 0x98badcfe;
	d0 = 0x10325476;
	initialise();
	collision();

	for(int i=0;i<16;i++)
		cout<<m[i]<<endl;
	cout<<endl;

	for(int i=1;i<=61;i+=4)
	{
		cout<< i/4 + 1<<endl;
		cout<<"   a d c b"<<endl;
		for(int j=0;j<32;j++)
		{
			if(j<9) cout<<"0";
			cout<< j+1 << " " << ((Q[i]&(1<<j))>>j) << " " << ((Q[i+1]&(1<<j))>>j) << " " << ((Q[i+2]&(1<<j))>>j) << " " << ((Q[i+3]&(1<<j))>>j)<<endl;
		}
		cout<<endl;
	}
}