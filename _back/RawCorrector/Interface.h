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


// struct
/*****************************************************************************\
	[Structure]
		InputdataInfo
	[Purpose]
		入力RAWデータ情報を管理する
\*****************************************************************************/
typedef struct tagINPUTDATAINFO
{
	// 先頭色
	const TCHAR* startcolor;
	// 画像幅
	const TCHAR* width;
	// 画像高さ
	const TCHAR* height;
	// ビット精度
	const TCHAR* bit;
	// ヘッダサイズ
	const TCHAR* headersize;
	// エンディアン
	const TCHAR* endian;
	// データ詰め方向
	const TCHAR* datavector;
	// Constructor / Destructor
	tagINPUTDATAINFO():
	startcolor(NULL),
	width(NULL),
	height(NULL),
	bit(NULL),
	headersize(NULL),
	endian(NULL),
	datavector(NULL)
	{};
	/*~tagINPUTDATAINFO()
	{
		free((void*)width);
		free((void*)height);
		free((void*)bit);
		free((void*)headersize);
	};*/
} InputdataInfo;
