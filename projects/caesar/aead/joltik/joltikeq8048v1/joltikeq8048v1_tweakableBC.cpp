/*
 * Joltik=-80-48 Reference C Implementation
 *
 * Copyright 2014:
 *     Jeremy Jean <JJean@ntu.edu.sg>
 *     Ivica Nikolic <INikolic@ntu.edu.sg>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// CHANGE namespace moved due to includes
namespace Joltikeq8048v1_raw {

#define GETU64(pt) ((((uint64_t)(pt)[0])<<56ULL)^(((uint64_t)(pt)[1])<<48ULL)^(((uint64_t)(pt)[2])<<40ULL)^(((uint64_t)(pt)[3])<<32ULL)^(((uint64_t)(pt)[4])<<24ULL)^(((uint64_t)(pt)[5])<<16ULL)^(((uint64_t)(pt)[6])<<8ULL)^((uint64_t)(pt)[7]))

#define PUTU64(ct, st) do {             \
    (ct)[0] = (uint8_t)((st) >> 56ULL); \
    (ct)[1] = (uint8_t)((st) >> 48ULL); \
    (ct)[2] = (uint8_t)((st) >> 40ULL); \
    (ct)[3] = (uint8_t)((st) >> 32ULL); \
    (ct)[4] = (uint8_t)((st) >> 24ULL); \
    (ct)[5] = (uint8_t)((st) >> 16ULL); \
    (ct)[6] = (uint8_t)((st) >>  8ULL); \
    (ct)[7] = (uint8_t)((st)         ); \
    } while(0)

static const uint32_t TeH[256] = {
    0x33dd, 0xd968, 0x4616, 0x6feb, 0x2e32, 0x855e, 0xed7a, 0xc487,
    0xaca3, 0x07cf, 0x1a20, 0x7204, 0x5bf9, 0xb14c, 0x98b1, 0xf095,
    0x9d86, 0x7733, 0xe84d, 0xc1b0, 0x8069, 0x2b05, 0x4321, 0x6adc,
    0x02f8, 0xa994, 0xb47b, 0xdc5f, 0xf5a2, 0x1f17, 0x36ea, 0x5ece,
    0x6461, 0x8ed4, 0x11aa, 0x3857, 0x798e, 0xd2e2, 0xbac6, 0x933b,
    0xfb1f, 0x5073, 0x4d9c, 0x25b8, 0x0c45, 0xe6f0, 0xcf0d, 0xa729,
    0xf6be, 0x1c0b, 0x8375, 0xaa88, 0xeb51, 0x403d, 0x2819, 0x01e4,
    0x69c0, 0xc2ac, 0xdf43, 0xb767, 0x9e9a, 0x742f, 0x5dd2, 0x35f6,
    0xe223, 0x0896, 0x97e8, 0xbe15, 0xffcc, 0x54a0, 0x3c84, 0x1579,
    0x7d5d, 0xd631, 0xcbde, 0xa3fa, 0x8a07, 0x60b2, 0x494f, 0x216b,
    0x58e5, 0xb250, 0x2d2e, 0x04d3, 0x450a, 0xee66, 0x8642, 0xafbf,
    0xc79b, 0x6cf7, 0x7118, 0x193c, 0x30c1, 0xda74, 0xf389, 0x9bad,
    0xdea7, 0x3412, 0xab6c, 0x8291, 0xc348, 0x6824, 0x0000, 0x29fd,
    0x41d9, 0xeab5, 0xf75a, 0x9f7e, 0xb683, 0x5c36, 0x75cb, 0x1def,
    0x4c78, 0xa6cd, 0x39b3, 0x104e, 0x5197, 0xfafb, 0x92df, 0xbb22,
    0xd306, 0x786a, 0x6585, 0x0da1, 0x245c, 0xcee9, 0xe714, 0x8f30,
    0xca3a, 0x208f, 0xbff1, 0x960c, 0xd7d5, 0x7cb9, 0x149d, 0x3d60,
    0x5544, 0xfe28, 0xe3c7, 0x8be3, 0xa21e, 0x48ab, 0x6156, 0x0972,
    0x70fc, 0x9a49, 0x0537, 0x2cca, 0x6d13, 0xc67f, 0xae5b, 0x87a6,
    0xef82, 0x44ee, 0x5901, 0x3125, 0x18d8, 0xf26d, 0xdb90, 0xb3b4,
    0xa102, 0x4bb7, 0xd4c9, 0xfd34, 0xbced, 0x1781, 0x7fa5, 0x5658,
    0x3e7c, 0x9510, 0x88ff, 0xe0db, 0xc926, 0x2393, 0x0a6e, 0x624a,
    0x2740, 0xcdf5, 0x528b, 0x7b76, 0x3aaf, 0x91c3, 0xf9e7, 0xd01a,
    0xb83e, 0x1352, 0x0ebd, 0x6699, 0x4f64, 0xa5d1, 0x8c2c, 0xe408,
    0xb59f, 0x5f2a, 0xc054, 0xe9a9, 0xa870, 0x031c, 0x6b38, 0x42c5,
    0x2ae1, 0x818d, 0x9c62, 0xf446, 0xddbb, 0x370e, 0x1ef3, 0x76d7,
    0x1bc4, 0xf171, 0x6e0f, 0x47f2, 0x062b, 0xad47, 0xc563, 0xec9e,
    0x84ba, 0x2fd6, 0x3239, 0x5a1d, 0x73e0, 0x9955, 0xb0a8, 0xd88c,
    0x891b, 0x63ae, 0xfcd0, 0xd52d, 0x94f4, 0x3f98, 0x57bc, 0x7e41,
    0x1665, 0xbd09, 0xa0e6, 0xc8c2, 0xe13f, 0x0b8a, 0x2277, 0x4a53,
    0x0f59, 0xe5ec, 0x7a92, 0x536f, 0x12b6, 0xb9da, 0xd1fe, 0xf803,
    0x9027, 0x3b4b, 0x26a4, 0x4e80, 0x677d, 0x8dc8, 0xa435, 0xcc11,
};
static const uint32_t TeL[256] = {
    0xdd33, 0x68d9, 0x1646, 0xeb6f, 0x322e, 0x5e85, 0x7aed, 0x87c4,
    0xa3ac, 0xcf07, 0x201a, 0x0472, 0xf95b, 0x4cb1, 0xb198, 0x95f0,
    0x869d, 0x3377, 0x4de8, 0xb0c1, 0x6980, 0x052b, 0x2143, 0xdc6a,
    0xf802, 0x94a9, 0x7bb4, 0x5fdc, 0xa2f5, 0x171f, 0xea36, 0xce5e,
    0x6164, 0xd48e, 0xaa11, 0x5738, 0x8e79, 0xe2d2, 0xc6ba, 0x3b93,
    0x1ffb, 0x7350, 0x9c4d, 0xb825, 0x450c, 0xf0e6, 0x0dcf, 0x29a7,
    0xbef6, 0x0b1c, 0x7583, 0x88aa, 0x51eb, 0x3d40, 0x1928, 0xe401,
    0xc069, 0xacc2, 0x43df, 0x67b7, 0x9a9e, 0x2f74, 0xd25d, 0xf635,
    0x23e2, 0x9608, 0xe897, 0x15be, 0xccff, 0xa054, 0x843c, 0x7915,
    0x5d7d, 0x31d6, 0xdecb, 0xfaa3, 0x078a, 0xb260, 0x4f49, 0x6b21,
    0xe558, 0x50b2, 0x2e2d, 0xd304, 0x0a45, 0x66ee, 0x4286, 0xbfaf,
    0x9bc7, 0xf76c, 0x1871, 0x3c19, 0xc130, 0x74da, 0x89f3, 0xad9b,
    0xa7de, 0x1234, 0x6cab, 0x9182, 0x48c3, 0x2468, 0x0000, 0xfd29,
    0xd941, 0xb5ea, 0x5af7, 0x7e9f, 0x83b6, 0x365c, 0xcb75, 0xef1d,
    0x784c, 0xcda6, 0xb339, 0x4e10, 0x9751, 0xfbfa, 0xdf92, 0x22bb,
    0x06d3, 0x6a78, 0x8565, 0xa10d, 0x5c24, 0xe9ce, 0x14e7, 0x308f,
    0x3aca, 0x8f20, 0xf1bf, 0x0c96, 0xd5d7, 0xb97c, 0x9d14, 0x603d,
    0x4455, 0x28fe, 0xc7e3, 0xe38b, 0x1ea2, 0xab48, 0x5661, 0x7209,
    0xfc70, 0x499a, 0x3705, 0xca2c, 0x136d, 0x7fc6, 0x5bae, 0xa687,
    0x82ef, 0xee44, 0x0159, 0x2531, 0xd818, 0x6df2, 0x90db, 0xb4b3,
    0x02a1, 0xb74b, 0xc9d4, 0x34fd, 0xedbc, 0x8117, 0xa57f, 0x5856,
    0x7c3e, 0x1095, 0xff88, 0xdbe0, 0x26c9, 0x9323, 0x6e0a, 0x4a62,
    0x4027, 0xf5cd, 0x8b52, 0x767b, 0xaf3a, 0xc391, 0xe7f9, 0x1ad0,
    0x3eb8, 0x5213, 0xbd0e, 0x9966, 0x644f, 0xd1a5, 0x2c8c, 0x08e4,
    0x9fb5, 0x2a5f, 0x54c0, 0xa9e9, 0x70a8, 0x1c03, 0x386b, 0xc542,
    0xe12a, 0x8d81, 0x629c, 0x46f4, 0xbbdd, 0x0e37, 0xf31e, 0xd776,
    0xc41b, 0x71f1, 0x0f6e, 0xf247, 0x2b06, 0x47ad, 0x63c5, 0x9eec,
    0xba84, 0xd62f, 0x3932, 0x1d5a, 0xe073, 0x5599, 0xa8b0, 0x8cd8,
    0x1b89, 0xae63, 0xd0fc, 0x2dd5, 0xf494, 0x983f, 0xbc57, 0x417e,
    0x6516, 0x09bd, 0xe6a0, 0xc2c8, 0x3fe1, 0x8a0b, 0x7722, 0x534a,
    0x590f, 0xece5, 0x927a, 0x6f53, 0xb612, 0xdab9, 0xfed1, 0x03f8,
    0x2790, 0x4b3b, 0xa426, 0x804e, 0x7d67, 0xc88d, 0x35a4, 0x11cc,
};
static const uint32_t TdH[256] = {
    0xddbb, 0x031c, 0xa870, 0x5f2a, 0x2ae1, 0xb59f, 0x370e, 0x818d,
    0x1ef3, 0x9c62, 0x42c5, 0xe9a9, 0x76d7, 0xf446, 0x6b38, 0xc054,
    0x30c1, 0xee66, 0x450a, 0xb250, 0xc79b, 0x58e5, 0xda74, 0x6cf7,
    0xf389, 0x7118, 0xafbf, 0x04d3, 0x9bad, 0x193c, 0x8642, 0x2d2e,
    0x8a07, 0x54a0, 0xffcc, 0x0896, 0x7d5d, 0xe223, 0x60b2, 0xd631,
    0x494f, 0xcbde, 0x1579, 0xbe15, 0x216b, 0xa3fa, 0x3c84, 0x97e8,
    0xf5a2, 0x2b05, 0x8069, 0x7733, 0x02f8, 0x9d86, 0x1f17, 0xa994,
    0x36ea, 0xb47b, 0x6adc, 0xc1b0, 0x5ece, 0xdc5f, 0x4321, 0xe84d,
    0xa21e, 0x7cb9, 0xd7d5, 0x208f, 0x5544, 0xca3a, 0x48ab, 0xfe28,
    0x6156, 0xe3c7, 0x3d60, 0x960c, 0x0972, 0x8be3, 0x149d, 0xbff1,
    0x5bf9, 0x855e, 0x2e32, 0xd968, 0xaca3, 0x33dd, 0xb14c, 0x07cf,
    0x98b1, 0x1a20, 0xc487, 0x6feb, 0xf095, 0x7204, 0xed7a, 0x4616,
    0x73e0, 0xad47, 0x062b, 0xf171, 0x84ba, 0x1bc4, 0x9955, 0x2fd6,
    0xb0a8, 0x3239, 0xec9e, 0x47f2, 0xd88c, 0x5a1d, 0xc563, 0x6e0f,
    0x18d8, 0xc67f, 0x6d13, 0x9a49, 0xef82, 0x70fc, 0xf26d, 0x44ee,
    0xdb90, 0x5901, 0x87a6, 0x2cca, 0xb3b4, 0x3125, 0xae5b, 0x0537,
    0xe13f, 0x3f98, 0x94f4, 0x63ae, 0x1665, 0x891b, 0x0b8a, 0xbd09,
    0x2277, 0xa0e6, 0x7e41, 0xd52d, 0x4a53, 0xc8c2, 0x57bc, 0xfcd0,
    0xc926, 0x1781, 0xbced, 0x4bb7, 0x3e7c, 0xa102, 0x2393, 0x9510,
    0x0a6e, 0x88ff, 0x5658, 0xfd34, 0x624a, 0xe0db, 0x7fa5, 0xd4c9,
    0x245c, 0xfafb, 0x5197, 0xa6cd, 0xd306, 0x4c78, 0xcee9, 0x786a,
    0xe714, 0x6585, 0xbb22, 0x104e, 0x8f30, 0x0da1, 0x92df, 0x39b3,
    0x9e9a, 0x403d, 0xeb51, 0x1c0b, 0x69c0, 0xf6be, 0x742f, 0xc2ac,
    0x5dd2, 0xdf43, 0x01e4, 0xaa88, 0x35f6, 0xb767, 0x2819, 0x8375,
    0x677d, 0xb9da, 0x12b6, 0xe5ec, 0x9027, 0x0f59, 0x8dc8, 0x3b4b,
    0xa435, 0x26a4, 0xf803, 0x536f, 0xcc11, 0x4e80, 0xd1fe, 0x7a92,
    0x4f64, 0x91c3, 0x3aaf, 0xcdf5, 0xb83e, 0x2740, 0xa5d1, 0x1352,
    0x8c2c, 0x0ebd, 0xd01a, 0x7b76, 0xe408, 0x6699, 0xf9e7, 0x528b,
    0xb683, 0x6824, 0xc348, 0x3412, 0x41d9, 0xdea7, 0x5c36, 0xeab5,
    0x75cb, 0xf75a, 0x29fd, 0x8291, 0x1def, 0x9f7e, 0x0000, 0xab6c,
    0x0c45, 0xd2e2, 0x798e, 0x8ed4, 0xfb1f, 0x6461, 0xe6f0, 0x5073,
    0xcf0d, 0x4d9c, 0x933b, 0x3857, 0xa729, 0x25b8, 0xbac6, 0x11aa,
};
static const uint32_t TdL[256] = {
    0xbbdd, 0x1c03, 0x70a8, 0x2a5f, 0xe12a, 0x9fb5, 0x0e37, 0x8d81,
    0xf31e, 0x629c, 0xc542, 0xa9e9, 0xd776, 0x46f4, 0x386b, 0x54c0,
    0xc130, 0x66ee, 0x0a45, 0x50b2, 0x9bc7, 0xe558, 0x74da, 0xf76c,
    0x89f3, 0x1871, 0xbfaf, 0xd304, 0xad9b, 0x3c19, 0x4286, 0x2e2d,
    0x078a, 0xa054, 0xccff, 0x9608, 0x5d7d, 0x23e2, 0xb260, 0x31d6,
    0x4f49, 0xdecb, 0x7915, 0x15be, 0x6b21, 0xfaa3, 0x843c, 0xe897,
    0xa2f5, 0x052b, 0x6980, 0x3377, 0xf802, 0x869d, 0x171f, 0x94a9,
    0xea36, 0x7bb4, 0xdc6a, 0xb0c1, 0xce5e, 0x5fdc, 0x2143, 0x4de8,
    0x1ea2, 0xb97c, 0xd5d7, 0x8f20, 0x4455, 0x3aca, 0xab48, 0x28fe,
    0x5661, 0xc7e3, 0x603d, 0x0c96, 0x7209, 0xe38b, 0x9d14, 0xf1bf,
    0xf95b, 0x5e85, 0x322e, 0x68d9, 0xa3ac, 0xdd33, 0x4cb1, 0xcf07,
    0xb198, 0x201a, 0x87c4, 0xeb6f, 0x95f0, 0x0472, 0x7aed, 0x1646,
    0xe073, 0x47ad, 0x2b06, 0x71f1, 0xba84, 0xc41b, 0x5599, 0xd62f,
    0xa8b0, 0x3932, 0x9eec, 0xf247, 0x8cd8, 0x1d5a, 0x63c5, 0x0f6e,
    0xd818, 0x7fc6, 0x136d, 0x499a, 0x82ef, 0xfc70, 0x6df2, 0xee44,
    0x90db, 0x0159, 0xa687, 0xca2c, 0xb4b3, 0x2531, 0x5bae, 0x3705,
    0x3fe1, 0x983f, 0xf494, 0xae63, 0x6516, 0x1b89, 0x8a0b, 0x09bd,
    0x7722, 0xe6a0, 0x417e, 0x2dd5, 0x534a, 0xc2c8, 0xbc57, 0xd0fc,
    0x26c9, 0x8117, 0xedbc, 0xb74b, 0x7c3e, 0x02a1, 0x9323, 0x1095,
    0x6e0a, 0xff88, 0x5856, 0x34fd, 0x4a62, 0xdbe0, 0xa57f, 0xc9d4,
    0x5c24, 0xfbfa, 0x9751, 0xcda6, 0x06d3, 0x784c, 0xe9ce, 0x6a78,
    0x14e7, 0x8565, 0x22bb, 0x4e10, 0x308f, 0xa10d, 0xdf92, 0xb339,
    0x9a9e, 0x3d40, 0x51eb, 0x0b1c, 0xc069, 0xbef6, 0x2f74, 0xacc2,
    0xd25d, 0x43df, 0xe401, 0x88aa, 0xf635, 0x67b7, 0x1928, 0x7583,
    0x7d67, 0xdab9, 0xb612, 0xece5, 0x2790, 0x590f, 0xc88d, 0x4b3b,
    0x35a4, 0xa426, 0x03f8, 0x6f53, 0x11cc, 0x804e, 0xfed1, 0x927a,
    0x644f, 0xc391, 0xaf3a, 0xf5cd, 0x3eb8, 0x4027, 0xd1a5, 0x5213,
    0x2c8c, 0xbd0e, 0x1ad0, 0x767b, 0x08e4, 0x9966, 0xe7f9, 0x8b52,
    0x83b6, 0x2468, 0x48c3, 0x1234, 0xd941, 0xa7de, 0x365c, 0xb5ea,
    0xcb75, 0x5af7, 0xfd29, 0x9182, 0xef1d, 0x7e9f, 0x0000, 0x6cab,
    0x450c, 0xe2d2, 0x8e79, 0xd48e, 0x1ffb, 0x6164, 0xf0e6, 0x7350,
    0x0dcf, 0x9c4d, 0x3b93, 0x5738, 0x29a7, 0xb825, 0xc6ba, 0xaa11,
};
static const uint32_t TmcH[256] = {
    0x0000, 0x41d9, 0x8291, 0xc348, 0x3412, 0x75cb, 0xb683, 0xf75a,
    0x6824, 0x29fd, 0xeab5, 0xab6c, 0x5c36, 0x1def, 0xdea7, 0x9f7e,
    0x149d, 0x5544, 0x960c, 0xd7d5, 0x208f, 0x6156, 0xa21e, 0xe3c7,
    0x7cb9, 0x3d60, 0xfe28, 0xbff1, 0x48ab, 0x0972, 0xca3a, 0x8be3,
    0x2819, 0x69c0, 0xaa88, 0xeb51, 0x1c0b, 0x5dd2, 0x9e9a, 0xdf43,
    0x403d, 0x01e4, 0xc2ac, 0x8375, 0x742f, 0x35f6, 0xf6be, 0xb767,
    0x3c84, 0x7d5d, 0xbe15, 0xffcc, 0x0896, 0x494f, 0x8a07, 0xcbde,
    0x54a0, 0x1579, 0xd631, 0x97e8, 0x60b2, 0x216b, 0xe223, 0xa3fa,
    0x4321, 0x02f8, 0xc1b0, 0x8069, 0x7733, 0x36ea, 0xf5a2, 0xb47b,
    0x2b05, 0x6adc, 0xa994, 0xe84d, 0x1f17, 0x5ece, 0x9d86, 0xdc5f,
    0x57bc, 0x1665, 0xd52d, 0x94f4, 0x63ae, 0x2277, 0xe13f, 0xa0e6,
    0x3f98, 0x7e41, 0xbd09, 0xfcd0, 0x0b8a, 0x4a53, 0x891b, 0xc8c2,
    0x6b38, 0x2ae1, 0xe9a9, 0xa870, 0x5f2a, 0x1ef3, 0xddbb, 0x9c62,
    0x031c, 0x42c5, 0x818d, 0xc054, 0x370e, 0x76d7, 0xb59f, 0xf446,
    0x7fa5, 0x3e7c, 0xfd34, 0xbced, 0x4bb7, 0x0a6e, 0xc926, 0x88ff,
    0x1781, 0x5658, 0x9510, 0xd4c9, 0x2393, 0x624a, 0xa102, 0xe0db,
    0x8642, 0xc79b, 0x04d3, 0x450a, 0xb250, 0xf389, 0x30c1, 0x7118,
    0xee66, 0xafbf, 0x6cf7, 0x2d2e, 0xda74, 0x9bad, 0x58e5, 0x193c,
    0x92df, 0xd306, 0x104e, 0x5197, 0xa6cd, 0xe714, 0x245c, 0x6585,
    0xfafb, 0xbb22, 0x786a, 0x39b3, 0xcee9, 0x8f30, 0x4c78, 0x0da1,
    0xae5b, 0xef82, 0x2cca, 0x6d13, 0x9a49, 0xdb90, 0x18d8, 0x5901,
    0xc67f, 0x87a6, 0x44ee, 0x0537, 0xf26d, 0xb3b4, 0x70fc, 0x3125,
    0xbac6, 0xfb1f, 0x3857, 0x798e, 0x8ed4, 0xcf0d, 0x0c45, 0x4d9c,
    0xd2e2, 0x933b, 0x5073, 0x11aa, 0xe6f0, 0xa729, 0x6461, 0x25b8,
    0xc563, 0x84ba, 0x47f2, 0x062b, 0xf171, 0xb0a8, 0x73e0, 0x3239,
    0xad47, 0xec9e, 0x2fd6, 0x6e0f, 0x9955, 0xd88c, 0x1bc4, 0x5a1d,
    0xd1fe, 0x9027, 0x536f, 0x12b6, 0xe5ec, 0xa435, 0x677d, 0x26a4,
    0xb9da, 0xf803, 0x3b4b, 0x7a92, 0x8dc8, 0xcc11, 0x0f59, 0x4e80,
    0xed7a, 0xaca3, 0x6feb, 0x2e32, 0xd968, 0x98b1, 0x5bf9, 0x1a20,
    0x855e, 0xc487, 0x07cf, 0x4616, 0xb14c, 0xf095, 0x33dd, 0x7204,
    0xf9e7, 0xb83e, 0x7b76, 0x3aaf, 0xcdf5, 0x8c2c, 0x4f64, 0x0ebd,
    0x91c3, 0xd01a, 0x1352, 0x528b, 0xa5d1, 0xe408, 0x2740, 0x6699,
};
static const uint32_t TmcL[256] = {
    0x0000, 0xd941, 0x9182, 0x48c3, 0x1234, 0xcb75, 0x83b6, 0x5af7,
    0x2468, 0xfd29, 0xb5ea, 0x6cab, 0x365c, 0xef1d, 0xa7de, 0x7e9f,
    0x9d14, 0x4455, 0x0c96, 0xd5d7, 0x8f20, 0x5661, 0x1ea2, 0xc7e3,
    0xb97c, 0x603d, 0x28fe, 0xf1bf, 0xab48, 0x7209, 0x3aca, 0xe38b,
    0x1928, 0xc069, 0x88aa, 0x51eb, 0x0b1c, 0xd25d, 0x9a9e, 0x43df,
    0x3d40, 0xe401, 0xacc2, 0x7583, 0x2f74, 0xf635, 0xbef6, 0x67b7,
    0x843c, 0x5d7d, 0x15be, 0xccff, 0x9608, 0x4f49, 0x078a, 0xdecb,
    0xa054, 0x7915, 0x31d6, 0xe897, 0xb260, 0x6b21, 0x23e2, 0xfaa3,
    0x2143, 0xf802, 0xb0c1, 0x6980, 0x3377, 0xea36, 0xa2f5, 0x7bb4,
    0x052b, 0xdc6a, 0x94a9, 0x4de8, 0x171f, 0xce5e, 0x869d, 0x5fdc,
    0xbc57, 0x6516, 0x2dd5, 0xf494, 0xae63, 0x7722, 0x3fe1, 0xe6a0,
    0x983f, 0x417e, 0x09bd, 0xd0fc, 0x8a0b, 0x534a, 0x1b89, 0xc2c8,
    0x386b, 0xe12a, 0xa9e9, 0x70a8, 0x2a5f, 0xf31e, 0xbbdd, 0x629c,
    0x1c03, 0xc542, 0x8d81, 0x54c0, 0x0e37, 0xd776, 0x9fb5, 0x46f4,
    0xa57f, 0x7c3e, 0x34fd, 0xedbc, 0xb74b, 0x6e0a, 0x26c9, 0xff88,
    0x8117, 0x5856, 0x1095, 0xc9d4, 0x9323, 0x4a62, 0x02a1, 0xdbe0,
    0x4286, 0x9bc7, 0xd304, 0x0a45, 0x50b2, 0x89f3, 0xc130, 0x1871,
    0x66ee, 0xbfaf, 0xf76c, 0x2e2d, 0x74da, 0xad9b, 0xe558, 0x3c19,
    0xdf92, 0x06d3, 0x4e10, 0x9751, 0xcda6, 0x14e7, 0x5c24, 0x8565,
    0xfbfa, 0x22bb, 0x6a78, 0xb339, 0xe9ce, 0x308f, 0x784c, 0xa10d,
    0x5bae, 0x82ef, 0xca2c, 0x136d, 0x499a, 0x90db, 0xd818, 0x0159,
    0x7fc6, 0xa687, 0xee44, 0x3705, 0x6df2, 0xb4b3, 0xfc70, 0x2531,
    0xc6ba, 0x1ffb, 0x5738, 0x8e79, 0xd48e, 0x0dcf, 0x450c, 0x9c4d,
    0xe2d2, 0x3b93, 0x7350, 0xaa11, 0xf0e6, 0x29a7, 0x6164, 0xb825,
    0x63c5, 0xba84, 0xf247, 0x2b06, 0x71f1, 0xa8b0, 0xe073, 0x3932,
    0x47ad, 0x9eec, 0xd62f, 0x0f6e, 0x5599, 0x8cd8, 0xc41b, 0x1d5a,
    0xfed1, 0x2790, 0x6f53, 0xb612, 0xece5, 0x35a4, 0x7d67, 0xa426,
    0xdab9, 0x03f8, 0x4b3b, 0x927a, 0xc88d, 0x11cc, 0x590f, 0x804e,
    0x7aed, 0xa3ac, 0xeb6f, 0x322e, 0x68d9, 0xb198, 0xf95b, 0x201a,
    0x5e85, 0x87c4, 0xcf07, 0x1646, 0x4cb1, 0x95f0, 0xdd33, 0x0472,
    0xe7f9, 0x3eb8, 0x767b, 0xaf3a, 0xf5cd, 0x2c8c, 0x644f, 0xbd0e,
    0xc391, 0x1ad0, 0x5213, 0x8b52, 0xd1a5, 0x08e4, 0x4027, 0x9966,
};



static const uint8_t mul2 [16]={0x0,0x2,0x4,0x6,0x8,0xa,0xc,0xe,0x3,0x1,0x7,0x5,0xb,0x9,0xf,0xd};
static const uint8_t mul4 [16]={0x0,0x4,0x8,0xc,0x3,0x7,0xb,0xf,0x6,0x2,0xe,0xa,0x5,0x1,0xd,0x9};

static const uint8_t perm[16] = {1,6,11,12,5,10,15,0,9,14,3,4,13,2,7,8};

static const uint64_t rcon[33] = { 
    0x0123010100000000ULL,
    0x0123030300000000ULL,
    0x0123070700000000ULL,
    0x0123171700000000ULL,
    0x0123373700000000ULL,
    0x0123767600000000ULL,
    0x0123757500000000ULL,
    0x0123737300000000ULL,
    0x0123676700000000ULL,
    0x0123575700000000ULL,
    0x0123363600000000ULL,
    0x0123747400000000ULL,
    0x0123717100000000ULL,
    0x0123636300000000ULL,
    0x0123474700000000ULL,
    0x0123161600000000ULL,
    0x0123353500000000ULL,
    0x0123727200000000ULL,
    0x0123656500000000ULL,
    0x0123535300000000ULL,
    0x0123262600000000ULL,
    0x0123545400000000ULL,
    0x0123303000000000ULL,
    0x0123606000000000ULL,
    0x0123414100000000ULL,
    0x0123020200000000ULL,
    0x0123050500000000ULL,
    0x0123131300000000ULL,
    0x0123272700000000ULL,
    0x0123565600000000ULL,
    0x0123343400000000ULL,
    0x0123707000000000ULL,
    0x0123616100000000ULL,
};

/*
** Multiplication by alpha in GF(256)/0x11b, for alpha \in {1,2,4}
*/
uint8_t multi (uint8_t x, uint8_t alpha) {
  if( 1 == alpha ) return x;
  if( 2 == alpha ) return mul2[x];
  if( 4 == alpha ) return mul4[x];

  printf("Incorrect alpha (%d) passed to the function g in the tweakey schedule. Exiting...\n", alpha); exit(2);
}

