
#include "PerfMetric_COMM.h"

#include "XPedia_AMC.h"

#include "XPedia_AMCsmp.c"

/* **** 4-bit CQI Table TS36.213  Table 7.2.3-1
CQI_index modulation  code_rate*1024  efficiency
1         QPSK        78              0.1523
2         QPSK        120             0.2344
3         QPSK        193             0.377
4         QPSK        308             0.6016
5         QPSK        449             0.877
6         QPSK        602             1.1758
7         16QAM       378             1.4766
8         16QAM       490             1.9141
9         16QAM       616             2.4063
10        64QAM       466             2.7305
11        64QAM       567             3.3223
12        64QAM       666             3.9023
13        64QAM       772             4.5234
14        64QAM       873             5.1152
15        64QAM       948             5.5547


MCS(0~28)   ModuType   TBS_Index(0~26)
0           2           0
1           2           1
2           2           2
3           2           3
4           2           4
5           2           5
6           2           6
7           2           7
8           2           8
9           2           9
10          2           10
11          4           10
12          4           11
13          4           12
14          4           13
15          4           14
16          4           15
17          4           16
18          4           17
19          4           18
20          4           19
21          6           19
22          6           20
23          6           21
24          6           22
25          6           23
26          6           24
27          6           25
28          6           26
*/

