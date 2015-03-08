#pragma once

// CBaseDialog : 定義

#include "GFunc.h"
#include <algorithm>
#include <shlobj.h>

// disable
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#pragma warning(disable:4244)


/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CBaseDlg
	[Purpose]
		ダイアログ基底クラス
\////////////////////////////////////////////////////////////////////////////*/
class CBaseDlg
{

/* Constructor / Destructor */
protected:
	CBaseDlg(const int& GetID)
		:m_hInst(NULL),m_ID(GetID),m_hDlg(NULL)
	{
	};
	virtual ~CBaseDlg(void)
	{
	};

/* コピー不可 */
private:
	CBaseDlg(CBaseDlg& obj){};
	CBaseDlg& operator = (const CBaseDlg& obj);

/* Member */
protected:
	// インスタンスハンドル
	HINSTANCE m_hInst;
	// ウインドウハンドル
	HWND m_hDlg;
	// リソースID
	int m_ID;
	// フックハンドル
	HHOOK m_hHook;


public:
	/*****************************************************************************\
		[Function]
			GetHinstance
		[Purpose]
			インスタンスハンドル取得
		[Returns]
			インスタンスハンドルの参照を返却
	\*****************************************************************************/
	inline const HINSTANCE& GetHinstance(void) const { return m_hInst; }


	/*****************************************************************************\
		[Function]
			GetHwnd
		[Purpose]
			ウインドウハンドル取得
		[Returns]
			ウインドウハンドルの参照を返却
	\*****************************************************************************/
	inline const HWND& GetHwnd(void) const { return m_hDlg; }


protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			MsgProc
		[Purpose]
			ダイアログボックスのコールバック関数
		[Parameter1] m_hDlg
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
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch(uMsg)
		{
		case WM_INITDIALOG:
			InitCommonControls();
			MoveCenter(hWnd);
			return HANDLE_WM_INITDIALOG(hWnd,wParam,lParam,OnInitDialog);
		case WM_COMMAND:
			return CommandProc(wParam);
		case WM_DROPFILES:
			OnDropFile(wParam);
			break;
		case WM_CLOSE:
			EndDialog(hWnd,FALSE);
			return FALSE;
		default:
			//if(LOWORD(wParam) == VK_SPACE)
				//MessageBox(NULL,_T("スペースキー動作確認"),_T("テスト"), MB_OK);
			break;
		}
		return FALSE;
	}


	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			GetHookProc
		[Purpose]
			メッセージを横取りするフックプロシージャ
		[Parameter2] nCode
			コード
		[Parameter3] wParam
			メッセージの最初のパラメータ
		[Parameter4] lParam
			メッセージの2番目のパラメータ
		[Returns]
			メッセージ処理の結果が返ります。
			戻り値の意味は、送信されたメッセージによって異なります。
			初期化時を除き、Falseが返ります
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	static LRESULT FAR PASCAL GetHookProc(int nCode, WPARAM wParam, LPARAM lParam)
	{
		//SetClassLong(m_hDlg,GCW_ATOM,0xAFF);
		CBaseDlg* ptr = reinterpret_cast<CBaseDlg*>(lParam);
		if(!ptr) return -1;
		LPMSG lpMsg = (LPMSG)lParam;
		if(nCode >= 0 && PM_REMOVE == wParam)
		{
			// Don't translate non-input events.
			if((lpMsg->message >= WM_KEYFIRST && lpMsg->message <= WM_KEYLAST))
			{
				if(IsDialogMessage(ptr->m_hDlg,lpMsg))
				{
					// The value returned from this hookproc is ignored, 
					// and it cannot be used to tell Windows the message has been handled.
					// To avoid further processing, convert the message to WM_NULL 
					// before returning.
					lpMsg->message = WM_NULL;
					lpMsg->lParam  = 0;
					lpMsg->wParam  = 0;
				}
			}
		}
		return CallNextHookEx(ptr->m_hHook,nCode,wParam,lParam);
	}

	
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			OnInitDialog
		[Purpose]
			ダイアログ初期化
		[Returns]
			TRUEを返す
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual BOOL OnInitDialog(const HWND hWnd, const HWND hwndFocus, const LPARAM lParam)
	{
		return TRUE;
	}

	
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			OnCancel
		[Purpose]
			キャンセルイベント処理
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual void OnCancel(void)
	{
		EndDialog(m_hDlg,FALSE);
	}
	
	
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			OnDropFile
		[Purpose]
			ファイルドラッグ＆ドロップイベント処理
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual void OnDropFile(const WPARAM wParam)
	{
	}


	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			MoveCenter
		[Purpose]
			ダイアログを画面の中心に移動させる : 親がないので何もしないと左上に配置される
		[Parameter1] hwnd
			ウインドウハンドル
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual void MoveCenter(const HWND& hWnd)
	{
		int w = 0, h = 0, wpos = 0, hpos = 0;
		{// ダイアログの縦横サイズ
			RECT rc;
			GetWindowRect(hWnd, &rc);
			w = rc.right - rc.left;
			h = rc.bottom - rc.top;
		}
		{// スクリーンサイズから計算
			const int wFull = GetSystemMetrics(SM_CXSCREEN);
			const int hFull = GetSystemMetrics(SM_CYSCREEN);
			wpos = static_cast<int>((wFull-w)*0.5);
			hpos = static_cast<int>((hFull-h)*0.5);
		}
		MoveWindow(hWnd,wpos,hpos,w,h,FALSE);
	}


	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			CommandProc
		[Purpose]
			コマンド系メッセージ処理
		[Parameter1] wParam
			メッセージ
		[Returns]
			メッセージ処理の結果が返ります。
			戻り値の意味は、送信されたメッセージによって異なります。
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual LRESULT CommandProc(const WPARAM wParam)
	{
		switch(LOWORD(wParam))
		{
		// キャンセルボタン
		case IDCANCEL:
			OnCancel();
			break;
		}
		return FALSE;
	}


	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			GetWindowTxtEx
		[Purpose]
			コントロールに表示されているテキストを取得する
		[Parameter1] gWnd
			指定ウインドウハンドル
		[Returns]
			表示されているテキストが文字列で返る
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	String GetWindowTxtEx(const HWND& hWnd)
	{
		String dst = _T("");
		{
			TCHAR str[MAX_PATH*0xFF];
			GetWindowText(hWnd,str,MAX_PATH*0xFF);
			dst = str;
		}
		return dst;
	}


}; // End CBaseDlg




