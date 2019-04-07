
#include <stdint.h>
#include "../../inc/tm4c123gh6pm.h"
#include "PLL.h"
#include <stdbool.h>
#include "musicStruct.h"






const unsigned short TestDacInstrument[32] =
{
	0,0,0,0,600,600,600,600,
	1100,1100,1100,1100,1600,1600,1600,1600,
	2100,2100,2100,2100,2600,2600,2600,2600,
	3100,3100,3100,3100,4095,4095,4095,4095
};
const unsigned short oneFour[2] =
{
	1,4
};
const unsigned short twoFour[2] =
{
	2,4
}; 
const unsigned short threeFour[2] =
{
	3,4
};
const unsigned short fourFour[2] =
{
	4,4
};

const unsigned short Wave[32] = {  
  2048,2438,2813,3159,3462,3711,3896,4010,4048,4010,3896,
  3711,3462,3159,2813,2438,2048,1658,1283,937,634,385,
  200,86,48,86,200,385,634,937,1283,1658
};  
const unsigned short Flute[32] = {  
  1007,1252,1374,1548,1698,1797,1825,1797,1675,1562,1383,
  1219,1092,1007,913,890,833,847,810,777,744,674,
  598,551,509,476,495,533,589,659,758,876
};  
const unsigned short Trumpet[32] = {  
  2013,2179,2318,2397,2135,1567,572,153,1567,3043,2973,
  2353,2135,2074,2170,2126,2022,2030,2091,2126,2022,2022,
  2118,2231,2170,2153,2161,2214,2179,2100,2030,2091
};
const unsigned long  test1[128] = {
  G,C,E,C,
  E,D,C,A,
  G,G,C,E,
  C,E,D,G,
	E,G,E,C,  
  G,A,A,G,
  G,C,E,D,
	
	C,C,C,C,
	D,D,D,D,
	E,E,E,E,
	F,F,F,F,
	G,G,G,G,
	A,A,A,A,
  B,B,B,B,
  C,C,C,C,
  BF,BF,BF,BF,
  

  A,D,BF_0,G_0,
  G,D,BF_0,G_0,
  GF,D,BF_0,G_0,
  G,D,BF_0,G_0,
  
  BF,EF,C_0,A_0,
  A,EF,C_0,A_0,
  AF,EF,C_0,A_0,
  A,EF,C_0,A_0,

  C,D,BF_0,G_0,
  BF,D,BF_0,G_0,
  A,D,BF_0,G_0,
  BF,D,BF_0,G_0,
  
  A,BF_0,G_0,E_0,
  G,BF_0,G_0,E_0,
  F,BF_0,G_0,E_0,
	E,BF_0,G_0,E_0
	
};	
const unsigned long  test1low[128] = {			
	
  BF_7,BF_7,D_0,A_0,
  A_0,A_0,A_0,A_0,
  A_0,D_0,A_0,G_0,
  C_0,A_0,G_0,D_0,
    
  A_7,A_7,C_7,G_0,
  G_0,G_0,G_0,G_0,
  G_0,A_7,G_0,F_0,
  C_0,A_0,G_0,C_7,
  
  G_7,G_7,C_7,F_0,
  F_0,F_0,F_0,F_0,
  F_0,G_7,F_0,E_0,
  G_0,E_0,C_7,C_7,

  F_7,F_7,A_7,E_0,
  E_0,E_0,E_0,E_0,
  F_7,C_7,E_0,D_0,
  G_0,F_0,C_7,BF_7,

  BF_7,BF_7,D_0,A_0,
  A_0,A_0,A_0,A_0,
  BF_7,D_0,A_0,G_0,
  D,A_0,G_0,D_0,
  
  A_7,A_7,C_7,C_0,
  C_0,C_0,C_0,C_0,
  D_0,D_0,C_0,A_0,
  EF,D,C_0,A_0,

  G_7,BF_7,D_0,BF_0,
  BF_0,BF_0,BF_0,BF_0,
  G_0,D_0,BF_0,A_0,
  C_0,BF_0,G_0,D_0,
  
  C_7,C_7,G_0,BF_0,
  BF_0,BF_0,BF_0,BF_0,
  C_7,C_7,BF_0,G_0,
	E,D,G,E
	
};
const unsigned long  jingleBells[128] = {			
	
  E_0,E_0,E_0,0,
  E_0,E_0,E_0,0,
  E_0,G_0,C_0,D_0,
  E_0,F_0,F_0,F_0,
    
  F_0,F_0,E_0,E_0,
  E_0,E_0,E_0,D_0,
  D_0,E_0,D_0,D_0,
  G_0,0,0,0,
  
  E_0,E_0,E_0,0,
  E_0,E_0,E_0,0,
  E_0,G_0,C_0,D_0,
  E_0,F_0,F_0,F_0,

  F_0,F_0,E_0,E_0,
  E_0,E_0,G_0,G_0,
  F_0,D_0,C_0,0,
  G,E_0,D_0,C_0,

  G,G,G,G,
  E_0,D_0,C_0,A_0,
  A_0,F_0,E_0,D_0,
  B_0,G_0,G_0,F_0,
  
  D_0,E_0,G,E_0,
  D_0,C_0,G,0,
  G,E_0,D_0,C_0,
  A_0,0,0,A_0,

  A_0,F_0,E_0,D_0,
  G_0,G_0,G_0,G_0,
  A_0,G_0,F_0,D_0,
  C_0,G_0,0,0,
  
  0,0,0,0,
  0,0,0,0,
  0,0,0,0,
  0,0,0,0,
	
};	