// **** TS36.213  Table 7.1.7.2.1-1: Transport block size table (dimension 27×110)
int gviTBS_lktbl_1lyr[110 * MAX_ITBS_N] = {
    16, 24, 32, 40, 56, 72, 328, 104, 120, 136, 144, 176, 208, 224, 256, 280, 328, 336, 376, 408, 440, 488, 520, 552, 584, 616, 712,
    32, 56, 72, 104, 120, 144, 176, 224, 256, 296, 328, 376, 440, 488, 552, 600, 632, 696, 776, 840, 904, 1000, 1064, 1128, 1192, 1256, 1480,
    56, 88, 144, 176, 208, 224, 256, 328, 392, 456, 504, 584, 680, 744, 840, 904, 968, 1064, 1160, 1288, 1384, 1480, 1608, 1736, 1800, 1864, 2216,
    88, 144, 176, 208, 256, 328, 392, 472, 536, 616, 680, 776, 904, 1000, 1128, 1224, 1288, 1416, 1544, 1736, 1864, 1992, 2152, 2280, 2408, 2536, 2984,
    120, 176, 208, 256, 328, 424, 504, 584, 680, 776, 872, 1000, 1128, 1256, 1416, 1544, 1608, 1800, 1992, 2152, 2344, 2472, 2664, 2856, 2984, 3112, 3752,
    152, 208, 256, 328, 408, 504, 600, 712, 808, 936, 1032, 1192, 1352, 1544, 1736, 1800, 1928, 2152, 2344, 2600, 2792, 2984, 3240, 3496, 3624, 3752, 4392,
    176, 224, 296, 392, 488, 600, 712, 840, 968, 1096, 1224, 1384, 1608, 1800, 1992, 2152, 2280, 2536, 2792, 2984, 3240, 3496, 3752, 4008, 4264, 4392, 5160,
    208, 256, 328, 440, 552, 680, 808, 968, 1096, 1256, 1384, 1608, 1800, 2024, 2280, 2472, 2600, 2856, 3112, 3496, 3752, 4008, 4264, 4584, 4968, 5160, 5992,
    224, 328, 376, 504, 632, 776, 936, 1096, 1256, 1416, 1544, 1800, 2024, 2280, 2600, 2728, 2984, 3240, 3624, 3880, 4136, 4584, 4776, 5160, 5544, 5736, 6712,
    256, 344, 424, 568, 696, 872, 1032, 1224, 1384, 1544, 1736, 2024, 2280, 2536, 2856, 3112, 3240, 3624, 4008, 4264, 4584, 4968, 5352, 5736, 5992, 6200, 7480,
    288, 376, 472, 616, 776, 968, 1128, 1320, 1544, 1736, 1928, 2216, 2472, 2856, 3112, 3368, 3624, 4008, 4392, 4776, 5160, 5544, 5992, 6200, 6712, 6968, 8248,
    328, 424, 520, 680, 840, 1032, 1224, 1480, 1672, 1864, 2088, 2408, 2728, 3112, 3496, 3624, 3880, 4392, 4776, 5160, 5544, 5992, 6456, 6968, 7224, 7480, 8760,
    344, 456, 568, 744, 904, 1128, 1352, 1608, 1800, 2024, 2280, 2600, 2984, 3368, 3752, 4008, 4264, 4776, 5160, 5544, 5992, 6456, 6968, 7480, 7992, 8248, 9528,
    376, 488, 616, 808, 1000, 1224, 1480, 1672, 1928, 2216, 2472, 2792, 3240, 3624, 4008, 4264, 4584, 5160, 5544, 5992, 6456, 6968, 7480, 7992, 8504, 8760, 10296,
    392, 520, 648, 872, 1064, 1320, 1544, 1800, 2088, 2344, 2664, 2984, 3368, 3880, 4264, 4584, 4968, 5352, 5992, 6456, 6968, 7480, 7992, 8504, 9144, 9528, 11064,
    424, 568, 696, 904, 1128, 1384, 1672, 1928, 2216, 2536, 2792, 3240, 3624, 4136, 4584, 4968, 5160, 5736, 6200, 6968, 7480, 7992, 8504, 9144, 9912, 10296, 11832,
    456, 600, 744, 968, 1192, 1480, 1736, 2088, 2344, 2664, 2984, 3496, 3880, 4392, 4968, 5160, 5544, 6200, 6712, 7224, 7992, 8504, 9144, 9912, 10296, 10680, 12576,
    488, 632, 776, 1032, 1288, 1544, 1864, 2216, 2536, 2856, 3112, 3624, 4136, 4584, 5160, 5544, 5992, 6456, 7224, 7736, 8248, 9144, 9528, 10296, 11064, 11448, 13536,
    504, 680, 840, 1096, 1352, 1672, 1992, 2344, 2664, 2984, 3368, 3880, 4392, 4968, 5544, 5736, 6200, 6712, 7480, 8248, 8760, 9528, 10296, 11064, 11448, 12216, 14112,
    536, 712, 872, 1160, 1416, 1736, 2088, 2472, 2792, 3112, 3496, 4008, 4584, 5160, 5736, 6200, 6456, 7224, 7992, 8504, 9144, 9912, 10680, 11448, 12216, 12576, 14688,
    568, 744, 936, 1224, 1480, 1864, 2216, 2536, 2984, 3368, 3752, 4264, 4776, 5352, 5992, 6456, 6712, 7480, 8248, 9144, 9912, 10680, 11448, 12216, 12960, 13536, 15264,
    600, 776, 968, 1256, 1544, 1928, 2280, 2664, 3112, 3496, 3880, 4392, 4968, 5736, 6200, 6712, 7224, 7992, 8760, 9528, 10296, 11064, 11832, 12576, 13536, 14112, 16416,
    616, 808, 1000, 1320, 1608, 2024, 2408, 2792, 3240, 3624, 4008, 4584, 5352, 5992, 6456, 6968, 7480, 8248, 9144, 9912, 10680, 11448, 12576, 12960, 14112, 14688, 16992,
    648, 872, 1064, 1384, 1736, 2088, 2472, 2984, 3368, 3752, 4264, 4776, 5544, 6200, 6968, 7224, 7736, 8760, 9528, 10296, 11064, 12216, 12960, 13536, 14688, 15264, 17568,
    680, 904, 1096, 1416, 1800, 2216, 2600, 3112, 3496, 4008, 4392, 4968, 5736, 6456, 7224, 7736, 7992, 9144, 9912, 10680, 11448, 12576, 13536, 14112, 15264, 15840, 18336,
    712, 936, 1160, 1480, 1864, 2280, 2728, 3240, 3624, 4136, 4584, 5352, 5992, 6712, 7480, 7992, 8504, 9528, 10296, 11064, 12216, 12960, 14112, 14688, 15840, 16416, 19080,
    744, 968, 1192, 1544, 1928, 2344, 2792, 3368, 3752, 4264, 4776, 5544, 6200, 6968, 7736, 8248, 8760, 9912, 10680, 11448, 12576, 13536, 14688, 15264, 16416, 16992, 19848,
    776, 1000, 1256, 1608, 1992, 2472, 2984, 3368, 3880, 4392, 4968, 5736, 6456, 7224, 7992, 8504, 9144, 10296, 11064, 12216, 12960, 14112, 15264, 15840, 16992, 17568, 20616,
    776, 1032, 1288, 1672, 2088, 2536, 2984, 3496, 4008, 4584, 5160, 5992, 6712, 7480, 8248, 8760, 9528, 10296, 11448, 12576, 13536, 14688, 15840, 16416, 17568, 18336, 21384,
    808, 1064, 1320, 1736, 2152, 2664, 3112, 3624, 4264, 4776, 5352, 5992, 6712, 7736, 8504, 9144, 9912, 10680, 11832, 12960, 14112, 15264, 16416, 16992, 18336, 19080, 22152,
    840, 1128, 1384, 1800, 2216, 2728, 3240, 3752, 4392, 4968, 5544, 6200, 6968, 7992, 8760, 9528, 9912, 11064, 12216, 13536, 14688, 15840, 16992, 17568, 19080, 19848, 22920,
    872, 1160, 1416, 1864, 2280, 2792, 3368, 3880, 4584, 5160, 5736, 6456, 7224, 8248, 9144, 9912, 10296, 11448, 12576, 13536, 14688, 15840, 16992, 18336, 19848, 20616, 23688,
    904, 1192, 1480, 1928, 2344, 2856, 3496, 4008, 4584, 5160, 5736, 6712, 7480, 8504, 9528, 10296, 10680, 11832, 12960, 14112, 15264, 16416, 17568, 19080, 19848, 20616, 24496,
    936, 1224, 1544, 1992, 2408, 2984, 3496, 4136, 4776, 5352, 5992, 6968, 7736, 8760, 9912, 10296, 11064, 12216, 13536, 14688, 15840, 16992, 18336, 19848, 20616, 21384, 25456,
    968, 1256, 1544, 2024, 2472, 3112, 3624, 4264, 4968, 5544, 6200, 6968, 7992, 9144, 9912, 10680, 11448, 12576, 14112, 15264, 16416, 17568, 19080, 19848, 21384, 22152, 25456,
    1000, 1288, 1608, 2088, 2600, 3112, 3752, 4392, 4968, 5736, 6200, 7224, 8248, 9144, 10296, 11064, 11832, 12960, 14112, 15264, 16992, 18336, 19080, 20616, 22152, 22920, 26416,
    1032, 1352, 1672, 2152, 2664, 3240, 3880, 4584, 5160, 5736, 6456, 7480, 8504, 9528, 10680, 11448, 12216, 13536, 14688, 15840, 16992, 18336, 19848, 21384, 22920, 23688, 27376,
    1032, 1384, 1672, 2216, 2728, 3368, 4008, 4584, 5352, 5992, 6712, 7736, 8760, 9912, 11064, 11832, 12216, 13536, 15264, 16416, 17568, 19080, 20616, 22152, 22920, 24496, 28336,
    1064, 1416, 1736, 2280, 2792, 3496, 4136, 4776, 5544, 6200, 6712, 7736, 8760, 9912, 11064, 11832, 12576, 14112, 15264, 16992, 18336, 19848, 21384, 22152, 23688, 24496, 29296,
    1096, 1416, 1800, 2344, 2856, 3496, 4136, 4968, 5544, 6200, 6968, 7992, 9144, 10296, 11448, 12216, 12960, 14688, 15840, 16992, 18336, 19848, 21384, 22920, 24496, 25456, 29296,
    1128, 1480, 1800, 2408, 2984, 3624, 4264, 4968, 5736, 6456, 7224, 8248, 9528, 10680, 11832, 12576, 13536, 14688, 16416, 17568, 19080, 20616, 22152, 23688, 25456, 26416, 30576,
    1160, 1544, 1864, 2472, 2984, 3752, 4392, 5160, 5992, 6712, 7480, 8504, 9528, 10680, 12216, 12960, 13536, 15264, 16416, 18336, 19848, 21384, 22920, 24496, 25456, 26416, 30576,
    1192, 1544, 1928, 2536, 3112, 3752, 4584, 5352, 5992, 6712, 7480, 8760, 9912, 11064, 12216, 12960, 14112, 15264, 16992, 18336, 19848, 21384, 22920, 24496, 26416, 27376, 31704,
    1224, 1608, 1992, 2536, 3112, 3880, 4584, 5352, 6200, 6968, 7736, 8760, 9912, 11448, 12576, 13536, 14112, 15840, 17568, 19080, 20616, 22152, 23688, 25456, 26416, 28336, 32856,
    1256, 1608, 2024, 2600, 3240, 4008, 4776, 5544, 6200, 6968, 7992, 9144, 10296, 11448, 12960, 13536, 14688, 16416, 17568, 19080, 20616, 22920, 24496, 25456, 27376, 28336, 32856,
    1256, 1672, 2088, 2664, 3240, 4008, 4776, 5736, 6456, 7224, 7992, 9144, 10680, 11832, 12960, 14112, 14688, 16416, 18336, 19848, 21384, 22920, 24496, 26416, 28336, 29296, 34008,
    1288, 1736, 2088, 2728, 3368, 4136, 4968, 5736, 6456, 7480, 8248, 9528, 10680, 12216, 13536, 14688, 15264, 16992, 18336, 20616, 22152, 23688, 25456, 27376, 28336, 29296, 35160,
    1320, 1736, 2152, 2792, 3496, 4264, 4968, 5992, 6712, 7480, 8504, 9528, 11064, 12216, 13536, 14688, 15840, 17568, 19080, 20616, 22152, 24496, 25456, 27376, 29296, 30576, 35160,
    1352, 1800, 2216, 2856, 3496, 4392, 5160, 5992, 6968, 7736, 8504, 9912, 11064, 12576, 14112, 15264, 15840, 17568, 19080, 21384, 22920, 24496, 26416, 28336, 29296, 31704, 36696,
    1384, 1800, 2216, 2856, 3624, 4392, 5160, 6200, 6968, 7992, 8760, 9912, 11448, 12960, 14112, 15264, 16416, 18336, 19848, 21384, 22920, 25456, 27376, 28336, 30576, 31704, 36696,
    1416, 1864, 2280, 2984, 3624, 4584, 5352, 6200, 7224, 7992, 9144, 10296, 11832, 12960, 14688, 15840, 16416, 18336, 19848, 22152, 23688, 25456, 27376, 29296, 31704, 32856, 37888,
    1416, 1864, 2344, 2984, 3752, 4584, 5352, 6456, 7224, 8248, 9144, 10680, 11832, 13536, 14688, 15840, 16992, 19080, 20616, 22152, 24496, 26416, 28336, 29296, 31704, 32856, 37888,
    1480, 1928, 2344, 3112, 3752, 4776, 5544, 6456, 7480, 8248, 9144, 10680, 12216, 13536, 15264, 16416, 16992, 19080, 21384, 22920, 24496, 26416, 28336, 30576, 32856, 34008, 39232,
    1480, 1992, 2408, 3112, 3880, 4776, 5736, 6712, 7480, 8504, 9528, 11064, 12216, 14112, 15264, 16416, 17568, 19848, 21384, 22920, 25456, 27376, 29296, 30576, 32856, 34008, 40576,
    1544, 1992, 2472, 3240, 4008, 4776, 5736, 6712, 7736, 8760, 9528, 11064, 12576, 14112, 15840, 16992, 17568, 19848, 22152, 23688, 25456, 27376, 29296, 31704, 34008, 35160, 40576,
    1544, 2024, 2536, 3240, 4008, 4968, 5992, 6712, 7736, 8760, 9912, 11448, 12576, 14688, 15840, 16992, 18336, 20616, 22152, 24496, 26416, 28336, 30576, 31704, 34008, 35160, 40576,
    1608, 2088, 2536, 3368, 4136, 4968, 5992, 6968, 7992, 9144, 9912, 11448, 12960, 14688, 16416, 17568, 18336, 20616, 22920, 24496, 26416, 28336, 30576, 32856, 35160, 36696, 42368,
    1608, 2088, 2600, 3368, 4136, 5160, 5992, 6968, 7992, 9144, 10296, 11832, 12960, 14688, 16416, 17568, 19080, 20616, 22920, 25456, 27376, 29296, 31704, 32856, 35160, 36696, 42368,
    1608, 2152, 2664, 3496, 4264, 5160, 6200, 7224, 8248, 9144, 10296, 11832, 13536, 15264, 16992, 18336, 19080, 21384, 23688, 25456, 27376, 29296, 31704, 34008, 36696, 37888, 43816,
    1672, 2152, 2664, 3496, 4264, 5352, 6200, 7224, 8504, 9528, 10680, 12216, 13536, 15264, 16992, 18336, 19848, 21384, 23688, 25456, 28336, 30576, 32856, 34008, 36696, 37888, 43816,
    1672, 2216, 2728, 3624, 4392, 5352, 6456, 7480, 8504, 9528, 10680, 12216, 14112, 15840, 17568, 18336, 19848, 22152, 24496, 26416, 28336, 30576, 32856, 35160, 36696, 39232, 45352,
    1736, 2280, 2792, 3624, 4392, 5544, 6456, 7480, 8760, 9912, 11064, 12576, 14112, 15840, 17568, 19080, 19848, 22152, 24496, 26416, 29296, 31704, 34008, 35160, 37888, 39232, 45352,
    1736, 2280, 2856, 3624, 4584, 5544, 6456, 7736, 8760, 9912, 11064, 12576, 14112, 16416, 18336, 19080, 20616, 22920, 24496, 27376, 29296, 31704, 34008, 36696, 37888, 40576, 46888,
    1800, 2344, 2856, 3752, 4584, 5736, 6712, 7736, 9144, 10296, 11448, 12960, 14688, 16416, 18336, 19848, 20616, 22920, 25456, 27376, 29296, 31704, 34008, 36696, 39232, 40576, 46888,
    1800, 2344, 2856, 3752, 4584, 5736, 6712, 7992, 9144, 10296, 11448, 12960, 14688, 16992, 18336, 19848, 21384, 23688, 25456, 28336, 30576, 32856, 35160, 37888, 39232, 40576, 48936,
    1800, 2408, 2984, 3880, 4776, 5736, 6968, 7992, 9144, 10296, 11448, 13536, 15264, 16992, 19080, 20616, 21384, 23688, 26416, 28336, 30576, 32856, 35160, 37888, 40576, 42368, 48936,
    1864, 2472, 2984, 3880, 4776, 5992, 6968, 8248, 9528, 10680, 11832, 13536, 15264, 16992, 19080, 20616, 22152, 24496, 26416, 29296, 31704, 34008, 36696, 37888, 40576, 42368, 48936,
    1864, 2472, 3112, 4008, 4968, 5992, 6968, 8248, 9528, 10680, 11832, 13536, 15264, 17568, 19848, 20616, 22152, 24496, 27376, 29296, 31704, 34008, 36696, 39232, 42368, 43816, 51024,
    1928, 2536, 3112, 4008, 4968, 5992, 7224, 8504, 9528, 11064, 12216, 14112, 15840, 17568, 19848, 21384, 22152, 24496, 27376, 29296, 31704, 35160, 36696, 39232, 42368, 43816, 51024,
    1928, 2536, 3112, 4136, 4968, 6200, 7224, 8504, 9912, 11064, 12216, 14112, 15840, 18336, 19848, 21384, 22920, 25456, 27376, 30576, 32856, 35160, 37888, 40576, 42368, 43816, 52752,
    1992, 2600, 3240, 4136, 5160, 6200, 7480, 8760, 9912, 11064, 12576, 14112, 16416, 18336, 20616, 22152, 22920, 25456, 28336, 30576, 32856, 35160, 37888, 40576, 43816, 45352, 52752,
    1992, 2600, 3240, 4264, 5160, 6200, 7480, 8760, 9912, 11448, 12576, 14688, 16416, 18336, 20616, 22152, 23688, 26416, 28336, 30576, 34008, 36696, 39232, 40576, 43816, 45352, 52752,
    2024, 2664, 3240, 4264, 5160, 6456, 7736, 8760, 10296, 11448, 12960, 14688, 16416, 19080, 20616, 22152, 23688, 26416, 29296, 31704, 34008, 36696, 39232, 42368, 45352, 46888, 55056,
    2088, 2728, 3368, 4392, 5352, 6456, 7736, 9144, 10296, 11832, 12960, 14688, 16992, 19080, 21384, 22920, 24496, 26416, 29296, 31704, 34008, 36696, 40576, 42368, 45352, 46888, 55056,
    2088, 2728, 3368, 4392, 5352, 6712, 7736, 9144, 10680, 11832, 12960, 15264, 16992, 19080, 21384, 22920, 24496, 27376, 29296, 32856, 35160, 37888, 40576, 43816, 45352, 46888, 55056,
    2088, 2792, 3368, 4392, 5544, 6712, 7992, 9144, 10680, 11832, 13536, 15264, 17568, 19848, 22152, 23688, 24496, 27376, 30576, 32856, 35160, 37888, 40576, 43816, 46888, 48936, 55056,
    2152, 2792, 3496, 4584, 5544, 6712, 7992, 9528, 10680, 12216, 13536, 15840, 17568, 19848, 22152, 23688, 25456, 27376, 30576, 32856, 35160, 39232, 42368, 43816, 46888, 48936, 57336,
    2152, 2856, 3496, 4584, 5544, 6968, 8248, 9528, 11064, 12216, 13536, 15840, 17568, 19848, 22152, 23688, 25456, 28336, 30576, 34008, 36696, 39232, 42368, 45352, 46888, 48936, 57336,
    2216, 2856, 3496, 4584, 5736, 6968, 8248, 9528, 11064, 12576, 14112, 15840, 18336, 20616, 22920, 24496, 25456, 28336, 31704, 34008, 36696, 39232, 42368, 45352, 48936, 51024, 57336,
    2216, 2856, 3624, 4776, 5736, 6968, 8248, 9912, 11064, 12576, 14112, 16416, 18336, 20616, 22920, 24496, 26416, 29296, 31704, 34008, 36696, 40576, 43816, 45352, 48936, 51024, 59256,
    2280, 2984, 3624, 4776, 5736, 7224, 8504, 9912, 11448, 12960, 14112, 16416, 18336, 20616, 22920, 24496, 26416, 29296, 31704, 35160, 37888, 40576, 43816, 46888, 48936, 51024, 59256,
    2280, 2984, 3624, 4776, 5992, 7224, 8504, 9912, 11448, 12960, 14688, 16416, 19080, 21384, 23688, 25456, 26416, 29296, 32856, 35160, 37888, 40576, 43816, 46888, 51024, 52752, 59256,
    2280, 2984, 3752, 4776, 5992, 7224, 8760, 10296, 11448, 12960, 14688, 16992, 19080, 21384, 23688, 25456, 27376, 30576, 32856, 35160, 39232, 42368, 45352, 46888, 51024, 52752, 61664,
    2344, 3112, 3752, 4968, 5992, 7480, 8760, 10296, 11832, 13536, 14688, 16992, 19080, 21384, 24496, 25456, 27376, 30576, 32856, 36696, 39232, 42368, 45352, 48936, 51024, 52752, 61664,
    2344, 3112, 3880, 4968, 5992, 7480, 8760, 10296, 11832, 13536, 14688, 16992, 19080, 22152, 24496, 26416, 27376, 30576, 34008, 36696, 39232, 42368, 45352, 48936, 52752, 55056, 61664,
    2408, 3112, 3880, 4968, 6200, 7480, 9144, 10680, 12216, 13536, 15264, 17568, 19848, 22152, 24496, 26416, 28336, 30576, 34008, 36696, 40576, 43816, 46888, 48936, 52752, 55056, 63776,
    2408, 3240, 3880, 5160, 6200, 7736, 9144, 10680, 12216, 13536, 15264, 17568, 19848, 22152, 25456, 26416, 28336, 31704, 34008, 37888, 40576, 43816, 46888, 51024, 52752, 55056, 63776,
    2472, 3240, 4008, 5160, 6200, 7736, 9144, 10680, 12216, 14112, 15264, 17568, 19848, 22920, 25456, 27376, 28336, 31704, 35160, 37888, 40576, 43816, 46888, 51024, 52752, 55056, 63776,
    2472, 3240, 4008, 5160, 6456, 7736, 9144, 11064, 12576, 14112, 15840, 18336, 20616, 22920, 25456, 27376, 29296, 31704, 35160, 37888, 42368, 45352, 48936, 51024, 55056, 57336, 66592,
    2536, 3240, 4008, 5352, 6456, 7992, 9528, 11064, 12576, 14112, 15840, 18336, 20616, 22920, 25456, 27376, 29296, 32856, 35160, 39232, 42368, 45352, 48936, 51024, 55056, 57336, 66592,
    2536, 3368, 4136, 5352, 6456, 7992, 9528, 11064, 12576, 14112, 15840, 18336, 20616, 23688, 26416, 28336, 29296, 32856, 36696, 39232, 42368, 45352, 48936, 52752, 55056, 57336, 66592,
    2536, 3368, 4136, 5352, 6456, 7992, 9528, 11448, 12960, 14688, 16416, 18336, 21384, 23688, 26416, 28336, 30576, 32856, 36696, 39232, 42368, 46888, 48936, 52752, 57336, 59256, 68808,
    2600, 3368, 4136, 5352, 6712, 8248, 9528, 11448, 12960, 14688, 16416, 19080, 21384, 23688, 26416, 28336, 30576, 34008, 36696, 40576, 43816, 46888, 51024, 52752, 57336, 59256, 68808,
    2600, 3496, 4264, 5544, 6712, 8248, 9912, 11448, 12960, 14688, 16416, 19080, 21384, 24496, 27376, 29296, 30576, 34008, 37888, 40576, 43816, 46888, 51024, 55056, 57336, 59256, 68808,
    2664, 3496, 4264, 5544, 6712, 8248, 9912, 11448, 13536, 15264, 16992, 19080, 21384, 24496, 27376, 29296, 30576, 34008, 37888, 40576, 43816, 46888, 51024, 55056, 57336, 61664, 71112,
    2664, 3496, 4264, 5544, 6968, 8504, 9912, 11832, 13536, 15264, 16992, 19080, 22152, 24496, 27376, 29296, 31704, 35160, 37888, 40576, 45352, 48936, 51024, 55056, 59256, 61664, 71112,
    2728, 3496, 4392, 5736, 6968, 8504, 10296, 11832, 13536, 15264, 16992, 19848, 22152, 25456, 28336, 29296, 31704, 35160, 37888, 42368, 45352, 48936, 52752, 55056, 59256, 61664, 71112,
    2728, 3624, 4392, 5736, 6968, 8760, 10296, 11832, 13536, 15264, 16992, 19848, 22152, 25456, 28336, 30576, 31704, 35160, 39232, 42368, 45352, 48936, 52752, 57336, 59256, 61664, 73712,
    2728, 3624, 4392, 5736, 6968, 8760, 10296, 12216, 14112, 15840, 17568, 19848, 22920, 25456, 28336, 30576, 31704, 35160, 39232, 42368, 46888, 48936, 52752, 57336, 61664, 63776, 73712,
    2792, 3624, 4584, 5736, 7224, 8760, 10296, 12216, 14112, 15840, 17568, 19848, 22920, 25456, 28336, 30576, 32856, 36696, 39232, 43816, 46888, 51024, 55056, 57336, 61664, 63776, 75376,
    2792, 3752, 4584, 5992, 7224, 8760, 10680, 12216, 14112, 15840, 17568, 20616, 22920, 26416, 29296, 30576, 32856, 36696, 40576, 43816, 46888, 51024, 55056, 57336, 61664, 63776, 75376,
    2856, 3752, 4584, 5992, 7224, 9144, 10680, 12576, 14112, 16416, 18336, 20616, 23688, 26416, 29296, 31704, 32856, 36696, 40576, 43816, 46888, 51024, 55056, 59256, 61664, 63776, 75376,
    2856, 3752, 4584, 5992, 7480, 9144, 10680, 12576, 14688, 16416, 18336, 20616, 23688, 26416, 29296, 31704, 34008, 36696, 40576, 43816, 48936, 51024, 55056, 59256, 63776, 66592, 75376,
    2856, 3752, 4584, 5992, 7480, 9144, 10680, 12576, 14688, 16416, 18336, 21384, 23688, 26416, 29296, 31704, 34008, 37888, 40576, 45352, 48936, 52752, 57336, 59256, 63776, 66592, 75376,
    2984, 3880, 4776, 6200, 7480, 9144, 11064, 12960, 14688, 16416, 18336, 21384, 23688, 27376, 30576, 31704, 34008, 37888, 42368, 45352, 48936, 52752, 57336, 59256, 63776, 66592, 75376,
    2984, 3880, 4776, 6200, 7480, 9528, 11064, 12960, 14688, 16992, 18336, 21384, 24496, 27376, 30576, 32856, 34008, 37888, 42368, 45352, 48936, 52752, 57336, 61664, 63776, 66592, 75376,
    2984, 3880, 4776, 6200, 7736, 9528, 11064, 12960, 15264, 16992, 19080, 21384, 24496, 27376, 30576, 32856, 35160, 39232, 42368, 46888, 48936, 52752, 57336, 61664, 66592, 68808, 75376,
    2984, 4008, 4776, 6200, 7736, 9528, 11448, 12960, 15264, 16992, 19080, 22152, 24496, 27376, 30576, 32856, 35160, 39232, 42368, 46888, 51024, 55056, 59256, 61664, 66592, 68808, 75376,
    2984, 4008, 4968, 6456, 7736, 9528, 11448, 13536, 15264, 16992, 19080, 22152, 24496, 28336, 31704, 34008, 35160, 39232, 43816, 46888, 51024, 55056, 59256, 61664, 66592, 68808, 75376,
    3112, 4008, 4968, 6456, 7992, 9528, 11448, 13536, 15264, 17568, 19080, 22152, 25456, 28336, 31704, 34008, 35160, 39232, 43816, 46888, 51024, 55056, 59256, 63776, 66592, 71112, 75376};

