/*****************************************************************************
 * bandlimited.h : bandlimited interpolation resampler
 *****************************************************************************
 * Copyright (C) 2002 VLC authors and VideoLAN
 * $Id$
 *
 * Authors: Gildas Bazin <gbazin@netcourrier.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

/* Conversion constants */
#define Nhc       8
#define Npc      (1<<Nhc)

/* Description of constants:
 *
 * Npc - is the number of look-up values available for the lowpass filter
 *    between the beginning of its impulse response and the "cutoff time"
 *    of the filter.  The cutoff time is defined as the reciprocal of the
 *    lowpass-filter cut off frequence in Hz.  For example, if the
 *    lowpass filter were a sinc function, Npc would be the index of the
 *    impulse-response lookup-table corresponding to the first zero-
 *    crossing of the sinc function.  (The inverse first zero-crossing
 *    time of a sinc function equals its nominal cutoff frequency in Hz.)
 *    Npc must be a power of 2 due to the details of the current
 *    implementation. The default value of 512 is sufficiently high that
 *    using linear interpolation to fill in between the table entries
 *    gives approximately 16-bit accuracy in filter coefficients.
 *
 * Nhc - is log base 2 of Npc.
 */

#define SMALL_FILTER_NMULT ((int16_t)13)
#define SMALL_FILTER_SCALE 13128 /* Unity-gain scale factor */
#define SMALL_FILTER_NWING 1536 /* Filter table length */
static const float SMALL_FILTER_FLOAT_IMP[] /* Impulse response */ = {
0.900000,
0.899980,
0.899920,
0.899821,
0.899681,
0.899502,
0.899283,
0.899024,
0.898726,
0.898388,
0.898010,
0.897592,
0.897135,
0.896638,
0.896102,
0.895526,
0.894911,
0.894256,
0.893562,
0.892829,
0.892056,
0.891244,
0.890394,
0.889504,
0.888575,
0.887608,
0.886602,
0.885557,
0.884474,
0.883352,
0.882192,
0.880993,
0.879756,
0.878482,
0.877169,
0.875818,
0.874430,
0.873004,
0.871541,
0.870040,
0.868502,
0.866927,
0.865315,
0.863667,
0.861981,
0.860259,
0.858501,
0.856707,
0.854876,
0.853010,
0.851108,
0.849170,
0.847197,
0.845189,
0.843146,
0.841067,
0.838954,
0.836807,
0.834625,
0.832409,
0.830160,
0.827876,
0.825559,
0.823209,
0.820825,
0.818408,
0.815959,
0.813477,
0.810963,
0.808417,
0.805839,
0.803229,
0.800588,
0.797916,
0.795213,
0.792479,
0.789714,
0.786919,
0.784095,
0.781240,
0.778356,
0.775442,
0.772500,
0.769529,
0.766529,
0.763501,
0.760444,
0.757361,
0.754249,
0.751110,
0.747945,
0.744753,
0.741534,
0.738289,
0.735018,
0.731721,
0.728400,
0.725053,
0.721681,
0.718285,
0.714865,
0.711420,
0.707953,
0.704461,
0.700947,
0.697410,
0.693851,
0.690269,
0.686665,
0.683040,
0.679394,
0.675727,
0.672039,
0.668331,
0.664602,
0.660854,
0.657087,
0.653300,
0.649495,
0.645671,
0.641829,
0.637969,
0.634091,
0.630197,
0.626285,
0.622357,
0.618412,
0.614452,
0.610476,
0.606485,
0.602478,
0.598457,
0.594422,
0.590373,
0.586310,
0.582234,
0.578144,
0.574042,
0.569928,
0.565801,
0.561663,
0.557514,
0.553353,
0.549182,
0.545001,
0.540809,
0.536607,
0.532397,
0.528177,
0.523948,
0.519711,
0.515466,
0.511214,
0.506954,
0.502686,
0.498413,
0.494132,
0.489846,
0.485554,
0.481256,
0.476954,
0.472646,
0.468335,
0.464019,
0.459699,
0.455377,
0.451050,
0.446722,
0.442390,
0.438057,
0.433722,
0.429385,
0.425048,
0.420709,
0.416370,
0.412031,
0.407692,
0.403354,
0.399016,
0.394679,
0.390344,
0.386011,
0.381680,
0.377351,
0.373025,
0.368702,
0.364382,
0.360066,
0.355754,
0.351446,
0.347143,
0.342844,
0.338551,
0.334264,
0.329982,
0.325706,
0.321437,
0.317174,
0.312918,
0.308670,
0.304429,
0.300197,
0.295972,
0.291756,
0.287548,
0.283350,
0.279161,
0.274982,
0.270812,
0.266653,
0.262504,
0.258366,
0.254239,
0.250123,
0.246018,
0.241926,
0.237846,
0.233777,
0.229722,
0.225679,
0.221650,
0.217634,
0.213632,
0.209643,
0.205669,
0.201709,
0.197764,
0.193833,
0.189918,
0.186018,
0.182134,
0.178265,
0.174413,
0.170577,
0.166758,
0.162955,
0.159169,
0.155401,
0.151650,
0.147916,
0.144201,
0.140503,
0.136824,
0.133163,
0.129521,
0.125898,
0.122294,
0.118710,
0.115145,
0.111599,
0.108073,
0.104568,
0.101083,
0.097618,
0.094174,
0.090750,
0.087348,
0.083966,
0.080606,
0.077268,
0.073951,
0.070656,
0.067383,
0.064132,
0.060903,
0.057697,
0.054513,
0.051352,
0.048214,
0.045099,
0.042006,
0.038938,
0.035892,
0.032870,
0.029872,
0.026898,
0.023947,
0.021021,
0.018118,
0.015240,
0.012386,
0.009557,
0.006752,
0.003972,
0.001217,
-0.001514,
-0.004219,
-0.006900,
-0.009555,
-0.012186,
-0.014790,
-0.017370,
-0.019924,
-0.022453,
-0.024956,
-0.027433,
-0.029885,
-0.032310,
-0.034710,
-0.037085,
-0.039433,
-0.041755,
-0.044051,
-0.046321,
-0.048565,
-0.050782,
-0.052974,
-0.055139,
-0.057278,
-0.059391,
-0.061477,
-0.063537,
-0.065570,
-0.067577,
-0.069558,
-0.071513,
-0.073440,
-0.075342,
-0.077217,
-0.079065,
-0.080887,
-0.082683,
-0.084452,
-0.086195,
-0.087911,
-0.089601,
-0.091265,
-0.092902,
-0.094513,
-0.096097,
-0.097656,
-0.099188,
-0.100693,
-0.102173,
-0.103626,
-0.105053,
-0.106454,
-0.107830,
-0.109179,
-0.110502,
-0.111799,
-0.113070,
-0.114316,
-0.115536,
-0.116730,
-0.117899,
-0.119042,
-0.120159,
-0.121251,
-0.122318,
-0.123360,
-0.124376,
-0.125368,
-0.126334,
-0.127275,
-0.128192,
-0.129083,
-0.129950,
-0.130793,
-0.131611,
-0.132404,
-0.133174,
-0.133919,
-0.134640,
-0.135337,
-0.136010,
-0.136659,
-0.137284,
-0.137886,
-0.138465,
-0.139020,
-0.139552,
-0.140061,
-0.140547,
-0.141010,
-0.141451,
-0.141868,
-0.142263,
-0.142636,
-0.142987,
-0.143316,
-0.143622,
-0.143907,
-0.144170,
-0.144412,
-0.144632,
-0.144830,
-0.145008,
-0.145165,
-0.145301,
-0.145416,
-0.145511,
-0.145585,
-0.145639,
-0.145673,
-0.145687,
-0.145681,
-0.145656,
-0.145611,
-0.145547,
-0.145464,
-0.145361,
-0.145240,
-0.145100,
-0.144942,
-0.144766,
-0.144571,
-0.144358,
-0.144127,
-0.143879,
-0.143613,
-0.143330,
-0.143030,
-0.142713,
-0.142379,
-0.142028,
-0.141661,
-0.141278,
-0.140878,
-0.140463,
-0.140032,
-0.139585,
-0.139123,
-0.138646,
-0.138153,
-0.137646,
-0.137124,
-0.136588,
-0.136037,
-0.135473,
-0.134894,
-0.134302,
-0.133696,
-0.133076,
-0.132444,
-0.131798,
-0.131140,
-0.130469,
-0.129785,
-0.129089,
-0.128381,
-0.127662,
-0.126930,
-0.126187,
-0.125433,
-0.124668,
-0.123891,
-0.123104,
-0.122306,
-0.121498,
-0.120680,
-0.119851,
-0.119013,
-0.118165,
-0.117308,
-0.116441,
-0.115565,
-0.114681,
-0.113788,
-0.112886,
-0.111976,
-0.111057,
-0.110131,
-0.109197,
-0.108255,
-0.107306,
-0.106350,
-0.105386,
-0.104416,
-0.103439,
-0.102455,
-0.101466,
-0.100470,
-0.099468,
-0.098460,
-0.097447,
-0.096428,
-0.095404,
-0.094375,
-0.093341,
-0.092303,
-0.091260,
-0.090212,
-0.089161,
-0.088105,
-0.087046,
-0.085982,
-0.084916,
-0.083846,
-0.082773,
-0.081697,
-0.080618,
-0.079536,
-0.078452,
-0.077366,
-0.076277,
-0.075187,
-0.074095,
-0.073001,
-0.071905,
-0.070808,
-0.069710,
-0.068611,
-0.067512,
-0.066411,
-0.065310,
-0.064209,
-0.063107,
-0.062005,
-0.060903,
-0.059802,
-0.058701,
-0.057600,
-0.056500,
-0.055401,
-0.054303,
-0.053206,
-0.052110,
-0.051015,
-0.049922,
-0.048831,
-0.047741,
-0.046654,
-0.045568,
-0.044485,
-0.043403,
-0.042325,
-0.041249,
-0.040175,
-0.039105,
-0.038037,
-0.036973,
-0.035912,
-0.034854,
-0.033799,
-0.032749,
-0.031701,
-0.030658,
-0.029619,
-0.028583,
-0.027552,
-0.026525,
-0.025502,
-0.024484,
-0.023471,
-0.022462,
-0.021458,
-0.020459,
-0.019464,
-0.018475,
-0.017491,
-0.016513,
-0.015539,
-0.014572,
-0.013610,
-0.012653,
-0.011702,
-0.010757,
-0.009818,
-0.008885,
-0.007958,
-0.007038,
-0.006123,
-0.005215,
-0.004313,
-0.003418,
-0.002530,
-0.001648,
-0.000772,
0.000096,
0.000958,
0.001813,
0.002660,
0.003501,
0.004335,
0.005161,
0.005980,
0.006792,
0.007597,
0.008394,
0.009183,
0.009965,
0.010740,
0.011507,
0.012266,
0.013018,
0.013762,
0.014498,
0.015226,
0.015946,
0.016658,
0.017363,
0.018059,
0.018747,
0.019428,
0.020100,
0.020764,
0.021420,
0.022067,
0.022707,
0.023338,
0.023961,
0.024575,
0.025181,
0.025779,
0.026369,
0.026950,
0.027523,
0.028087,
0.028643,
0.029191,
0.029730,
0.030260,
0.030782,
0.031296,
0.031801,
0.032297,
0.032785,
0.033265,
0.033736,
0.034199,
0.034653,
0.035098,
0.035536,
0.035964,
0.036384,
0.036796,
0.037199,
0.037594,
0.037980,
0.038358,
0.038727,
0.039088,
0.039441,
0.039785,
0.040121,
0.040448,
0.040768,
0.041078,
0.041381,
0.041675,
0.041961,
0.042239,
0.042509,
0.042770,
0.043024,
0.043269,
0.043506,
0.043735,
0.043956,
0.044169,
0.044375,
0.044572,
0.044761,
0.044943,
0.045116,
0.045282,
0.045440,
0.045591,
0.045734,
0.045869,
0.045996,
0.046117,
0.046229,
0.046334,
0.046432,
0.046522,
0.046605,
0.046681,
0.046750,
0.046811,
0.046865,
0.046913,
0.046953,
0.046986,
0.047012,
0.047032,
0.047044,
0.047050,
0.047049,
0.047042,
0.047028,
0.047007,
0.046980,
0.046946,
0.046907,
0.046860,
0.046808,
0.046749,
0.046684,
0.046613,
0.046536,
0.046453,
0.046365,
0.046270,
0.046169,
0.046063,
0.045951,
0.045834,
0.045711,
0.045583,
0.045449,
0.045310,
0.045165,
0.045016,
0.044861,
0.044701,
0.044536,
0.044366,
0.044192,
0.044012,
0.043828,
0.043639,
0.043445,
0.043247,
0.043045,
0.042838,
0.042626,
0.042411,
0.042191,
0.041967,
0.041738,
0.041506,
0.041270,
0.041030,
0.040786,
0.040539,
0.040288,
0.040033,
0.039774,
0.039513,
0.039247,
0.038979,
0.038707,
0.038432,
0.038154,
0.037872,
0.037588,
0.037301,
0.037011,
0.036718,
0.036422,
0.036124,
0.035823,
0.035520,
0.035214,
0.034906,
0.034595,
0.034282,
0.033967,
0.033650,
0.033330,
0.033009,
0.032686,
0.032361,
0.032034,
0.031705,
0.031375,
0.031043,
0.030709,
0.030374,
0.030037,
0.029700,
0.029360,
0.029020,
0.028678,
0.028336,
0.027992,
0.027647,
0.027301,
0.026955,
0.026607,
0.026259,
0.025910,
0.025561,
0.025210,
0.024860,
0.024508,
0.024157,
0.023805,
0.023453,
0.023100,
0.022748,
0.022395,
0.022042,
0.021689,
0.021336,
0.020983,
0.020630,
0.020278,
0.019926,
0.019573,
0.019222,
0.018870,
0.018520,
0.018169,
0.017819,
0.017470,
0.017121,
0.016773,
0.016426,
0.016080,
0.015734,
0.015389,
0.015045,
0.014702,
0.014360,
0.014019,
0.013679,
0.013341,
0.013003,
0.012667,
0.012332,
0.011998,
0.011665,
0.011334,
0.011004,
0.010676,
0.010349,
0.010024,
0.009700,
0.009377,
0.009057,
0.008738,
0.008421,
0.008105,
0.007791,
0.007479,
0.007169,
0.006861,
0.006554,
0.006249,
0.005947,
0.005646,
0.005347,
0.005051,
0.004756,
0.004464,
0.004173,
0.003885,
0.003599,
0.003315,
0.003033,
0.002753,
0.002476,
0.002201,
0.001928,
0.001658,
0.001390,
0.001124,
0.000861,
0.000600,
0.000341,
0.000085,
-0.000169,
-0.000420,
-0.000669,
-0.000915,
-0.001159,
-0.001400,
-0.001639,
-0.001875,
-0.002109,
-0.002340,
-0.002568,
-0.002794,
-0.003017,
-0.003238,
-0.003456,
-0.003671,
-0.003884,
-0.004094,
-0.004301,
-0.004506,
-0.004708,
-0.004907,
-0.005104,
-0.005298,
-0.005489,
-0.005678,
-0.005863,
-0.006046,
-0.006227,
-0.006405,
-0.006579,
-0.006752,
-0.006921,
-0.007088,
-0.007252,
-0.007413,
-0.007572,
-0.007728,
-0.007881,
-0.008031,
-0.008179,
-0.008324,
-0.008466,
-0.008606,
-0.008743,
-0.008877,
-0.009008,
-0.009137,
-0.009263,
-0.009387,
-0.009507,
-0.009626,
-0.009741,
-0.009854,
-0.009964,
-0.010071,
-0.010176,
-0.010278,
-0.010378,
-0.010475,
-0.010569,
-0.010661,
-0.010751,
-0.010837,
-0.010922,
-0.011003,
-0.011082,
-0.011159,
-0.011233,
-0.011305,
-0.011374,
-0.011441,
-0.011505,
-0.011567,
-0.011626,
-0.011683,
-0.011738,
-0.011790,
-0.011840,
-0.011887,
-0.011932,
-0.011975,
-0.012016,
-0.012054,
-0.012090,
-0.012124,
-0.012156,
-0.012185,
-0.012212,
-0.012237,
-0.012260,
-0.012281,
-0.012299,
-0.012316,
-0.012330,
-0.012342,
-0.012352,
-0.012361,
-0.012367,
-0.012371,
-0.012373,
-0.012374,
-0.012372,
-0.012368,
-0.012363,
-0.012356,
-0.012346,
-0.012335,
-0.012323,
-0.012308,
-0.012292,
-0.012274,
-0.012254,
-0.012232,
-0.012209,
-0.012184,
-0.012157,
-0.012129,
-0.012099,
-0.012068,
-0.012035,
-0.012001,
-0.011965,
-0.011927,
-0.011888,
-0.011848,
-0.011806,
-0.011763,
-0.011718,
-0.011672,
-0.011625,
-0.011576,
-0.011527,
-0.011475,
-0.011423,
-0.011369,
-0.011314,
-0.011258,
-0.011201,
-0.011143,
-0.011083,
-0.011022,
-0.010961,
-0.010898,
-0.010834,
-0.010769,
-0.010704,
-0.010637,
-0.010569,
-0.010501,
-0.010431,
-0.010361,
-0.010289,
-0.010217,
-0.010144,
-0.010070,
-0.009996,
-0.009921,
-0.009845,
-0.009768,
-0.009690,
-0.009612,
-0.009533,
-0.009454,
-0.009374,
-0.009293,
-0.009212,
-0.009130,
-0.009048,
-0.008965,
-0.008882,
-0.008798,
-0.008714,
-0.008629,
-0.008544,
-0.008459,
-0.008373,
-0.008287,
-0.008200,
-0.008113,
-0.008026,
-0.007938,
-0.007851,
-0.007763,
-0.007674,
-0.007586,
-0.007497,
-0.007408,
-0.007319,
-0.007230,
-0.007141,
-0.007051,
-0.006962,
-0.006872,
-0.006783,
-0.006693,
-0.006603,
-0.006514,
-0.006424,
-0.006334,
-0.006244,
-0.006155,
-0.006065,
-0.005976,
-0.005886,
-0.005797,
-0.005708,
-0.005619,
-0.005530,
-0.005441,
-0.005352,
-0.005264,
-0.005176,
-0.005088,
-0.005000,
-0.004912,
-0.004825,
-0.004738,
-0.004651,
-0.004565,
-0.004479,
-0.004393,
-0.004307,
-0.004222,
-0.004137,
-0.004053,
-0.003969,
-0.003885,
-0.003802,
-0.003719,
-0.003636,
-0.003554,
-0.003472,
-0.003391,
-0.003310,
-0.003230,
-0.003150,
-0.003071,
-0.002992,
-0.002913,
-0.002835,
-0.002758,
-0.002681,
-0.002604,
-0.002528,
-0.002453,
-0.002378,
-0.002304,
-0.002230,
-0.002157,
-0.002084,
-0.002012,
-0.001941,
-0.001870,
-0.001800,
-0.001730,
-0.001661,
-0.001593,
-0.001525,
-0.001458,
-0.001391,
-0.001325,
-0.001260,
-0.001195,
-0.001131,
-0.001068,
-0.001005,
-0.000943,
-0.000881,
-0.000821,
-0.000760,
-0.000701,
-0.000642,
-0.000584,
-0.000526,
-0.000470,
-0.000413,
-0.000358,
-0.000303,
-0.000249,
-0.000196,
-0.000143,
-0.000091,
-0.000039,
0.000011,
0.000061,
0.000111,
0.000159,
0.000207,
0.000254,
0.000301,
0.000347,
0.000392,
0.000437,
0.000480,
0.000523,
0.000566,
0.000608,
0.000649,
0.000689,
0.000729,
0.000768,
0.000806,
0.000844,
0.000881,
0.000917,
0.000953,
0.000988,
0.001022,
0.001056,
0.001089,
0.001121,
0.001153,
0.001184,
0.001214,
0.001244,
0.001273,
0.001302,
0.001329,
0.001356,
0.001383,
0.001409,
0.001434,
0.001459,
0.001483,
0.001506,
0.001529,
0.001551,
0.001573,
0.001594,
0.001614,
0.001634,
0.001653,
0.001671,
0.001689,
0.001707,
0.001724,
0.001740,
0.001756,
0.001771,
0.001785,
0.001799,
0.001813,
0.001826,
0.001838,
0.001850,
0.001862,
0.001872,
0.001883,
0.001893,
0.001902,
0.001911,
0.001919,
0.001927,
0.001934,
0.001941,
0.001947,
0.001953,
0.001959,
0.001964,
0.001968,
0.001972,
0.001976,
0.001979,
0.001982,
0.001984,
0.001986,
0.001988,
0.001989,
0.001990,
0.001990,
0.001990,
0.001989,
0.001988,
0.001987,
0.001986,
0.001984,
0.001981,
0.001979,
0.001976,
0.001972,
0.001968,
0.001964,
0.001960,
0.001955,
0.001950,
0.001945,
0.001939,
0.001933,
0.001927,
0.001921,
0.001914,
0.001907,
0.001900,
0.001892,
0.001884,
0.001876,
0.001868,
0.001859,
0.001850,
0.001841,
0.001832,
0.001822,
0.001813,
0.001803,
0.001792,
0.001782,
0.001772,
0.001761,
0.001750,
0.001739,
0.001727,
0.001716,
0.001704,
0.001693,
0.001681,
0.001669,
0.001656,
0.001644,
0.001631,
0.001619,
0.001606,
0.001593,
0.001580,
0.001567,
0.001554,
0.001540,
0.001527,
0.001514,
0.001500,
0.001486,
0.001472,
0.001459,
0.001445,
0.001431,
0.001417,
0.001402,
0.001388,
0.001374,
0.001360,
0.001345,
0.001331,
0.001317,
0.001302,
0.001288,
0.001273,
0.001259,
0.001244,
0.001230,
0.001215,
0.001200,
0.001186,
0.001171,
0.001157,
0.001142,
0.001128,
0.001113,
0.001098,
0.001084,
0.001069,
0.001055,
0.001041,
0.001026,
0.001012,
0.000997,
0.000983,
0.000969,
0.000955,
0.000940,
0.000926,
0.000912,
0.000898,
0.000884,
0.000870,
0.000856,
0.000843,
0.000829,
0.000815,
0.000802,
0.000788,
0.000775,
0.000761,
0.000748,
0.000735,
0.000722,
0.000709,
0.000696,
0.000683,
0.000670,
0.000657,
0.000645,
0.000632,
0.000620,
0.000608,
0.000595,
0.000583,
0.000571,
0.000559,
0.000547,
0.000536,
0.000524,
0.000512,
0.000501,
0.000490,
0.000479,
0.000467,
0.000456,
0.000446,
0.000435,
0.000424,
0.000414,
0.000403,
0.000393,
0.000383,
0.000373,
0.000363,
0.000353,
0.000343,
0.000333,
0.000324,
0.000315,
0.000305,
0.000296,
0.000287,
0.000278,
0.000269,
0.000261,
0.000252,
0.000244,
0.000235,
0.000227,
0.000219,
0.000211,
0.000203,
0.000196,
0.000188,
0.000181,
0.000173,
0.000166,
0.000159,
0.000152,
0.000145,
0.000138,
0.000131,
0.000125,
0.000118,
0.000112,
0.000106,
0.000100,
0.000094,
0.000088,
0.000082,
0.000077,
0.000071,
0.000066,
0.000060,
0.000055,
0.000050,
0.000045,
0.000040,
0.000035,
0.000031,
0.000026,
0.000022,
0.000017,
0.000013,
0.000009,
0.000005,
0.000001,
-0.000003,
-0.000007,
-0.000010,
-0.000014,
-0.000017,
-0.000021,
-0.000024,
-0.000027,
-0.000030,
-0.000033,
-0.000036,
-0.000039,
-0.000042,
-0.000044,
-0.000047,
-0.000049,
-0.000052,
-0.000054,
-0.000056,
-0.000059,
-0.000061,
-0.000063,
-0.000065,
-0.000066,
-0.000068,
-0.000070,
-0.000071,
-0.000073,
-0.000074,
-0.000076,
-0.000077,
-0.000078,
-0.000080,
-0.000081,
-0.000082,
-0.000083,
-0.000084,
-0.000085,
-0.000085,
-0.000086,
-0.000087,
-0.000087,
-0.000088,
-0.000089,
-0.000089,
-0.000089,
-0.000090,
-0.000090,
-0.000090,
-0.000091,
-0.000091,
-0.000091,
-0.000091,
-0.000091,
-0.000091,
-0.000091,
-0.000091,
-0.000091,
-0.000090,
-0.000090,
-0.000090,
-0.000090,
-0.000089,
-0.000089,
-0.000089,
-0.000088,
-0.000088,
-0.000087,
-0.000087,
-0.000086,
-0.000085,
-0.000085,
-0.000084,
-0.000084,
-0.000083,
-0.000082,
-0.000081,
-0.000081,
-0.000080,
-0.000079,
-0.000078,
-0.000077,
-0.000077,
-0.000076,
-0.000075,
-0.000074,
-0.000073,
-0.000072,
-0.000071,
-0.000070,
-0.000069,
-0.000068,
-0.000067,
-0.000066,
-0.000065,
-0.000064,
-0.000063,
-0.000062,
-0.000061,
-0.000060,
-0.000059,
-0.000058,
-0.000057,
-0.000056,
-0.000055,
-0.000054,
-0.000052,
-0.000051,
-0.000050,
-0.000049,
-0.000048,
-0.000047,
-0.000046
};