/*
** Function G from the specifications
*/
uint64_t G (uint64_t tweakey, uint8_t alpha) {
  uint64_t i;
  uint64_t shift;
  uint8_t tmp;
  for(i=0; i<16; i++) {
    shift=4ULL*i;

    tmp=(tweakey>>shift)&0xf;
    tweakey&=0xffffffffffffffffULL^(0xfULL<<shift);

    tmp=multi(tmp, alpha);
    tweakey^=((uint64_t)tmp)<<shift;
  }

  return tweakey;
}

/*
** Function H from the specifications
*/
uint64_t H(uint64_t tweakey) {

  uint64_t i;
  uint64_t shiftIn;
  uint64_t shiftOut;
  uint64_t res=0;
  for (i=0; i<16; i++) {
    shiftIn=60ULL-4ULL*i;
    shiftOut=60ULL-4ULL*perm[i];
    res^=((tweakey>>shiftIn)&0xf)<<shiftOut;
  }
 return res;
}

/*
** Prepare the round subtweakeys for the encryption process
*/
int joltikKeySetupEnc128(uint64_t* rtweakey,
                        const uint8_t* Tweakey,
                        const int no_tweakeys)
{

  int r;
  uint64_t tweakey[3];
  uint8_t alpha[3];
  int Nr;

  tweakey[0]=GETU64(Tweakey+0);
  tweakey[1]=GETU64(Tweakey+8);
  tweakey[2]=0;

  if( 2 == no_tweakeys ){
    alpha[0] = 1; /* key   */
    alpha[1] = 2; /* tweak */

    /* Number of rounds is 24 for Joltik-BC-128 */
    Nr=24;

  } else if( 3 == no_tweakeys ){

    tweakey[2]=GETU64(Tweakey+16);
    alpha[0] = 1; /* key 1 */
    alpha[1] = 2; /* key 2 */
    alpha[2] = 4; /* tweak */

    /* Number of rounds is 36 for Joltik-BC-192 */
    Nr=32;

  } else {
    printf("The #tweakeys is %d, and it should be either 2 or 3. Exiting...\n", no_tweakeys);
    exit(1);
  }

  /* For each rounds */
  for(r=0; r<=Nr; r++) {

    /* Produce the round tweakey */
    rtweakey[r] = tweakey[0] ^ tweakey[1] ^ tweakey[2] ^ rcon[r];

    /* Apply H and G functions */
    tweakey[0]=H(tweakey[0]);
    tweakey[0]=G(tweakey[0], alpha[0]);

    tweakey[1]=H(tweakey[1]);
    tweakey[1]=G(tweakey[1], alpha[1]);

    if (3 == no_tweakeys) {
      tweakey[2]=H(tweakey[2]);
      tweakey[2]=G(tweakey[2], alpha[2]);
    }

  }/*r*/

  return Nr;
}


