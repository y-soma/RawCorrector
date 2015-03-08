#pragma once

// CMainDialog : 定義

#include "Interface.h"
#include "Dialog.h"
#include "resource.h"
#include "SubclsCtrl.h"
#include "SubDialog.h"
#include "Proc.h"

#define VERSION	_T("1.0.0.0")
#define COPYRIGHT	_T("Copyright (C) 2012 OLYMPUS IMAGING CORP. All Rights Reserved.")



/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CMainDialog
	[Purpose]
		メインダイアログ
\////////////////////////////////////////////////////////////////////////////*/
class CMainDialog : public CModalDlg
{

/* Constructor / Destructor */
public:
	CMainDialog(void)
		:CModalDlg(IDD_MAIN_DIALOG)
		,m_hFileList(NULL)
		,m_hProcList(NULL)
		,m_hPrmList(NULL)
		,m_hProcCourseCombo(NULL)
		,m_hPrmEdit(NULL)
		,m_hStaticStartColor(NULL)
		,m_hStaticDatastuff(NULL)
		,m_hStaticEndian(NULL)
		,m_hStaticBitnum(NULL)
		,m_hStaticHeadersize(NULL)
		,m_hStaticWidth(NULL)
		,m_hStaticHeight(NULL)
		,m_hStaticEvaexepath(NULL)
		,m_hStaticEvaprmpath(NULL)
		,m_Evaexepath(NULL)
		,m_Evaprmpath(NULL)
		,m_iProcCount(0)
		,m_SelectProcIndex_Old(-1)
		,m_SelectProcIndex_Old2(-1)
	{
		_tsetlocale(LC_ALL, _T("Japanese"));
	};
	~CMainDialog(void)
	{
		free((void*)m_Evaexepath);
		free((void*)m_Evaprmpath);
	};


protected:
	WNDPROC m_DefStaticProc;

private:
	// GUIコントロールのウインドウハンドル
	HWND m_hFileList;
	HWND m_hProcList;
	HWND m_hPrmList;
	HWND m_hProcCourseCombo;
	HWND m_hPrmEdit;
	HWND m_hStaticStartColor;
	HWND m_hStaticDatastuff;
	HWND m_hStaticEndian;
	HWND m_hStaticBitnum;
	HWND m_hStaticHeadersize;
	HWND m_hStaticWidth;
	HWND m_hStaticHeight;
	HWND m_hStaticEvaexepath;
	HWND m_hStaticEvaprmpath;
	// ファイルリストのサブクラス化管理
	CListSubcls m_FilelistSubcls;
	// 処理モジュール
	CProcBase** m_pProc;
	// 処理項目カウント
	int m_iProcCount;
	// 入力データ情報
	InputdataInfo m_Inputdatainfo;
	// Evaパス情報
	const TCHAR* m_Evaexepath;
	const TCHAR* m_Evaprmpath;
	// 処理項目選択インデックスを保持
	int m_SelectProcIndex_Old;
	int m_SelectProcIndex_Old2;


protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			OnInitDialog
		[Purpose]
			ダイアログ初期化
		[Returns]
			TRUEを返却
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual BOOL OnInitDialog(const HWND hWnd, const HWND hwndFocus, const LPARAM lParam)
	{
		{// ダイアログの題名
			String title = _T("RAW補正シミュレータ  (Version ");
			title += VERSION;
			title += _T(")");
			SetWindowText(hWnd,title.data());
		}
		// 既存のコントロールからハンドルを取得
		m_hFileList = GetDlgItem(hWnd,IDC_FILE_LIST);
		m_hProcList = GetDlgItem(hWnd,IDC_PROC_LIST);
		m_hPrmList = GetDlgItem(hWnd,IDC_PRM_LIST);
		m_hProcCourseCombo = GetDlgItem(hWnd,IDC_COMBO_PROC_SELECT);
		m_hPrmEdit = GetDlgItem(hWnd,IDC_EDIT_PRM);
		m_hStaticStartColor = GetDlgItem(hWnd,IDC_STATIC_STARTCOLOR);
		m_hStaticDatastuff = GetDlgItem(hWnd,IDC_STATIC_DATASTUFF);
		m_hStaticEndian = GetDlgItem(hWnd,IDC_STATIC_ENDIAN);
		m_hStaticBitnum = GetDlgItem(hWnd,IDC_STATIC_BITNUM);
		m_hStaticHeadersize = GetDlgItem(hWnd,IDC_STATIC_HEADERSIZE);
		m_hStaticWidth = GetDlgItem(hWnd,IDC_STATIC_WIDTH);
		m_hStaticHeight = GetDlgItem(hWnd,IDC_STATIC_HEIGHT);
		m_hStaticEvaexepath = GetDlgItem(hWnd,IDC_STATIC_EVAEXEPATH);
		m_hStaticEvaprmpath = GetDlgItem(hWnd,IDC_STATIC_EVAPRMPATH);
		
		BOOL ReadFaild = FALSE;
		String FaildComment = INI_FILENAME;
		FaildComment += _T(" の読み込みに失敗しました");
		// 先頭色
		const String startcolor = GFunc::GetIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("startcolor"));
		m_Inputdatainfo.startcolor = (unsigned char)GFunc::StrToL(startcolor.data());
		if(startcolor == _T("")){
			ReadFaild = TRUE;
			FaildComment += _T("\n※先頭色を読み込めませんでした");
		}
		// 詰め方向
		const String datavector = GFunc::GetIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("datavector"));
		m_Inputdatainfo.datavector = (unsigned char)GFunc::StrToL(datavector.data());
		if(datavector == _T("")){
			ReadFaild = TRUE;
			FaildComment += _T("\n※詰め方向を読み込めませんでした");
		}
		// エンディアン
		const String endian = GFunc::GetIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("endian"));
		m_Inputdatainfo.endian = (unsigned char)GFunc::StrToL(endian.data());
		if(endian == _T("")){
			ReadFaild = TRUE;
			FaildComment += _T("\n※エンディアンを読み込めませんでした");
		}
		// 設定情報のセット
		const String width = GFunc::GetIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("width"));
		m_Inputdatainfo.width = GFunc::StrToL(width.data());
		if(!m_Inputdatainfo.width){
			ReadFaild = TRUE;
			FaildComment += _T("\n※水平方向サイズを読み込めませんでした");
		}
		const String height = GFunc::GetIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("height"));
		m_Inputdatainfo.height = GFunc::StrToL(height.data());
		if(!m_Inputdatainfo.height){
			ReadFaild = TRUE;
			FaildComment += _T("\n※垂直方向サイズを読み込めませんでした");
		}
		const String bit = GFunc::GetIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("bit"));
		m_Inputdatainfo.bit = GFunc::StrToL(bit.data());
		if(!m_Inputdatainfo.bit){
			ReadFaild = TRUE;
			FaildComment += _T("\n※ビットを読み込めませんでした");
		}
		const String header = GFunc::GetIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("header"));
		m_Inputdatainfo.headersize = GFunc::StrToL(header.data());
		if(!m_Inputdatainfo.headersize){
			ReadFaild = TRUE;
			FaildComment += _T("\n※ヘッダサイズを読み込めませんでした");
		}
		const String exe = GFunc::GetIniParam(INI_FILENAME, _T("EVA_PATH"), _T("exe"));
		m_Evaexepath = GFunc::StrCopy(exe.data(), (ULONG)exe.length());
		if(!m_Evaexepath){
			ReadFaild = TRUE;
			FaildComment += _T("\n※Eva実行パスを読み込めませんでした");
		}
		const String prm = GFunc::GetIniParam(INI_FILENAME, _T("EVA_PATH"), _T("prm"));
		m_Evaprmpath = GFunc::StrCopy(prm.data(), (ULONG)prm.length());
		if(!m_Evaprmpath){
			ReadFaild = TRUE;
			FaildComment += _T("\n※Evaパラメータパスを読み込めませんでした");
		}

		if(ReadFaild){
			MessageBox(NULL, FaildComment.data(), NULL, MB_OK | MB_ICONERROR);
			EndDialog(hWnd, FALSE);
		}
		
		UpdateGUI();

		//_T("5200,3568,Gr,UP,LITTLE,12,0,");
		

		// リストコントロールの初期化
		std::vector<String> caption(0,_T(""));
		std::vector<double> mag(0,0.0);
		{// ファイルリスト初期化
			caption.clear();
			caption.push_back(_T("FileName"));
			caption.push_back(_T("Dir"));
			mag.clear();
			mag.push_back(0.4);
			mag.push_back(0.59);
			InitList(m_hFileList, caption, mag);
		}
		{// 処理リスト初期化
			caption.clear();
			caption.push_back(_T("順序"));
			caption.push_back(_T("処理項目"));
			mag.clear();
			mag.push_back(0.16);
			mag.push_back(0.825);
			InitList(m_hProcList, caption, mag);
		}
		{// パラメータリスト初期化
			caption.clear();
			caption.push_back(_T("Name"));
			caption.push_back(_T("Value"));
			mag.clear();
			mag.push_back(0.35);
			mag.push_back(0.64);
			InitList(m_hPrmList, caption, mag);
		}

		// ファイルリストのサブクラス化
		m_FilelistSubcls.InitSubcls(hWnd, IDC_FILE_LIST);
		
		return TRUE;
	}


	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			CommandProc
		[Purpose]
			コマンド系メッセージ処理
		[Parameter1] wParam
			コマンド系メッセージ
		[Parameter2] lParam
			コマンド系メッセージ
		[Returns]
			メッセージ処理の結果を返却
			返却値の意味は、送信されたメッセージによって異なります。
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual LRESULT CommandProc(const WPARAM wParam, const LPARAM lParam)
	{
		switch(LOWORD(wParam))
		{
		case ID_OPEN:{// メニューからファイルを開く
			std::vector<String> path = m_FilelistSubcls.GetDropPath();
			std::vector<String> ext(0,_T(""));
			ext.push_back(_T(".raw"));
			GFunc::AddListItem(m_hFileList, path, GFunc::FileSelectDlg(m_hDlg,_T("RAWファイルを開く"),TEXT("RAW {*.RAW}\0*.raw\0"),_T("RAW")), ext);
			m_FilelistSubcls.SetDropPath(path);
			break;}
		case IDC_BUTTON_PHASEDIFF:{// 位相差RAW
			AddProc(CProcBase::PK_PHASEDIFF);
			break;}
		case IDC_BUTTON_GAIN:{// ゲイン補正
			AddProc(CProcBase::PK_GAIN_COMPE);
			break;}
		case IDC_BUTTON_FHDMONITOR:{// FHD MonitorRAW
			AddProc(CProcBase::PK_FHD_MONITOR);
			break;}
		case IDC_BUTTON_PIXELCORRECT:{// 画素補正
			AddProc(CProcBase::PK_PIXEL_COMPE);
			break;}
		case IDC_BUTTON_OPTICAXIS:{// 光軸補正
			AddProc(CProcBase::PK_OPTICAXIS);
			break;}
		case IDC_BUTTON_DEVELOP:{// 現像
			AddProc(CProcBase::PK_DEVELOP);
			break;}
		case IDC_BUTTON_PROCTURNCHANGE_UP:{// 処理順早める
			SwapProcOrder(0);
			break;}
		case IDC_BUTTON_PROCTURNCHANGE_DOWN:{// 処理順遅める
			SwapProcOrder(1);
			break;}
		case IDC_BUTTON_CLEAR:{// 処理項目を一つ削除
			DeleteProc();
			ListView_DeleteAllItems(m_hPrmList);
			m_SelectProcIndex_Old = -1;
			break;}
		case IDC_BUTTON_ALLCLEAR:{// 処理項目を全て削除
			// リストは全て消去
			ListView_DeleteAllItems(m_hProcList);
			ListView_DeleteAllItems(m_hPrmList);
			// 処理データをクリア
			m_iProcCount = 0;
			m_pProc = (CProcBase**)malloc(sizeof(CProcBase*) * m_iProcCount);
			m_SelectProcIndex_Old = -1;
			break;}
		case IDC_BUTTON_PROCREGISTR:{// 表示されている処理内容を登録
			//SetWindowText(m_hPrmEdit, _T("※テスト挿入"));
			break;}
		case IDC_BUTTON_PRM_WRITE:{// GUI表示中のパラメータをiniファイルへ書き込み
			if(m_SelectProcIndex_Old == -1)
				break;
			const CParamData& prm = m_pProc[m_SelectProcIndex_Old]->GetParam();
			String mes = _T("表示中の \"");
			mes += prm.GetProcname();
			mes += _T("\" のパラメータをiniファイルへ書き込みます。よろしいですか?");
			if(MessageBox(NULL, mes.c_str(), _T("確認"), MB_YESNO|MB_ICONQUESTION) == IDNO)
				break;
			const std::vector<ParamValue>& val = prm.GetParamValue();
			for(UINT i=0; i<val.size(); i++)
				GFunc::WriteIniParam(INI_FILENAME, prm.GetSectionName(), val[i].param_name, val[i].val);
			break;}
		case IDC_BUTTON_INPUTDATA_EDIT:{// 入力データサイズ変更
			const InputdataInfo backupinfo = m_Inputdatainfo;
			CInputdataDialog IndataDlg(m_Inputdatainfo);
			const int ret = IndataDlg.DoModal(m_hInst, m_hDlg);
			if(ret == IDOK){
				m_Inputdatainfo = IndataDlg.GetInputdatainfo();
				UpdateGUI();
				UpdateIni_Inputdata();
			}
			else if(ret == IDCANCEL)
				m_Inputdatainfo = backupinfo;
			break;}
		case IDC_BUTTON_EVAPATH_EDIT:{// Evaパス変更
			CEvasetDialog EvaDlg;
			EvaDlg.Setpath(m_Evaexepath, m_Evaprmpath);
			const int ret = EvaDlg.DoModal(m_hInst, m_hDlg);
			if(ret == IDOK){
				const String exe = EvaDlg.GetExepath();
				const String prm = EvaDlg.GetPrmpath();
				m_Evaexepath = GFunc::StrCopy(exe.c_str(), exe.length());
				m_Evaprmpath = GFunc::StrCopy(prm.c_str(), prm.length());
				UpdateGUI();
				UpdateIni_Evapath();
			}
			break;}
		case IDC_BUTTON_EXEC:{// 実行
			OnExecution();
			break;}
		case IDCANCEL: case ID_CLOSE:{// 終了
			OnCancel();
			break;}
		default:
			break;
		}
		
		if(lParam == (LPARAM)m_hPrmEdit)
		{// エディットボックス変更イベント
			static String oldPrmEditTxt = _T("");
			switch(HIWORD(wParam))
			{
			case EN_UPDATE: // 変更直前
				return FALSE;
			case EN_CHANGE:{ // 変更直後
				TCHAR str[MAX_PATH * 0x0F];
				GetWindowText(m_hPrmEdit, str, MAX_PATH * 0x0F);
				const String newPrmEditTxt = str;
				if(oldPrmEditTxt != newPrmEditTxt)
				{// エディットに編集が加えられたら、リストとデータメンバの内容をアップデートする
					const int index = GetSelectedListIndex(m_hPrmList);
					if(index == -1)
						return FALSE;
					ListView_SetItemText(m_hPrmList, index, 1, (LPTSTR)newPrmEditTxt.c_str());
					m_pProc[m_SelectProcIndex_Old]->SetParam((UINT)index, newPrmEditTxt.c_str());
				}
				return FALSE;}
			}
		}
		return FALSE;
	}


	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			OnNotify
		[Purpose]
			通知メッセージハンドラ
		[Parameter1] id
			通知メッセージを発行したコントロールID。これより、hdr構造体のIDのほうが正確である。
		[Parameter2] hdr
			NMHDR構造体へのポインタ
		[Returns]
			メッセージに依存する
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual INT_PTR OnNotify(const int& id, NMHDR* hdr)
	{
		// 処理項目リスト選択イベント
		UpdateParamList();
		// パラメータリスト選択イベント
		UpdateParamEdit();
		return FALSE;
	}