int gviMCS_lktbl_1lyr[3 * MAX_MCS_N] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, // MCS index
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,                    // Qm
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 10, 11, 12, 13, 14, 15, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26}; // I_tbs

// MCS lkt example for 40RB case
//TBSlist=[1096, 1416, 1800, 2344, 2856, 3496, 4136, 4968, 5544, 6200,6200, 6968, 7992, 9144, 10296,11448, 12216, 12216, 12960, 14688, 15840, 16992, 18336, 19848, 21384, 22920, 24496, 25456, 29296]
//SNRlist= [-9.71199989, -8.62059975, -7.59399986, -6.4604001, -5.61030006, -4.73880005, -4.01329994, -2.92149997, -2.24720001, 0.63647002, 1.23650002, 1.64180005, 2.13540006, 2.7184999, 3.23259997, 3.69219995, 4.07359982, 4.87360001, 6.12989998, 6.87249994, 7.39989996, 7.80429983, 8.53450012, 9.77820015, 10.5019999, 11.2019997, 12.4910002, 12.658, 14.467];

float gvfMCS_snr_lktbl[MAX_MCS_N * 10];
int giMCS_snr_lktbl_CHK = 0;

int AMC_getMCSsnrs(float *vfSNR_list, int iNUM, int RBnum, float fSNRdB_inc)
/* generate snr table for MCS0~MCS27
*  vfSNR_list : snr list for mcs0~27
*  iNUM       : number of MCS
*  RBnum      : number of RB
*  fSNRdB_inc : fixed snr bias
Change History
*  1st version designed by Duan Weiming in 2020-04-10
*  average SNR (over rx channels) is supposed , modified by by Duan Weiming in 2021-03-17
*/
{

  ret0ERR_LEZ2(iNUM, RBnum) ret0ERR_NEQ(iNUM, MAX_MCS_N) ret0ERR_RNG(RBnum, 5, 100) //ret0ERR_LIST(RxNUM,1,2,4)
      MEMCHK(vfSNR_list, iNUM)

      //float fSNRdB_inc = 10*log10((float)RxNUM);

      char strMiQfile[] = "SDLview_data_2Rgauss_10RB.txt";
  //float  vfMCSsnr_2R40RB[MAX_MCS_N] = {-9.71199989, -8.62059975, -7.59399986, -6.4604001, -5.61030006, -4.73880005, -4.01329994, -2.92149997, -2.24720001, 0.63647002, 1.23650002, 1.64180005, 2.13540006, 2.7184999, 3.23259997, 3.69219995, 4.07359982, 4.87360001, 6.12989998, 6.87249994, 7.39989996, 7.80429983, 8.53450012, 9.77820015, 10.5019999, 11.2019997, 12.4910002, 12.658, 14.467};
  float vfMCSsnr_2R40RB[MAX_MCS_N] = {-9.71199989, -8.62059975, -7.59399986, -6.4604001, -5.61030006, -4.73880005, -4.01329994, -2.92149997, -2.24720001, -1.46350002, 0.436470002, 0.741789997, 1.23539996, 2.11849999, 2.93260002, 3.59220004, 4.07359982, 4.87360001, 5.42990017, 6.47249985, 7.09989977, 7.70429993, 8.53450012, 9.37819958, 10.2019997, 11.1020002, 11.9910002, 12.4580002, 14.467};
  float vfMCSsnr_2R20RB[MAX_MCS_N] = {-9.4119997, -8.32509995, -7.57079983, -6.26039982, -5.41029978, -4.56050014, -3.84699988, -2.82150006, -2.09759998, -1.43019998, 0.46983999, 0.671500027, 1.32969999, 2.04119992, 2.79879999, 3.61030006, 4.28009987, 4.98010015, 5.35389996, 6.33690023, 7.17159986, 7.73890018, 8.35149956, 9.19909954, 10.1210003, 10.9209995, 11.5089998, 12.1569996, 14.9689999};
  float vfMCSsnr_2R10RB[MAX_MCS_N] = {-9.4119997, -8.32509995, -7.57079983, -6.26039982, -5.41029978, -4.56050014, -3.84699988, -2.82150006, -2.09759998, -1.43019998, 0.46983999, 0.671500027, 1.32969999, 2.04119992, 2.79879999, 3.61030006, 4.28009987, 4.98010015, 5.35389996, 6.33690023, 7.17159986, 7.73890018, 8.35149956, 9.19909954, 10.1210003, 10.9209995, 11.5089998, 12.1569996, 14.9689999};

  //giMCS_snr_lktbl_CHK = 1;  // skip the following
  float fBLERobj = 0.2; // 20% BLER

  if (0 == giMCS_snr_lktbl_CHK)
  {
    //AMC_readMCSsnr(gvfMCS_snr_lktbl, MAX_MCS_N,  fBLERobj , strMiQfile);
    giMCS_snr_lktbl_CHK = 1;
  }
  float *pfSRC = vfMCSsnr_2R10RB;
  if ((15 <= RBnum) && (30 > RBnum))
  {
    pfSRC = vfMCSsnr_2R20RB;
  }
  if ((30 <= RBnum) && (100 >= RBnum))
  {
    pfSRC = vfMCSsnr_2R40RB;
  }

  FLT_CP(pfSRC, vfSNR_list, iNUM);
  //if( 0 == isDualRX) { VEC_addC(vfSNR_list, iNUM, 3.0);   }  // added by Duan Weiming in 2021-01-30
  VEC_addC(vfSNR_list, iNUM, 3.0 + fSNRdB_inc);

  return iNUM;
}

