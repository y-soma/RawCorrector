#pragma once

#include "ProcBase.h"

/* 各処理クラス定義場所 */
// 基底クラス"CProcBase"を継承して各処理クラスを定義


// 各処理 iniファイルセクション名定義
#define INI_SECTION_PHASEDIFF	_T("PHASEDIFF")
#define INI_SECTION_GAINCOMPE	_T("GAIN_COMPE")
#define INI_SECTION_FHD_MONITOR	_T("FHD_MONITOR")
#define INI_SECTION_PIXELCOMPE	_T("PIXEL_COMPE")
#define INI_SECTION_OPTICAXIS	_T("OPTICAXIS")
#define INI_SECTION_DEVELOP		_T("DEVELOP")



/*################################## (1) ####################################*/

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CProcPhasediff
	[Purpose]
		位相差RAW処理クラス
\////////////////////////////////////////////////////////////////////////////*/
class CProcPhasediff : public CProcBase
{
public:
	CProcPhasediff(void)
	{
		LoadParam();
	};
	~CProcPhasediff(void)
	{
		delete this;
	};

private:
	
	
public:
	/*****************************************************************************\
		[Function]
			Execution
		[Purpose]
			処理実行
		[Returns]
			成功した場合はTRUEを返却する
	\*****************************************************************************/
	virtual BOOL Execution(void)
	{
		MessageBox(NULL, _T("位相差RAW処理"), _T("確認"), MB_OK);
		return TRUE;
	}

	/*****************************************************************************\
		[Function]
			GetProckind
		[Purpose]
			処理識別を取得する
		[Returns]
			処理識別番号
	\*****************************************************************************/
	inline virtual const int GetProckind(void) const { return PK_PHASEDIFF; }


protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			GetIniSectionName
		[Purpose]
			iniファイルセクション名を取得する
		[Returns]
			セクション名
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	inline virtual const TCHAR* const GetIniSectionName(void) const { return INI_SECTION_PHASEDIFF; }


};// End CProcPhasediff



/*################################## (2) ####################################*/

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CProcGaincompe
	[Purpose]
		ゲイン補正処理クラス
\////////////////////////////////////////////////////////////////////////////*/
class CProcGaincompe : public CProcBase
{
public:
	CProcGaincompe(void)
	{
		LoadParam();
	};
	~CProcGaincompe(void)
	{
		delete this;
	};

private:
	
	
public:
	/*****************************************************************************\
		[Function]
			Execution
		[Purpose]
			処理実行
		[Returns]
			成功した場合はTRUEを返却する
	\*****************************************************************************/
	virtual BOOL Execution(void)
	{
		MessageBox(NULL, _T("ゲイン補正処理"), _T("確認"), MB_OK);
		return TRUE;
	}

	/*****************************************************************************\
		[Function]
			GetProckind
		[Purpose]
			処理識別を取得する
		[Returns]
			処理識別番号
	\*****************************************************************************/
	inline virtual const int GetProckind(void) const { return PK_GAIN_COMPE; }


protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			GetIniSectionName
		[Purpose]
			iniファイルセクション名を取得する
		[Returns]
			セクション名
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	inline virtual const TCHAR* const GetIniSectionName(void) const { return INI_SECTION_GAINCOMPE; }


};// End CProcGaincompe



/*################################## (3) ####################################*/

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CProcPixelcompe
	[Purpose]
		画素補正処理クラス
\////////////////////////////////////////////////////////////////////////////*/
class CProcPixelcompe : public CProcBase
{
public:
	CProcPixelcompe(void)
	{
		LoadParam();
	};
	~CProcPixelcompe(void)
	{
		delete this;
	};

private:
	
	
public:
	/*****************************************************************************\
		[Function]
			Execution
		[Purpose]
			処理実行
		[Returns]
			成功した場合はTRUEを返却する
	\*****************************************************************************/
	virtual BOOL Execution(void)
	{
		MessageBox(NULL, _T("画素補正処理"), _T("確認"), MB_OK);
		return TRUE;
	}

