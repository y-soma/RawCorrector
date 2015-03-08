#pragma once

// CMainDialog : ��`

#include "Interface.h"
#include "Dialog.h"
#include "resource.h"
#include "SubclsCtrl.h"
#include "SubDialog.h"

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
		,m_ProcCount(0)
	{
		_tsetlocale(LC_ALL, _T("Japanese"));
		m_Path.clear();
	};
	~CMainDialog(void)
	{
		free((void*)m_Evaexepath);
		free((void*)m_Evaprmpath);
	};


protected:
	std::vector<String> m_Path;
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
	// �������ڂ̃J�E���g
	int m_ProcCount;
	// ���̓f�[�^���
	InputdataInfo m_Inputdatainfo;

	const TCHAR* m_Evaexepath;
	const TCHAR* m_Evaprmpath;


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
		String FaildComment = _T("RawCorrector.ini �̓ǂݍ��݂Ɏ��s���܂���");
		// �擪�F
		const String startcolor = GFunc::GetIniParam(_T("RawCorrector.ini"), _T("INPUT_DATA"), _T("startcolor"));
		m_Inputdatainfo.startcolor = CInputdataDialog::GetStartcolorStr(GFunc::StrToL(startcolor.data()));
		if(startcolor == _T("")){
			ReadFaild = TRUE;
			FaildComment += _T("\n���擪�F��ǂݍ��߂܂���ł���");
		}
		// �l�ߕ���
		const String datavector = GFunc::GetIniParam(_T("RawCorrector.ini"), _T("INPUT_DATA"), _T("datavector"));
		m_Inputdatainfo.datavector = CInputdataDialog::GetDatavectorStr(GFunc::StrToL(datavector.data()));
		if(datavector == _T("")){
			ReadFaild = TRUE;
			FaildComment += _T("\n���l�ߕ�����ǂݍ��߂܂���ł���");
		}
		// �G���f�B�A��
		const String endian = GFunc::GetIniParam(_T("RawCorrector.ini"), _T("INPUT_DATA"), _T("endian"));
		m_Inputdatainfo.endian = CInputdataDialog::GetEndianStr(GFunc::StrToL(endian.data()));
		if(endian == _T("")){
			ReadFaild = TRUE;
			FaildComment += _T("\n���G���f�B�A����ǂݍ��߂܂���ł���");
		}
		// �ݒ���̃Z�b�g
		const String width = GFunc::GetIniParam(_T("RawCorrector.ini"), _T("INPUT_DATA"), _T("width"));
		m_Inputdatainfo.width = GFunc::StrCopy(width.data(), (ULONG)width.length());
		if(!m_Inputdatainfo.width){
			ReadFaild = TRUE;
			FaildComment += _T("\n�����������T�C�Y��ǂݍ��߂܂���ł���");
		}
		const String height = GFunc::GetIniParam(_T("RawCorrector.ini"), _T("INPUT_DATA"), _T("height"));
		m_Inputdatainfo.height = GFunc::StrCopy(height.data(), (ULONG)height.length());
		if(!m_Inputdatainfo.height){
			ReadFaild = TRUE;
			FaildComment += _T("\n�����������T�C�Y��ǂݍ��߂܂���ł���");
		}
		const String bit = GFunc::GetIniParam(_T("RawCorrector.ini"), _T("INPUT_DATA"), _T("bit"));
		m_Inputdatainfo.bit = GFunc::StrCopy(bit.data(), (ULONG)bit.length());
		if(!m_Inputdatainfo.bit){
			ReadFaild = TRUE;
			FaildComment += _T("\n���r�b�g��ǂݍ��߂܂���ł���");
		}
		const String header = GFunc::GetIniParam(_T("RawCorrector.ini"), _T("INPUT_DATA"), _T("header"));
		m_Inputdatainfo.headersize = GFunc::StrCopy(header.data(), (ULONG)header.length());
		if(!m_Inputdatainfo.headersize){
			ReadFaild = TRUE;
			FaildComment += _T("\n���w�b�_�T�C�Y��ǂݍ��߂܂���ł���");
		}
		const String exe = GFunc::GetIniParam(_T("RawCorrector.ini"), _T("EVA_PATH"), _T("exe"));
		m_Evaexepath = GFunc::StrCopy(exe.data(), (ULONG)exe.length());
		if(!m_Evaexepath){
			ReadFaild = TRUE;
			FaildComment += _T("\n��Eva���s�p�X��ǂݍ��߂܂���ł���");
		}
		const String prm = GFunc::GetIniParam(_T("RawCorrector.ini"), _T("EVA_PATH"), _T("prm"));
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
			InitList(m_hFileList,caption,mag);
		}
		{// �������X�g������
			caption.clear();
			caption.push_back(_T("����"));
			caption.push_back(_T("��������"));
			mag.clear();
			mag.push_back(0.16);
			mag.push_back(0.825);
			InitList(m_hProcList,caption,mag);
		}
		{// �p�����[�^���X�g������
			caption.clear();
			caption.push_back(_T("Name"));
			caption.push_back(_T("Value"));
			mag.clear();
			mag.push_back(0.35);
			mag.push_back(0.64);
			InitList(m_hPrmList,caption,mag);
		}

		// �t�@�C�����X�g�̃T�u�N���X��
		m_FilelistSubcls.InitSubcls(hWnd,IDC_FILE_LIST);

		// �\���e�X�g�p�}��
		GFunc::InsertSubItem(m_hPrmList,0,0,_T("INPUT_SIZE"));
		GFunc::InsertSubItem(m_hPrmList,0,1,_T("5200,3568"));
		GFunc::InsertSubItem(m_hPrmList,1,0,_T("TYPE13_PERIOD_SIZE"));
		GFunc::InsertSubItem(m_hPrmList,1,1,_T("6,6"));
		GFunc::InsertSubItem(m_hPrmList,2,0,_T("TYPE13_START_POINT"));
		GFunc::InsertSubItem(m_hPrmList,2,1,_T("0,0"));
		GFunc::InsertSubItem(m_hPrmList,3,0,_T("TYPE13_SUM_PATTERN"));
		GFunc::InsertSubItem(m_hPrmList,3,1,_T("1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1"));
		
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
	virtual LRESULT CommandProc(const WPARAM wParam)
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
			AddProcList(_T("�ʑ���RAW"));
			break;}
		case IDC_BUTTON_GAIN:{// �Q�C���␳
			AddProcList(_T("�Q�C���␳"));
			break;}
		case IDC_BUTTON_FHDMONITOR:{// FHD MonitorRAW
			AddProcList(_T("FHD_MonitorRAW"));
			break;}
		case IDC_BUTTON_PIXELCORRECT:{// ��f�␳
			AddProcList(_T("��f�␳"));
			break;}
		case IDC_BUTTON_OPTICAXIS:{// �����␳
			AddProcList(_T("�����␳"));
			break;}
		case IDC_BUTTON_DEVELOP:{// ����
			AddProcList(_T("����"));
			break;}
		case IDC_BUTTON_PROCTURNCHANGE_UP:{// ���������߂�
			SwapProcOrder(0);
			break;}
		case IDC_BUTTON_PROCTURNCHANGE_DOWN:{// �������x�߂�
			SwapProcOrder(1);
			break;}
		case IDC_BUTTON_CLEAR:{// �������ڂ���폜
			
			break;}
		case IDC_BUTTON_ALLCLEAR:{// �������ڂ�S�č폜
			ListView_DeleteAllItems(m_hProcList);
			m_ProcCount = 0;
			break;}
		case IDC_BUTTON_PROCREGISTR:{// �\������Ă��鏈�����e��o�^
			
			break;}
		case IDC_BUTTON_INPUTDATA_EDIT:{// ���̓f�[�^�T�C�Y�ύX
			const InputdataInfo backupinfo = m_Inputdatainfo;
			CInputdataDialog IndataDlg(m_Inputdatainfo);
			const int ret = IndataDlg.DoModal(m_hInst,m_hDlg);
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
			const int ret = EvaDlg.DoModal(m_hInst,m_hDlg);
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
			MessageBox(NULL,_T("�������@�\"),_T("���s"), MB_OK);
			break;}
		case IDCANCEL: case ID_CLOSE:{// �I��
			OnCancel();
			break;}
		}
		return FALSE;
	}