int AMC_readMCSsnr(float *vfSNR_list, int MaxN, float fBLERobj, char *strMiQfile)
/*
Change History
*  1st version decoupled from AMC_getMCSsnrs(), by Duan Weiming in 2020-04-11
*/
{
  ret0ERR_NEQ(MaxN, MAX_MCS_N) MEMCHK(vfSNR_list, MaxN) FLT_ZERO(vfSNR_list, MaxN);
  int VEClen = 200;
  int iMaxCurve = 100;
  int iPlotOBJ = 0; //float fBLERobj = 0.2;
  int jjj, lll, ilen, iSumLEN, iFind;
  float *pfVx, *pfVy;
  _NEW_INIT()
  _NEW_FLT0(vfVx_list, VEClen * iMaxCurve)
  _NEW_FLT0(vfVy_list, VEClen * iMaxCurve)
  _NEW_INT0(viVlen_list, iMaxCurve)
  _NEW_INT0(viMCS_ids, iMaxCurve)
  _NEW_FLT0(vfVECmem, VEClen)

  int MCSnum = miQ_2DcurveSread(vfVx_list, vfVy_list, VEClen, viVlen_list, iMaxCurve, iPlotOBJ, strMiQfile, 0, viMCS_ids, 0);
  ERR_NEQ(MCSnum, MAX_MCS_N)

  iSumLEN = 0;
  int RealMCS_N = MINOP(MCSnum, MAX_MCS_N);
  int iMcs;
  _LOOPUP_LT(jjj, 0, RealMCS_N)
  {
    ilen = viVlen_list[jjj];
    iMcs = viMCS_ids[jjj];
    pfVx = vfVx_list + iSumLEN;
    pfVy = vfVy_list + iSumLEN;
    FLT_CP(pfVy, vfVECmem, ilen);
    VEC_subC(vfVECmem, ilen, fBLERobj);
    VEC_abs(vfVECmem, vfVECmem, ilen, 0);
    VEC_minSTD(vfVECmem, ilen, &iFind); //iFind = VEC_findsorted(pfVy, ilen, fBLERobj,  0); //  isAscend=0
    ERR_CHKrng(iFind, 0, ilen - 1)
        vfSNR_list[iMcs] = pfVx[iFind];
    iSumLEN += ilen;
  }

  _NEW_FREE()
  return RealMCS_N;
}

