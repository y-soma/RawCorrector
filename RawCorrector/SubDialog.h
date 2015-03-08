#pragma once

/* �q�_�C�A���O��`�ꏊ */


/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CEvasetDialog
	[Purpose]
		Eva�̃p�X��ݒ肷��_�C�A���O
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
	// �R���g���[���̃E�C���h�E�n���h��
	HWND m_hEditExepath;
	HWND m_hEditPrmpath;
	// ���s�p�X�G�f�B�b�g�̃T�u�N���X���Ǘ�
	CEditSubcls m_ExepathSubcls;
	// �p�����[�^�p�X�G�f�B�b�g�̃T�u�N���X���Ǘ�
	CEditSubcls m_PrmpathSubcls;
	// exe�p�X��ێ�
	String m_Exepath;
	// prm�p�X��ێ�
	String m_Prmpath;


public:
	/*****************************************************************************\
		[Function]
			Setpath
		[Purpose]
			�p�X�������o�ϐ��փZ�b�g����
		[Parameter1] exe
			exe�p�X
		[Parameter2] prm
			prm�p�X
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
			���̃��W���[�����ŕύX����exe�p�X���擾����
	\*****************************************************************************/
	inline const String& GetExepath() const { return m_Exepath; }

	/*****************************************************************************\
		[Function]
			GetPrmpath
		[Purpose]
			���̃��W���[�����ŕύX����prm�p�X���擾����
	\*****************************************************************************/
	inline const String& GetPrmpath() const { return m_Prmpath; }


protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			OnInitDialog
		[Purpose]
			�_�C�A���O������
		[Returns]
			TRUE��ԋp
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual BOOL OnInitDialog(const HWND hWnd, const HWND hwndFocus, const LPARAM lParam)
	{
		// �����̃R���g���[������n���h�����擾
		m_hEditExepath = GetDlgItem(hWnd,IDC_EDIT_EVAEXEPATH);
		m_hEditPrmpath = GetDlgItem(hWnd,IDC_EDIT_EVAPRMPATH);
		// �T�u�N���X��
		m_ExepathSubcls.InitSubcls(hWnd,IDC_EDIT_EVAEXEPATH);
		m_PrmpathSubcls.InitSubcls(hWnd,IDC_EDIT_EVAPRMPATH);
		// �\��
		SetWindowText(m_hEditExepath, m_Exepath.data());
		SetWindowText(m_hEditPrmpath, m_Prmpath.data());

		return TRUE;
	}

	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			CommandProc
		[Purpose]
			�R�}���h�n���b�Z�[�W����
		[Parameter1] wParam
			�R�}���h�n���b�Z�[�W
		[Returns]
			���b�Z�[�W�����̌��ʂ�ԋp
			�ԋp�l�̈Ӗ��́A���M���ꂽ���b�Z�[�W�ɂ���ĈقȂ�܂��B
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual LRESULT CommandProc(const WPARAM wParam, const LPARAM lParam)
	{
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON_REF_EVAPATH:{// ���s�t�@�C���܂ł̃p�X
			const std::vector<String> path = GFunc::FileSelectDlg(m_hDlg,_T("exe�t�@�C�����J��"),TEXT("EXE {*.exe}\0*.exe\0"),_T("EXE"));
			if(path.size() < 1) return FALSE;
			SetWindowText(m_hEditExepath, path[0].data());
			break;}
		case IDC_BUTTON_REF_PRMPATH:{// �p�����[�^�t�@�C���܂ł̃p�X
			const std::vector<String> path = GFunc::FileSelectDlg(m_hDlg,_T("dc�t�@�C�����J��"),TEXT("DC11 {*.dc11}")TEXT("DC9 {*.dc9}")TEXT("DC7 {*.dc7}")TEXT("DC5 {*.dc5}"),_T("DC"));
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
		case IDCANCEL:{// �I��
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
		���̓f�[�^����ݒ肷��_�C�A���O
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
	// �R���g���[���̃E�C���h�E�n���h��
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

	// ���̓f�[�^���
	InputdataInfo m_Inputdatainfo;


public:
	// ���̓f�[�^���̎Q�Ƃ𓾂�
	inline const InputdataInfo& GetInputdatainfo() const { return m_Inputdatainfo; };


	/*****************************************************************************\
		[Function]
			GetStartcolorStr
		[Purpose]
			�擪�F�ԍ��ɉ�������������擾����
		[Parameter1] color
			�F�ԍ��w��(R:0, Gr:1, Gb:2, B:3)
		[Returns]
			������̊m�ۂɐ��������|�C���^��ԋp
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
			�擪�F������ɉ������ԍ����擾����
		[Parameter1] color
			�擪�F������
		[Returns]
			�F�ԍ���ԋp(R:0, Gr:1, Gb:2, B:3, �s��:-1)
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
			�l�ߕ����ԍ��ɉ�������������擾����
		[Parameter1] vector
			�ԍ��w��(Up:0, Down:1)
		[Returns]
			������̊m�ۂɐ��������|�C���^��ԋp
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
			�l�ߕ���������ɉ������ԍ����擾����
		[Parameter1] vector
			�l�ߕ���������
		[Returns]
			�l�ߕ����ԍ���ԋp(UP:0, DOWN:1, �s��:-1)
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
			�G���f�B�A���ԍ��ɉ�������������擾����
		[Parameter1] endian
			�ԍ��w��(Big:0, Little:1)
		[Returns]
			������̊m�ۂɐ��������|�C���^��ԋp
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
			�G���f�B�A��������ɉ������ԍ����擾����
		[Parameter1] endian
			�G���f�B�A��������
		[Returns]
			�G���f�B�A���ԍ���ԋp(BIG:0, LITTLE:1, �s��:-1)
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
			�_�C�A���O������
		[Returns]
			TRUE��ԋp
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual BOOL OnInitDialog(const HWND hWnd, const HWND hwndFocus, const LPARAM lParam)
	{
		// �����̃R���g���[������n���h�����擾
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
		// �����l�}��
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
			�R�}���h�n���b�Z�[�W����
		[Parameter1] wParam
			�R�}���h�n���b�Z�[�W
		[Returns]
			���b�Z�[�W�����̌��ʂ�ԋp
			�ԋp�l�̈Ӗ��́A���M���ꂽ���b�Z�[�W�ɂ���ĈقȂ�܂��B
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual LRESULT CommandProc(const WPARAM wParam, const LPARAM lParam)
	{
		switch(LOWORD(wParam))
		{
		case IDOK:{// OK
			m_Inputdatainfo.startcolor = GetCheckStartcolor();
			m_Inputdatainfo.datavector = GetCheckDatavector();
			m_Inputdatainfo.endian = GetCheckEndian();
			{// ��
				TCHAR width[MAX_PATH] = {0};
				GetWindowText(m_hEditWidth, (LPTSTR)width, MAX_PATH);
				m_Inputdatainfo.width = GFunc::StrToL(width);
			}
			{// ����
				TCHAR height[MAX_PATH] = {0};
				GetWindowText(m_hEditHeight, (LPTSTR)height, MAX_PATH);
				m_Inputdatainfo.height = GFunc::StrToL(height);
			}
			{// �r�b�g
				TCHAR bit[MAX_PATH] = {0};
				GetWindowText(m_hEditBit, (LPTSTR)bit, MAX_PATH);
				m_Inputdatainfo.bit = GFunc::StrToL(bit);
			}
			{// �w�b�_
				TCHAR header[MAX_PATH] = {0};
				GetWindowText(m_hEditHeader, (LPTSTR)header, MAX_PATH);
				m_Inputdatainfo.headersize = GFunc::StrToL(header);
			}
			EndDialog(m_hDlg, IDOK);
			break;}
		case IDCANCEL:{// �I��
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
			�擪�F�̃��W�I�{�^���փ`�F�b�N������
		[Parameter1] color
			�`�F�b�N�F�w��(R:0, Gr:1, Gb:2, B:3)
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
			�擪�F�̃��W�I�{�^�����`�F�b�N�F���擾����
		[Returns]
			�擪�F�ԍ�(R:0, Gr:1, Gb:2, B:3, �s��:-1)
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
			�f�[�^�l�ߕ����̃��W�I�{�^���փ`�F�b�N������
		[Parameter1] vector
			�`�F�b�N�l�w��(Up:0, Down:1)
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
			�f�[�^�l�ߕ����̃��W�I�{�^�����l�ߕ������擾����
		[Returns]
			�l�ߕ����ԍ�(Up:0, Down:1, �s��:-1)
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
			�G���f�B�A���̃��W�I�{�^���փ`�F�b�N������
		[Parameter1] endian
			�`�F�b�N�l�w��(Big:0, Little:1)
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
			�G���f�B�A���̃��W�I�{�^�����G���f�B�A�����擾����
		[Returns]
			�G���f�B�A���ԍ�(Big:0, Little:1, �s��:-1)
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
