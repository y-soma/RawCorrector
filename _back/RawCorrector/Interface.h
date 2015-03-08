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
		����RAW�f�[�^�����Ǘ�����
\*****************************************************************************/
typedef struct tagINPUTDATAINFO
{
	// �擪�F
	const TCHAR* startcolor;
	// �摜��
	const TCHAR* width;
	// �摜����
	const TCHAR* height;
	// �r�b�g���x
	const TCHAR* bit;
	// �w�b�_�T�C�Y
	const TCHAR* headersize;
	// �G���f�B�A��
	const TCHAR* endian;
	// �f�[�^�l�ߕ���
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
