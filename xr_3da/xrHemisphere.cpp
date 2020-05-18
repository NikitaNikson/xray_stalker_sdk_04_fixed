#include "stdafx.h"
#pragma hdrstop

#include "xrHemisphere.h"

#define HEMI1_VERTS	26
#define HEMI1_FACES	40
#define HEMI2_VERTS	91
#define HEMI2_FACES	160
#define HEMI3_VERTS	196

#define HEMI4_VERTS 341
#define HEMI4_FACES 640

#pragma warning (disable:4305)
const Fvector hemi_1[HEMI1_VERTS] = {
	{ 0.525730,	 0.850655,	-0.000000},
	{ 0.162460,	 0.850655,	 0.500000},
	{ 0.000000,	 1.000000,	-0.000000},
	{-0.425324,	 0.850655,	 0.309015},
	{-0.425324,	 0.850655,	-0.309017},
	{ 0.162460,	 0.850655,	-0.500000},
	{ 0.688194,	 0.525730,	 0.500000},
	{-0.262865,	 0.525730,	 0.809013},
	{-0.850647,	 0.525730,	-0.000001},
	{-0.262865,	 0.525730,	-0.809021},
	{ 0.688194,	 0.525730,	-0.500000},
	{ 0.894424,	 0.447212,	-0.000000},
	{ 0.276394,	 0.447212,	 0.850647},
	{-0.723610,	 0.447212,	 0.525730},
	{-0.723610,	 0.447212,	-0.525734},
	{ 0.276394,	 0.447212,	-0.850655},
	{ 0.951057,	 0.000000,	 0.309017},
	{ 0.587788,	 0.000000,	 0.809013},
	{ 0.000000,	 0.000000,	 1.000000},
	{-0.587784,	 0.000000,	 0.809013},
	{-0.951057,	 0.000000,	 0.309015},
	{-0.951057,	 0.000000,	-0.309017},
	{-0.587784,	 0.000000,	-0.809021},
	{ 0.000000,	 0.000000,	-1.000000},
	{ 0.587788,	 0.000000,	-0.809013},
	{ 0.951057,	 0.000000,	-0.309017},
};
const u16 hemi_1v[HEMI1_FACES*3] = {
	0,		1,		2,
	1,		3,		2,
	3,		4,		2,
	4,		5,		2,
	5,		0,		2,
	1,		0,		6,
	3,		1,		7,
	4,		3,		8,
	5,		4,		9,
	0,		5,		10,
	10,		11,		0,
	11,		6,		0,
	6,		12,		1,
	12,		7,		1,
	7,		13,		3,
	13,		8,		3,
	8,		14,		4,
	14,		9,		4,
	9,		15,		5,
	15,		10,		5,
	6,		11,		16,
	12,		6,		17,
	7,		12,		18,
	13,		7,		19,
	8,		13,		20,
	14,		8,		21,
	9,		14,		22,
	15,		9,		23,
	10,		15,		24,
	11,		10,		25,
	25,		16,		11,
	16,		17,		6,
	17,		18,		12,
	18,		19,		7,
	19,		20,		13,
	20,		21,		8,
	21,		22,		14,
	22,		23,		9,
	23,		24,		15,
	24,		25,		10,
};

