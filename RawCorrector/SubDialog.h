#pragma once

/* 子ダイアログ定義場所 */


/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CEvasetDialog
	[Purpose]
		Evaのパスを設定するダイアログ
\////////////////////////////////////////////////////////////////////////////*/
class CEvasetDialog : public CModalDlg
{

/* Constructor / Destructor */
public:
	CEvasetDialog(void)
		:CModalDlg(IDD_EVASET_DIALOG)
		,m_hEditExepath(NULL), m_hEditPrmpath(NULL)
	{
		_tsetlocale(LC_ALL, _T("Japanese"));
	};
	~CEvasetDialog(void)
	{
	};

	
private:
	// コントロールのウインドウハンドル
	HWND m_hEditExepath;
	HWND m_hEditPrmpath;
	// 実行パスエディットのサブクラス化管理
	CEditSubcls m_ExepathSubcls;
	// パラメータパスエディットのサブクラス化管理
	CEditSubcls m_PrmpathSubcls;
	// exeパスを保持
	String m_Exepath;
	// prmパスを保持
	String m_Prmpath;


public:
	/*****************************************************************************\
		[Function]
			Setpath
		[Purpose]
			パスをメンバ変数へセットする
		[Parameter1] exe
			exeパス
		[Parameter2] prm
			prmパス
	\*****************************************************************************/
	inline void Setpath(const TCHAR* const exe, const TCHAR* const prm)
	{
		m_Exepath = exe;
		m_Prmpath = prm;
	}

	/*****************************************************************************\
		[Function]
			GetExepath
		[Purpose]
			このモジュール内で変更したexeパスを取得する
	\*****************************************************************************/
	inline const String& GetExepath() const { return m_Exepath; }

	/*****************************************************************************\
		[Function]
			GetPrmpath
		[Purpose]
			このモジュール内で変更したprmパスを取得する
	\*****************************************************************************/
	inline const String& GetPrmpath() const { return m_Prmpath; }


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
		// 既存のコントロールからハンドルを取得
		m_hEditExepath = GetDlgItem(hWnd,IDC_EDIT_EVAEXEPATH);
		m_hEditPrmpath = GetDlgItem(hWnd,IDC_EDIT_EVAPRMPATH);
		// サブクラス化
		m_ExepathSubcls.InitSubcls(hWnd,IDC_EDIT_EVAEXEPATH);
		m_PrmpathSubcls.InitSubcls(hWnd,IDC_EDIT_EVAPRMPATH);
		// 表示
		SetWindowText(m_hEditExepath, m_Exepath.data());
		SetWindowText(m_hEditPrmpath, m_Prmpath.data());

		return TRUE;
	}

	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			CommandProc
		[Purpose]
			コマンド系メッセージ処理
		[Parameter1] wParam
			コマンド系メッセージ
		[Returns]
			メッセージ処理の結果を返却
			返却値の意味は、送信されたメッセージによって異なります。
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual LRESULT CommandProc(const WPARAM wParam, const LPARAM lParam)
	{
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON_REF_EVAPATH:{// 実行ファイルまでのパス
			const std::vector<String> path = GFunc::FileSelectDlg(m_hDlg,_T("exeファイルを開く"),TEXT("EXE {*.exe}\0*.exe\0"),_T("EXE"));
			if(path.size() < 1) return FALSE;
			SetWindowText(m_hEditExepath, path[0].data());
			break;}
		case IDC_BUTTON_REF_PRMPATH:{// パラメータファイルまでのパス
			const std::vector<String> path = GFunc::FileSelectDlg(m_hDlg,_T("dcファイルを開く"),TEXT("DC11 {*.dc11}")TEXT("DC9 {*.dc9}")TEXT("DC7 {*.dc7}")TEXT("DC5 {*.dc5}"),_T("DC"));
			if(path.size() < 1) return FALSE;
			SetWindowText(m_hEditPrmpath, path[0].data());
			break;}
		case IDOK:{// OK
			TCHAR exe[MAX_PATH] = {0};
			TCHAR prm[MAX_PATH] = {0};
			GetWindowText(m_hEditExepath, (LPTSTR)exe, MAX_PATH);
			GetWindowText(m_hEditPrmpath, (LPTSTR)prm, MAX_PATH);
			m_Exepath = exe;
			m_Prmpath = prm;
			EndDialog(m_hDlg, IDOK);
			break;}
		case IDCANCEL:{// 終了
			EndDialog(m_hDlg, IDCANCEL);
			break;}
		}
		return FALSE;
	}

};




/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CInputdataDialog
	[Purpose]
		入力データ情報を設定するダイアログ