// 256, 344, 424, 568, 696, 872, 1032, 1224, 1384, 1544, 1736, 2024, 2280, 2536, 2856, 3112, 3240, 3624, 4008, 4264, 4584, 4968, 5352, 5736, 5992, 6200, 7480,
// 10*144

int AMC_mcslkt(int *viNetTBS_list, int *viQamType_list, float *vfCodeR_list, int MaxLEN, int RBnum)
/*
Change History
*  1st version designed by Duan Weiming in 2020-04-04
*/
{
  ret0ERR_LT(MaxLEN, MAX_MCS_N) MEMCHK3(viNetTBS_list, viQamType_list, vfCodeR_list, MaxLEN) ret0ERR_RNG(RBnum, 1, 110) int SUMsc = 144 * RBnum;
  int jjj, Itbs, NetTBS, iQamB, iQamType;
  float fCodeR;
  int *piTBS_list = gviTBS_lktbl_1lyr + (RBnum - 1) * MAX_ITBS_N;
  int *piQamB_lst = gviMCS_lktbl_1lyr + 1 * MAX_MCS_N;
  int *piItbs_lst = gviMCS_lktbl_1lyr + 2 * MAX_MCS_N;

  int iMaxMCS_N = MINOP(MAX_MCS_N, MCS_MAX + 1);

  _LOOPUP_LT(jjj, 0, iMaxMCS_N)
  {
    Itbs = piItbs_lst[jjj];
    NetTBS = piTBS_list[Itbs];
    iQamB = piQamB_lst[jjj];
    iQamType = MAPQamB_QamType(iQamB);
    fCodeR = _DIVOP(NetTBS + 24, SUMsc * iQamB);

    viNetTBS_list[jjj] = NetTBS;
    viQamType_list[jjj] = iQamType;
    vfCodeR_list[jjj] = fCodeR;
  }

  int iTST = 3;
  return iMaxMCS_N;
}