const Fvector hemi_2[HEMI2_VERTS] = 
{
	{ 0.273268,	 0.961937,	-0.000000},
	{ 0.084444,	 0.961937,	 0.259892},
	{ 0.000000,	 1.000000,	-0.000000},
	{ 0.525730,	 0.850655,	-0.000000},
	{ 0.361805,	 0.894424,	 0.262865},
	{ 0.162460,	 0.850655,	 0.500000},
	{-0.221077,	 0.961937,	 0.160622},
	{-0.138196,	 0.894424,	 0.425324},
	{-0.425324,	 0.850655,	 0.309015},
	{-0.221077,	 0.961937,	-0.160623},
	{-0.447212,	 0.894424,	-0.000001},
	{-0.425324,	 0.850655,	-0.309017},
	{ 0.084445,	 0.961937,	-0.259892},
	{-0.138196,	 0.894424,	-0.425327},
	{ 0.162460,	 0.850655,	-0.500000},
	{ 0.361805,	 0.894424,	-0.262865},
	{ 0.447212,	 0.723610,	 0.525730},
	{ 0.638195,	 0.723610,	 0.262865},
	{ 0.688194,	 0.525730,	 0.500000},
	{-0.361801,	 0.723610,	 0.587784},
	{-0.052786,	 0.723610,	 0.688187},
	{-0.262865,	 0.525730,	 0.809013},
	{-0.670822,	 0.723610,	-0.162460},
	{-0.670822,	 0.723610,	 0.162458},
	{-0.850647,	 0.525730,	-0.000001},
	{-0.052786,	 0.723610,	-0.688194},
	{-0.361801,	 0.723610,	-0.587788},
	{-0.262865,	 0.525730,	-0.809021},
	{ 0.638195,	 0.723610,	-0.262865},
	{ 0.447212,	 0.723610,	-0.525734},
	{ 0.688194,	 0.525730,	-0.500000},
	{ 0.738174,	 0.674606,	-0.000000},
	{ 0.822617,	 0.505722,	-0.259892},
	{ 0.894424,	 0.447212,	-0.000000},
	{ 0.822617,	 0.505722,	 0.259892},
	{ 0.228109,	 0.674606,	 0.702049},
	{ 0.501377,	 0.505722,	 0.702049},
	{ 0.276394,	 0.447212,	 0.850647},
	{ 0.007032,	 0.505722,	 0.862671},
	{-0.597195,	 0.674606,	 0.433887},
	{-0.512752,	 0.505722,	 0.693779},
	{-0.723602,	 0.447212,	 0.525730},
	{-0.818275,	 0.505722,	 0.273266},
	{-0.597195,	 0.674606,	-0.433887},
	{-0.818275,	 0.505722,	-0.273268},
	{-0.723602,	 0.447212,	-0.525734},
	{-0.512753,	 0.505722,	-0.693779},
	{ 0.228109,	 0.674606,	-0.702049},
	{ 0.007032,	 0.505722,	-0.862671},
	{ 0.276394,	 0.447212,	-0.850655},
	{ 0.501377,	 0.505722,	-0.702049},
	{ 0.861801,	 0.276394,	 0.425323},
	{ 0.959251,	 0.232454,	 0.160622},
	{ 0.951057,	 0.000000,	 0.309017},
	{ 0.449184,	 0.232454,	 0.862671},
	{ 0.670822,	 0.276394,	 0.688187},
	{ 0.587788,	 0.000000,	 0.809013},
	{-0.138196,	 0.276394,	 0.951057},
	{ 0.143665,	 0.232454,	 0.961937},
	{ 0.000000,	 0.000000,	 1.000000},
	{-0.681641,	 0.232454,	 0.693779},
	{-0.447212,	 0.276394,	 0.850647},
	{-0.587784,	 0.000000,	 0.809013},
	{-0.947212,	 0.276394,	 0.162458},
	{-0.870460,	 0.232454,	 0.433887},
	{-0.951057,	 0.000000,	 0.309015},
	{-0.870460,	 0.232454,	-0.433887},
	{-0.947212,	 0.276394,	-0.162460},
	{-0.951057,	 0.000000,	-0.309017},
	{-0.447212,	 0.276394,	-0.850655},
	{-0.681641,	 0.232454,	-0.693779},
	{-0.587784,	 0.000000,	-0.809021},
	{ 0.143665,	 0.232454,	-0.961937},
	{-0.138196,	 0.276394,	-0.951057},
	{ 0.000000,	 0.000000,	-1.000000},
	{ 0.670822,	 0.276394,	-0.688194},
	{ 0.449188,	 0.232454,	-0.862671},
	{ 0.587788,	 0.000000,	-0.809013},
	{ 0.959251,	 0.232454,	-0.160623},
	{ 0.861801,	 0.276394,	-0.425327},
	{ 0.951057,	 0.000000,	-0.309017},
	{ 1.000000,	 0.000000,	-0.000000},
	{ 0.809021,	 0.000000,	 0.587784},
	{ 0.309017,	 0.000000,	 0.951057},
	{-0.309015,	 0.000000,	 0.951057},
	{-0.809013,	 0.000000,	 0.587784},
	{-1.000000,	 0.000000,	-0.000001},
	{-0.809013,	 0.000000,	-0.587788},
	{-0.309015,	 0.000000,	-0.951057},
	{ 0.309017,	 0.000000,	-0.951057},
	{ 0.809021,	 0.000000,	-0.587788},
};					   	
const u16 hemi_2v[HEMI2_FACES*3] = {
	0,		1,		2,
	3,		4,		0,
	4,		1,		0,
	4,		5,		1,
	1,		6,		2,
	5,		7,		1,
	7,		6,		1,
	7,		8,		6,
	6,		9,		2,
	8,		10,		6,
	10,		9,		6,
	10,		11,		9,
	9,		12,		2,
	11,		13,		9,
	13,		12,		9,
	13,		14,		12,
	12,		0,		2,
	14,		15,		12,
	15,		0,		12,
	15,		3,		0,
	16,		17,		18,
	5,		4,		16,
	4,		17,		16,
	4,		3,		17,
	19,		20,		21,
	8,		7,		19,
	7,		20,		19,
	7,		5,		20,
	22,		23,		24,
	11,		10,		22,
	10,		23,		22,
	10,		8,		23,
	25,		26,		27,
	14,		13,		25,
	13,		26,		25,
	13,		11,		26,
	28,		29,		30,
	3,		15,		28,
	15,		29,		28,
	15,		14,		29,
	28,		31,		3,
	30,		32,		28,
	32,		31,		28,
	32,		33,		31,
	31,		17,		3,
	33,		34,		31,
	34,		17,		31,
	34,		18,		17,
	16,		35,		5,
	18,		36,		16,
	36,		35,		16,
	36,		37,		35,
	35,		20,		5,
	37,		38,		35,
	38,		20,		35,
	38,		21,		20,
	19,		39,		8,
	21,		40,		19,
	40,		39,		19,
	40,		41,		39,
	39,		23,		8,
	41,		42,		39,
	42,		23,		39,
	42,		24,		23,
	22,		43,		11,
	24,		44,		22,
	44,		43,		22,
	44,		45,		43,
	43,		26,		11,
	45,		46,		43,
	46,		26,		43,
	46,		27,		26,
	25,		47,		14,
	27,		48,		25,
	48,		47,		25,
	48,		49,		47,
	47,		29,		14,
	49,		50,		47,
	50,		29,		47,
	50,		30,		29,
	51,		52,		53,
	18,		34,		51,
	34,		52,		51,
	34,		33,		52,
	54,		55,		56,
	37,		36,		54,
	36,		55,		54,
	36,		18,		55,
	57,		58,		59,
	21,		38,		57,
	38,		58,		57,
	38,		37,		58,
	60,		61,		62,
	41,		40,		60,
	40,		61,		60,
	40,		21,		61,
	63,		64,		65,
	24,		42,		63,
	42,		64,		63,
	42,		41,		64,
	66,		67,		68,
	45,		44,		66,
	44,		67,		66,
	44,		24,		67,
	69,		70,		71,
	27,		46,		69,
	46,		70,		69,
	46,		45,		70,
	72,		73,		74,
	49,		48,		72,
	48,		73,		72,
	48,		27,		73,
	75,		76,		77,
	30,		50,		75,
	50,		76,		75,
	50,		49,		76,
	78,		79,		80,
	33,		32,		78,
	32,		79,		78,
	32,		30,		79,
	78,		52,		33,
	80,		81,		78,
	81,		52,		78,
	81,		53,		52,
	51,		55,		18,
	53,		82,		51,
	82,		55,		51,
	82,		56,		55,
	54,		58,		37,
	56,		83,		54,
	83,		58,		54,
	83,		59,		58,
	57,		61,		21,
	59,		84,		57,
	84,		61,		57,
	84,		62,		61,
	60,		64,		41,
	62,		85,		60,
	85,		64,		60,
	85,		65,		64,
	63,		67,		24,
	65,		86,		63,
	86,		67,		63,
	86,		68,		67,
	66,		70,		45,
	68,		87,		66,
	87,		70,		66,
	87,		71,		70,
	69,		73,		27,
	71,		88,		69,
	88,		73,		69,
	88,		74,		73,
	72,		76,		49,
	74,		89,		72,
	89,		76,		72,
	89,		77,		76,
	75,		79,		30,
	77,		90,		75,
	90,		79,		75,
	90,		80,		79,
};

