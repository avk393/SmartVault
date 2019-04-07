#define C_01 	1195
#define B_01	1266
#define BF_01	1341
#define A_01	1421
#define AF_01	1505
#define G_01	1595
#define GF_01 1689
#define F_01  1790
#define E_01  1896
#define EF_01	2009
#define D_01	2129
#define DF_01 2255 // 
#define C 	2389	 // 1046.5 Hz
#define B 	2531	 // 987.8 Hz
#define BF	2681	 // 932.3 Hz
#define A 	2841	 // 880 Hz
#define AF	3010	 // 830.6 Hz
#define G 	3189	 // 784 Hz
#define GF	3378	 // 740 Hz
#define F 	3579	 // 698.5 Hz
#define E 	3792	 // 659.3 Hz
#define EF	4018	 // 622.3 Hz
#define D 	4257	 // 587.3 Hz
#define DF	4510	 // 554.4 Hz
#define C_0	4778	 // 523.3 Hz
#define B_0	5062	 // 493.9 Hz
#define BF_0	5363	 // 466.2 Hz
#define A_0	5682	 // 440 Hz
#define AF_0	6020	 // 415.3 Hz
#define G_0	6378	 // 392 Hz
#define GF_0	6757	 // 370 Hz
#define F_0	7159	 // 349.2 Hz
#define E_0	7584	 // 329.6 Hz
#define EF_0	8035	 // 311.1 Hz
#define D_0	8513	 // 293.7 Hz
#define DF_0	9019	 // 277.2 Hz
#define C_7	9556	 // 261.6 Hz
#define B_7	10200	 // 246.9 Hz (Sounds a little sharp
#define BF_7	10726	 // 233.1 Hz	(BE CAREFUL WITH THESE 2
#define A_7	11364	 // 220 Hz
#define AF_7	12039	 // 207.7 Hz
#define G_7	12755	 // 196 Hz
#define GF_7	13514	 // 185 Hz
#define F_7	14317	 // 174.6 Hz
#define E_7	15169	 // 164.8 Hz
#define EF_7	16071	 // 155.6 Hz
#define D_7	17026	 // 146.8 Hz
#define DF_7	18039	 // 138.6 Hz
#define C_6	19111	 // 130.8 Hz

#ifndef MUSICSTRUCT_H
#define MUSICSTRUCT_H
// time signature
// beats per bar 
struct bar{
	const unsigned short *beats;
	const unsigned short *bar;
};
struct instrument{
	const unsigned short *melody;		// horizontal
	const unsigned short *harmonic;	// vertial value
};
typedef const struct instrument instrument;
struct SimpleSong{ 
	int length;
	int  tempo; //assuming always 4
	char name[30];
	struct instrument instrument;
	const unsigned long *melody;
	const unsigned long *harmonic;
};

typedef const struct SimpleSong SimpleSong;
#endif 

extern const SimpleSong TEST1;
