#pragma once

#include "Subcls.h"

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CListSubcls
	[Purpose]
		リストコントロールをサブクラス化するためのクラス
\////////////////////////////////////////////////////////////////////////////*/
class CListSubcls : public CBaseSubcls
{
public:
	CListSubcls(void)
	: CBaseSubcls(){};
	~CListSubcls(void){};

protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			DeployDropFile
		[Purpose]
			ドラッグ＆ドロップされたファイルをコントロールへ展開する
		[Parameter1] path
			ドラッグ＆ドロップで取得したファイルパス
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual void DeployDropFile(const std::vector<String>& path)
	{
		std::vector<String> ext(0,_T(""));
		ext.push_back(_T(".raw"));
		GFunc::AddListItem(m_hWnd, m_DropPath, path, ext);
	}

};// End CListSubcls



/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CEditSubcls
	[Purpose]
		エディットコントロールをサブクラス化するためのクラス
\////////////////////////////////////////////////////////////////////////////*/
class CEditSubcls : public CBaseSubcls
{
public:
	CEditSubcls(void)
	: CBaseSubcls(){};
	~CEditSubcls(void){};

protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			DeployDropFile
		[Purpose]
			ドラッグ＆ドロップされたファイルをコントロールへ展開する
		[Parameter1] path
			ドラッグ＆ドロップで取得したファイルパス
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual void DeployDropFile(const std::vector<String>& path)
	{
		if(path.size() < 1) return;
		SetWindowText(m_hWnd, path[0].data());
	}

};// End CEditSubcls