int AMC_chk(int *pAMCmem)
/*
Change History
*  1st version designed by Duan Weiming  in 2020-04-01
*  add new member(m_RBuse ),  by Duan Weiming in 2021-03-17
*/
{
  stAMC *pstAMC = (stAMC *)pAMCmem;
  ERR_LT(pstAMC->m_maxTBS, 6144)
  //int RBnum = pstAMC->m_QamN/(144);    ERR_NEQ(pstAMC->m_QamN, RBnum*144)    ERR_CHKrng(RBnum,5,110)
  int RBnum = pstAMC->m_RBuse;
  ERR_CHKrng(RBnum, 5, 110) return RBnum;
}

void AMC_rst(int *pAMCmem)
/* reset AMC configuration
*  pAMCmem : AMC pointer
Change History
*  1st version designed by Duan Weiming in 2021-03-20
*/
{
  stAMC *psAMC = (stAMC *)pAMCmem;

  MEMCHK(pAMCmem, (sizeof(stAMC) >> 2))

  psAMC->m_RvID = 0;
  psAMC->m_RVlen = 0;
  psAMC->m_netTBS = 0;
  psAMC->m_QamType = 0;
  psAMC->m_MCSnow = 0;
  psAMC->m_QamN = 0;
  psAMC->m_Transtimes = 0;
}

