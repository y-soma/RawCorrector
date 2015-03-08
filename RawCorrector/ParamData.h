#pragma once

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CParamData
	[Purpose]
		パラメータデータ管理クラス
\////////////////////////////////////////////////////////////////////////////*/
class CParamData
{
public:
	CParamData(void):
	  m_ProcName(NULL),
	  m_LoadFlg(FALSE),
	  m_IniSection(NULL)
	{};
	~CParamData(void){};

private:
	// 処理名
	const TCHAR* m_ProcName;
	// パラメータ読み込みフラグ
	BOOL m_LoadFlg;
	// パラメータデータ
	std::vector<ParamValue> m_Data;
	// iniファイルセクション名
	const TCHAR* m_IniSection;

public:
	/*****************************************************************************\
		[Function]
			IsLoadParam
		[Purpose]
			パラメータ読み込みフラグを取得する
		[Returns]
			フラグ
	\*****************************************************************************/
	inline const BOOL IsLoadParam(void) const { return m_LoadFlg; }

	
	/*****************************************************************************\
		[Function]
			SetProcname
		[Purpose]
			処理名を登録する
		[Parameter1] name
			処理名
	\*****************************************************************************/
	inline void SetProcname(const String& name) { m_ProcName = GFunc::StrCopy(name.c_str(), name.length()); }
	
	
	/*****************************************************************************\
		[Function]
			GetProcname
		[Purpose]
			処理名を取得する
		[Returns]
			処理名
	\*****************************************************************************/
	inline const TCHAR* const GetProcname(void) const { return m_ProcName; }


	/*****************************************************************************\
		[Function]
			GetSectionName
		[Purpose]
			処理名を取得する
		[Returns]
			処理名
	\*****************************************************************************/
	inline const TCHAR* const GetSectionName(void) const { return m_IniSection; }


	/*****************************************************************************\
		[Function]
			GetParam
		[Purpose]
			パラメータデータを取得する
		[Returns]
			パラメータデータ
	\*****************************************************************************/
	inline const std::vector<ParamValue>& GetParamValue(void) const { return m_Data; }


	/*****************************************************************************\
		[Function]
			LoadParam
		[Purpose]
			iniファイルからパラメータを読み込み、データを格納する
			データは読み込んだ分だけ追加されていく
		[Parameter1] section
			セクション名
		\*****************************************************************************/
	void LoadParam(const String& section)
	{
		m_IniSection = GFunc::StrCopy(section.c_str(), section.length());
		// 1セクション下の全てのパラメータを読み込む
		const std::vector<String> prm = GFunc::GetIniAllSection(INI_FILENAME, m_IniSection);
		if(prm.size() < 1) return;
		int add = 0;
		for(UINT i=0; i<prm.size(); i++)
		{
			const std::vector<String> split_str = GFunc::Split(prm[i].c_str(), _T("="));
			if(split_str.size() > 1)
			{
				ParamValue dummy;
				m_Data.push_back(dummy);
				m_Data[add].param_name = GFunc::StrCopy(split_str[0].c_str(), split_str[0].length());
				m_Data[add].val = GFunc::StrCopy(split_str[1].c_str(), split_str[1].length());
				++add;
			}
		}
		m_LoadFlg = TRUE;
	}


	/*****************************************************************************\
		[Function]
			ReLoadParam
		[Purpose]
			iniファイルからパラメータを読み込み、データを格納する
			こちらは一度今までのデータを削除してから、新しいものを読みこむ
		[Parameter1] section
			セクション名
	\*****************************************************************************/
	void ReLoadParam(const String& section)
	{
		m_Data.clear();
		LoadParam(section);
	}


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
		for(UINT i=0; i<m_Data.size(); i++)
		{
			if(!lstrcmpi(m_Data[i].param_name, param_name))
			{
				m_Data[i].val = GFunc::StrCopy(val.c_str(), val.length());
				break;
			}
		}
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
		if(m_Data.size() < index+1)
			return;
		m_Data[index].val = GFunc::StrCopy(val.c_str(), val.length());
	}


	/*****************************************************************************\
		[Function]
			UpdateIni
		[Purpose]
			現在保持しているデータでiniファイルを更新する
	\*****************************************************************************/
	void UpdateIni(void)
	{
		for(UINT i=0; i<m_Data.size(); i++)
			GFunc::WriteIniParam(INI_FILENAME, m_IniSection, m_Data[i].param_name, m_Data[i].val);
	}


};// End CParamData