const Fvector hemi_3[HEMI3_VERTS] = 
{					   	
	{+0.0000,	+0.5000,	+0.0000	},
	{+0.2629,	+0.4253,	+0.0000	},
	{+0.0812,	+0.4253,	+0.2500	},
	{-0.2127,	+0.4253,	+0.1545	},
	{-0.2127,	+0.4253,	-0.1545	},
	{+0.0812,	+0.4253,	-0.2500	},
	{+0.4472,	+0.2236,	+0.0000	},
	{+0.1382,	+0.2236,	+0.4253	},
	{-0.3618,	+0.2236,	+0.2629	},
	{-0.3618,	+0.2236,	-0.2629	},
	{+0.1382,	+0.2236,	-0.4253	},
	{+0.3441,	+0.2629,	+0.2500	},
	{-0.1314,	+0.2629,	+0.4045	},
	{-0.4253,	+0.2629,	-0.0000	},
	{-0.1314,	+0.2629,	-0.4045	},
	{+0.3441,	+0.2629,	-0.2500	},
	{+0.4755,	+0.0000,	+0.1545	},
	{+0.2939,	+0.0000,	+0.4045	},
	{-0.0000,	+0.0000,	+0.5000	},
	{-0.2939,	+0.0000,	+0.4045	},
	{-0.4755,	+0.0000,	+0.1545	},
	{-0.4755,	+0.0000,	-0.1545	},
	{-0.2939,	+0.0000,	-0.4045	},
	{+0.0000,	+0.0000,	-0.5000	},
	{+0.2939,	+0.0000,	-0.4045	},
	{+0.4755,	+0.0000,	-0.1545	},
	{+0.0917,	+0.4915,	+0.0000	},
	{+0.1804,	+0.4663,	+0.0000	},
	{+0.0283,	+0.4915,	+0.0872	},
	{+0.0557,	+0.4663,	+0.1715	},
	{-0.0742,	+0.4915,	+0.0539	},
	{-0.1459,	+0.4663,	+0.1060	},
	{-0.0742,	+0.4915,	-0.0539	},
	{-0.1459,	+0.4663,	-0.1060	},
	{+0.0283,	+0.4915,	-0.0872	},
	{+0.0557,	+0.4663,	-0.1715	},
	{+0.2106,	+0.4448,	+0.0884	},
	{+0.1492,	+0.4448,	+0.1730	},
	{-0.0190,	+0.4448,	+0.2276	},
	{-0.1184,	+0.4448,	+0.1953	},
	{-0.2224,	+0.4448,	+0.0523	},
	{-0.2224,	+0.4448,	-0.0523	},
	{-0.1184,	+0.4448,	-0.1953	},
	{-0.0190,	+0.4448,	-0.2276	},
	{+0.1492,	+0.4448,	-0.1730	},
	{+0.2106,	+0.4448,	-0.0884	},
	{+0.3364,	+0.3699,	+0.0000	},
	{+0.3986,	+0.3019,	+0.0000	},
	{+0.1040,	+0.3699,	+0.3200	},
	{+0.1232,	+0.3019,	+0.3791	},
	{-0.2722,	+0.3699,	+0.1978	},
	{-0.3225,	+0.3019,	+0.2343	},
	{-0.2722,	+0.3699,	-0.1978	},
	{-0.3225,	+0.3019,	-0.2343	},
	{+0.1040,	+0.3699,	-0.3200	},
	{+0.1232,	+0.3019,	-0.3791	},
	{+0.3036,	+0.3873,	+0.0884	},
	{+0.3311,	+0.3323,	+0.1730	},
	{+0.0097,	+0.3873,	+0.3161	},
	{-0.0622,	+0.3323,	+0.3683	},
	{-0.2976,	+0.3873,	+0.1069	},
	{-0.3695,	+0.3323,	+0.0547	},
	{-0.1936,	+0.3873,	-0.2500	},
	{-0.1662,	+0.3323,	-0.3346	},
	{+0.1779,	+0.3873,	-0.2614	},
	{+0.2668,	+0.3323,	-0.2614	},
	{+0.3036,	+0.3873,	-0.0884	},
	{+0.3311,	+0.3323,	-0.1730	},
	{+0.1779,	+0.3873,	+0.2614	},
	{+0.2668,	+0.3323,	+0.2614	},
	{-0.1936,	+0.3873,	+0.2500	},
	{-0.1662,	+0.3323,	+0.3346	},
	{-0.2976,	+0.3873,	-0.1069	},
	{-0.3695,	+0.3323,	-0.0547	},
	{+0.0097,	+0.3873,	-0.3161	},
	{-0.0622,	+0.3323,	-0.3683	},
	{+0.4269,	+0.2452,	+0.0872	},
	{+0.3922,	+0.2584,	+0.1715	},
	{+0.0490,	+0.2452,	+0.4330	},
	{-0.0420,	+0.2584,	+0.4260	},
	{-0.3967,	+0.2452,	+0.1804	},
	{-0.4181,	+0.2584,	+0.0917	},
	{-0.2941,	+0.2452,	-0.3215	},
	{-0.2165,	+0.2584,	-0.3693	},
	{+0.2149,	+0.2452,	-0.3791	},
	{+0.2843,	+0.2584,	-0.3200	},
	{+0.3922,	+0.2584,	-0.1715	},
	{+0.4269,	+0.2452,	-0.0872	},
	{+0.2843,	+0.2584,	+0.3200	},
	{+0.2149,	+0.2452,	+0.3791	},
	{-0.2165,	+0.2584,	+0.3693	},
	{-0.2941,	+0.2452,	+0.3215	},
	{-0.4181,	+0.2584,	-0.0917	},
	{-0.3967,	+0.2452,	-0.1804	},
	{-0.0420,	+0.2584,	-0.4260	},
	{+0.0490,	+0.2452,	-0.4330	},
	{+0.4728,	+0.1534,	+0.0539	},
	{+0.4824,	+0.0780,	+0.1060	},
	{+0.4063,	+0.1819,	+0.2276	},
	{+0.4508,	+0.0930,	+0.1953	},
	{+0.3421,	+0.1819,	+0.3161	},
	{+0.3251,	+0.0930,	+0.3683	},
	{+0.1974,	+0.1534,	+0.4330	},
	{+0.2499,	+0.0780,	+0.4260	},
	{+0.0948,	+0.1534,	+0.4663	},
	{+0.0482,	+0.0780,	+0.4915	},
	{-0.0909,	+0.1819,	+0.4568	},
	{-0.0465,	+0.0930,	+0.4891	},
	{-0.1949,	+0.1819,	+0.4230	},
	{-0.2499,	+0.0930,	+0.4230	},
	{-0.3508,	+0.1534,	+0.3215	},
	{-0.3279,	+0.0780,	+0.3693	},
	{-0.4142,	+0.1534,	+0.2343	},
	{-0.4526,	+0.0780,	+0.1978	},
	{-0.4625,	+0.1819,	+0.0547	},
	{-0.4795,	+0.0930,	+0.1069	},
	{-0.4625,	+0.1819,	-0.0547	},
	{-0.4795,	+0.0930,	-0.1069	},
	{-0.4142,	+0.1534,	-0.2343	},
	{-0.4526,	+0.0780,	-0.1978	},
	{-0.3508,	+0.1534,	-0.3215	},
	{-0.3279,	+0.0780,	-0.3693	},
	{-0.1949,	+0.1819,	-0.4230	},
	{-0.2499,	+0.0930,	-0.4230	},
	{-0.0909,	+0.1819,	-0.4568	},
	{-0.0465,	+0.0930,	-0.4891	},
	{+0.0948,	+0.1534,	-0.4663	},
	{+0.0482,	+0.0780,	-0.4915	},
	{+0.1974,	+0.1534,	-0.4330	},
	{+0.2499,	+0.0780,	-0.4260	},
	{+0.3421,	+0.1819,	-0.3161	},
	{+0.3251,	+0.0930,	-0.3683	},
	{+0.4063,	+0.1819,	-0.2276	},
	{+0.4508,	+0.0930,	-0.1953	},
	{+0.4728,	+0.1534,	-0.0539	},
	{+0.4824,	+0.0780,	-0.1060	},
	{+0.4330,	+0.0000,	+0.2500	},
	{+0.3716,	+0.0000,	+0.3346	},
	{+0.2034,	+0.0000,	+0.4568	},
	{+0.1040,	+0.0000,	+0.4891	},
	{-0.1040,	+0.0000,	+0.4891	},
	{-0.2034,	+0.0000,	+0.4568	},
	{-0.3716,	+0.0000,	+0.3346	},
	{-0.4330,	+0.0000,	+0.2500	},
	{-0.4973,	+0.0000,	+0.0523	},
	{-0.4973,	+0.0000,	-0.0523	},
	{-0.4330,	+0.0000,	-0.2500	},
	{-0.3716,	+0.0000,	-0.3346	},
	{-0.2034,	+0.0000,	-0.4568	},
	{-0.1040,	+0.0000,	-0.4891	},
	{+0.1040,	+0.0000,	-0.4891	},
	{+0.2034,	+0.0000,	-0.4568	},
	{+0.3716,	+0.0000,	-0.3346	},
	{+0.4330,	+0.0000,	-0.2500	},
	{+0.4973,	+0.0000,	-0.0523	},
	{+0.4973,	+0.0000,	+0.0523	},
	{+0.1208,	+0.4772,	+0.0878	},
	{-0.0461,	+0.4772,	+0.1420	},
	{-0.1493,	+0.4772,	-0.0000	},
	{-0.0461,	+0.4772,	-0.1420	},
	{+0.1208,	+0.4772,	-0.0878	},
	{+0.2465,	+0.3965,	+0.1791	},
	{-0.0941,	+0.3965,	+0.2897	},
	{-0.3047,	+0.3965,	-0.0000	},
	{-0.0941,	+0.3965,	-0.2897	},
	{+0.2465,	+0.3965,	-0.1791	},
	{+0.3715,	+0.3229,	-0.0881	},
	{+0.3715,	+0.3229,	+0.0881	},
	{+0.1986,	+0.3229,	+0.3261	},
	{+0.0310,	+0.3229,	+0.3805	},
	{-0.2488,	+0.3229,	+0.2896	},
	{-0.3523,	+0.3229,	+0.1471	},
	{-0.3523,	+0.3229,	-0.1471	},
	{-0.2488,	+0.3229,	-0.2896	},
	{+0.0310,	+0.3229,	-0.3805	},
	{+0.1986,	+0.3229,	-0.3261	},
	{+0.4476,	+0.1707,	+0.1433	},
	{+0.2746,	+0.1707,	+0.3814	},
	{+0.0020,	+0.1707,	+0.4700	},
	{-0.2778,	+0.1707,	+0.3790	},
	{-0.4463,	+0.1707,	+0.1471	},
	{-0.4463,	+0.1707,	-0.1471	},
	{-0.2778,	+0.1707,	-0.3790	},
	{+0.0020,	+0.1707,	-0.4700	},
	{+0.2746,	+0.1707,	-0.3814	},
	{+0.4476,	+0.1707,	-0.1433	},
	{+0.4936,	+0.0799,	+0.0000	},
	{+0.3971,	+0.0952,	+0.2885	},
	{+0.1525,	+0.0799,	+0.4694	},
	{-0.1517,	+0.0952,	+0.4668	},
	{-0.3993,	+0.0799,	+0.2901	},
	{-0.4909,	+0.0952,	-0.0000	},
	{-0.3993,	+0.0799,	-0.2901	},
	{-0.1517,	+0.0952,	-0.4668	},
	{+0.1525,	+0.0799,	-0.4694	},
	{+0.3971,	+0.0952,	-0.2885	},
};

