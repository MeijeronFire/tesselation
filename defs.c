// SPDX-License-Identifier: GPL
#include "defs.h"

const size_t num_threads = 4;
const size_t num_items   = 3;

const int WIDTH  = 1000;
const int HEIGHT = 1000;

const unsigned char COLORS[COLORAMOUNT][3] = {
	{255,   0,   0}, // Red
	{  0, 255,   0}, // Green
	{  0,   0, 255}, // Blue
	{255, 255,   0}, // Yellow
	{255,   0, 255}, // Magenta
	{  0, 255, 255}, // Cyan
	{255, 128,   0}, // Orange
	{128,   0, 255}, // Purple
	{  0, 128, 255}, // Azure
	{128, 255,   0}, // Chartreuse
	{255,   0, 128}, // Rose
	{128, 128, 128}, // Gray
	{192, 192, 192}, // Silver
	{128,   0,   0}, // Maroon
	{  0, 128,   0}, // Dark Green
	{  0,   0, 128}, // Navy
	{128, 128,   0}, // Olive
	{128,   0, 128}, // Indigo
	{  0, 128, 128}, // Teal
	{255, 165,   0}  // Gold/Amber
};
