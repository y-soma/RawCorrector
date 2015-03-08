#pragma once

// CMainDialog : ��`

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
		���C���_�C�A���O
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
	// GUI�R���g���[���̃E�C���h�E�n���h��
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
	// �t�@�C�����X�g�̃T�u�N���X���Ǘ�
	CListSubcls m_FilelistSubcls;
	// �������W���[��
	CProcBase** m_pProc;
	// �������ڃJ�E���g
	int m_iProcCount;
	// ���̓f�[�^���
	InputdataInfo m_Inputdatainfo;
	// Eva�p�X���
	const TCHAR* m_Evaexepath;
	const TCHAR* m_Evaprmpath;
	// �������ڑI���C���f�b�N�X��ێ�
	int m_SelectProcIndex_Old;
	int m_SelectProcIndex_Old2;


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
		{// �_�C�A���O�̑薼
			String title = _T("RAW�␳�V�~�����[�^  (Version ");
			title += VERSION;
			title += _T(")");
			SetWindowText(hWnd,title.data());
		}
		// �����̃R���g���[������n���h�����擾
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
		FaildComment += _T(" �̓ǂݍ��݂Ɏ��s���܂���");
		// �擪�F
		const String startcolor = GFunc::GetIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("startcolor"));
		m_Inputdatainfo.startcolor = (unsigned char)GFunc::StrToL(startcolor.data());
		if(startcolor == _T("")){
			ReadFaild = TRUE;
			FaildComment += _T("\n���擪�F��ǂݍ��߂܂���ł���");
		}
		// �l�ߕ���
		const String datavector = GFunc::GetIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("datavector"));
		m_Inputdatainfo.datavector = (unsigned char)GFunc::StrToL(datavector.data());
		if(datavector == _T("")){
			ReadFaild = TRUE;
			FaildComment += _T("\n���l�ߕ�����ǂݍ��߂܂���ł���");
		}
		// �G���f�B�A��
		const String endian = GFunc::GetIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("endian"));
		m_Inputdatainfo.endian = (unsigned char)GFunc::StrToL(endian.data());
		if(endian == _T("")){
			ReadFaild = TRUE;
			FaildComment += _T("\n���G���f�B�A����ǂݍ��߂܂���ł���");
		}
		// �ݒ���̃Z�b�g
		const String width = GFunc::GetIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("width"));
		m_Inputdatainfo.width = GFunc::StrToL(width.data());
		if(!m_Inputdatainfo.width){
			ReadFaild = TRUE;
			FaildComment += _T("\n�����������T�C�Y��ǂݍ��߂܂���ł���");
		}
		const String height = GFunc::GetIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("height"));
		m_Inputdatainfo.height = GFunc::StrToL(height.data());
		if(!m_Inputdatainfo.height){
			ReadFaild = TRUE;
			FaildComment += _T("\n�����������T�C�Y��ǂݍ��߂܂���ł���");
		}
		const String bit = GFunc::GetIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("bit"));
		m_Inputdatainfo.bit = GFunc::StrToL(bit.data());
		if(!m_Inputdatainfo.bit){
			ReadFaild = TRUE;
			FaildComment += _T("\n���r�b�g��ǂݍ��߂܂���ł���");
		}
		const String header = GFunc::GetIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("header"));
		m_Inputdatainfo.headersize = GFunc::StrToL(header.data());
		if(!m_Inputdatainfo.headersize){
			ReadFaild = TRUE;
			FaildComment += _T("\n���w�b�_�T�C�Y��ǂݍ��߂܂���ł���");
		}
		const String exe = GFunc::GetIniParam(INI_FILENAME, _T("EVA_PATH"), _T("exe"));
		m_Evaexepath = GFunc::StrCopy(exe.data(), (ULONG)exe.length());
		if(!m_Evaexepath){
			ReadFaild = TRUE;
			FaildComment += _T("\n��Eva���s�p�X��ǂݍ��߂܂���ł���");
		}
		const String prm = GFunc::GetIniParam(INI_FILENAME, _T("EVA_PATH"), _T("prm"));
		m_Evaprmpath = GFunc::StrCopy(prm.data(), (ULONG)prm.length());
		if(!m_Evaprmpath){
			ReadFaild = TRUE;
			FaildComment += _T("\n��Eva�p�����[�^�p�X��ǂݍ��߂܂���ł���");
		}

		if(ReadFaild){
			MessageBox(NULL, FaildComment.data(), NULL, MB_OK | MB_ICONERROR);
			EndDialog(hWnd, FALSE);
		}
		
		UpdateGUI();

		//_T("5200,3568,Gr,UP,LITTLE,12,0,");
		

		// ���X�g�R���g���[���̏�����
		std::vector<String> caption(0,_T(""));
		std::vector<double> mag(0,0.0);
		{// �t�@�C�����X�g������
			caption.clear();
			caption.push_back(_T("FileName"));
			caption.push_back(_T("Dir"));
			mag.clear();
			mag.push_back(0.4);
			mag.push_back(0.59);
			InitList(m_hFileList, caption, mag);
		}
		{// �������X�g������
			caption.clear();
			caption.push_back(_T("����"));
			caption.push_back(_T("��������"));
			mag.clear();
			mag.push_back(0.16);
			mag.push_back(0.825);
			InitList(m_hProcList, caption, mag);
		}
		{// �p�����[�^���X�g������
			caption.clear();
			caption.push_back(_T("Name"));
			caption.push_back(_T("Value"));
			mag.clear();
			mag.push_back(0.35);
			mag.push_back(0.64);
			InitList(m_hPrmList, caption, mag);
		}

		// �t�@�C�����X�g�̃T�u�N���X��
		m_FilelistSubcls.InitSubcls(hWnd, IDC_FILE_LIST);
		
		return TRUE;
	}


	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			CommandProc
		[Purpose]
			�R�}���h�n���b�Z�[�W����
		[Parameter1] wParam
			�R�}���h�n���b�Z�[�W
		[Parameter2] lParam
			�R�}���h�n���b�Z�[�W
		[Returns]
			���b�Z�[�W�����̌��ʂ�ԋp
			�ԋp�l�̈Ӗ��́A���M���ꂽ���b�Z�[�W�ɂ���ĈقȂ�܂��B
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual LRESULT CommandProc(const WPARAM wParam, const LPARAM lParam)
	{
		switch(LOWORD(wParam))
		{
		case ID_OPEN:{// ���j���[����t�@�C�����J��
			std::vector<String> path = m_FilelistSubcls.GetDropPath();
			std::vector<String> ext(0,_T(""));
			ext.push_back(_T(".raw"));
			GFunc::AddListItem(m_hFileList, path, GFunc::FileSelectDlg(m_hDlg,_T("RAW�t�@�C�����J��"),TEXT("RAW {*.RAW}\0*.raw\0"),_T("RAW")), ext);
			m_FilelistSubcls.SetDropPath(path);
			break;}
		case IDC_BUTTON_PHASEDIFF:{// �ʑ���RAW
			AddProc(CProcBase::PK_PHASEDIFF);
			break;}
		case IDC_BUTTON_GAIN:{// �Q�C���␳
			AddProc(CProcBase::PK_GAIN_COMPE);
			break;}
		case IDC_BUTTON_FHDMONITOR:{// FHD MonitorRAW
			AddProc(CProcBase::PK_FHD_MONITOR);
			break;}
		case IDC_BUTTON_PIXELCORRECT:{// ��f�␳
			AddProc(CProcBase::PK_PIXEL_COMPE);
			break;}
		case IDC_BUTTON_OPTICAXIS:{// �����␳
			AddProc(CProcBase::PK_OPTICAXIS);
			break;}
		case IDC_BUTTON_DEVELOP:{// ����
			AddProc(CProcBase::PK_DEVELOP);
			break;}
		case IDC_BUTTON_PROCTURNCHANGE_UP:{// ���������߂�
			SwapProcOrder(0);
			break;}
		case IDC_BUTTON_PROCTURNCHANGE_DOWN:{// �������x�߂�
			SwapProcOrder(1);
			break;}
		case IDC_BUTTON_CLEAR:{// �������ڂ���폜
			DeleteProc();
			ListView_DeleteAllItems(m_hPrmList);
			m_SelectProcIndex_Old = -1;
			break;}
		case IDC_BUTTON_ALLCLEAR:{// �������ڂ�S�č폜
			// ���X�g�͑S�ď���
			ListView_DeleteAllItems(m_hProcList);
			ListView_DeleteAllItems(m_hPrmList);
			// �����f�[�^���N���A
			m_iProcCount = 0;
			m_pProc = (CProcBase**)malloc(sizeof(CProcBase*) * m_iProcCount);
			m_SelectProcIndex_Old = -1;
			break;}
		case IDC_BUTTON_PROCREGISTR:{// �\������Ă��鏈�����e��o�^
			//SetWindowText(m_hPrmEdit, _T("���e�X�g�}��"));
			break;}
		case IDC_BUTTON_PRM_WRITE:{// GUI�\�����̃p�����[�^��ini�t�@�C���֏�������
			if(m_SelectProcIndex_Old == -1)
				break;
			const CParamData& prm = m_pProc[m_SelectProcIndex_Old]->GetParam();
			String mes = _T("�\������ \"");
			mes += prm.GetProcname();
			mes += _T("\" �̃p�����[�^��ini�t�@�C���֏������݂܂��B��낵���ł���?");
			if(MessageBox(NULL, mes.c_str(), _T("�m�F"), MB_YESNO|MB_ICONQUESTION) == IDNO)
				break;
			const std::vector<ParamValue>& val = prm.GetParamValue();
			for(UINT i=0; i<val.size(); i++)
				GFunc::WriteIniParam(INI_FILENAME, prm.GetSectionName(), val[i].param_name, val[i].val);
			break;}
		case IDC_BUTTON_INPUTDATA_EDIT:{// ���̓f�[�^�T�C�Y�ύX
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
		case IDC_BUTTON_EVAPATH_EDIT:{// Eva�p�X�ύX
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
		case IDC_BUTTON_EXEC:{// ���s
			OnExecution();
			break;}
		case IDCANCEL: case ID_CLOSE:{// �I��
			OnCancel();
			break;}
		default:
			break;
		}
		
		if(lParam == (LPARAM)m_hPrmEdit)
		{// �G�f�B�b�g�{�b�N�X�ύX�C�x���g
			static String oldPrmEditTxt = _T("");
			switch(HIWORD(wParam))
			{
			case EN_UPDATE: // �ύX���O
				return FALSE;
			case EN_CHANGE:{ // �ύX����
				TCHAR str[MAX_PATH * 0x0F];
				GetWindowText(m_hPrmEdit, str, MAX_PATH * 0x0F);
				const String newPrmEditTxt = str;
				if(oldPrmEditTxt != newPrmEditTxt)
				{// �G�f�B�b�g�ɕҏW��������ꂽ��A���X�g�ƃf�[�^�����o�̓��e���A�b�v�f�[�g����
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
			�ʒm���b�Z�[�W�n���h��
		[Parameter1] id
			�ʒm���b�Z�[�W�𔭍s�����R���g���[��ID�B������Ahdr�\���̂�ID�̂ق������m�ł���B
		[Parameter2] hdr
			NMHDR�\���̂ւ̃|�C���^
		[Returns]
			���b�Z�[�W�Ɉˑ�����
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual INT_PTR OnNotify(const int& id, NMHDR* hdr)
	{
		// �������ڃ��X�g�I���C�x���g
		UpdateParamList();
		// �p�����[�^���X�g�I���C�x���g
		UpdateParamEdit();
		return FALSE;
	}


private:
	/*----------------------------------------------------------------------------\
		[Function]
			OnExecution
		[Purpose]
			���s
	\----------------------------------------------------------------------------*/
	void OnExecution(void)
	{
		// ������m�F
		for(int i=0; i<m_iProcCount; i++)
			m_pProc[i]->Execution();
	}
	
	
	/*----------------------------------------------------------------------------\
		[Function]
			InitList
		[Purpose]
			���X�g������
		[Parameter1] hList
			���X�g�R���g���[���ւ̃E�C���h�E�n���h��
		[Parameter2] caption
			�s�w�b�_�^�C�g���̎w��
		[Parameter3] mag
			�e��̃T�C�Y�{��
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
			{// ���X�g�R���g���[���̕��T�C�Y�擾
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
			�������ڂ���ǉ�����
		[Parameter1] proc_code
			�����R�[�h
		[Returns]
			���������TRUE��ԋp
	\----------------------------------------------------------------------------*/
	BOOL AddProc(const int& proc_code)
	{
		try
		{
			++m_iProcCount;

			// �����̈�쐬
			CProcBase**& p = m_pProc;
			CProcBase** backup = (CProcBase**)malloc(sizeof(CProcBase*) * (m_iProcCount-1));
			{// �V�����̈搔�ōĊm�ۂ���
				// �o�b�N�A�b�v�m��
				for(int i=0; i<m_iProcCount-1; i++)
					backup[i] = dynamic_cast<CProcBase*>(p[i]);
				// �V�̈�ֈڂ�
				p = (CProcBase**)malloc(sizeof(CProcBase*) * m_iProcCount);
				for(int i=0; i<m_iProcCount-1; i++)
					p[i] = backup[i];
			}
			
			String procname = _T("");
			switch(proc_code)
			{// �ǉ����ڂ͖ړI�̏����ɉ����ă_�E���L���X�g���s��
			case CProcBase::PK_PHASEDIFF:
				p[m_iProcCount-1] = new(std::nothrow) CProcPhasediff;
				procname = _T("�ʑ���RAW");
				break;
			case CProcBase::PK_GAIN_COMPE:
				p[m_iProcCount-1] = new(std::nothrow) CProcGaincompe;
				procname = _T("�Q�C���␳");
				break;
			case CProcBase::PK_FHD_MONITOR:
				p[m_iProcCount-1] = new(std::nothrow) CProcFHDMonitor;
				procname = _T("FHD_MonitorRAW");
				break;
			case CProcBase::PK_PIXEL_COMPE:
				p[m_iProcCount-1] = new(std::nothrow) CProcPixelcompe;
				procname = _T("��f�␳");
				break;
			case CProcBase::PK_OPTICAXIS:
				p[m_iProcCount-1] = new(std::nothrow) CProcOpticaxis;
				procname = _T("�����␳");
				break;
			case CProcBase::PK_DEVELOP:
				p[m_iProcCount-1] = new(std::nothrow) CProcDevelop;
				procname = _T("����");
				break;
			case CProcBase::PK_NONE:
			default:
				return FALSE;
			}
			p[m_iProcCount-1]->SetProcname(procname);
			// ���X�g�̍X�V
			GFunc::InsertSubItem(m_hProcList,m_iProcCount-1,0,GFunc::LToStr(m_iProcCount).data());
			GFunc::InsertSubItem(m_hProcList,m_iProcCount-1,1,procname.c_str());
			
			return TRUE;
		}
		catch(std::bad_cast)
		{
			MessageBox(NULL, _T("�������W���[���̃_�E���L���X�g�Ɏ��s���܂���"), NULL, MB_OK|MB_ICONERROR);
			return FALSE;
		}
		catch(...)
		{
			MessageBox(NULL, _T("�����f�[�^�̍쐬�Ɏ��s���܂���"), NULL, MB_OK|MB_ICONERROR);
			return FALSE;
		}
	}


	/*----------------------------------------------------------------------------\
		[Function]
			DeleteProc
		[Purpose]
			�����̈����폜���čX�V����
	\----------------------------------------------------------------------------*/
	void DeleteProc(void)
	{
		const int index = GetSelectedListIndex(m_hProcList);
		if(index == -1 || m_iProcCount < 1) return;
		
		CProcBase**& p = m_pProc;
		CProcBase** backup = (CProcBase**)malloc(sizeof(CProcBase*) * (m_iProcCount-1));
		{// �V�����̈搔�ōĊm�ۂ���
			// �o�b�N�A�b�v�m��
			int add = 0;
			for(int i=0; i<m_iProcCount; i++)
			{
				if(i == index) continue;
				backup[add] = p[i];
				++add;
			}
			// �V�̈�ֈڂ�
			p = (CProcBase**)malloc(sizeof(CProcBase*) * (m_iProcCount-1));
			for(int i=0; i<m_iProcCount-1; i++)
				p[i] = backup[i];
		}
		--m_iProcCount;
		
		// ���X�g�r���[�̍X�V
		ListView_DeleteItem(m_hProcList, index);
		for(int i=0; i<m_iProcCount; i++)
		{// �A�C�e���ԍ��`��
			const String num = GFunc::LToStr(i+1).c_str();
			const TCHAR* str = GFunc::StrCopy(num.c_str(), num.length());
			ListView_SetItemText(m_hProcList, i, 0, (LPTSTR)str);
		}
	}


	/*----------------------------------------------------------------------------\
		[Function]
			SwapProcOrder
		[Purpose]
			�������ڂ̏��Ԃ����ւ���
		[Parameter1] vect
			�ύX����(���Ԃ𑁂߂�:0 or �x������:1)
	\----------------------------------------------------------------------------*/
	void SwapProcOrder(const int& vect)
	{
		const UINT size = ListView_GetItemCount(m_hProcList);
		// 2�����̏ꍇ�A���בւ��̕K�v�Ȃ�
		if(size < 2 || size != m_iProcCount) return;
		for(UINT i=0; i<size; i++)
		{// �I����Ԃ̍��ڂ�����
			const UINT uiState = ListView_GetItemState(m_hProcList, i, LVIS_SELECTED);
			if(uiState & LVIS_SELECTED)
			{// ����ւ����
				// ��[�A���[�ɂ��邩�ǂ����`�F�b�N
				BOOL check = FALSE;
				int iItem = 0;
				if(!vect){// ���߂�
					check = !i;
					iItem = i - 1;
				}
				else if(vect == 1){// �x������
					check = i == (size - 1);
					iItem = i + 1;
				}
				if(check) break;
				{// �����f�[�^�̍X�V
					CProcBase**& p = m_pProc;
					CProcBase* swap1 = p[i];
					CProcBase* swap2 = p[iItem];
					p[i] = swap2;
					p[iItem] = swap1;
				}
				{// ���X�g�r���[�̍X�V
					// �Ώۂ̃e�L�X�g���e���ꎞ�ێ�
					TCHAR obj[_MAX_PATH * 0x0F];
					ListView_GetItemText(m_hProcList, i, 1, obj, sizeof(obj));
					TCHAR objbefor[_MAX_PATH * 0x0F];
					ListView_GetItemText(m_hProcList, iItem, 1, objbefor, sizeof(objbefor));
					// ����ւ�
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
			GUI�\�����ڂ̍X�V
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
			���̓f�[�^����ini�p�����[�^���e���X�V
	\----------------------------------------------------------------------------*/
	void UpdateIni_Inputdata(void)
	{
		// �擪�F
		GFunc::WriteIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("startcolor"), GFunc::LToStr(m_Inputdatainfo.startcolor).data());
		// �G���f�B�A��
		GFunc::WriteIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("endian"), GFunc::LToStr(m_Inputdatainfo.endian).data());
		// �l�ߕ���
		GFunc::WriteIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("datavector"), GFunc::LToStr(m_Inputdatainfo.datavector).data());
		// ��
		GFunc::WriteIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("width"), GFunc::LToStr(m_Inputdatainfo.width).data());
		// ����
		GFunc::WriteIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("height"), GFunc::LToStr(m_Inputdatainfo.height).data());
		// �r�b�g
		GFunc::WriteIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("bit"), GFunc::LToStr(m_Inputdatainfo.bit).data());
		// �w�b�_
		GFunc::WriteIniParam(INI_FILENAME, _T("INPUT_DATA"), _T("header"), GFunc::LToStr(m_Inputdatainfo.headersize).data());
	}


	/*----------------------------------------------------------------------------\
		[Function]
			UpdateIni_Evapath
		[Purpose]
			Eva�p�X��ini�p�����[�^���e���X�V
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
			���X�g�R���g���[���̑I����Ԃ̃A�C�e���C���f�b�N�X���擾����
		[Parameter1] hWnd
			���X�g�R���g���[���̃n���h��
		[Returns]
			�A�C�e���C���f�b�N�X��ԋp
	\----------------------------------------------------------------------------*/
	int GetSelectedListIndex(const HWND hWnd)
	{
		const int Cnt = ListView_GetSelectedCount(hWnd);
		if(Cnt > 0)
		{// �������ڃ��X�g�̑I����Ԃ����o
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
			���X�g�R���g���[���̑I����Ԃ𒲂ׂ�
		[Parameter1] hWnd
			���X�g�R���g���[���̃n���h��
		[Parameter2] old_select
			�I�����ꂽ�A�C�e���̕������ێ�
		[Returns]
			�O�ƕʂ̃A�C�e�����I�����ꂽ�ꍇ�̓A�C�e���C���f�b�N�X��ԋp
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
			�I�������������ڂɉ����ăp�����[�^�\�����X�g�̓��e���X�V����
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
			�I�������p�����[�^�ɉ����ăp�����[�^�ҏW�G�f�B�b�g�̓��e���X�V����
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
			�R���{�{�b�N�X������
		[Argument1] hDlg
			�E�C���h�E�n���h��
		[Return]
			�����FTRUE  ���s�FFALSE
	\----------------------------------------------------------------------------*/
	BOOL InitTaglistCombo(void)
	{
		std::map<ULONG,String> StdTag;
		CImgExif::InitStdTag(StdTag);
		const ULONG TagID[] =
		{// �����őI��Ώۂɂ���^�OID��C�ӂɓo�^����
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
			MessageBox(NULL,_T("""tagsetJ.xml""�̓ǂݍ��݂Ɏ��s���܂���"),_T("Error"), MB_OK | MB_ICONERROR);
			return FALSE;
		}
		/*{// xml����擾�������ōX�V����
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
		// ��Ԗڂ̃A�C�e����I��
		SendMessage(hCombo, CB_SETCURSEL,0,0);
		return TRUE;
	}
	
#endif

}; // CMainDialog