\////////////////////////////////////////////////////////////////////////////*/
class CInputdataDialog : public CModalDlg
{

/* Constructor / Destructor */
public:
	CInputdataDialog(void)
		:CModalDlg(IDD_INPUTDATA_DIALOG)
		,m_hEditWidth(NULL)
		,m_hEditHeight(NULL)
		,m_hEditBit(NULL)
		,m_hEditHeader(NULL)
		,m_hRadioR(NULL)
		,m_hRadioGr(NULL)
		,m_hRadioGb(NULL)
		,m_hRadioB(NULL)
		,m_hRadioUp(NULL)
		,m_hRadioDown(NULL)
		,m_hRadioBig(NULL)
		,m_hRadioLittle(NULL)
	{
		_tsetlocale(LC_ALL, _T("Japanese"));
	};
	CInputdataDialog(InputdataInfo& pInputdatainfo)
		:CModalDlg(IDD_INPUTDATA_DIALOG)
	{
		CInputdataDialog();
		m_Inputdatainfo = pInputdatainfo;
	};
	~CInputdataDialog(void)
	{
	};

	
private:
	// コントロールのウインドウハンドル
	HWND m_hEditWidth;
	HWND m_hEditHeight;
	HWND m_hEditBit;
	HWND m_hEditHeader;
	HWND m_hRadioR;
	HWND m_hRadioGr;
	HWND m_hRadioGb;
	HWND m_hRadioB;
	HWND m_hRadioUp;
	HWND m_hRadioDown;
	HWND m_hRadioBig;
	HWND m_hRadioLittle;

	// 入力データ情報
	InputdataInfo m_Inputdatainfo;


public:
	// 入力データ情報の参照を得る
	inline const InputdataInfo& GetInputdatainfo() const { return m_Inputdatainfo; };


	/*****************************************************************************\
		[Function]
			GetStartcolorStr
		[Purpose]
			先頭色番号に応じた文字列を取得する
		[Parameter1] color
			色番号指定(R:0, Gr:1, Gb:2, B:3)
		[Returns]
			文字列の確保に成功したポインタを返却
	\*****************************************************************************/
	static const TCHAR* GetStartcolorStr(const unsigned int& color)
	{
		switch(color)
		{
		case 0:
			return _T("R");
		case 1:
			return _T("Gr");
		case 2:
			return _T("Gb");
		case 3:
			return _T("B");
		}
		return NULL;
	}


	/*****************************************************************************\
		[Function]
			GetStartcolorInt
		[Purpose]
			先頭色文字列に応じた番号を取得する
		[Parameter1] color
			先頭色文字列
		[Returns]
			色番号を返却(R:0, Gr:1, Gb:2, B:3, 不明:-1)
	\*****************************************************************************/
	static int GetStartcolorInt(const TCHAR* const color)
	{
		if(!lstrcmpi(color, _T("R")))
			return 0;
		else if(!lstrcmpi(color, _T("Gr")))
			return 1;
		else if(!lstrcmpi(color, _T("Gb")))
			return 2;
		else if(!lstrcmpi(color, _T("B")))
			return 3;
		else
			return -1;
	}


	/*****************************************************************************\
		[Function]
			GetDatavectorStr
		[Purpose]
			詰め方向番号に応じた文字列を取得する
		[Parameter1] vector
			番号指定(Up:0, Down:1)
		[Returns]
			文字列の確保に成功したポインタを返却
	\*****************************************************************************/
	static const TCHAR* GetDatavectorStr(const unsigned int& vector)
	{
		switch(vector)
		{
		case 0:
			return _T("UP");
		case 1:
			return _T("DOWN");
		}
		return NULL;
	}


	/*****************************************************************************\
		[Function]
			GetDatavectorInt
		[Purpose]
			詰め方向文字列に応じた番号を取得する
		[Parameter1] vector
			詰め方向文字列
		[Returns]
			詰め方向番号を返却(UP:0, DOWN:1, 不明:-1)
	\*****************************************************************************/
	static int GetDatavectorInt(const TCHAR* const vector)
	{
		if(!lstrcmpi(vector, _T("UP")))
			return 0;
		else if(!lstrcmpi(vector, _T("DOWN")))
			return 1;
		else
			return -1;
	}


	/*****************************************************************************\
		[Function]
			GetEndianStr
		[Purpose]
			エンディアン番号に応じた文字列を取得する
		[Parameter1] endian
			番号指定(Big:0, Little:1)
		[Returns]
			文字列の確保に成功したポインタを返却
	\*****************************************************************************/
	static const TCHAR* GetEndianStr(const unsigned int& endian)
	{
		switch(endian)
		{
		case 0:
			return _T("BIG");
		case 1:
			return _T("LITTLE");
		}
		return NULL;
	}