const unsigned long  test1Frequency[128] = {			
	
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
    
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,

  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,

  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,

  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
	
};	

const unsigned long  MidleC[128] = {			
	
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
    
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,

  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,

  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,

  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
  C_0,C_0,C_0,C_0,
	
};	

const unsigned long  MidleG[128] = {			
	
  G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	
  G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,

  
  G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,


  G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,


  G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,

  
  G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,

  G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,

  
  G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,
	G_0,G_0,G_0,G_0,

	
};	



const unsigned long  MidleF[128] = {			
	
  F,F,F,F,
	F,F,F,F,
	F,F,F,F,
	F,F,F,F,
	
  F,F,F,F,
	F,F,F,F,
	F,F,F,F,
	F,F,F,F,

  
  F,F,F,F,
	F,F,F,F,
	F,F,F,F,
	F,F,F,F,


  F,F,F,F,
	F,F,F,F,
	F,F,F,F,
	F,F,F,F,


  F,F,F,F,
	F,F,F,F,
	F,F,F,F,
	F,F,F,F,

  
  F,F,F,F,
	F,F,F,F,
	F,F,F,F,
	F,F,F,F,
	
  F,F,F,F,
	F,F,F,F,
	F,F,F,F,
	F,F,F,F,

  
    F,F,F,F,
	F,F,F,F,
	F,F,F,F,
	F,F,F,F,

	
};	

const unsigned long  MidleB[128] = {			
	
  B_0,B_0,B_0,B_0,
B_0,B_0,B_0,B_0,
B_0,B_0,B_0,B_0,
B_0,B_0,B_0,B_0,
	
  B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,

  
  B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,


  B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,


  B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,

  
	B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,

  B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,

  
  B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,
	B_0,B_0,B_0,B_0,

	
};	


//const SimpleSong TEST1 = {128,4,"Zelda",{Wave,Wave},test1low,test1low};
//const SimpleSong TEST1 = {128,4,"Zelda ",{TestDacInstrument,TestDacInstrument},test1Frequency,test1Frequency};
const SimpleSong JINGLE = {128,8,"Jingle Bells",{Wave,Wave},jingleBells,jingleBells};
const SimpleSong BADSOUND = {128,8,"Bad Sound", {Wave,Wave},MidleB,MidleC};
const SimpleSong GOODSOUND = {128,8,"Good Sound",{Wave,Wave},MidleF,MidleG};