const Fvector hemi_4[HEMI4_VERTS] = {
	{ 0.276388, 0.447220, 0.850649 },
	{ -0.723607, 0.447220, 0.525725 },
	{ -0.723607, 0.447220, -0.525725 },
	{ 0.276388, 0.447220, -0.850649 },
	{ 0.894426, 0.447216, 0.000000 },
	{ 0.000000, 1.000000, 0.000000 },
	{ 0.931188, 0.357738, 0.070089 },
	{ 0.956626, 0.251149, 0.147618 },
	{ 0.964711, 0.129893, 0.229041 },
	{ 0.951058, -0.000000, 0.309013 },
	{ 0.951058, 0.000000, -0.309013 },
	{ 0.964711, 0.129893, -0.229041 },
	{ 0.956626, 0.251149, -0.147618 },
	{ 0.931188, 0.357738, -0.070089 },
	{ 0.221089, 0.357741, 0.907271 },
	{ 0.155215, 0.251152, 0.955422 },
	{ 0.080276, 0.129894, 0.988273 },
	{ -0.000000, -0.000000, 1.000000 },
	{ 0.587786, 0.000000, 0.809017 },
	{ 0.515946, 0.129894, 0.846716 },
	{ 0.436007, 0.251152, 0.864188 },
	{ 0.354409, 0.357742, 0.863953 },
	{ -0.794547, 0.357741, 0.490629 },
	{ -0.860698, 0.251151, 0.442858 },
	{ -0.915098, 0.129893, 0.381737 },
	{ -0.951058, -0.000000, 0.309013 },
	{ -0.587786, 0.000000, 0.809017 },
	{ -0.645839, 0.129894, 0.752342 },
	{ -0.687159, 0.251152, 0.681715 },
	{ -0.712150, 0.357741, 0.604039 },
	{ -0.712150, 0.357741, -0.604039 },
	{ -0.687159, 0.251152, -0.681715 },
	{ -0.645839, 0.129894, -0.752343 },
	{ -0.587786, -0.000000, -0.809017 },
	{ -0.951058, 0.000000, -0.309013 },
	{ -0.915098, 0.129893, -0.381737 },
	{ -0.860698, 0.251151, -0.442858 },
	{ -0.794547, 0.357741, -0.490629 },
	{ 0.354409, 0.357742, -0.863953 },
	{ 0.436007, 0.251152, -0.864188 },
	{ 0.515946, 0.129894, -0.846716 },
	{ 0.587786, -0.000000, -0.809017 },
	{ 0.000000, 0.000000, -1.000000 },
	{ 0.080276, 0.129894, -0.988273 },
	{ 0.155215, 0.251152, -0.955422 },
	{ 0.221089, 0.357741, -0.907271 },
	{ 0.871565, 0.476984, 0.113408 },
	{ 0.831051, 0.502299, 0.238853 },
	{ 0.769872, 0.519570, 0.370600 },
	{ 0.688189, 0.525736, 0.499997 },
	{ 0.590366, 0.519572, 0.617668 },
	{ 0.483971, 0.502302, 0.716565 },
	{ 0.377183, 0.476988, 0.793861 },
	{ 0.161465, 0.476988, 0.863951 },
	{ 0.029639, 0.502302, 0.864184 },
	{ -0.114564, 0.519573, 0.846711 },
	{ -0.262869, 0.525738, 0.809012 },
	{ -0.405008, 0.519572, 0.752338 },
	{ -0.531941, 0.502302, 0.681712 },
	{ -0.638453, 0.476987, 0.604038 },
	{ -0.771771, 0.476987, 0.420539 },
	{ -0.812729, 0.502301, 0.295238 },
	{ -0.840673, 0.519571, 0.152694 },
	{ -0.850648, 0.525736, -0.000000 },
	{ -0.840673, 0.519571, -0.152694 },
	{ -0.812729, 0.502301, -0.295238 },
	{ -0.771771, 0.476987, -0.420539 },
	{ -0.638452, 0.476987, -0.604038 },
	{ -0.531941, 0.502302, -0.681712 },
	{ -0.405008, 0.519572, -0.752338 },
	{ -0.262869, 0.525738, -0.809012 },
	{ -0.114564, 0.519572, -0.846711 },
	{ 0.029639, 0.502302, -0.864184 },
	{ 0.161465, 0.476988, -0.863951 },
	{ 0.377183, 0.476988, -0.793861 },
	{ 0.483971, 0.502302, -0.716565 },
	{ 0.590366, 0.519572, -0.617668 },
	{ 0.688189, 0.525736, -0.499997 },
	{ 0.769872, 0.519570, -0.370600 },
	{ 0.831051, 0.502299, -0.238853 },
	{ 0.871565, 0.476984, -0.113408 },
	{ 0.036848, 0.992865, 0.113408 },
	{ 0.077607, 0.967950, 0.238853 },
	{ 0.120413, 0.920955, 0.370598 },
	{ 0.162456, 0.850654, 0.499995 },
	{ 0.200688, 0.760403, 0.617666 },
	{ 0.232822, 0.657519, 0.716563 },
	{ 0.257937, 0.550685, 0.793860 },
	{ 0.834716, 0.550681, 0.000000 },
	{ 0.753442, 0.657515, 0.000000 },
	{ 0.649456, 0.760399, 0.000000 },
	{ 0.525730, 0.850652, 0.000000 },
	{ 0.389673, 0.920953, 0.000000 },
	{ 0.251147, 0.967949, 0.000000 },
	{ 0.119245, 0.992865, 0.000000 },
	{ -0.096471, 0.992865, 0.070089 },
	{ -0.203181, 0.967950, 0.147618 },
	{ -0.315251, 0.920955, 0.229040 },
	{ -0.425323, 0.850654, 0.309011 },
	{ -0.525420, 0.760403, 0.381735 },
	{ -0.609547, 0.657519, 0.442856 },
	{ -0.675300, 0.550685, 0.490628 },
	{ -0.096471, 0.992865, -0.070089 },
	{ -0.203181, 0.967950, -0.147618 },
	{ -0.315251, 0.920955, -0.229040 },
	{ -0.425323, 0.850654, -0.309011 },
	{ -0.525420, 0.760403, -0.381735 },
	{ -0.609547, 0.657519, -0.442856 },
	{ -0.675300, 0.550685, -0.490628 },
	{ 0.036848, 0.992865, -0.113408 },
	{ 0.077607, 0.967950, -0.238853 },
	{ 0.120413, 0.920955, -0.370598 },
	{ 0.162456, 0.850654, -0.499995 },
	{ 0.200688, 0.760403, -0.617666 },
	{ 0.232822, 0.657519, -0.716563 },
	{ 0.257937, 0.550685, -0.793860 },
	{ 0.166198, 0.978672, -0.120749 },
	{ 0.307167, 0.943208, -0.126518 },
	{ 0.215245, 0.943209, -0.253036 },
	{ 0.451375, 0.882854, -0.129731 },
	{ 0.361800, 0.894429, -0.262863 },
	{ 0.262862, 0.882855, -0.389192 },
	{ 0.587783, 0.798549, -0.129731 },
	{ 0.506729, 0.819912, -0.266403 },
	{ 0.409951, 0.819913, -0.399604 },
	{ 0.305014, 0.798552, -0.518924 },
	{ 0.706258, 0.696558, -0.126519 },
	{ 0.638194, 0.723610, -0.262864 },
	{ 0.550008, 0.733353, -0.399605 },
	{ 0.447209, 0.723612, -0.525728 },
	{ 0.338569, 0.696561, -0.632593 },
	{ 0.801022, 0.586331, -0.120750 },
	{ 0.747366, 0.614342, -0.253038 },
	{ 0.672087, 0.629942, -0.389194 },
	{ 0.577830, 0.629943, -0.518926 },
	{ 0.471599, 0.614344, -0.632594 },
	{ 0.362366, 0.586334, -0.724502 },
	{ -0.063483, 0.978672, -0.195376 },
	{ -0.025408, 0.943209, -0.331227 },
	{ -0.174138, 0.943209, -0.282901 },
	{ 0.016098, 0.882855, -0.469369 },
	{ -0.138197, 0.894430, -0.425319 },
	{ -0.288916, 0.882855, -0.370262 },
	{ 0.058250, 0.798552, -0.599101 },
	{ -0.096779, 0.819914, -0.564248 },
	{ -0.253366, 0.819914, -0.513369 },
	{ -0.399272, 0.798552, -0.450440 },
	{ 0.097915, 0.696561, -0.710785 },
	{ -0.052790, 0.723612, -0.688185 },
	{ -0.210088, 0.733355, -0.646571 },
	{ -0.361804, 0.723612, -0.587778 },
	{ -0.497009, 0.696561, -0.517479 },
	{ 0.132684, 0.586334, -0.799129 },
	{ -0.009708, 0.614345, -0.788978 },
	{ -0.162463, 0.629944, -0.759458 },
	{ -0.314971, 0.629944, -0.709904 },
	{ -0.455902, 0.614344, -0.643998 },
	{ -0.577066, 0.586334, -0.568513 },
	{ -0.205432, 0.978671, 0.000000 },
	{ -0.322868, 0.943208, -0.078192 },
	{ -0.322868, 0.943208, 0.078192 },
	{ -0.441423, 0.882855, -0.160354 },
	{ -0.447210, 0.894429, 0.000000 },
	{ -0.441423, 0.882855, 0.160354 },
	{ -0.551779, 0.798551, -0.240532 },
	{ -0.566539, 0.819912, -0.082322 },
	{ -0.566539, 0.819912, 0.082322 },
	{ -0.551779, 0.798551, 0.240532 },
	{ -0.645740, 0.696561, -0.312768 },
	{ -0.670817, 0.723611, -0.162457 },
	{ -0.679848, 0.733353, 0.000000 },
	{ -0.670817, 0.723611, 0.162457 },
	{ -0.645740, 0.696560, 0.312768 },
	{ -0.719015, 0.586334, -0.373135 },
	{ -0.753363, 0.614343, -0.234576 },
	{ -0.772492, 0.629942, -0.080177 },
	{ -0.772492, 0.629942, 0.080177 },
	{ -0.753363, 0.614343, 0.234576 },
	{ -0.719015, 0.586334, 0.373135 },
	{ -0.063483, 0.978672, 0.195376 },
	{ -0.174138, 0.943209, 0.282901 },
	{ -0.025408, 0.943209, 0.331227 },
	{ -0.288916, 0.882855, 0.370262 },
	{ -0.138197, 0.894430, 0.425319 },
	{ 0.016098, 0.882855, 0.469369 },
	{ -0.399272, 0.798552, 0.450440 },
	{ -0.253366, 0.819914, 0.513369 },
	{ -0.096779, 0.819914, 0.564248 },
	{ 0.058250, 0.798552, 0.599101 },
	{ -0.497009, 0.696561, 0.517479 },
	{ -0.361804, 0.723612, 0.587778 },
	{ -0.210088, 0.733355, 0.646571 },
	{ -0.052790, 0.723612, 0.688185 },
	{ 0.097915, 0.696561, 0.710785 },
	{ -0.577066, 0.586334, 0.568513 },
	{ -0.455902, 0.614345, 0.643998 },
	{ -0.314971, 0.629944, 0.709904 },
	{ -0.162463, 0.629944, 0.759458 },
	{ -0.009708, 0.614345, 0.788978 },
	{ 0.132684, 0.586335, 0.799129 },
	{ 0.166198, 0.978672, 0.120749 },
	{ 0.215245, 0.943209, 0.253036 },
	{ 0.307167, 0.943208, 0.126518 },
	{ 0.262862, 0.882855, 0.389192 },
	{ 0.361800, 0.894429, 0.262863 },
	{ 0.451375, 0.882854, 0.129731 },
	{ 0.305014, 0.798552, 0.518924 },
	{ 0.409951, 0.819913, 0.399604 },
	{ 0.506729, 0.819912, 0.266403 },
	{ 0.587783, 0.798549, 0.129731 },
	{ 0.338569, 0.696561, 0.632593 },
	{ 0.447209, 0.723612, 0.525728 },
	{ 0.550008, 0.733353, 0.399605 },
	{ 0.638194, 0.723610, 0.262864 },
	{ 0.706258, 0.696558, 0.126519 },
	{ 0.362366, 0.586334, 0.724502 },
	{ 0.471599, 0.614344, 0.632594 },
	{ 0.577830, 0.629943, 0.518926 },
	{ 0.672087, 0.629942, 0.389194 },
	{ 0.747366, 0.614342, 0.253038 },
	{ 0.801022, 0.586331, 0.120750 },
	{ 0.903740, 0.380897, -0.195376 },
	{ 0.921508, 0.266063, -0.282902 },
	{ 0.854992, 0.399094, -0.331229 },
	{ 0.918856, 0.136410, -0.370264 },
	{ 0.861804, 0.276396, -0.425322 },
	{ 0.782446, 0.409229, -0.469371 },
	{ 0.892805, -0.000000, -0.450443 },
	{ 0.846660, 0.140059, -0.513372 },
	{ 0.776630, 0.280118, -0.564251 },
	{ 0.688190, 0.409230, -0.599104 },
	{ 0.809019, 0.000000, -0.587782 },
	{ 0.749882, 0.140059, -0.646576 },
	{ 0.670821, 0.276397, -0.688189 },
	{ 0.579226, 0.399096, -0.710788 },
	{ 0.704293, 0.000000, -0.709909 },
	{ 0.636088, 0.136411, -0.759463 },
	{ 0.553820, 0.266065, -0.788982 },
	{ 0.465085, 0.380900, -0.799132 },
	{ 0.093451, 0.380900, -0.919882 },
	{ 0.015700, 0.266064, -0.963827 },
	{ -0.050816, 0.399096, -0.915500 },
	{ -0.068205, 0.136410, -0.988302 },
	{ -0.138198, 0.276397, -0.951055 },
	{ -0.204615, 0.409230, -0.889193 },
	{ -0.152509, -0.000000, -0.988302 },
	{ -0.226618, 0.140059, -0.963861 },
	{ -0.296648, 0.280118, -0.912981 },
	{ -0.357124, 0.409230, -0.839639 },
	{ -0.309016, -0.000000, -0.951057 },
	{ -0.383207, 0.140059, -0.912982 },
	{ -0.447215, 0.276397, -0.850649 },
	{ -0.497012, 0.399096, -0.770520 },
	{ -0.457527, -0.000000, -0.889196 },
	{ -0.525732, 0.136410, -0.839642 },
	{ -0.579229, 0.266065, -0.770522 },
	{ -0.616302, 0.380900, -0.689266 },
	{ -0.845982, 0.380899, -0.373136 },
	{ -0.911804, 0.266063, -0.312769 },
	{ -0.886396, 0.399095, -0.234577 },
	{ -0.961008, 0.136410, -0.240533 },
	{ -0.947213, 0.276396, -0.162458 },
	{ -0.908902, 0.409229, -0.080178 },
	{ -0.987059, 0.000000, -0.160355 },
	{ -0.986715, 0.140059, -0.082322 },
	{ -0.959966, 0.280117, 0.000000 },
	{ -0.908902, 0.409229, 0.080178 },
	{ -1.000000, 0.000001, 0.000000 },
	{ -0.986715, 0.140059, 0.082323 },
	{ -0.947213, 0.276397, 0.162458 },
	{ -0.886395, 0.399095, 0.234577 },
	{ -0.987059, 0.000001, 0.160356 },
	{ -0.961008, 0.136411, 0.240534 },
	{ -0.911803, 0.266065, 0.312769 },
	{ -0.845982, 0.380900, 0.373136 },
	{ -0.616302, 0.380900, 0.689266 },
	{ -0.579229, 0.266064, 0.770521 },
	{ -0.497012, 0.399096, 0.770520 },
	{ -0.525732, 0.136410, 0.839641 },
	{ -0.447216, 0.276397, 0.850649 },
	{ -0.357124, 0.409230, 0.839639 },
	{ -0.457527, -0.000001, 0.889196 },
	{ -0.383208, 0.140059, 0.912982 },
	{ -0.296649, 0.280118, 0.912981 },
	{ -0.204616, 0.409230, 0.889193 },
	{ -0.309017, -0.000001, 0.951056 },
	{ -0.226619, 0.140059, 0.963861 },
	{ -0.138199, 0.276397, 0.951055 },
	{ -0.050817, 0.399096, 0.915500 },
	{ -0.152509, -0.000000, 0.988302 },
	{ -0.068206, 0.136410, 0.988302 },
	{ 0.015699, 0.266064, 0.963827 },
	{ 0.093451, 0.380900, 0.919882 },
	{ 0.465085, 0.380900, 0.799132 },
	{ 0.553820, 0.266064, 0.788983 },
	{ 0.579226, 0.399096, 0.710788 },
	{ 0.636088, 0.136410, 0.759463 },
	{ 0.670820, 0.276396, 0.688190 },
	{ 0.688190, 0.409229, 0.599104 },
	{ 0.704293, -0.000001, 0.709909 },
	{ 0.749882, 0.140058, 0.646576 },
	{ 0.776630, 0.280116, 0.564252 },
	{ 0.782446, 0.409228, 0.469372 },
	{ 0.809019, -0.000002, 0.587783 },
	{ 0.846659, 0.140057, 0.513373 },
	{ 0.861804, 0.276394, 0.425323 },
	{ 0.854992, 0.399093, 0.331230 },
	{ 0.892805, -0.000002, 0.450444 },
	{ 0.918856, 0.136407, 0.370266 },
	{ 0.921508, 0.266061, 0.282904 },
	{ 0.903740, 0.380896, 0.195377 },
	{ 0.298886, 0.253934, -0.919883 },
	{ 0.379681, 0.133033, -0.915502 },
	{ 0.230948, 0.133033, -0.963828 },
	{ 0.457527, -0.000000, -0.889196 },
	{ 0.309017, -0.000000, -0.951056 },
	{ 0.152509, 0.000000, -0.988302 },
	{ -0.782501, 0.253934, -0.568515 },
	{ -0.753368, 0.133032, -0.644002 },
	{ -0.845290, 0.133032, -0.517482 },
	{ -0.704293, -0.000000, -0.709910 },
	{ -0.809018, -0.000000, -0.587783 },
	{ -0.892805, 0.000000, -0.450444 },
	{ -0.782501, 0.253934, 0.568515 },
	{ -0.845290, 0.133032, 0.517482 },
	{ -0.753368, 0.133032, 0.644002 },
	{ -0.892805, -0.000000, 0.450444 },
	{ -0.809018, 0.000000, 0.587783 },
	{ -0.704293, 0.000000, 0.709910 },
	{ 0.298886, 0.253934, 0.919883 },
	{ 0.230948, 0.133032, 0.963828 },
	{ 0.379681, 0.133033, 0.915502 },
	{ 0.152509, -0.000000, 0.988302 },
	{ 0.309017, 0.000000, 0.951056 },
	{ 0.457527, 0.000000, 0.889196 },
	{ 0.967222, 0.253931, 0.000000 },
	{ 0.988023, 0.133031, 0.078192 },
	{ 0.988023, 0.133031, -0.078192 },
	{ 0.987059, -0.000000, 0.160355 },
	{ 1.000000, 0.000000, 0.000000 },
	{ 0.987059, 0.000000, -0.160355 }
};
const u16 hemi_4v[HEMI4_FACES*3] = {
	1, 53, 88,
	2, 60, 102,
	3, 67, 109,
	4, 74, 116,
	5, 81, 89,
	95, 110, 6,
	94, 117, 95,
	93, 118, 94,
	92, 120, 93,
	91, 123, 92,
	90, 127, 91,
	89, 132, 90,
	95, 117, 110,
	117, 111, 110,
	94, 118, 117,
	118, 119, 117,
	117, 119, 111,
	119, 112, 111,
	93, 120, 118,
	120, 121, 118,
	118, 121, 119,
	121, 122, 119,
	119, 122, 112,
	122, 113, 112,
	92, 123, 120,
	123, 124, 120,
	120, 124, 121,
	124, 125, 121,
	121, 125, 122,
	125, 126, 122,
	122, 126, 113,
	126, 114, 113,
	91, 127, 123,
	127, 128, 123,
	123, 128, 124,
	128, 129, 124,
	124, 129, 125,
	129, 130, 125,
	125, 130, 126,
	130, 131, 126,
	126, 131, 114,
	131, 115, 114,
	90, 132, 127,
	132, 133, 127,
	127, 133, 128,
	133, 134, 128,
	128, 134, 129,
	134, 135, 129,
	129, 135, 130,
	135, 136, 130,
	130, 136, 131,
	136, 137, 131,
	131, 137, 115,
	137, 116, 115,
	89, 81, 132,
	81, 80, 132,
	132, 80, 133,
	80, 79, 133,
	133, 79, 134,
	79, 78, 134,
	134, 78, 135,
	78, 77, 135,
	135, 77, 136,
	77, 76, 136,
	136, 76, 137,
	76, 75, 137,
	137, 75, 116,
	75, 4, 116,
	110, 103, 6,
	111, 138, 110,
	112, 139, 111,
	113, 141, 112,
	114, 144, 113,
	115, 148, 114,
	116, 153, 115,
	110, 138, 103,
	138, 104, 103,
	111, 139, 138,
	139, 140, 138,
	138, 140, 104,
	140, 105, 104,
	112, 141, 139,
	141, 142, 139,
	139, 142, 140,
	142, 143, 140,
	140, 143, 105,
	143, 106, 105,
	113, 144, 141,
	144, 145, 141,
	141, 145, 142,
	145, 146, 142,
	142, 146, 143,
	146, 147, 143,
	143, 147, 106,
	147, 107, 106,
	114, 148, 144,
	148, 149, 144,
	144, 149, 145,
	149, 150, 145,
	145, 150, 146,
	150, 151, 146,
	146, 151, 147,
	151, 152, 147,
	147, 152, 107,
	152, 108, 107,
	115, 153, 148,
	153, 154, 148,
	148, 154, 149,
	154, 155, 149,
	149, 155, 150,
	155, 156, 150,
	150, 156, 151,
	156, 157, 151,
	151, 157, 152,
	157, 158, 152,
	152, 158, 108,
	158, 109, 108,
	116, 74, 153,
	74, 73, 153,
	153, 73, 154,
	73, 72, 154,
	154, 72, 155,
	72, 71, 155,
	155, 71, 156,
	71, 70, 156,
	156, 70, 157,
	70, 69, 157,
	157, 69, 158,
	69, 68, 158,
	158, 68, 109,
	68, 3, 109,
	103, 96, 6,
	104, 159, 103,
	105, 160, 104,
	106, 162, 105,
	107, 165, 106,
	108, 169, 107,
	109, 174, 108,
	103, 159, 96,
	159, 97, 96,
	104, 160, 159,
	160, 161, 159,
	159, 161, 97,
	161, 98, 97,
	105, 162, 160,
	162, 163, 160,
	160, 163, 161,
	163, 164, 161,
	161, 164, 98,
	164, 99, 98,
	106, 165, 162,
	165, 166, 162,
	162, 166, 163,
	166, 167, 163,
	163, 167, 164,
	167, 168, 164,
	164, 168, 99,
	168, 100, 99,
	107, 169, 165,
	169, 170, 165,
	165, 170, 166,
	170, 171, 166,
	166, 171, 167,
	171, 172, 167,
	167, 172, 168,
	172, 173, 168,
	168, 173, 100,
	173, 101, 100,
	108, 174, 169,
	174, 175, 169,
	169, 175, 170,
	175, 176, 170,
	170, 176, 171,
	176, 177, 171,
	171, 177, 172,
	177, 178, 172,
	172, 178, 173,
	178, 179, 173,
	173, 179, 101,
	179, 102, 101,
	109, 67, 174,
	67, 66, 174,
	174, 66, 175,
	66, 65, 175,
	175, 65, 176,
	65, 64, 176,
	176, 64, 177,
	64, 63, 177,
	177, 63, 178,
	63, 62, 178,
	178, 62, 179,
	62, 61, 179,
	179, 61, 102,
	61, 2, 102,
	96, 82, 6,
	97, 180, 96,
	98, 181, 97,
	99, 183, 98,
	100, 186, 99,
	101, 190, 100,
	102, 195, 101,
	96, 180, 82,
	180, 83, 82,
	97, 181, 180,
	181, 182, 180,
	180, 182, 83,
	182, 84, 83,
	98, 183, 181,
	183, 184, 181,
	181, 184, 182,
	184, 185, 182,
	182, 185, 84,
	185, 85, 84,
	99, 186, 183,
	186, 187, 183,
	183, 187, 184,
	187, 188, 184,
	184, 188, 185,
	188, 189, 185,
	185, 189, 85,
	189, 86, 85,
	100, 190, 186,
	190, 191, 186,
	186, 191, 187,
	191, 192, 187,
	187, 192, 188,
	192, 193, 188,
	188, 193, 189,
	193, 194, 189,
	189, 194, 86,
	194, 87, 86,
	101, 195, 190,
	195, 196, 190,
	190, 196, 191,
	196, 197, 191,
	191, 197, 192,
	197, 198, 192,
	192, 198, 193,
	198, 199, 193,
	193, 199, 194,
	199, 200, 194,
	194, 200, 87,
	200, 88, 87,
	102, 60, 195,
	60, 59, 195,
	195, 59, 196,
	59, 58, 196,
	196, 58, 197,
	58, 57, 197,
	197, 57, 198,
	57, 56, 198,
	198, 56, 199,
	56, 55, 199,
	199, 55, 200,
	55, 54, 200,
	200, 54, 88,
	54, 1, 88,
	82, 95, 6,
	83, 201, 82,
	84, 202, 83,
	85, 204, 84,
	86, 207, 85,
	87, 211, 86,
	88, 216, 87,
	82, 201, 95,
	201, 94, 95,
	83, 202, 201,
	202, 203, 201,
	201, 203, 94,
	203, 93, 94,
	84, 204, 202,
	204, 205, 202,
	202, 205, 203,
	205, 206, 203,
	203, 206, 93,
	206, 92, 93,
	85, 207, 204,
	207, 208, 204,
	204, 208, 205,
	208, 209, 205,
	205, 209, 206,
	209, 210, 206,
	206, 210, 92,
	210, 91, 92,
	86, 211, 207,
	211, 212, 207,
	207, 212, 208,
	212, 213, 208,
	208, 213, 209,
	213, 214, 209,
	209, 214, 210,
	214, 215, 210,
	210, 215, 91,
	215, 90, 91,
	87, 216, 211,
	216, 217, 211,
	211, 217, 212,
	217, 218, 212,
	212, 218, 213,
	218, 219, 213,
	213, 219, 214,
	219, 220, 214,
	214, 220, 215,
	220, 221, 215,
	215, 221, 90,
	221, 89, 90,
	88, 53, 216,
	53, 52, 216,
	216, 52, 217,
	52, 51, 217,
	217, 51, 218,
	51, 50, 218,
	218, 50, 219,
	50, 49, 219,
	219, 49, 220,
	49, 48, 220,
	220, 48, 221,
	48, 47, 221,
	221, 47, 89,
	47, 5, 89,
	14, 81, 5,
	13, 222, 14,
	12, 223, 13,
	11, 225, 12,
	14, 222, 81,
	222, 80, 81,
	13, 223, 222,
	223, 224, 222,
	222, 224, 80,
	224, 79, 80,
	12, 225, 223,
	225, 226, 223,
	223, 226, 224,
	226, 227, 224,
	224, 227, 79,
	227, 78, 79,
	11, 228, 225,
	228, 229, 225,
	225, 229, 226,
	229, 230, 226,
	226, 230, 227,
	230, 231, 227,
	227, 231, 78,
	231, 77, 78,
	228, 232, 229,
	232, 233, 229,
	229, 233, 230,
	233, 234, 230,
	230, 234, 231,
	234, 235, 231,
	231, 235, 77,
	235, 76, 77,
	232, 236, 233,
	236, 237, 233,
	233, 237, 234,
	237, 238, 234,
	234, 238, 235,
	238, 239, 235,
	235, 239, 76,
	239, 75, 76,
	236, 42, 237,
	42, 41, 237,
	237, 41, 238,
	41, 40, 238,
	238, 40, 239,
	40, 39, 239,
	239, 39, 75,
	39, 4, 75,
	46, 74, 4,
	45, 240, 46,
	44, 241, 45,
	43, 243, 44,
	46, 240, 74,
	240, 73, 74,
	45, 241, 240,
	241, 242, 240,
	240, 242, 73,
	242, 72, 73,
	44, 243, 241,
	243, 244, 241,
	241, 244, 242,
	244, 245, 242,
	242, 245, 72,
	245, 71, 72,
	43, 246, 243,
	246, 247, 243,
	243, 247, 244,
	247, 248, 244,
	244, 248, 245,
	248, 249, 245,
	245, 249, 71,
	249, 70, 71,
	246, 250, 247,
	250, 251, 247,
	247, 251, 248,
	251, 252, 248,
	248, 252, 249,
	252, 253, 249,
	249, 253, 70,
	253, 69, 70,
	250, 254, 251,
	254, 255, 251,
	251, 255, 252,
	255, 256, 252,
	252, 256, 253,
	256, 257, 253,
	253, 257, 69,
	257, 68, 69,
	254, 34, 255,
	34, 33, 255,
	255, 33, 256,
	33, 32, 256,
	256, 32, 257,
	32, 31, 257,
	257, 31, 68,
	31, 3, 68,
	38, 67, 3,
	37, 258, 38,
	36, 259, 37,
	35, 261, 36,
	38, 258, 67,
	258, 66, 67,
	37, 259, 258,
	259, 260, 258,
	258, 260, 66,
	260, 65, 66,
	36, 261, 259,
	261, 262, 259,
	259, 262, 260,
	262, 263, 260,
	260, 263, 65,
	263, 64, 65,
	35, 264, 261,
	264, 265, 261,
	261, 265, 262,
	265, 266, 262,
	262, 266, 263,
	266, 267, 263,
	263, 267, 64,
	267, 63, 64,
	264, 268, 265,
	268, 269, 265,
	265, 269, 266,
	269, 270, 266,
	266, 270, 267,
	270, 271, 267,
	267, 271, 63,
	271, 62, 63,
	268, 272, 269,
	272, 273, 269,
	269, 273, 270,
	273, 274, 270,
	270, 274, 271,
	274, 275, 271,
	271, 275, 62,
	275, 61, 62,
	272, 26, 273,
	26, 25, 273,
	273, 25, 274,
	25, 24, 274,
	274, 24, 275,
	24, 23, 275,
	275, 23, 61,
	23, 2, 61,
	30, 60, 2,
	29, 276, 30,
	28, 277, 29,
	27, 279, 28,
	30, 276, 60,
	276, 59, 60,
	29, 277, 276,
	277, 278, 276,
	276, 278, 59,
	278, 58, 59,
	28, 279, 277,
	279, 280, 277,
	277, 280, 278,
	280, 281, 278,
	278, 281, 58,
	281, 57, 58,
	27, 282, 279,
	282, 283, 279,
	279, 283, 280,
	283, 284, 280,
	280, 284, 281,
	284, 285, 281,
	281, 285, 57,
	285, 56, 57,
	282, 286, 283,
	286, 287, 283,
	283, 287, 284,
	287, 288, 284,
	284, 288, 285,
	288, 289, 285,
	285, 289, 56,
	289, 55, 56,
	286, 290, 287,
	290, 291, 287,
	287, 291, 288,
	291, 292, 288,
	288, 292, 289,
	292, 293, 289,
	289, 293, 55,
	293, 54, 55,
	290, 18, 291,
	18, 17, 291,
	291, 17, 292,
	17, 16, 292,
	292, 16, 293,
	16, 15, 293,
	293, 15, 54,
	15, 1, 54,
	22, 53, 1,
	21, 294, 22,
	20, 295, 21,
	19, 297, 20,
	22, 294, 53,
	294, 52, 53,
	21, 295, 294,
	295, 296, 294,
	294, 296, 52,
	296, 51, 52,
	20, 297, 295,
	297, 298, 295,
	295, 298, 296,
	298, 299, 296,
	296, 299, 51,
	299, 50, 51,
	19, 300, 297,
	300, 301, 297,
	297, 301, 298,
	301, 302, 298,
	298, 302, 299,
	302, 303, 299,
	299, 303, 50,
	303, 49, 50,
	300, 304, 301,
	304, 305, 301,
	301, 305, 302,
	305, 306, 302,
	302, 306, 303,
	306, 307, 303,
	303, 307, 49,
	307, 48, 49,
	304, 308, 305,
	308, 309, 305,
	305, 309, 306,
	309, 310, 306,
	306, 310, 307,
	310, 311, 307,
	307, 311, 48,
	311, 47, 48,
	308, 10, 309,
	10, 9, 309,
	309, 9, 310,
	9, 8, 310,
	310, 8, 311,
	8, 7, 311,
	311, 7, 47,
	7, 5, 47,
	39, 46, 4,
	40, 312, 39,
	41, 313, 40,
	42, 315, 41,
	39, 312, 46,
	312, 45, 46,
	40, 313, 312,
	313, 314, 312,
	312, 314, 45,
	314, 44, 45,
	41, 315, 313,
	315, 316, 313,
	313, 316, 314,
	316, 317, 314,
	314, 317, 44,
	317, 43, 44,
	31, 38, 3,
	32, 318, 31,
	33, 319, 32,
	34, 321, 33,
	31, 318, 38,
	318, 37, 38,
	32, 319, 318,
	319, 320, 318,
	318, 320, 37,
	320, 36, 37,
	33, 321, 319,
	321, 322, 319,
	319, 322, 320,
	322, 323, 320,
	320, 323, 36,
	323, 35, 36,
	23, 30, 2,
	24, 324, 23,
	25, 325, 24,
	26, 327, 25,
	23, 324, 30,
	324, 29, 30,
	24, 325, 324,
	325, 326, 324,
	324, 326, 29,
	326, 28, 29,
	25, 327, 325,
	327, 328, 325,
	325, 328, 326,
	328, 329, 326,
	326, 329, 28,
	329, 27, 28,
	15, 22, 1,
	16, 330, 15,
	17, 331, 16,
	18, 333, 17,
	15, 330, 22,
	330, 21, 22,
	16, 331, 330,
	331, 332, 330,
	330, 332, 21,
	332, 20, 21,
	17, 333, 331,
	333, 334, 331,
	331, 334, 332,
	334, 335, 332,
	332, 335, 20,
	335, 19, 20,
	7, 14, 5,
	8, 336, 7,
	9, 337, 8,
	10, 339, 9,
	7, 336, 14,
	336, 13, 14,
	8, 337, 336,
	337, 338, 336,
	336, 338, 13,
	338, 12, 13,
	9, 339, 337,
	339, 340, 337,
	337, 340, 338,
	340, 341, 338,
	338, 341, 12,
	341, 11, 12
};
#pragma warning(default:4305)