	/*****************************************************************************\
		[Function]
			GetEndianInt
		[Purpose]
			エンディアン文字列に応じた番号を取得する
		[Parameter1] endian
			エンディアン文字列
		[Returns]
			エンディアン番号を返却(BIG:0, LITTLE:1, 不明:-1)
	\*****************************************************************************/
	static int GetEndianInt(const TCHAR* const endian)
	{
		if(!lstrcmpi(endian, _T("BIG")))
			return 0;
		else if(!lstrcmpi(endian, _T("LITTLE")))
			return 1;
		else
			return -1;
	}


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
		// 既存のコントロールからハンドルを取得
		m_hEditWidth = GetDlgItem(hWnd, IDC_EDIT_WIDTH);
		m_hEditHeight = GetDlgItem(hWnd, IDC_EDIT_HEIGHT);
		m_hEditBit = GetDlgItem(hWnd, IDC_EDIT_BIT);
		m_hEditHeader = GetDlgItem(hWnd, IDC_EDIT_HEADER);
		m_hRadioR = GetDlgItem(hWnd, IDC_RADIO_R);
		m_hRadioGr = GetDlgItem(hWnd, IDC_RADIO_GR);
		m_hRadioGb = GetDlgItem(hWnd, IDC_RADIO_GB);
		m_hRadioB = GetDlgItem(hWnd, IDC_RADIO_B);
		m_hRadioUp = GetDlgItem(hWnd, IDC_RADIO_UP);
		m_hRadioDown = GetDlgItem(hWnd, IDC_RADIO_DOWN);
		m_hRadioBig = GetDlgItem(hWnd, IDC_RADIO_BIG);
		m_hRadioLittle = GetDlgItem(hWnd, IDC_RADIO_LITTLE);
		// 初期値挿入
		SetWindowText(m_hEditWidth, GFunc::LToStr(m_Inputdatainfo.width).c_str());
		SetWindowText(m_hEditHeight, GFunc::LToStr(m_Inputdatainfo.height).c_str());
		SetWindowText(m_hEditBit, GFunc::LToStr(m_Inputdatainfo.bit).c_str());
		SetWindowText(m_hEditHeader, GFunc::LToStr(m_Inputdatainfo.headersize).c_str());
		SetCheckStartcolor(m_Inputdatainfo.startcolor);
		SetCheckDatavector(m_Inputdatainfo.datavector);
		SetCheckEndian(m_Inputdatainfo.endian);

		return TRUE;
	}


	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			CommandProc
		[Purpose]
			コマンド系メッセージ処理
		[Parameter1] wParam
			コマンド系メッセージ
		[Returns]
			メッセージ処理の結果を返却
			返却値の意味は、送信されたメッセージによって異なります。
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual LRESULT CommandProc(const WPARAM wParam, const LPARAM lParam)
	{
		switch(LOWORD(wParam))
		{
		case IDOK:{// OK
			m_Inputdatainfo.startcolor = GetCheckStartcolor();
			m_Inputdatainfo.datavector = GetCheckDatavector();
			m_Inputdatainfo.endian = GetCheckEndian();
			{// 幅
				TCHAR width[MAX_PATH] = {0};
				GetWindowText(m_hEditWidth, (LPTSTR)width, MAX_PATH);
				m_Inputdatainfo.width = GFunc::StrToL(width);
			}
			{// 高さ
				TCHAR height[MAX_PATH] = {0};
				GetWindowText(m_hEditHeight, (LPTSTR)height, MAX_PATH);
				m_Inputdatainfo.height = GFunc::StrToL(height);
			}
			{// ビット
				TCHAR bit[MAX_PATH] = {0};
				GetWindowText(m_hEditBit, (LPTSTR)bit, MAX_PATH);
				m_Inputdatainfo.bit = GFunc::StrToL(bit);
			}
			{// ヘッダ
				TCHAR header[MAX_PATH] = {0};
				GetWindowText(m_hEditHeader, (LPTSTR)header, MAX_PATH);
				m_Inputdatainfo.headersize = GFunc::StrToL(header);
			}
			EndDialog(m_hDlg, IDOK);
			break;}
		case IDCANCEL:{// 終了
			EndDialog(m_hDlg, IDCANCEL);
			break;}
		}
		return FALSE;
	}