void AMC_init(int *pAMCmem, int NetTBS, int SUMsc, int iModuType, float fEsN0_init, int iRXnum, int iAMC_ON)
/*   only one layer is assumed !!!
Change History
*  1st version designed by Duan Weiming  in 2020-04-01
*  support static configuration, by Duan Weiming in 2020-04-02
*/
{
  stAMC *pstAMC = (stAMC *)pAMCmem;
  retERR_RNG(NetTBS, MAX_NetTBS_MIN, MAX_NetTBS_MAX) retERR_LIST(iRXnum, 1, 2, 4) int RBnum = SUMsc / 144;
  ERR_NEQ(SUMsc, RBnum * 144)
  ERR_CHKrng(RBnum, 5, 110) retERR_LIST(iModuType, 2, 4, 16, 64, 256)

      pstAMC->m_RvID = 0;
  pstAMC->m_RVlen = GetQamBITS(iModuType) * SUMsc;
  pstAMC->m_netTBS = NetTBS;
  pstAMC->m_QamType = iModuType;
  pstAMC->m_QamN = SUMsc; // m_RBuse*144
  pstAMC->m_maxTBS = MAX_NetTBS_MAX;
  pstAMC->m_MCSnow = 0;
  pstAMC->m_AMC_ON = iAMC_ON;
  pstAMC->m_RBuse = RBnum;
  pstAMC->m_RXnum = iRXnum;
  pstAMC->m_Transtimes = MAX_TRANSTIMES - 2; //init trans times: MAX_TRANSTIMES - 1 , set 0 in AMC_contorl

  int *vTBS_list = gviTBS_lktbl_1lyr + (RBnum - 1) * MAX_ITBS_N;
  int iminTBS = 0; //  pstAMC->m_RVlen/3;
  int jjj;
  int iITBSmin = 0;
  _LOOPUP_LT(jjj, 0, MAX_ITBS_N)
  {
    if (iminTBS <= vTBS_list[jjj])
    {
      iITBSmin = jjj;
      break;
    }
  }

  int *vQamB_list = gviMCS_lktbl_1lyr + MAX_MCS_N;
  int iQamB = 2;
  int *vITBS_list = gviMCS_lktbl_1lyr + MAX_MCS_N * 2;
  int iMCSmin = 0;

  _LOOPUP_LT(jjj, 0, MAX_MCS_N)
  {
    if (iITBSmin == vITBS_list[jjj])
    {
      iQamB = vQamB_list[jjj];
      iMCSmin = jjj;
      break;
    }
  }
  pstAMC->m_MCSmin = iMCSmin;

  /*
    int gviMCS_lktbl_1lyr[3*MAX_MCS_N] = {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,   // MCS index
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,   // Qm
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  9 ,  10,  11,  12,  13,  14,  15,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26};  // I_tbs
    */

  stRingBUF_init((int *)&pstAMC->m_RingBUFmeas, pstAMC->m_MeasBUFF, MAX_MEAS_DLY + 10, fEsN0_init);
  int iNACK = 0;
  if (pstAMC->m_AMC_ON)
  {
    AMC_control(pAMCmem, 0, 0, iNACK, fEsN0_init);
  }

  _NEW_INIT()
  _NEW_FLT0(vfCodeR_list, 29)
  _NEW_INT0(viNetTBS_list, 29)
  _NEW_INT0(viQamType_list, 29)
  _NEW_INT0(viMCSmatch, 29)

  int MCSnum = AMC_mcslkt(viNetTBS_list, viQamType_list, vfCodeR_list, 29, 10);
  int iITBSnow = IVEC_findsorted(viNetTBS_list, MCSnum, NetTBS);
  int *piItbs_lkt = gviMCS_lktbl_1lyr + 2 * MAX_MCS_N;
  int iFindN = IVEC_match(piItbs_lkt, MAX_MCS_N, iITBSnow, viMCSmatch);
  pstAMC->m_MCSnow = viMCSmatch[iFindN - 1];

  _NEW_FREE()
}

int Update_RV(int RvIDnow, int iNACK)
/*
Change History
*  1st version de-coupled from AMC_updateRV(), by Duan Weiming in 2021-01-31
*/
{
  int RvID = 0;
  int MaxTXnum = MAX_HARQ_TRANS_N;
  ret0ERR_RNG(RvIDnow, 0, MaxTXnum - 1)

      if (0 == iNACK)
  {
    RvID = 0;
  } // ACK
  else
  { // NACK
    if (MaxTXnum - 1 <= RvIDnow)
    {
      RvID = 0;
    } // reset after max trans.
    else
    {
      RvID = RvIDnow + 1;
    } // re-trans
  }
  return RvID;
}

int AMC_updateRV(int *pAMCmem, int iNACK)
/*  update RvID
Change History
*  1st version designed by Duan WeiminG in 2020-04-01
*/
{
  stAMC *pstAMC = (stAMC *)pAMCmem;
  int RvIDnow = pstAMC->m_RvID;

  int RvID = Update_RV(RvIDnow, iNACK);
  /*
    int RvID = 0;
    int MaxTXnum = MAX_HARQ_TRANS_N;       ret0ERR_RNG(RvIDnow,0,MaxTXnum-1)

    if(0 == iNACK) { RvID = 0;  }                       // ACK
    else {                                              // NACK
        if( MaxTXnum-1 <= RvIDnow) { RvID = 0;        } // reset after max trans.
        else                       { RvID = RvIDnow+1;} // re-trans

    } */
  pstAMC->m_RvID = RvID;
  return RvID;
}