static const float SMALL_FILTER_FLOAT_IMPD[] /* Impulse response */ = {
-0.000020,
-0.000060,
-0.000100,
-0.000139,
-0.000179,
-0.000219,
-0.000259,
-0.000299,
-0.000338,
-0.000378,
-0.000418,
-0.000457,
-0.000497,
-0.000536,
-0.000576,
-0.000615,
-0.000655,
-0.000694,
-0.000733,
-0.000772,
-0.000812,
-0.000851,
-0.000890,
-0.000929,
-0.000967,
-0.001006,
-0.001045,
-0.001083,
-0.001122,
-0.001160,
-0.001199,
-0.001237,
-0.001275,
-0.001313,
-0.001351,
-0.001388,
-0.001426,
-0.001463,
-0.001501,
-0.001538,
-0.001575,
-0.001612,
-0.001649,
-0.001685,
-0.001722,
-0.001758,
-0.001794,
-0.001830,
-0.001866,
-0.001902,
-0.001938,
-0.001973,
-0.002008,
-0.002043,
-0.002078,
-0.002113,
-0.002147,
-0.002182,
-0.002216,
-0.002250,
-0.002284,
-0.002317,
-0.002350,
-0.002384,
-0.002417,
-0.002449,
-0.002482,
-0.002514,
-0.002546,
-0.002578,
-0.002610,
-0.002641,
-0.002672,
-0.002703,
-0.002734,
-0.002765,
-0.002795,
-0.002825,
-0.002855,
-0.002884,
-0.002913,
-0.002942,
-0.002971,
-0.003000,
-0.003028,
-0.003056,
-0.003084,
-0.003111,
-0.003139,
-0.003166,
-0.003192,
-0.003219,
-0.003245,
-0.003271,
-0.003296,
-0.003322,
-0.003347,
-0.003372,
-0.003396,
-0.003420,
-0.003444,
-0.003468,
-0.003491,
-0.003514,
-0.003537,
-0.003559,
-0.003582,
-0.003604,
-0.003625,
-0.003646,
-0.003667,
-0.003688,
-0.003708,
-0.003728,
-0.003748,
-0.003767,
-0.003787,
-0.003805,
-0.003824,
-0.003842,
-0.003860,
-0.003877,
-0.003895,
-0.003912,
-0.003928,
-0.003944,
-0.003960,
-0.003976,
-0.003991,
-0.004006,
-0.004021,
-0.004035,
-0.004049,
-0.004063,
-0.004076,
-0.004089,
-0.004102,
-0.004114,
-0.004126,
-0.004138,
-0.004149,
-0.004161,
-0.004171,
-0.004182,
-0.004192,
-0.004201,
-0.004211,
-0.004220,
-0.004229,
-0.004237,
-0.004245,
-0.004253,
-0.004260,
-0.004267,
-0.004274,
-0.004280,
-0.004286,
-0.004292,
-0.004297,
-0.004303,
-0.004307,
-0.004312,
-0.004316,
-0.004320,
-0.004323,
-0.004326,
-0.004329,
-0.004331,
-0.004333,
-0.004335,
-0.004337,
-0.004338,
-0.004339,
-0.004339,
-0.004339,
-0.004339,
-0.004338,
-0.004338,
-0.004337,
-0.004335,
-0.004333,
-0.004331,
-0.004329,
-0.004326,
-0.004323,
-0.004320,
-0.004316,
-0.004312,
-0.004308,
-0.004303,
-0.004298,
-0.004293,
-0.004288,
-0.004282,
-0.004276,
-0.004269,
-0.004263,
-0.004256,
-0.004248,
-0.004241,
-0.004233,
-0.004225,
-0.004216,
-0.004207,
-0.004198,
-0.004189,
-0.004179,
-0.004170,
-0.004159,
-0.004149,
-0.004138,
-0.004127,
-0.004116,
-0.004104,
-0.004092,
-0.004080,
-0.004068,
-0.004055,
-0.004043,
-0.004029,
-0.004016,
-0.004002,
-0.003988,
-0.003974,
-0.003960,
-0.003945,
-0.003930,
-0.003915,
-0.003900,
-0.003884,
-0.003868,
-0.003852,
-0.003836,
-0.003819,
-0.003803,
-0.003786,
-0.003768,
-0.003751,
-0.003733,
-0.003716,
-0.003697,
-0.003679,
-0.003661,
-0.003642,
-0.003623,
-0.003604,
-0.003585,
-0.003565,
-0.003545,
-0.003526,
-0.003506,
-0.003485,
-0.003465,
-0.003444,
-0.003423,
-0.003402,
-0.003381,
-0.003360,
-0.003339,
-0.003317,
-0.003295,
-0.003273,
-0.003251,
-0.003229,
-0.003206,
-0.003184,
-0.003161,
-0.003138,
-0.003115,
-0.003092,
-0.003069,
-0.003045,
-0.003022,
-0.002998,
-0.002974,
-0.002951,
-0.002927,
-0.002902,
-0.002878,
-0.002854,
-0.002829,
-0.002805,
-0.002780,
-0.002755,
-0.002731,
-0.002706,
-0.002681,
-0.002655,
-0.002630,
-0.002605,
-0.002580,
-0.002554,
-0.002529,
-0.002503,
-0.002477,
-0.002452,
-0.002426,
-0.002400,
-0.002374,
-0.002348,
-0.002322,
-0.002296,
-0.002270,
-0.002244,
-0.002218,
-0.002191,
-0.002165,
-0.002139,
-0.002113,
-0.002086,
-0.002060,
-0.002034,
-0.002007,
-0.001981,
-0.001954,
-0.001928,
-0.001901,
-0.001875,
-0.001849,
-0.001822,
-0.001796,
-0.001769,
-0.001743,
-0.001716,
-0.001690,
-0.001664,
-0.001637,
-0.001611,
-0.001585,
-0.001558,
-0.001532,
-0.001506,
-0.001480,
-0.001453,
-0.001427,
-0.001401,
-0.001375,
-0.001349,
-0.001323,
-0.001297,
-0.001271,
-0.001246,
-0.001220,
-0.001194,
-0.001169,
-0.001143,
-0.001118,
-0.001092,
-0.001067,
-0.001042,
-0.001016,
-0.000991,
-0.000966,
-0.000941,
-0.000916,
-0.000892,
-0.000867,
-0.000842,
-0.000818,
-0.000794,
-0.000769,
-0.000745,
-0.000721,
-0.000697,
-0.000673,
-0.000649,
-0.000626,
-0.000602,
-0.000579,
-0.000555,
-0.000532,
-0.000509,
-0.000486,
-0.000463,
-0.000440,
-0.000418,
-0.000395,
-0.000373,
-0.000351,
-0.000329,
-0.000307,
-0.000285,
-0.000263,
-0.000242,
-0.000220,
-0.000199,
-0.000178,
-0.000157,
-0.000136,
-0.000115,
-0.000095,
-0.000074,
-0.000054,
-0.000034,
-0.000014,
0.000006,
0.000025,
0.000045,
0.000064,
0.000083,
0.000102,
0.000121,
0.000140,
0.000158,
0.000177,
0.000195,
0.000213,
0.000231,
0.000248,
0.000266,
0.000283,
0.000300,
0.000317,
0.000334,
0.000351,
0.000367,
0.000383,
0.000399,
0.000415,
0.000431,
0.000447,
0.000462,
0.000477,
0.000492,
0.000507,
0.000522,
0.000536,
0.000551,
0.000565,
0.000579,
0.000592,
0.000606,
0.000619,
0.000633,
0.000646,
0.000658,
0.000671,
0.000684,
0.000696,
0.000708,
0.000720,
0.000731,
0.000743,
0.000754,
0.000765,
0.000776,
0.000787,
0.000798,
0.000808,
0.000818,
0.000828,
0.000838,
0.000848,
0.000857,
0.000867,
0.000876,
0.000885,
0.000893,
0.000902,
0.000910,
0.000918,
0.000926,
0.000934,
0.000942,
0.000949,
0.000956,
0.000963,
0.000970,
0.000977,
0.000983,
0.000990,
0.000996,
0.001002,
0.001008,
0.001013,
0.001019,
0.001024,
0.001029,
0.001034,
0.001039,
0.001043,
0.001047,
0.001052,
0.001056,
0.001059,
0.001063,
0.001067,
0.001070,
0.001073,
0.001076,
0.001079,
0.001082,
0.001084,
0.001086,
0.001088,
0.001090,
0.001092,
0.001094,
0.001095,
0.001097,
0.001098,
0.001099,
0.001100,
0.001101,
0.001101,
0.001101,
0.001102,
0.001102,
0.001102,
0.001102,
0.001101,
0.001101,
0.001100,
0.001099,
0.001098,
0.001097,
0.001096,
0.001095,
0.001093,
0.001091,
0.001090,
0.001088,
0.001086,
0.001083,
0.001081,
0.001079,
0.001076,
0.001073,
0.001070,
0.001068,
0.001064,
0.001061,
0.001058,
0.001054,
0.001051,
0.001047,
0.001043,
0.001039,
0.001035,
0.001031,
0.001027,
0.001023,
0.001018,
0.001014,
0.001009,
0.001004,
0.000999,
0.000994,
0.000989,
0.000984,
0.000979,
0.000973,
0.000968,
0.000962,
0.000957,
0.000951,
0.000945,
0.000939,
0.000933,
0.000927,
0.000921,
0.000914,
0.000908,
0.000902,
0.000895,
0.000889,
0.000882,
0.000875,
0.000869,
0.000862,
0.000855,
0.000848,
0.000841,
0.000834,
0.000826,
0.000819,
0.000812,
0.000805,
0.000797,
0.000790,
0.000782,
0.000775,
0.000767,
0.000759,
0.000752,
0.000744,
0.000736,
0.000728,
0.000720,
0.000712,
0.000704,
0.000696,
0.000688,
0.000680,
0.000672,
0.000664,
0.000656,
0.000648,
0.000639,
0.000631,
0.000623,
0.000615,
0.000606,
0.000598,
0.000590,
0.000581,
0.000573,
0.000564,
0.000556,
0.000547,
0.000539,
0.000531,
0.000522,
0.000514,
0.000505,
0.000497,
0.000488,
0.000480,
0.000471,
0.000463,
0.000454,
0.000446,
0.000437,
0.000429,
0.000420,
0.000412,
0.000403,
0.000395,
0.000386,
0.000378,
0.000369,
0.000361,
0.000353,
0.000344,
0.000336,
0.000327,
0.000319,
0.000311,
0.000303,
0.000294,
0.000286,
0.000278,
0.000270,
0.000261,
0.000253,
0.000245,
0.000237,
0.000229,
0.000221,
0.000213,
0.000205,
0.000197,
0.000189,
0.000181,
0.000174,
0.000166,
0.000158,
0.000150,
0.000143,
0.000135,
0.000128,
0.000120,
0.000113,
0.000105,
0.000098,
0.000090,
0.000083,
0.000076,
0.000069,
0.000061,
0.000054,
0.000047,
0.000040,
0.000033,
0.000026,
0.000019,
0.000013,
0.000006,
-0.000001,
-0.000008,
-0.000014,
-0.000021,
-0.000027,
-0.000034,
-0.000040,
-0.000046,
-0.000053,
-0.000059,
-0.000065,
-0.000071,
-0.000077,
-0.000083,
-0.000089,
-0.000095,
-0.000100,
-0.000106,
-0.000112,
-0.000117,
-0.000123,
-0.000128,
-0.000134,
-0.000139,
-0.000144,
-0.000150,
-0.000155,
-0.000160,
-0.000165,
-0.000170,
-0.000175,
-0.000180,
-0.000184,
-0.000189,
-0.000194,
-0.000198,
-0.000203,
-0.000207,
-0.000211,
-0.000216,
-0.000220,
-0.000224,
-0.000228,
-0.000232,
-0.000236,
-0.000240,
-0.000244,
-0.000248,
-0.000251,
-0.000255,
-0.000258,
-0.000262,
-0.000265,
-0.000269,
-0.000272,
-0.000275,
-0.000278,
-0.000281,
-0.000284,
-0.000287,
-0.000290,
-0.000293,
-0.000296,
-0.000298,
-0.000301,
-0.000303,
-0.000306,
-0.000308,
-0.000311,
-0.000313,
-0.000315,
-0.000317,
-0.000319,
-0.000321,
-0.000323,
-0.000325,
-0.000327,
-0.000329,
-0.000330,
-0.000332,
-0.000334,
-0.000335,
-0.000337,
-0.000338,
-0.000339,
-0.000340,
-0.000342,
-0.000343,
-0.000344,
-0.000345,
-0.000346,
-0.000347,
-0.000347,
-0.000348,
-0.000349,
-0.000350,
-0.000350,
-0.000351,
-0.000351,
-0.000352,
-0.000352,
-0.000352,
-0.000352,
-0.000353,
-0.000353,
-0.000353,
-0.000353,
-0.000353,
-0.000353,
-0.000353,
-0.000353,
-0.000352,
-0.000352,
-0.000352,
-0.000351,
-0.000351,
-0.000350,
-0.000350,
-0.000349,
-0.000349,
-0.000348,
-0.000347,
-0.000346,
-0.000346,
-0.000345,
-0.000344,
-0.000343,
-0.000342,
-0.000341,
-0.000340,
-0.000339,
-0.000338,
-0.000336,
-0.000335,
-0.000334,
-0.000333,
-0.000331,
-0.000330,
-0.000328,
-0.000327,
-0.000325,
-0.000324,
-0.000322,
-0.000321,
-0.000319,
-0.000317,
-0.000316,
-0.000314,
-0.000312,
-0.000310,
-0.000308,
-0.000306,
-0.000305,
-0.000303,
-0.000301,
-0.000299,
-0.000297,
-0.000295,
-0.000293,
-0.000290,
-0.000288,
-0.000286,
-0.000284,
-0.000282,
-0.000280,
-0.000277,
-0.000275,
-0.000273,
-0.000270,
-0.000268,
-0.000266,
-0.000263,
-0.000261,
-0.000259,
-0.000256,
-0.000254,
-0.000251,
-0.000249,
-0.000246,
-0.000244,
-0.000241,
-0.000239,
-0.000236,
-0.000234,
-0.000231,
-0.000228,
-0.000226,
-0.000223,
-0.000221,
-0.000218,
-0.000215,
-0.000213,
-0.000210,
-0.000207,
-0.000205,
-0.000202,
-0.000199,
-0.000197,
-0.000194,
-0.000191,
-0.000189,
-0.000186,
-0.000183,
-0.000180,
-0.000178,
-0.000175,
-0.000172,
-0.000169,
-0.000167,
-0.000164,
-0.000161,
-0.000159,
-0.000156,
-0.000153,
-0.000150,
-0.000148,
-0.000145,
-0.000142,
-0.000140,
-0.000137,
-0.000134,
-0.000131,
-0.000129,
-0.000126,
-0.000123,
-0.000121,
-0.000118,
-0.000115,
-0.000113,
-0.000110,
-0.000107,
-0.000105,
-0.000102,
-0.000100,
-0.000097,
-0.000094,
-0.000092,
-0.000089,
-0.000087,
-0.000084,
-0.000082,
-0.000079,
-0.000077,
-0.000074,
-0.000072,
-0.000069,
-0.000067,
-0.000064,
-0.000062,
-0.000059,
-0.000057,
-0.000055,
-0.000052,
-0.000050,
-0.000048,
-0.000045,
-0.000043,
-0.000041,
-0.000038,
-0.000036,
-0.000034,
-0.000032,
-0.000029,
-0.000027,
-0.000025,
-0.000023,
-0.000021,
-0.000019,
-0.000016,
-0.000014,
-0.000012,
-0.000010,
-0.000008,
-0.000006,
-0.000004,
-0.000002,
-0.000000,
0.000002,
0.000004,
0.000005,
0.000007,
0.000009,
0.000011,
0.000013,
0.000015,
0.000016,
0.000018,
0.000020,
0.000022,
0.000023,
0.000025,
0.000027,
0.000028,
0.000030,
0.000031,
0.000033,
0.000034,
0.000036,
0.000037,
0.000039,
0.000040,
0.000042,
0.000043,
0.000045,
0.000046,
0.000047,
0.000049,
0.000050,
0.000051,
0.000052,
0.000054,
0.000055,
0.000056,
0.000057,
0.000058,
0.000060,
0.000061,
0.000062,
0.000063,
0.000064,
0.000065,
0.000066,
0.000067,
0.000068,
0.000069,
0.000070,
0.000070,
0.000071,
0.000072,
0.000073,
0.000074,
0.000075,
0.000075,
0.000076,
0.000077,
0.000077,
0.000078,
0.000079,
0.000079,
0.000080,
0.000081,
0.000081,
0.000082,
0.000082,
0.000083,
0.000083,
0.000084,
0.000084,
0.000085,
0.000085,
0.000085,
0.000086,
0.000086,
0.000087,
0.000087,
0.000087,
0.000087,
0.000088,
0.000088,
0.000088,
0.000088,
0.000089,
0.000089,
0.000089,
0.000089,
0.000089,
0.000089,
0.000090,
0.000090,
0.000090,
0.000090,
0.000090,
0.000090,
0.000090,
0.000090,
0.000090,
0.000090,
0.000090,
0.000090,
0.000089,
0.000089,
0.000089,
0.000089,
0.000089,
0.000089,
0.000089,
0.000088,
0.000088,
0.000088,
0.000088,
0.000088,
0.000087,
0.000087,
0.000087,
0.000086,
0.000086,
0.000086,
0.000086,
0.000085,
0.000085,
0.000084,
0.000084,
0.000084,
0.000083,
0.000083,
0.000083,
0.000082,
0.000082,
0.000081,
0.000081,
0.000080,
0.000080,
0.000079,
0.000079,
0.000078,
0.000078,
0.000077,
0.000077,
0.000076,
0.000076,
0.000075,
0.000075,
0.000074,
0.000074,
0.000073,
0.000073,
0.000072,
0.000071,
0.000071,
0.000070,
0.000070,
0.000069,
0.000068,
0.000068,
0.000067,
0.000067,
0.000066,
0.000065,
0.000065,
0.000064,
0.000063,
0.000063,
0.000062,
0.000061,
0.000061,
0.000060,
0.000059,
0.000059,
0.000058,
0.000057,
0.000057,
0.000056,
0.000055,
0.000055,
0.000054,
0.000053,
0.000053,
0.000052,
0.000051,
0.000051,
0.000050,
0.000049,
0.000049,
0.000048,
0.000047,
0.000047,
0.000046,
0.000045,
0.000045,
0.000044,
0.000043,
0.000042,
0.000042,
0.000041,
0.000040,
0.000040,
0.000039,
0.000038,
0.000038,
0.000037,
0.000036,
0.000036,
0.000035,
0.000034,
0.000034,
0.000033,
0.000032,
0.000032,
0.000031,
0.000030,
0.000030,
0.000029,
0.000028,
0.000028,
0.000027,
0.000027,
0.000026,
0.000025,
0.000025,
0.000024,
0.000023,
0.000023,
0.000022,
0.000022,
0.000021,
0.000020,
0.000020,
0.000019,
0.000019,
0.000018,
0.000017,
0.000017,
0.000016,
0.000016,
0.000015,
0.000015,
0.000014,
0.000014,
0.000013,
0.000012,
0.000012,
0.000011,
0.000011,
0.000010,
0.000010,
0.000009,
0.000009,
0.000008,
0.000008,
0.000007,
0.000007,
0.000006,
0.000006,
0.000005,
0.000005,
0.000005,
0.000004,
0.000004,
0.000003,
0.000003,
0.000002,
0.000002,
0.000002,
0.000001,
0.000001,
0.000000,
-0.000000,
-0.000000,
-0.000001,
-0.000001,
-0.000002,
-0.000002,
-0.000002,
-0.000003,
-0.000003,
-0.000003,
-0.000004,
-0.000004,
-0.000004,
-0.000005,
-0.000005,
-0.000005,
-0.000006,
-0.000006,
-0.000006,
-0.000007,
-0.000007,
-0.000007,
-0.000007,
-0.000008,
-0.000008,
-0.000008,
-0.000008,
-0.000009,
-0.000009,
-0.000009,
-0.000009,
-0.000010,
-0.000010,
-0.000010,
-0.000010,
-0.000010,
-0.000011,
-0.000011,
-0.000011,
-0.000011,
-0.000011,
-0.000011,
-0.000012,
-0.000012,
-0.000012,
-0.000012,
-0.000012,
-0.000012,
-0.000013,
-0.000013,
-0.000013,
-0.000013,
-0.000013,
-0.000013,
-0.000013,
-0.000013,
-0.000013,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000015,
-0.000015,
-0.000015,
-0.000015,
-0.000015,
-0.000015,
-0.000015,
-0.000015,
-0.000015,
-0.000015,
-0.000015,
-0.000015,
-0.000015,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000014,
-0.000013,
-0.000013,
-0.000013,
-0.000013,
-0.000013,
-0.000013,
-0.000013,
-0.000013,
-0.000013,
-0.000013,
-0.000013,
-0.000013,
-0.000012,
-0.000012,
-0.000012,
-0.000012,
-0.000012,
-0.000012,
-0.000012,
-0.000012,
-0.000012,
-0.000012,
-0.000011,
-0.000011,
-0.000011,
-0.000011,
-0.000011,
-0.000011,
-0.000011,
-0.000011,
-0.000011,
-0.000010,
-0.000010,
-0.000010,
-0.000010,
-0.000010,
-0.000010,
-0.000010,
-0.000010,
-0.000010,
-0.000009,
-0.000009,
-0.000009,
-0.000009,
-0.000009,
-0.000009,
-0.000009,
-0.000009,
-0.000008,
-0.000008,
-0.000008,
-0.000008,
-0.000008,
-0.000008,
-0.000008,
-0.000008,
-0.000007,
-0.000007,
-0.000007,
-0.000007,
-0.000007,
-0.000007,
-0.000007,
-0.000007,
-0.000007,
-0.000006,
-0.000006,
-0.000006,
-0.000006,
-0.000006,
-0.000006,
-0.000006,
-0.000006,
-0.000006,
-0.000005,
-0.000005,
-0.000005,
-0.000005,
-0.000005,
-0.000005,
-0.000005,
-0.000005,
-0.000005,
-0.000004,
-0.000004,
-0.000004,
-0.000004,
-0.000004,
-0.000004,
-0.000004,
-0.000004,
-0.000004,
-0.000004,
-0.000003,
-0.000003,
-0.000003,
-0.000003,
-0.000003,
-0.000003,
-0.000003,
-0.000003,
-0.000003,
-0.000003,
-0.000003,
-0.000002,
-0.000002,
-0.000002,
-0.000002,
-0.000002,
-0.000002,
-0.000002,
-0.000002,
-0.000002,
-0.000002,
-0.000002,
-0.000002,
-0.000002,
-0.000001,
-0.000001,
-0.000001,
-0.000001,
-0.000001,
-0.000001,
-0.000001,
-0.000001,
-0.000001,
-0.000001,
-0.000001,
-0.000001,
-0.000001,
-0.000001,
-0.000001,
-0.000001,
-0.000000,
-0.000000,
-0.000000,
-0.000000,
-0.000000,
-0.000000,
-0.000000,
-0.000000,
-0.000000,
-0.000000,
0.000000,
0.000000,
0.000000,
0.000000,
0.000000,
0.000000,
0.000000,
0.000000,
0.000000,
0.000000,
0.000000,
0.000000,
0.000000,
0.000000,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001,
0.000001
};