private:
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
			AddProcList
		[Purpose]
			�������ڃ��X�g�֍��ڂ���ǉ�����
		[Parameter1] procname
			������
	\----------------------------------------------------------------------------*/
	void AddProcList(const TCHAR* const procname)
	{
		++m_ProcCount;
		GFunc::InsertSubItem(m_hProcList,m_ProcCount-1,0,GFunc::LToStr(m_ProcCount).data());
		GFunc::InsertSubItem(m_hProcList,m_ProcCount-1,1,procname);
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
		for(UINT i=0; i<size; i++)
		{// �I����Ԃ̍��ڂ�����
			const UINT uiState = ListView_GetItemState(m_hProcList, i, LVIS_SELECTED);
			if(uiState & LVIS_SELECTED)
			{// ����ւ����
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
		SetWindowText(m_hStaticStartColor, m_Inputdatainfo.startcolor);
		SetWindowText(m_hStaticDatastuff, m_Inputdatainfo.datavector);
		SetWindowText(m_hStaticEndian, m_Inputdatainfo.endian);
		SetWindowText(m_hStaticBitnum, m_Inputdatainfo.bit);
		SetWindowText(m_hStaticHeadersize, m_Inputdatainfo.headersize);
		SetWindowText(m_hStaticWidth, m_Inputdatainfo.width);
		SetWindowText(m_hStaticHeight, m_Inputdatainfo.height);
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
		const String startcolor = GFunc::LToStr(CInputdataDialog::GetStartcolorInt(m_Inputdatainfo.startcolor));
		GFunc::WriteIniParam(_T("RawCorrector.ini"), _T("INPUT_DATA"), _T("startcolor"), startcolor.data());
		// �G���f�B�A��
		const String endian = GFunc::LToStr(CInputdataDialog::GetEndianInt(m_Inputdatainfo.endian));
		GFunc::WriteIniParam(_T("RawCorrector.ini"), _T("INPUT_DATA"), _T("endian"), endian.data());
		// �l�ߕ���
		const String datavector = GFunc::LToStr(CInputdataDialog::GetDatavectorInt(m_Inputdatainfo.datavector));
		GFunc::WriteIniParam(_T("RawCorrector.ini"), _T("INPUT_DATA"), _T("datavector"), datavector.data());
		// ��
		GFunc::WriteIniParam(_T("RawCorrector.ini"), _T("INPUT_DATA"), _T("width"), m_Inputdatainfo.width);
		// ����
		GFunc::WriteIniParam(_T("RawCorrector.ini"), _T("INPUT_DATA"), _T("height"), m_Inputdatainfo.height);
		// �r�b�g
		GFunc::WriteIniParam(_T("RawCorrector.ini"), _T("INPUT_DATA"), _T("bit"), m_Inputdatainfo.bit);
		// �w�b�_
		GFunc::WriteIniParam(_T("RawCorrector.ini"), _T("INPUT_DATA"), _T("header"), m_Inputdatainfo.headersize);
	}


	/*----------------------------------------------------------------------------\
		[Function]
			UpdateIni_Evapath
		[Purpose]
			Eva�p�X��ini�p�����[�^���e���X�V
	\----------------------------------------------------------------------------*/
	void UpdateIni_Evapath(void)
	{
		GFunc::WriteIniParam(_T("RawCorrector.ini"), _T("EVA_PATH"), _T("exe"), m_Evaexepath);
		GFunc::WriteIniParam(_T("RawCorrector.ini"), _T("EVA_PATH"), _T("prm"), m_Evaprmpath);
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


	/*----------------------------------------------------------------------------\
		[Function]
			Execution
		[Details]
			���������s����
		[Argument1] files
			���[�U�[���h���b�v�����t�@�C��
		[Return]
			���� : 1  ���s : 0  �G���[ : -1
	\----------------------------------------------------------------------------*/
	int Execution(const std::vector<FileInfo>& files)
	{
		if(files.size() < 1) return 0;
		const BOOL CCheck = (BOOL)SendMessage(hCheck,BM_GETCHECK,0,NULL);
		const String SelectTag = GetWindowTxtEx(hCombo);
		//CProc proc(hDlg,CCheck,SelectTag);
		return 1;
		//return proc.Execution(files);
	}


	
#endif

}; // CMainDialog


