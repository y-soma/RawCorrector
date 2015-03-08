#pragma once

#include "ParamData.h"


/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CProcBase
	[Purpose]
		基本処理クラス
\////////////////////////////////////////////////////////////////////////////*/
class CProcBase
{
// ※protected指定により、派生クラスのインスタンスのみ許可されます
protected:
	CProcBase(void){};
	virtual ~CProcBase(void){};

public:
	/*****************************************************************************\
		[Enumeration]
			PROC_KIND
		[Purpose]
			処理項目の識別列挙
	\*****************************************************************************/
	enum PROC_KIND
	{
		PK_NONE			= 0x00,	// 不明
		PK_PHASEDIFF	= 0x01,	// 位相差RAW
		PK_GAIN_COMPE	= 0x02,	// ゲイン補正
		PK_FHD_MONITOR	= 0x03,	// FHD_Monitor RAW
		PK_PIXEL_COMPE	= 0x04,	// 画素補正
		PK_OPTICAXIS	= 0x05,	// 光軸補正
		PK_DEVELOP		= 0x06,	// 現像
	};


protected:
	// パラメータデータ
	CParamData m_clParamdt;


// 純粋仮想関数は必ず派生先で再定義(オーバーライド)
public:
	/*****************************************************************************\
		[Function]
			Execution
		[Purpose]
			処理実行
		[Returns]
			成功した場合はTRUEを返却
	\*****************************************************************************/
	virtual BOOL Execution(void) = 0;

	/*****************************************************************************\
		[Function]
			GetProckind
		[Purpose]
			処理識別を取得する
		[Returns]
			処理識別番号
	\*****************************************************************************/
	inline virtual const int GetProckind(void) const = 0;


	/*****************************************************************************\
		[Function]
			GetParam
		[Purpose]
			パラメータデータを取得する
		[Parameter1] name
			処理名
		[Returns]
			フラグ
	\*****************************************************************************/
	inline const CParamData& GetParam(void) const { return m_clParamdt; }


	/*****************************************************************************\
		[Function]
			SetParam
		[Purpose]
			パラメータの値を一つ変更する
		[Parameter1] param_name
			パラメータ名
		[Parameter2] val
			変更値
	\*****************************************************************************/
	void SetParam(const TCHAR* const param_name, const String& val)
	{
		m_clParamdt.SetParam(param_name, val);
	}


	/*****************************************************************************\
		[Function]
			SetProcname
		[Purpose]
			処理名を登録する
		[Parameter1] name
			処理名
	\*****************************************************************************/
	inline void SetProcname(const String& name)
	{
		m_clParamdt.SetProcname(name);
	}


	/*****************************************************************************\
		[Function]
			SetParam
		[Purpose]
			パラメータの値を一つ変更する
		[Parameter1] index
			インデックス番号
		[Parameter2] val
			変更値
	\*****************************************************************************/
	void SetParam(const UINT& index, const String& val)
	{
		m_clParamdt.SetParam(index, val);
	}


protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			GetIniSectionName
		[Purpose]
			iniファイルセクション名を取得する
		[Returns]
			セクション名
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	inline virtual const TCHAR* const GetIniSectionName(void) const = 0;


	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			LoadParam
		[Purpose]
			パラメータ読み込み
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	void LoadParam(void)
	{
		m_clParamdt.LoadParam(GetIniSectionName());
	}


};// End CProcBase