/*
** Prepare the round subtweakeys for the decryption process
*/
int joltikKeySetupDec128(uint64_t* rtweakey, 
                        const uint8_t* Tweakey,
                        int no_tweakeys)
{

    int i;
    int j;
    int Nr;
    uint64_t temp;

    uint64_t s;

    uint32_t s0;
    uint32_t s1;
    uint32_t s2;
    uint32_t s3;
    uint32_t s4;
    uint32_t s5;
    uint32_t s6;
    uint32_t s7;    

    /* Produce the round tweakeys used for the encryption */
    Nr=joltikKeySetupEnc128 (rtweakey, Tweakey, no_tweakeys);

    /* invert their order */
    for (i = 0, j = Nr; i < j; ++i, --j) {
        temp = rtweakey[i];
        rtweakey[i] = rtweakey[j];
        rtweakey[j] = temp;
    }


    /* apply the inverse MixColumn transform to all round keys but the first and the last */
    for (i = 1; i <= Nr; i++) {

        s=rtweakey[i];
        s0 = (s>>56ULL)&0xff;
        s1 = (s>>48ULL)&0xff;
        s2 = (s>>40ULL)&0xff;
        s3 = (s>>32ULL)&0xff;
        s4 = (s>>24ULL)&0xff;
        s5 = (s>>16ULL)&0xff;
        s6 = (s>> 8ULL)&0xff;
        s7 = (s>> 0ULL)&0xff;

        s  = (((uint64_t)(TmcH[s0]^TmcL[s1]))<<48ULL) ^ 
             (((uint64_t)(TmcH[s2]^TmcL[s3]))<<32ULL) ^ 
             (((uint64_t)(TmcH[s4]^TmcL[s5]))<<16ULL) ^ 
             (((uint64_t)(TmcH[s6]^TmcL[s7]))<< 0ULL);

        rtweakey[i]=s;
    }
    return Nr;
}

