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
		����RAW�f�[�^�����Ǘ�����
\*****************************************************************************/
typedef struct tagINPUTDATAINFO
{
	// �擪�F (R:0, Gr:1, Gb:2, B:3)
	unsigned char startcolor;
	// �摜�� (1�ȏ�̐���)
	unsigned long width;
	// �摜���� (1�ȏ�̐���)
	unsigned long height;
	// �r�b�g���x (2�ȏ�̐���)
	unsigned char bit;
	// �w�b�_�T�C�Y (0�ȏ�̐���)
	unsigned long headersize;
	// �G���f�B�A�� (BIG:0, LITTLE:1)
	unsigned char endian;
	// �f�[�^�l�ߕ��� (UP:0, DOWN:1)
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
		�p�����[�^�̒l���Ǘ�
\*****************************************************************************/
typedef struct tagPARAMVALUE
{
	// �p�����[�^��
	const TCHAR* param_name;
	// �l
	const TCHAR* val;
	// Constructor
	tagPARAMVALUE():
	param_name(NULL),
	val(NULL)
	{};
} ParamValue;

