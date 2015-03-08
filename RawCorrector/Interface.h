#pragma once

// Include
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <math.h>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include <algorithm>
#include <shlobj.h>

// typedef
#ifdef UNICODE
	typedef std::wstring String;
#else
	typedef std::string String;
#endif


#define INI_FILENAME	_T("RawCorrector.ini")


// struct
/*****************************************************************************\
	[Structure]
		InputdataInfo
	[Purpose]
		入力RAWデータ情報を管理する
\*****************************************************************************/
typedef struct tagINPUTDATAINFO
{
	// 先頭色 (R:0, Gr:1, Gb:2, B:3)
	unsigned char startcolor;
	// 画像幅 (1以上の整数)
	unsigned long width;
	// 画像高さ (1以上の整数)
	unsigned long height;
	// ビット精度 (2以上の整数)
	unsigned char bit;
	// ヘッダサイズ (0以上の整数)
	unsigned long headersize;
	// エンディアン (BIG:0, LITTLE:1)
	unsigned char endian;
	// データ詰め方向 (UP:0, DOWN:1)
	unsigned char datavector;
	// Constructor
	tagINPUTDATAINFO():
	startcolor(0),
	width(1),
	height(1),
	bit(2),
	headersize(0),
	endian(0),
	datavector(0)
	{};
} InputdataInfo;

/*****************************************************************************\
	[Structure]
		ParamValue
	[Purpose]
		パラメータの値を管理
\*****************************************************************************/
typedef struct tagPARAMVALUE
{
	// パラメータ名
	const TCHAR* param_name;
	// 値
	const TCHAR* val;
	// Constructor
	tagPARAMVALUE():
	param_name(NULL),
	val(NULL)
	{};
} ParamValue;