/*
** Tweakable block cipher encryption function
*/
void aesTweakEncrypt(uint32_t tweakey_size,
                     // CHANGE const added
                     const uint8_t pt[8],
                     // CHANGE const added
                     const uint8_t key[],
                     uint8_t ct[8]) {


    int i;
    int Nr;    
    uint64_t s;

    uint32_t s0;
    uint32_t s1;
    uint32_t s2;
    uint32_t s3;
    uint32_t s4;
    uint32_t s5;
    uint32_t s6;
    uint32_t s7;

    uint64_t rk[33];

    /* Produce the round tweakeys */
    Nr=joltikKeySetupEnc128 (rk, key, tweakey_size/64);

    /* Get the plaintext + key/tweak prewhitening */
    s=GETU64(pt) ^ rk[0];


    for(i=1; i<=Nr; ++i) {

        /* round i: */
        s0 = (((s>>56ULL)&0xf0))^((s>>40ULL)&0xf); 
        s1 = (((s>>16ULL)&0xf0))^((s>> 0ULL)&0xf);
        s2 = (((s>>40ULL)&0xf0))^((s>>24ULL)&0xf); 
        s3 = (((s>> 0ULL)&0xf0))^((s>>48ULL)&0xf);
        s4 = (((s>>24ULL)&0xf0))^((s>> 8ULL)&0xf); 
        s5 = (((s>>48ULL)&0xf0))^((s>>32ULL)&0xf);
        s6 = (((s>> 8ULL)&0xf0))^((s>>56ULL)&0xf); 
        s7 = (((s>>32ULL)&0xf0))^((s>>16ULL)&0xf);

        s  = (((uint64_t)(TeH[s0]^TeL[s1]))<<48ULL) ^ 
             (((uint64_t)(TeH[s2]^TeL[s3]))<<32ULL) ^ 
             (((uint64_t)(TeH[s4]^TeL[s5]))<<16ULL) ^ 
             (((uint64_t)(TeH[s6]^TeL[s7]))<< 0ULL) ^ rk[i];

    }

    /* Put the state into the ciphertext */
    PUTU64(ct, s);

}