private:
	/*----------------------------------------------------------------------------\
		[Function]
			OnExecution
		[Purpose]
			実行
	\----------------------------------------------------------------------------*/
	void OnExecution(void)
	{
		// ※動作確認
		for(int i=0; i<m_iProcCount; i++)
			m_pProc[i]->Execution();
	}
	
	
	/*----------------------------------------------------------------------------\
		[Function]
			InitList
		[Purpose]
			リスト初期化
		[Parameter1] hList
			リストコントロールへのウインドウハンドル
		[Parameter2] caption
			行ヘッダタイトルの指定
		[Parameter3] mag
			各列のサイズ倍率
	\----------------------------------------------------------------------------*/
	BOOL InitList(HWND& hList, const std::vector<String>& caption, const std::vector<double>& mag)
	{
		try
		{
			{// Style
				DWORD dwStyle;
				dwStyle = ListView_GetExtendedListViewStyle(hList);
				dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;
				ListView_SetExtendedListViewStyle(hList,dwStyle);
			}

			const int clmNum = (int)caption.size();
			if(clmNum != mag.size())
				return FALSE;

			long width = 0;
			{// リストコントロールの幅サイズ取得
				RECT rect;
				::GetWindowRect(hList,&rect);
				width = rect.right - rect.left;
			}

			LV_COLUMN lvcol;
			lvcol.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			lvcol.fmt = LVCFMT_LEFT;
			for(int i = 0; i < clmNum; i++)
			{
				lvcol.iSubItem = i;
				lvcol.pszText = (LPTSTR)caption[i].data();
				lvcol.cx = static_cast<int>((double)width * mag[i]);	
				if(ListView_InsertColumn(hList,i,&lvcol) == -1)
					return FALSE;
			}
			return TRUE;
		}
		catch(...)
		{
			return FALSE;
		}
	}
	

	/*----------------------------------------------------------------------------\
		[Function]
			AddProc
		[Purpose]
			処理項目を一つ追加する
		[Parameter1] proc_code
			処理コード
		[Returns]
			成功するとTRUEを返却
	\----------------------------------------------------------------------------*/
	BOOL AddProc(const int& proc_code)
	{
		try
		{
			++m_iProcCount;

			// 処理領域作成
			CProcBase**& p = m_pProc;
			CProcBase** backup = (CProcBase**)malloc(sizeof(CProcBase*) * (m_iProcCount-1));
			{// 新しい領域数で再確保する
				// バックアップ確保
				for(int i=0; i<m_iProcCount-1; i++)
					backup[i] = dynamic_cast<CProcBase*>(p[i]);
				// 新領域へ移す
				p = (CProcBase**)malloc(sizeof(CProcBase*) * m_iProcCount);
				for(int i=0; i<m_iProcCount-1; i++)
					p[i] = backup[i];
			}
			
			String procname = _T("");
			switch(proc_code)
			{// 追加項目は目的の処理に応じてダウンキャストを行う
			case CProcBase::PK_PHASEDIFF:
				p[m_iProcCount-1] = new(std::nothrow) CProcPhasediff;
				procname = _T("位相差RAW");
				break;
			case CProcBase::PK_GAIN_COMPE:
				p[m_iProcCount-1] = new(std::nothrow) CProcGaincompe;
				procname = _T("ゲイン補正");
				break;
			case CProcBase::PK_FHD_MONITOR:
				p[m_iProcCount-1] = new(std::nothrow) CProcFHDMonitor;
				procname = _T("FHD_MonitorRAW");
				break;
			case CProcBase::PK_PIXEL_COMPE:
				p[m_iProcCount-1] = new(std::nothrow) CProcPixelcompe;
				procname = _T("画素補正");
				break;
			case CProcBase::PK_OPTICAXIS:
				p[m_iProcCount-1] = new(std::nothrow) CProcOpticaxis;
				procname = _T("光軸補正");
				break;
			case CProcBase::PK_DEVELOP:
				p[m_iProcCount-1] = new(std::nothrow) CProcDevelop;
				procname = _T("現像");
				break;
			case CProcBase::PK_NONE:
			default:
				return FALSE;
			}
			p[m_iProcCount-1]->SetProcname(procname);
			// リストの更新
			GFunc::InsertSubItem(m_hProcList,m_iProcCount-1,0,GFunc::LToStr(m_iProcCount).data());
			GFunc::InsertSubItem(m_hProcList,m_iProcCount-1,1,procname.c_str());
			
			return TRUE;
		}
		catch(std::bad_cast)
		{
			MessageBox(NULL, _T("処理モジュールのダウンキャストに失敗しました"), NULL, MB_OK|MB_ICONERROR);
			return FALSE;
		}
		catch(...)
		{
			MessageBox(NULL, _T("処理データの作成に失敗しました"), NULL, MB_OK|MB_ICONERROR);
			return FALSE;
		}
	}


	/*----------------------------------------------------------------------------\
		[Function]
			DeleteProc
		[Purpose]
			処理領域を一つ削除して更新する
	\----------------------------------------------------------------------------*/
	void DeleteProc(void)
	{
		const int index = GetSelectedListIndex(m_hProcList);
		if(index == -1 || m_iProcCount < 1) return;
		
		CProcBase**& p = m_pProc;
		CProcBase** backup = (CProcBase**)malloc(sizeof(CProcBase*) * (m_iProcCount-1));
		{// 新しい領域数で再確保する
			// バックアップ確保
			int add = 0;
			for(int i=0; i<m_iProcCount; i++)
			{
				if(i == index) continue;
				backup[add] = p[i];
				++add;
			}
			// 新領域へ移す
			p = (CProcBase**)malloc(sizeof(CProcBase*) * (m_iProcCount-1));
			for(int i=0; i<m_iProcCount-1; i++)
				p[i] = backup[i];
		}
		--m_iProcCount;
		
		// リストビューの更新
		ListView_DeleteItem(m_hProcList, index);
		for(int i=0; i<m_iProcCount; i++)
		{// アイテム番号描写
			const String num = GFunc::LToStr(i+1).c_str();
			const TCHAR* str = GFunc::StrCopy(num.c_str(), num.length());
			ListView_SetItemText(m_hProcList, i, 0, (LPTSTR)str);
		}
	}


	/*----------------------------------------------------------------------------\
		[Function]
			SwapProcOrder
		[Purpose]
			処理項目の順番を入れ替える
		[Parameter1] vect
			変更方向(順番を早める:0 or 遅くする:1)
	\----------------------------------------------------------------------------*/
	void SwapProcOrder(const int& vect)
	{
		const UINT size = ListView_GetItemCount(m_hProcList);
		// 2個未満の場合、並べ替えの必要なし
		if(size < 2 || size != m_iProcCount) return;
		for(UINT i=0; i<size; i++)
		{// 選択状態の項目を検索
			const UINT uiState = ListView_GetItemState(m_hProcList, i, LVIS_SELECTED);
			if(uiState & LVIS_SELECTED)
			{// 入れ替え作業
				// 上端、下端にいるかどうかチェック
				BOOL check = FALSE;
				int iItem = 0;
				if(!vect){// 早める
					check = !i;
					iItem = i - 1;
				}
				else if(vect == 1){// 遅くする
					check = i == (size - 1);
					iItem = i + 1;
				}
				if(check) break;
				{// 処理データの更新
					CProcBase**& p = m_pProc;
					CProcBase* swap1 = p[i];
					CProcBase* swap2 = p[iItem];
					p[i] = swap2;
					p[iItem] = swap1;
				}
				{// リストビューの更新
					// 対象のテキスト内容を一時保持
					TCHAR obj[_MAX_PATH * 0x0F];
					ListView_GetItemText(m_hProcList, i, 1, obj, sizeof(obj));
					TCHAR objbefor[_MAX_PATH * 0x0F];
					ListView_GetItemText(m_hProcList, iItem, 1, objbefor, sizeof(objbefor));
					// 入れ替え
					ListView_SetItemText(m_hProcList, i, 1, objbefor);
					ListView_SetItemText(m_hProcList, iItem, 1, obj);
					ListView_SetItemState(m_hProcList, i, 0, LVIS_SELECTED);
					ListView_SetItemState(m_hProcList, iItem, LVIS_SELECTED, LVIS_SELECTED);
				}
				break;
			}
		}
	}


	/*----------------------------------------------------------------------------\
		[Function]
			UpdateGUI
		[Purpose]
			GUI表示項目の更新
	\----------------------------------------------------------------------------*/
	void UpdateGUI(void)
	{
		SetWindowText(m_hStaticStartColor, CInputdataDialog::GetStartcolorStr(m_Inputdatainfo.startcolor));
		SetWindowText(m_hStaticDatastuff, CInputdataDialog::GetDatavectorStr(m_Inputdatainfo.datavector));
		SetWindowText(m_hStaticEndian, CInputdataDialog::GetEndianStr(m_Inputdatainfo.endian));
		SetWindowText(m_hStaticBitnum, GFunc::LToStr(m_Inputdatainfo.bit).c_str());
		SetWindowText(m_hStaticHeadersize, GFunc::LToStr(m_Inputdatainfo.headersize).c_str());
		SetWindowText(m_hStaticWidth, GFunc::LToStr(m_Inputdatainfo.width).c_str());
		SetWindowText(m_hStaticHeight, GFunc::LToStr(m_Inputdatainfo.height).c_str());
		SetWindowText(m_hStaticEvaexepath, m_Evaexepath);
		SetWindowText(m_hStaticEvaprmpath, m_Evaprmpath);
	}


	/*----------------------------------------------------------------------------\
		[Function]
			UpdateIni_Inputdata
		[Purpose]
			入力データ情報のiniパラメータ内容を更新
	\----------------------------------------------------------------------------*/
	void UpdateIni_Inputdata(void)
	{
		// 先頭色
		GFunc::WriteIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("startcolor"), GFunc::LToStr(m_Inputdatainfo.startcolor).data());
		// エンディアン
		GFunc::WriteIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("endian"), GFunc::LToStr(m_Inputdatainfo.endian).data());
		// 詰め方向
		GFunc::WriteIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("datavector"), GFunc::LToStr(m_Inputdatainfo.datavector).data());
		// 幅
		GFunc::WriteIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("width"), GFunc::LToStr(m_Inputdatainfo.width).data());
		// 高さ
		GFunc::WriteIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("height"), GFunc::LToStr(m_Inputdatainfo.height).data());
		// ビット
		GFunc::WriteIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("bit"), GFunc::LToStr(m_Inputdatainfo.bit).data());
		// ヘッダ
		GFunc::WriteIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("header"), GFunc::LToStr(m_Inputdatainfo.headersize).data());
	}


	/*----------------------------------------------------------------------------\
		[Function]
			UpdateIni_Evapath
		[Purpose]
			Evaパスのiniパラメータ内容を更新
	\----------------------------------------------------------------------------*/
	void UpdateIni_Evapath(void)
	{
		GFunc::WriteIniParam(INI_FILENAME, _T("EVA_PATH"), _T("exe"), m_Evaexepath);
		GFunc::WriteIniParam(INI_FILENAME, _T("EVA_PATH"), _T("prm"), m_Evaprmpath);
	}


	/*----------------------------------------------------------------------------\
		[Function]
			GetSelectedListIndex
		[Purpose]
			リストコントロールの選択状態のアイテムインデックスを取得する
		[Parameter1] hWnd
			リストコントロールのハンドル
		[Returns]
			アイテムインデックスを返却
	\----------------------------------------------------------------------------*/
	int GetSelectedListIndex(const HWND hWnd)
	{
		const int Cnt = ListView_GetSelectedCount(hWnd);
		if(Cnt > 0)
		{// 処理項目リストの選択状態を検出
			for(int i=0; i<ListView_GetItemCount(hWnd); i++){
				const UINT uiState = ListView_GetItemState(hWnd, i, LVIS_SELECTED|LVIS_FOCUSED);
				if(uiState & LVIS_SELECTED)
					return i;
			}
		}
		return -1;
	}
	
	
	
	/*----------------------------------------------------------------------------\
		[Function]
			IsSelected_ListCtrl
		[Purpose]
			リストコントロールの選択状態を調べる
		[Parameter1] hWnd
			リストコントロールのハンドル
		[Parameter2] old_select
			選択されたアイテムの文字列を保持
		[Returns]
			前と別のアイテムが選択された場合はアイテムインデックスを返却
	\----------------------------------------------------------------------------*/
	int IsSelected_ListCtrl(const HWND hWnd, String& old_select)
	{
		const int index = GetSelectedListIndex(hWnd);
		if(index != -1)
		{
			TCHAR str[MAX_PATH];
			ListView_GetItemText(hWnd, index, 1, str, MAX_PATH);
			const String new_select = str;
			if(old_select != new_select)
			{	
				old_select = new_select;
				return index;
			}
		}
		return -1;
	}


	/*----------------------------------------------------------------------------\
		[Function]
			UpdateParamList
		[Purpose]
			選択した処理項目に応じてパラメータ表示リストの内容を更新する
	\----------------------------------------------------------------------------*/
	void UpdateParamList(void)
	{
		const int index = GetSelectedListIndex(m_hProcList);
		if(index == -1 || index == m_SelectProcIndex_Old)
			return;
		m_SelectProcIndex_Old = index;
		const CParamData prm = m_pProc[index]->GetParam();
		const int prm_select = GetSelectedListIndex(m_hPrmList);
		if(prm_select != -1)
			ListView_SetItemState(m_hPrmList, prm_select, 0, LVIS_SELECTED);
		SetWindowText(m_hPrmEdit, _T(""));
		ListView_DeleteAllItems(m_hPrmList);
		const std::vector<ParamValue> prmval = prm.GetParamValue();
		for(UINT i=0; i<prmval.size(); i++)
		{
			GFunc::InsertSubItem(m_hPrmList, i, 0, prmval[i].param_name);
			GFunc::InsertSubItem(m_hPrmList, i, 1, prmval[i].val);
		}
	}


	/*----------------------------------------------------------------------------\
		[Function]
			UpdateParamEdit
		[Purpose]
			選択したパラメータに応じてパラメータ編集エディットの内容を更新する
	\----------------------------------------------------------------------------*/
	void UpdateParamEdit(void)
	{
		const int index = GetSelectedListIndex(m_hPrmList);
		if(index == -1)
			return;
		static int old_prmindex = -1;
		if(m_SelectProcIndex_Old2 == m_SelectProcIndex_Old && index == old_prmindex)
			return;
		old_prmindex = index;
		m_SelectProcIndex_Old2 = m_SelectProcIndex_Old;

		const CParamData prm = m_pProc[m_SelectProcIndex_Old]->GetParam();
		const std::vector<ParamValue> prmval = prm.GetParamValue();
		if(prmval.size() < (UINT)old_prmindex+1)
			return;
		SetWindowText(m_hPrmEdit, prmval[old_prmindex].val);
	}



