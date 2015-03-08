#pragma once

#include "GFunc.h"

#define PROP_NAME _T("SubclsProp")


/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CBaseSubcls
	[Purpose]
		コントロールをサブクラス化するための基底クラス
\////////////////////////////////////////////////////////////////////////////*/
class CBaseSubcls
{
/* Constructor / Destructor */
protected:
	CBaseSubcls(void)
	: m_hWnd(NULL), m_DefStaticProc(NULL)
	{
		m_DropPath.clear();
	};
	virtual ~CBaseSubcls(void){};


/* コピー禁止 */
private:
	CBaseSubcls(CBaseSubcls& obj){};
	CBaseSubcls& operator = (const CBaseSubcls& obj);


protected:
	// コントロールのウインドウハンドル
	HWND m_hWnd;
	// サブクラス化用ハンドル
	WNDPROC m_DefStaticProc;
	// ドラッグ＆ドロップで読み込んだパス管理
	std::vector<String> m_DropPath;


public:
	/*****************************************************************************\
		[Function]
			InitSubcls
		[Purpose]
			サブクラス化
		[Parameter1] hWnd
			オーナーウインドウハンドル
		[Parameter2] hID
			コントロールID
		[Returns]
			成功時はTRUEを返却
	\*****************************************************************************/
	BOOL InitSubcls(const HWND& hWnd, const int& hID)
	{
		m_hWnd = GetDlgItem(hWnd, hID);
		if(!SetProp(m_hWnd, PROP_NAME, this))
			return FALSE;
		m_DefStaticProc = SubclassWindow(m_hWnd, WndProc);
		return TRUE;
	}

	/*****************************************************************************\
		[Function]
			GetFilepath
		[Purpose]
			コントロールへドラッグ＆ドロップされたパスの参照を得る
		[Returns]
			ファイルパスを返却
	\*****************************************************************************/
	inline const std::vector<String>& GetDropPath(void) const { return m_DropPath; }

	/*****************************************************************************\
		[Function]
			SetDropPath
		[Purpose]
			ドロップパス所持メンバの変更
	\*****************************************************************************/
	inline void SetDropPath(const std::vector<String>& src) { m_DropPath = src; }


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
	}

	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			OnMouseMove
		[Purpose]
			マウスムーブイベント
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual void OnMouseMove(void)
	{
	}

	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			OnLButtonDown
		[Purpose]
			マウス左ボタンクリックイベント
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual void OnLButtonDown(void)
	{
	}

	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			OnSetFocus
		[Purpose]
			フォーカス取得イベント
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual void OnSetFocus(void)
	{
	}
	
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			OnKillFocus
		[Purpose]
			フォーカス消失イベント
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual void OnKillFocus(void)
	{
	}


private:
	/*----------------------------------------------------------------------------\
		[Function]
			WndProc
		[Purpose]
			ウインドへ組み込むコールバック関数
		[Parameter1] hWnd
			ダイアログのウインドウハンドル
		[Parameter2] uMsg
			取得メッセージ
		[Parameter3] wParam
			メッセージの最初のパラメータ
		[Parameter4] lParam
			メッセージの2番目のパラメータ
		[Returns]
			メッセージ処理の結果が返ります。
			戻り値の意味は、送信されたメッセージによって異なります。
			初期化時を除き、Falseが返ります
	\----------------------------------------------------------------------------*/
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		CBaseSubcls* p = reinterpret_cast<CBaseSubcls*>(::GetProp(hWnd, PROP_NAME));
		if(!p) return -1;
		p->m_hWnd = hWnd;
		return p->MsgProc(hWnd, uMsg, wParam, lParam);
	}

	/*----------------------------------------------------------------------------\
		[Function]
			MsgProc
		[Purpose]
			メッセージ処理コールバック関数
		[Parameter1] hDlg
			ウインドウハンドル
		[Parameter2] uMsg
			メッセージ
		[Parameter3] wParam
			メッセージの最初のパラメータ
		[Parameter4] lParam
			メッセージの2番目のパラメータ
		[Returns]
			メッセージ処理の結果が返ります。
			戻り値の意味は、送信されたメッセージによって異なります。
			初期化時を除き、Falseが返ります
	\----------------------------------------------------------------------------*/
	LRESULT CALLBACK MsgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch(uMsg)
		{
		case WM_DROPFILES:
			OnDropFile(wParam);
			return FALSE;
		case WM_MOUSEMOVE:
			OnMouseMove();
			break;
		case WM_LBUTTONDOWN:
			OnLButtonDown();
			break;
		case WM_SETFOCUS:
			OnSetFocus();
			break;
		case WM_KILLFOCUS:
			OnKillFocus();
			break;
		}	
		return CallWindowProc(m_DefStaticProc, hDlg, uMsg, wParam, lParam);
	}

	/*----------------------------------------------------------------------------\
		[Function]
			OnDropFile
		[Purpose]
			ファイルドラッグ＆ドロップイベント処理
		[Parameter1] wParam
			メッセージパラメータ
		[Description]
			ドロップファイルからファイル名を取得する機構は共通のため固定処理とする
	\----------------------------------------------------------------------------*/
	void OnDropFile(const WPARAM wParam)
	{
		try
		{
			TCHAR FileName[MAX_PATH] = _T("");
			HDROP hDrop = (HDROP)wParam;

			int ic = 0;
			{// ドロップファイル数を取得
				ic = DragQueryFile(hDrop,0xFFFFFFFF,FileName,MAX_PATH);
				if(ic < 1){
					MessageBox(NULL,_T("ファイルをドロップできませんでした"),_T("Error"), MB_OK|MB_ICONERROR);
					return;
				}
			}
			
			std::vector<String> path(0,_T(""));
			{// 取得
				POINT pDrop;
				DragQueryPoint(hDrop,&pDrop);
				for(int i=0; i<ic; i++)
				{// ファイル数分
					const int StrLength = DragQueryFile(hDrop,i,FileName,MAX_PATH);
					FileName[StrLength] = '\0';
					path.push_back(FileName);
				}
				DragFinish(hDrop);
				std::sort(path.begin(),path.end());
			}
			// ドロップファイルをコントロールへ展開
			DeployDropFile(path);
		}
		catch(...)
		{
			MessageBox(NULL,_T("ファイルをドロップ中にエラーが発生しました"),_T("Error"), MB_OK|MB_ICONERROR);
		}
	}

};// End CBaseSubcls