private:
	/*----------------------------------------------------------------------------\
		[Function]
			SetCheckStartcolor
		[Purpose]
			先頭色のラジオボタンへチェックを入れる
		[Parameter1] color
			チェック色指定(R:0, Gr:1, Gb:2, B:3)
	\----------------------------------------------------------------------------*/
	void SetCheckStartcolor(const unsigned int& color)
	{
		SendMessage(m_hRadioR, BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(m_hRadioGr, BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(m_hRadioGb, BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(m_hRadioB, BM_SETCHECK, BST_UNCHECKED, 0);
		switch(color)
		{
		case 0:
			SendMessage(m_hRadioR, BM_SETCHECK, BST_CHECKED, 0);
			break;
		case 1:
			SendMessage(m_hRadioGr, BM_SETCHECK, BST_CHECKED, 0);
			break;
		case 2:
			SendMessage(m_hRadioGb, BM_SETCHECK, BST_CHECKED, 0);
			break;
		case 3:
			SendMessage(m_hRadioB, BM_SETCHECK, BST_CHECKED, 0);
			break;
		}
	}


	/*----------------------------------------------------------------------------\
		[Function]
			GetCheckStartcolor
		[Purpose]
			先頭色のラジオボタンよりチェック色を取得する
		[Returns]
			先頭色番号(R:0, Gr:1, Gb:2, B:3, 不明:-1)
	\----------------------------------------------------------------------------*/
	int GetCheckStartcolor(void)
	{
		int ret[4] = {0};
		ret[0] = (int)SendMessage(m_hRadioR, BM_GETCHECK, 0, 0);
		ret[1] = (int)SendMessage(m_hRadioGr, BM_GETCHECK, 0, 0);
		ret[2] = (int)SendMessage(m_hRadioGb, BM_GETCHECK, 0, 0);
		ret[3] = (int)SendMessage(m_hRadioB, BM_GETCHECK, 0, 0);
		for(int i=0; i<sizeof(ret)/sizeof(ret[0]); i++){
			if(ret[i] == BST_CHECKED)
				return i;
		}
		return -1;
	}


	/*----------------------------------------------------------------------------\
		[Function]
			SetCheckDatavector
		[Purpose]
			データ詰め方向のラジオボタンへチェックを入れる
		[Parameter1] vector
			チェック値指定(Up:0, Down:1)
	\----------------------------------------------------------------------------*/
	void SetCheckDatavector(const unsigned int& vector)
	{
		SendMessage(m_hRadioUp, BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(m_hRadioDown, BM_SETCHECK, BST_UNCHECKED, 0);
		switch(vector)
		{
		case 0:
			SendMessage(m_hRadioUp, BM_SETCHECK, BST_CHECKED, 0);
			break;
		case 1:
			SendMessage(m_hRadioDown, BM_SETCHECK, BST_CHECKED, 0);
			break;
		}
	}


	/*----------------------------------------------------------------------------\
		[Function]
			GetCheckDatavector
		[Purpose]
			データ詰め方向のラジオボタンより詰め方向を取得する
		[Returns]
			詰め方向番号(Up:0, Down:1, 不明:-1)
	\----------------------------------------------------------------------------*/
	int GetCheckDatavector(void)
	{
		int ret[2] = {0};
		ret[0] = (int)SendMessage(m_hRadioUp, BM_GETCHECK, 0, 0);
		ret[1] = (int)SendMessage(m_hRadioDown, BM_GETCHECK, 0, 0);
		for(int i=0; i<sizeof(ret)/sizeof(ret[0]); i++){
			if(ret[i] == BST_CHECKED)
				return i;
		}
		return -1;
	}


	/*----------------------------------------------------------------------------\
		[Function]
			SetCheckEndian
		[Purpose]
			エンディアンのラジオボタンへチェックを入れる
		[Parameter1] endian
			チェック値指定(Big:0, Little:1)
	\----------------------------------------------------------------------------*/
	void SetCheckEndian(const unsigned int& endian)
	{
		SendMessage(m_hRadioBig, BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(m_hRadioLittle, BM_SETCHECK, BST_UNCHECKED, 0);
		switch(endian)
		{
		case 0:
			SendMessage(m_hRadioBig, BM_SETCHECK, BST_CHECKED, 0);
			break;
		case 1:
			SendMessage(m_hRadioLittle, BM_SETCHECK, BST_CHECKED, 0);
			break;
		}
	}


	/*----------------------------------------------------------------------------\
		[Function]
			GetCheckEndian
		[Purpose]
			エンディアンのラジオボタンよりエンディアンを取得する
		[Returns]
			エンディアン番号(Big:0, Little:1, 不明:-1)
	\----------------------------------------------------------------------------*/
	int GetCheckEndian(void)
	{
		int ret[2] = {0};
		ret[0] = (int)SendMessage(m_hRadioBig, BM_GETCHECK, 0, 0);
		ret[1] = (int)SendMessage(m_hRadioLittle, BM_GETCHECK, 0, 0);
		for(int i=0; i<sizeof(ret)/sizeof(ret[0]); i++){
			if(ret[i] == BST_CHECKED)
				return i;
		}
		return -1;
	}

};