void AMC_updateMCS(int *pAMCmem, float fEsN0_meas, int iDly, int iLyrN)
/*  update AMC parameters according to delayed measurement
Change History
*  1st version designed by Duan WeiminG in 2020-04-01
*  support dynamic layer number , modified by Duan Weiming in 2020-03-17
*/
{
  stAMC *pstAMC = (stAMC *)pAMCmem;
  float fEsN0_use;
  int iMCS;
  retERR_RNG(iLyrN, 1, 4) int RBnum = AMC_chk(pAMCmem);
  int RvID = pstAMC->m_RvID;
  int iRXnum = pstAMC->m_RXnum;
  retERR_LIST(iRXnum, 1, 2, 4) int Transtimes = pstAMC->m_Transtimes;

  //float fSNR_bias = 10*log10((float)iRXnum) - 6.0*log2(iLyrN);    // added by Duan Weiming in 2021-03-17
  float fSNR_bias = 10 * log10((float)iRXnum); // modified by Duan Weiming in 2021-03-19

  float vfMapMCS_EsN0list[MAX_MCS_N];
  int iMaxMCS_N = AMC_getMCSsnrs(vfMapMCS_EsN0list, MAX_MCS_N, RBnum, 0.0); // fSNR_bias ==> 0.0 , modified by Duan Weiming in 2021-03-18
  retERR_NEQ(iMaxMCS_N, MAX_MCS_N)

      retERR_RNG(iDly, 0, 19) retERR_RNG(RvID, 0, MAX_HARQ_TRANS_N - 1)

          stRingBUF_push((int *)&pstAMC->m_RingBUFmeas, &fEsN0_meas, 1);
  stRingBUF_pop((int *)&pstAMC->m_RingBUFmeas, &fEsN0_use, 1, iDly);
  fEsN0_use += fSNR_bias; // modified by Duan Weiming in 2021-03-18
  // if( ( 0 < RvID ) && (0 < pstAMC->m_netTBS) ) { return;  }  // not update MCS if re-trans
  if ((0 < Transtimes) && (0 < pstAMC->m_netTBS))
  {
    return;
  } // not update MCS if not new TB

  pstAMC->m_AvgSNRdB = fEsN0_use; // added for testing , by Duan Weiming in 2021-03-18
  pstAMC->m_LyrN = iLyrN;         // added for testing , by Duan Weiming in 2021-03-20

  int RBuse = pstAMC->m_RBuse;
  retERR_RNG(RBuse, 5, 110) pstAMC->m_QamN = iLyrN * RBuse * 144; // update m_QamN, added by Duan Weiming in 2021-03-17

  iMCS = VEC_findsorted(vfMapMCS_EsN0list, MAX_MCS_N, fEsN0_use, 1);
  iMCS = MAXOP(pstAMC->m_MCSmin, iMCS);
  iMCS = MINOP(MCS_MAX, iMCS); // added for one code word , by Duan Weiming in 2020-04-06
  ERR_CHKrng(iMCS, 0, MAX_MCS_N) int *vQamB_list = gviMCS_lktbl_1lyr + MAX_MCS_N;
  int iQamType = MAPQamB_QamType(vQamB_list[iMCS]);
  int *vITBS_list = gviMCS_lktbl_1lyr + MAX_MCS_N * 2;
  int iITBS = vITBS_list[iMCS];
  int *vTBS_list = gviTBS_lktbl_1lyr + (RBnum - 1) * MAX_ITBS_N;

  pstAMC->m_RVlen = vQamB_list[iMCS] * pstAMC->m_QamN; // added by Duan Weiming in 2020-04-02
  pstAMC->m_MCSnow = iMCS;
  pstAMC->m_netTBS = vTBS_list[iITBS];
  // fprintf(stderr, "\n m_netTBS:%d\n", pstAMC->m_netTBS);

  pstAMC->m_QamType = iQamType;
#ifdef GDB_FLAG
  ERR_LT(3 * (pstAMC->m_netTBS + 24) + 12, pstAMC->m_RVlen)
  float fCodeRate = _DIVOP(pstAMC->m_netTBS, pstAMC->m_RVlen);
  if (_CHK_OPT2(iQamType, 4, 16))
  {
    ERR_LT(0.75, fCodeRate)
  } // QPSK & 16QAM cr < 0.7,
  if (_CHK_OPT2(iQamType, 64, 256))
  {
    ERR_LT(0.98, fCodeRate)
  } // QPSK & 16QAM cr < 0.7,
#endif
}

int AMC_updateTT(int *pAMCmem)
/*
update the transtime times for each TB

*/
{
  stAMC *pstAMC = (stAMC *)pAMCmem;
  int TTnow = pstAMC->m_Transtimes;

  int TT = 0;

  //只传输一次
  if (MAX_TRANSTIMES - 1 == TTnow)  { TT = 0;  }      // finish 4 times trans ，reset m_Transtimes = 0.
  else {TT = TTnow + 1;}                             // update m_Transtimes += 1.

  pstAMC->m_Transtimes = TT;
  return TT;
}

int AMC_control(int *pAMCmem, int *viINFObits, int MAXlen, int iNACK, float fEsN0_meas, int iDly, int iLyrN)
/*  iNACK =0 : ACK
Change History
*  1st version designed by Duan WeiminG in 2020-03-30
*/
{
  //int iDly     = 0;
  //int RxNUM = 1;

  stAMC *pstAMC = (stAMC *)pAMCmem;
  ret0ERR_LTZ(MAXlen) nzMEMCHK(viINFObits, MAXlen) ret0ERR_RNG(iLyrN, 1, 4) ret0ERR_LTZ(iDly)

      //if(0 == pstAMC->m_AMC_ON ) { return 0; }    // a bug !!!
      // int RvID = 0;    if( pstAMC->m_AMC_ON ) { RvID = AMC_updateRV(pAMCmem, iNACK); }
      // if( 0 < RvID ) {
      //     int iTST = 3;
      // }

      // if( 1 == pstAMC->m_AMC_ON )        {  AMC_updateMCS(pAMCmem, fEsN0_meas, iDly, iLyrN); }
      // if( ( 0 ==  RvID ) && viINFObits ) {  RandomBits(viINFObits, pstAMC->m_netTBS);        }

      // return RvID;

      int TT = 0;
  if (pstAMC->m_AMC_ON)
  {
    TT = AMC_updateTT(pAMCmem);
  }

  pstAMC->m_RvID = TT;

  if (1 == pstAMC->m_AMC_ON)
  {
    AMC_updateMCS(pAMCmem, fEsN0_meas, iDly, iLyrN);
  }

  if ((0 == TT) && viINFObits)
  {
    RandomBits(viINFObits, pstAMC->m_netTBS);
  }

  return TT;
}