	/*****************************************************************************\
		[Function]
			GetProckind
		[Purpose]
			処理識別を取得する
		[Returns]
			処理識別番号
	\*****************************************************************************/
	inline virtual const int GetProckind(void) const { return PK_PIXEL_COMPE; }


protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			GetIniSectionName
		[Purpose]
			iniファイルセクション名を取得する
		[Returns]
			セクション名
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	inline virtual const TCHAR* const GetIniSectionName(void) const { return INI_SECTION_PIXELCOMPE; }


};// End CProcPixelcompe



/*################################## (4) ####################################*/

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CProcFHDMonitor
	[Purpose]
		FHD_MonitorRAW処理クラス
\////////////////////////////////////////////////////////////////////////////*/
class CProcFHDMonitor : public CProcBase
{
public:
	CProcFHDMonitor(void)
	{
		LoadParam();
	};
	~CProcFHDMonitor(void)
	{
		delete this;
	};

private:
	
	
public:
	/*****************************************************************************\
		[Function]
			Execution
		[Purpose]
			処理実行
		[Returns]
			成功した場合はTRUEを返却する
	\*****************************************************************************/
	virtual BOOL Execution(void)
	{
		MessageBox(NULL, _T("FHD_Monitor処理"), _T("確認"), MB_OK);
		return TRUE;
	}

	/*****************************************************************************\
		[Function]
			GetProckind
		[Purpose]
			処理識別を取得する
		[Returns]
			処理識別番号
	\*****************************************************************************/
	inline virtual const int GetProckind(void) const { return PK_FHD_MONITOR; }


protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			GetIniSectionName
		[Purpose]
			iniファイルセクション名を取得する
		[Returns]
			セクション名
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	inline virtual const TCHAR* const GetIniSectionName(void) const { return INI_SECTION_FHD_MONITOR; }


};// End CProcFHDMonitor



/*################################## (5) ####################################*/

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CProcOpticaxis
	[Purpose]
		光軸補正処理クラス
\////////////////////////////////////////////////////////////////////////////*/
class CProcOpticaxis : public CProcBase
{
public:
	CProcOpticaxis(void)
	{
		LoadParam();
	};
	~CProcOpticaxis(void)
	{
		delete this;
	};

private:
	
	
public:
	/*****************************************************************************\
		[Function]
			Execution
		[Purpose]
			処理実行
		[Returns]
			成功した場合はTRUEを返却する
	\*****************************************************************************/
	virtual BOOL Execution(void)
	{
		MessageBox(NULL, _T("光軸補正処理"), _T("確認"), MB_OK);
		return TRUE;
	}

	/*****************************************************************************\
		[Function]
			GetProckind
		[Purpose]
			処理識別を取得する
		[Returns]
			処理識別番号
	\*****************************************************************************/
	inline virtual const int GetProckind(void) const { return PK_OPTICAXIS; }


protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			GetIniSectionName
		[Purpose]
			iniファイルセクション名を取得する
		[Returns]
			セクション名
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	inline virtual const TCHAR* const GetIniSectionName(void) const { return INI_SECTION_OPTICAXIS; }


};// End CProcOpticaxis



/*################################## (6) ####################################*/

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CProcDevelop
	[Purpose]
		現像処理クラス
\////////////////////////////////////////////////////////////////////////////*/
class CProcDevelop : public CProcBase
{
public:
	CProcDevelop(void)
	{
		LoadParam();
	};
	~CProcDevelop(void)
	{
		delete this;
	};

private:
	
	
public:
	/*****************************************************************************\
		[Function]
			Execution
		[Purpose]
			処理実行
		[Returns]
			成功した場合はTRUEを返却する
	\*****************************************************************************/
	virtual BOOL Execution(void)
	{
		MessageBox(NULL, _T("現像処理"), _T("確認"), MB_OK);
		return TRUE;
	}

	/*****************************************************************************\
		[Function]
			GetProckind
		[Purpose]
			処理識別を取得する
		[Returns]
			処理識別番号
	\*****************************************************************************/
	inline virtual const int GetProckind(void) const { return PK_DEVELOP; }
	
	
protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			GetIniSectionName
		[Purpose]
			iniファイルセクション名を取得する
		[Returns]
			セクション名
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	inline virtual const TCHAR* const GetIniSectionName(void) const { return INI_SECTION_DEVELOP; }


};// End CProcDevelop