/*
** Tweakable block cipher decryption function
*/
void aesTweakDecrypt(uint32_t tweakey_size,
                     const uint8_t ct[8],
                     const uint8_t key[],
                     uint8_t pt[8])
{

    int i;
    int Nr;    
    uint64_t s;

    uint32_t s0;
    uint32_t s1;
    uint32_t s2;
    uint32_t s3;
    uint32_t s4;
    uint32_t s5;
    uint32_t s6;
    uint32_t s7;

    uint64_t rk[33];

    /* Produce the round tweakeys */
    Nr=joltikKeySetupDec128 (rk, key, tweakey_size/64);

    /* Get the ciphertext + key/tweak prewhitening */
    s=GETU64(ct) ^ rk[0];

    s0 = (s>>56ULL)&0xff;
    s1 = (s>>48ULL)&0xff;
    s2 = (s>>40ULL)&0xff;
    s3 = (s>>32ULL)&0xff;
    s4 = (s>>24ULL)&0xff;
    s5 = (s>>16ULL)&0xff;
    s6 = (s>> 8ULL)&0xff;
    s7 = (s>> 0ULL)&0xff;

    s  = (((uint64_t)(TmcH[s0]^TmcL[s1]))<<48ULL) ^ 
         (((uint64_t)(TmcH[s2]^TmcL[s3]))<<32ULL) ^ 
         (((uint64_t)(TmcH[s4]^TmcL[s5]))<<16ULL) ^ 
         (((uint64_t)(TmcH[s6]^TmcL[s7]))<< 0ULL);

    for(i=1; i<=Nr; ++i) {

        /* round i: */
        s0 = (((s>>56ULL)&0xf0))^((s>> 8ULL)&0xf); 
        s1 = (((s>>16ULL)&0xf0))^((s>>32ULL)&0xf);
        s2 = (((s>>40ULL)&0xf0))^((s>>56ULL)&0xf); 
        s3 = (((s>> 0ULL)&0xf0))^((s>>16ULL)&0xf);
        s4 = (((s>>24ULL)&0xf0))^((s>>40ULL)&0xf); 
        s5 = (((s>>48ULL)&0xf0))^((s>> 0ULL)&0xf);
        s6 = (((s>> 8ULL)&0xf0))^((s>>24ULL)&0xf); 
        s7 = (((s>>32ULL)&0xf0))^((s>>48ULL)&0xf);

        s  = (((uint64_t)(TdH[s0]^TdL[s1]))<<48ULL) ^ 
             (((uint64_t)(TdH[s2]^TdL[s3]))<<32ULL) ^ 
             (((uint64_t)(TdH[s4]^TdL[s5]))<<16ULL) ^ 
             (((uint64_t)(TdH[s6]^TdL[s7]))<< 0ULL) ^ rk[i];
    }

    /* Apply the MixColum to invert the last one performed in the Td table */
    s0 = (s>>56ULL)&0xff;
    s1 = (s>>48ULL)&0xff;
    s2 = (s>>40ULL)&0xff;
    s3 = (s>>32ULL)&0xff;
    s4 = (s>>24ULL)&0xff;
    s5 = (s>>16ULL)&0xff;
    s6 = (s>> 8ULL)&0xff;
    s7 = (s>> 0ULL)&0xff;

    s  = (((uint64_t)(TmcH[s0]^TmcL[s1]))<<48ULL) ^ 
         (((uint64_t)(TmcH[s2]^TmcL[s3]))<<32ULL) ^ 
         (((uint64_t)(TmcH[s4]^TmcL[s5]))<<16ULL) ^ 
         (((uint64_t)(TmcH[s6]^TmcL[s7]))<< 0ULL);

    /* Put the state into the plaintext */
    PUTU64(pt, s);
}

} // namespace Joltikeq8048v1_raw