/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CModalDlg
	[Purpose]
		モーダルダイアログクラス
\////////////////////////////////////////////////////////////////////////////*/
class CModalDlg : public CBaseDlg
{

/* Constructor / Destructor */
protected:
	CModalDlg(const int& GetID)
		:CBaseDlg(GetID)
	{
	};
	virtual ~CModalDlg(void)
	{
	};

/* コピー禁止 */
private:
	CModalDlg& operator = (const CModalDlg& obj);


/* Public Member Function */
public:
	/*****************************************************************************\
		[Function]
			DoModal
		[Purpose]
			モーダルダイアログ作成
		[Parameter1] hInstance
			インスタンスハンドル
		[Parameter2] hOwner
			オーナーウインドウを指定する場合
		[Returns]
			Falseを返します
	\*****************************************************************************/
	int DoModal(const HINSTANCE hInstance, const HWND hOwner = NULL)
	{
		m_hInst = hInstance;
		return (int)DialogBoxParam(hInstance,MAKEINTRESOURCE(m_ID),(HWND)hOwner,(DLGPROC)DlgProc,reinterpret_cast<LPARAM>(this));
	}


/* CALLBACK Function */
private:
	/*----------------------------------------------------------------------------\
		[Function]
			DlgProc
		[Purpose]
			ダイアログボックスのコールバック関数
		[Parameter1] m_hDlg
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
	static LRESULT CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		static const TCHAR PropName[] = _T("ModalDlgProp");
		switch(uMsg)
		{
		case WM_INITDIALOG:{// 初期化
			// 既存のコントロールからthisポインタ取得
			CModalDlg* ptr = reinterpret_cast<CModalDlg*>(lParam);
			if(!ptr) return -1;
			// プロパティにWindowクラスのポインタを設定する
			if(!::SetProp(hWnd, PropName,reinterpret_cast<HANDLE>(ptr))) return -1;
			// ウィンドウハンドルセット
			ptr->m_hDlg = hWnd;
			// メッセージ処理関数コール
			return ptr->MsgProc(hWnd,uMsg,wParam,lParam);}
		case WM_CLOSE:{// 終了
			CModalDlg* ptr = reinterpret_cast<CModalDlg*>(::GetProp(hWnd,PropName));
			LRESULT ret = 0;
			// メッセージ処理関数コール
			if(ptr != NULL){
				ret = ptr->MsgProc(hWnd,uMsg,wParam,lParam);
				ptr->m_hDlg = NULL;
			}
			else{
				ret = ::DefWindowProc(hWnd,uMsg,wParam,lParam);
			}
			// 設定したプロパティのデータを削除する
			::RemoveProp(hWnd, PropName);
			return ret;}
		default:{// その他
			CModalDlg* ptr = reinterpret_cast<CModalDlg*>(::GetProp(hWnd,PropName));
			if(ptr != NULL)
				return ptr->MsgProc(hWnd,uMsg,wParam,lParam);
			else
				return ::DefWindowProc(hWnd,uMsg,wParam,lParam);}
		}
		return FALSE;
	}

}; // End CModalDlg




/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CModelessDlg
	[Purpose]
		モードレスダイアログクラス
\////////////////////////////////////////////////////////////////////////////*/
class CModelessDlg : public CBaseDlg
{

/* Constructor / Destructor ※継承なしでは作れない */
protected:
	CModelessDlg(const HWND& hWnd, const int& GetID)
		:CBaseDlg(GetID),OwnerWnd(hWnd)
	{
	};
	virtual ~CModelessDlg(void)
	{
	};

/* コピー禁止 */
private:
	CModelessDlg& operator = (const CModelessDlg& obj);

protected:
	// オーナーウインドウハンドル
	HWND OwnerWnd;

/* Public Member Function */
public:
	/*****************************************************************************\
		[Function]
			DoModeless
		[Purpose]
			モードレスダイアログ作成
		[Parameter1] hInstance
			インスタンスハンドル
		[Returns]
			ウインドウハンドル
	\*****************************************************************************/
	HWND DoModeless(const HINSTANCE hInstance)
	{
		m_hInst = hInstance;
		return CreateDialogParam(hInstance,MAKEINTRESOURCE(m_ID),OwnerWnd,(DLGPROC)DlgProc,reinterpret_cast<LPARAM>(this));
	}


/* CALLBACK Function */
private:
	/*----------------------------------------------------------------------------\
		[Function]
			DlgProc
		[Purpose]
			ダイアログボックスのコールバック関数
		[Parameter1] m_hDlg
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
	static LRESULT CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		static const TCHAR PropName[] = _T("ModelessDlgProp");
		switch(uMsg)
		{
		case WM_INITDIALOG:{// 初期化
			// 既存のコントロールからthisポインタ取得
			CModelessDlg* ptr = reinterpret_cast<CModelessDlg*>(lParam);
			if(!ptr) return -1;
			// プロパティにWindowクラスのポインタを設定する
			if(!::SetProp(hWnd, PropName,reinterpret_cast<HANDLE>(ptr))) return -1;
			// ウィンドウハンドルセット
			ptr->m_hDlg = hWnd;
			// メッセージ処理関数コール
			return ptr->MsgProc(hWnd,uMsg,wParam,lParam);}
		case WM_CLOSE:{// 終了
			CModelessDlg* ptr = reinterpret_cast<CModelessDlg*>(::GetProp(hWnd,PropName));
			LRESULT ret = 0;
			// メッセージ処理関数コール
			if(ptr != NULL){
				ret = ptr->MsgProc(hWnd,uMsg,wParam,lParam);
				ptr->m_hDlg = NULL;
			}
			else{
				ret = ::DefWindowProc(hWnd,uMsg,wParam,lParam);
			}
			// 設定したプロパティのデータを削除する
			::RemoveProp(hWnd, PropName);
			return ret;}
		default:{// その他
			CModelessDlg* ptr = reinterpret_cast<CModelessDlg*>(::GetProp(hWnd,PropName));
			if(ptr != NULL)
				return ptr->MsgProc(hWnd,uMsg,wParam,lParam);
			else
				return ::DefWindowProc(hWnd,uMsg,wParam,lParam);}
		}
		return FALSE;
	}


protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			MoveCenter
		[Purpose]
			ダイアログをオーナーウインドウの中心に移動させる
		[Parameter1] hwnd
			ウインドウハンドル
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual void MoveCenter(const HWND& hWnd)
	{
		if(!OwnerWnd) return CBaseDlg::MoveCenter(hWnd);	
		int w = 0, h = 0, wpos = 0, hpos = 0;
		{// ダイアログの縦横サイズ
			RECT rc;
			GetWindowRect(hWnd,&rc);
			w = rc.right - rc.left;
			h = rc.bottom - rc.top;
		}
		{// オーナーウインドウの中央の座標から計算
			RECT rc;
			GetWindowRect(OwnerWnd,&rc);
			const int oc_wpos = rc.left + ((rc.right-rc.left)/2);
			const int oc_hpos = rc.top + ((rc.bottom-rc.top)/2);
			const int wpos_t = oc_wpos - (w/2);
			const int hpos_t = oc_hpos - (h/2);
			wpos = wpos_t<0? 0:wpos_t;
			hpos = hpos_t<0? 0:hpos_t;
		}
		MoveWindow(hWnd,wpos,hpos,w,h,FALSE);
	}


}; // End CModalDlg