void ECORE_API xrHemisphereBuild	(int quality, float energy, xrHemisphereIterator* iterator, LPVOID param)
{
	const Fvector* hemi=0;
	int h_count		= xrHemisphereVertices(quality,hemi); VERIFY(h_count>0);
    // Calculate energy
    float total		= (float)h_count;
    float E			= 1.f/total;
		
    // Iterate
    for (int i=0; i<h_count; i++){
        float x		=	-float	(hemi[i][0]);
        float y		=	-float	(hemi[i][1]);
        float z		=	-float	(hemi[i][2]);
        float mag	=	_sqrt	(x*x + y*y + z*z);
        x /= mag;	y /= mag;	z /= mag;
        iterator	(x,y,z,E*energy,param);
    }
}

int ECORE_API xrHemisphereVertices	(int quality, const Fvector*& verts)
{
	// SELECT table
	int				h_count	= 0;
	switch (quality)
	{
	case 1:	// LOW quality
		h_count		= HEMI1_VERTS;
		verts		= hemi_1;
		break;
	case 2:	// HIGH quality
		h_count		= HEMI2_VERTS;
		verts		= hemi_2;
		break;
	case 3:	// SUPER HIGH quality
		h_count		= HEMI3_VERTS;
		verts		= hemi_3;
		break;
	case 4: // SUPER MEGA HIGH quality
		h_count		= HEMI4_VERTS;
		verts		= hemi_4;
		break;
	default:// NO 	
		NODEFAULT;
	}
	return h_count;
}

int	ECORE_API xrHemisphereIndices	(int quality, const u16*& indices)
{
	// SELECT table
	int				h_count	= 0;
	switch (quality)
	{
	case 1:	// LOW quality
		h_count		= HEMI1_FACES*3;
		indices		= hemi_1v;
		break;
	case 2:	// HIGH quality
		h_count		= HEMI2_FACES*3;
		indices		= hemi_2v;
		break;
//	case 3:	// SUPER HIGH quality
//		h_count		= HEMI3_FACES*3;
//		indices		= hemi_3v;
//		break;
	case 4: // SUPER MEGA HIGH quality
		h_count		= HEMI4_FACES*3;
		indices		= hemi_4v;
		break;
	default:// NO 	
		NODEFAULT;
	}
	return h_count;
}