#if 0
	/*----------------------------------------------------------------------------\
		[Function]
			InitTaglistCombo
		[Details]
			コンボボックス初期化
		[Argument1] hDlg
			ウインドウハンドル
		[Return]
			成功：TRUE  失敗：FALSE
	\----------------------------------------------------------------------------*/
	BOOL InitTaglistCombo(void)
	{
		std::map<ULONG,String> StdTag;
		CImgExif::InitStdTag(StdTag);
		const ULONG TagID[] =
		{// ここで選択対象にするタグIDを任意に登録する
			0x010F,
			0x0110,
			0xA002,
			0xA003,
			0x829A,
			0x829D,
			0x8827,
			0x9204,
			0x920A,
			0x0102,
			0x0104,
			0x0203,
		};
		const String xmlpath = GetModuleDir() + _T("\\tagsetJ.xml");
		CXml pXml(xmlpath.data());
		if(!pXml.IsXmlLoad()){
			MessageBox(NULL,_T("""tagsetJ.xml""の読み込みに失敗しました"),_T("Error"), MB_OK | MB_ICONERROR);
			return FALSE;
		}
		/*{// xmlから取得した情報で更新する
			std::vector<String> str(0,_T(""));
			pXml.GetAttribute(str,_T("entry"),_T("name"));
			std::vector<CXml::EntryAttribute> eAttribute;
			pXml.GetEntryAttribute(eAttribute);
			for(int i=0; i<str.size(); i++)
			{
				SendMessage(hCombo,CB_INSERStringING,i,(LPARAM)str[i].data());
			}
		}*/
		for(int i=0; i<sizeof(TagID)/sizeof(TagID[0]); i++)
		{
			SendMessage(hCombo,CB_INSERStringING,i,(LPARAM)StdTag[TagID[i]].data());
		}
		// 一番目のアイテムを選択
		SendMessage(hCombo, CB_SETCURSEL,0,0);
		return TRUE;
	}
	
#endif

}; // CMainDialog


