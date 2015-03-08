#pragma once

#include "Interface.h"

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		GFunc
	[Purpose]
		�ėp�֐������N���X
	[Description]
		�N���X���Ƀ����o�ϐ���݂����A�����o�֐��͑S��static�Ƃ���
\////////////////////////////////////////////////////////////////////////////*/
class GFunc
{
private:
	GFunc(void){}; ~GFunc(void){};	//! �C���X�^���X�̋֎~

public:
	/*****************************************************************************\
		[Function]
			LToStr()
		[Purpose]
			���l�𕶎���ɕϊ�����
		[Parameter1] val
			�ϊ��Ώ�
		[Returns]
			�ϊ���̕�����
	\*****************************************************************************/
	static inline String LToStr(const ULONG& val)
	{ 
		TCHAR buf[MAX_PATH*0xFF] = {0};
		wsprintf(buf,_T("%d"),val);
		return buf;
	}


	/*****************************************************************************\
		[Function]
			StrToL()
		[Purpose]
			������̐��l�𐮐��^�ɕϊ�����
		[Parameter1] str
			�ϊ��Ώ�
		[Returns]
			�ϊ�����
	\*****************************************************************************/
	static inline long StrToL(const TCHAR* const str)
	{ 
		#ifndef UNICODE
			return atol(str);
		#else
			return _wtol(str);
		#endif
	}


	/*****************************************************************************\
		[Function]
			DToStr()
		[Purpose]
			�����𕶎���ɕϊ�����
		[Parameter1] val
			�ϊ��Ώ�
		[Parameter2] precision
			�����_�ȉ��̐��x(�����_��[precision]��)
		[Returns]
			�ϊ���̕�����
	\*****************************************************************************/
	static inline String DToStr(const double& val, const int& precision = -1)
	{ 
		TCHAR buf[MAX_PATH] = {0};
		if(precision == -1)
		{// �����_�w�薳��
			_stprintf_s(buf, _T("%f"), val);
		}
		else if(precision > -1)
		{
			const String pre = _T("%.")+LToStr((long)precision)+_T("f");
			_stprintf_s(buf, pre.data(), val);
		}
		return buf;
	}


	/*****************************************************************************\
		[Function]
			StrToD()
		[Purpose]
			������̐��l�������^�ɕϊ�����
		[Parameter1] str
			�ϊ��Ώ�
		[Returns]
			�ϊ���̕�������
	\*****************************************************************************/
	static inline double StrToD(const TCHAR* const str)
	{ 
		#ifndef UNICODE
			return atof(str);
		#else
			return _wtof(str);
		#endif
	}


	/*****************************************************************************\
		[Function]
			StrCopy
		[Purpose]
			������|�C���^�֎w�肵���������R�s�[����
		[Parameter1] src
			�R�s�[��
		[Parameter2] size
			�R�s�[�T�C�Y
		[Returns]
			������̊m�ۂɐ��������|�C���^��ԋp
		[Description]
			std::string�Ȃǂŕ�����������ꍇ�ɂ͕s�v�ƂȂ�
	\*****************************************************************************/
	static const TCHAR* StrCopy(const TCHAR* src, const size_t& size)
	{
		if(!size) return NULL;
		const TCHAR* p = (const TCHAR*)malloc(sizeof(TCHAR) * (size+1));
		if(!p) return NULL;
		memcpy((void*)p, src, sizeof(TCHAR) * size);
		memcpy((void*)&p[size], _T("\0"), sizeof(TCHAR));
		return p;
	}


	/*****************************************************************************\
		[Function]
			RoundInt
		[Purpose]
			�����̎l�̌ܓ�
		[Parameter1] src
			�l
		[Parameter2] precision
			�؂�̂Ă錅�̈�(precision�̈�)
		[Returns]
			�l�̌ܓ���̒l  ���s����ƌ��̒l��Ԃ�
	\*****************************************************************************/
	static long RoundInt(const long& src, const int& precision = 1)
	{	
		try
		{
			if(src < 0) return src;
			long dst = src;
			{
				long grade = 1;
				for(int i=1; i<precision+1; i++) grade *= 10;
				const double diff = 0.5 * (double)grade;
				double val = (double)src;
				val += diff;
				val /= (double)grade;
				dst = (long)val;
				dst *= grade;
			}
			return dst;
		}
		catch(...)
		{
			return src;
		}
	}


	/*****************************************************************************\
		[Function]
			FileSelectDlg
		[Purpose]
			�t�@�C���I���_�C�A���O
		[Parameter1] hwndOwner
			�I�[�i�[�E�C���h�E�n���h��
		[Parameter2] lpstrTitle
			�_�C�A���O�^�C�g��
		[Parameter3] lpstrFilter
			�g���q�t�B���^
		[Parameter4] lpstrDefExt
			�f�t�H���g�g���q
		[Returns]
			�擾�����t�@�C���p�X��ԋp
	\*****************************************************************************/
	static std::vector<String> FileSelectDlg(
		const HWND hwndOwner,
		const LPCTSTR lpstrTitle = _T("�t�@�C�����J��"),
		const LPCTSTR lpstrFilter = TEXT("JPEG {*.JPG}\0*.JPG;*.JPEG;*.JPE\0")TEXT("ORF {*.ORF}\0*.ORF\0")TEXT("All files {*.*}\0*.*\0\0"),
		const LPCTSTR lpstrDefExt = _T("JPG"))
	{
		try
		{
			std::vector<String> dst(0,_T(""));
			TCHAR filename_full[MAX_PATH*0x0F];
			WORD nFileOffset = 0;
			WORD nMaxFile = 0;
			{// �_�C�A���O���烆�[�U�[���I�������t�@�C�����擾
				OPENFILENAME ofn;
				TCHAR filename_n[MAX_PATH*0x0F];
				{// Dialog Setting
					ZeroMemory(&ofn, sizeof(ofn));
					ZeroMemory(&filename_full, sizeof(filename_full));
					ZeroMemory(&filename_n, sizeof(filename_n));
					ofn.lStructSize = sizeof(ofn);
					ofn.hwndOwner = hwndOwner;
					ofn.lpstrFile = filename_full;
					ofn.nMaxFile = sizeof(filename_full);
					ofn.lpstrTitle = lpstrTitle;
					ofn.lpstrFilter = lpstrFilter;
					ofn.lpstrDefExt = lpstrDefExt;
					ofn.lpstrFileTitle = filename_n;
					ofn.nMaxFileTitle = sizeof(filename_n);
					ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;
				}
				if(!GetOpenFileName(&ofn))
					return dst;
				nFileOffset = ofn.nFileOffset;
				nMaxFile = (WORD)ofn.nMaxFile;
			}

			const String path = filename_full;
			for(WORD i=nFileOffset-1; i<nMaxFile; i++)
			{// OFN_ALLOWMULTISELECT�̌`���ɍ��킹�ĕ����t�@�C�������擾
				if(filename_full[i])
					continue;
				if(filename_full[i+1] != NULL)
				{// 1��̃|�C���^��NULL����Ȃ��ꍇ�A�����̃t�@�C����񂪑����Ă���
					ULONG cp = i+1;
					String fNameTemp = _T("");
					while(filename_full[cp] != NULL)
					{// ����NULL�|�C���^�܂ł�1�����P�ʂŌ���������
						fNameTemp += filename_full[cp];
						cp++;
					}
					dst.push_back(path + _T('\\') + fNameTemp);
				}
				else
				{// NULL�̏ꍇ�A�I��
					break;
				}
			}
			// �I�����ꂽ�t�@�C����1�̂�
			if(!dst.size())
				dst.push_back(path);

			std::sort(dst.begin(),dst.end());
			return dst;
		}
		catch(...)
		{
			std::vector<String> ret(0,_T(""));
			return ret;
		}
	}


	#pragma warning (disable:4996)
	/*****************************************************************************\
		[Function]
			PathIsDirectoryEX
		[Purpose]
			�f�B���N�g���̑��݊m�F
			(�W��PathIsDirectory�֐��͌�����Ȃ��Ƃ��ɏ��������d�ɂȂ�̂ō�������}��������)
		[Parameter1] dir
			�f�B���N�g��
		[Returns]
			���� : 1   ������Ȃ� : 0   �������ɃG���[ �F -1
	\*****************************************************************************/
	static int PathIsDirectoryEX(const TCHAR* const dir)
	{
		try
		{
			const String DummyPath = GetDummyFilePath(dir);
			FILE* fp = NULL;
			#ifdef UNICODE
				fp = _wfopen(DummyPath.data(),L"w");
			#else
				fp = fopen(DummyPath,"w");
			#endif
			if(!fp) return FALSE;
			fclose(fp);
			if(!DeleteFile(DummyPath.data())) return -1;	
			return TRUE;
		}
		catch(...)
		{
			return -1;
		}
	}


	/*****************************************************************************\
		[Function]
			GetDir
		[Purpose]
			�t���p�X����f�B���N�g���݂̂����o����
		[Parameter1] fullpath
			�t���p�X
		[Returns]
			�f�B���N�g��
	\*****************************************************************************/
	static String GetDir(const TCHAR* const fullpath)
	{
		TCHAR drive[_MAX_DRIVE];
		TCHAR dir[_MAX_DIR];
		TCHAR fname[_MAX_FNAME];
		TCHAR ext[_MAX_EXT];
		#ifdef UNICODE
			_wsplitpath(fullpath,drive,dir,fname,ext);
		#else
			_splitpath(fullpath,drive,dir,fname,ext);
		#endif
		String dst = drive;
		dst += dir;
		return dst;
	}
	
	
	/*****************************************************************************\
		[Function]
			GetFileName
		[Purpose]
			�t���p�X����t�@�C�����݂̂����o����
		[Parameter1] fullpath
			�t���p�X
		[Returns]
			�t�@�C����
	\*****************************************************************************/
	static String GetFileName(const TCHAR* const fullpath)
	{
		TCHAR drive[_MAX_DRIVE];
		TCHAR dir[_MAX_DIR];
		TCHAR fname[_MAX_FNAME];
		TCHAR ext[_MAX_EXT];
		#ifdef UNICODE
			_wsplitpath(fullpath,drive,dir,fname,ext);
		#else
			_splitpath(fullpath,drive,dir,fname,ext);
		#endif
		String dst = fname;
		dst += ext;
		return dst;
	}


	/*****************************************************************************\
		[Function]
			GetExt
		[Purpose]
			�t���p�X����g���q�݂̂����o����
		[Parameter1] fullpath
			�t���p�X
		[Returns]
			�t�@�C����
	\*****************************************************************************/
	static String GetExt(const TCHAR* const fullpath)
	{
		TCHAR drive[_MAX_DRIVE];
		TCHAR dir[_MAX_DIR];
		TCHAR fname[_MAX_FNAME];
		TCHAR ext[_MAX_EXT];
		#ifdef UNICODE
			_wsplitpath(fullpath,drive,dir,fname,ext);
		#else
			_splitpath(fullpath,drive,dir,fname,ext);
		#endif
		return ext;
	}


	/*****************************************************************************\
		[Function]
			GetRemoveExtPath
		[Purpose]
			�t���p�X����g���q�݂̂���菜��
		[Parameter1] fullpath
			�t���p�X
		[Returns]
			�g���q����菜�����p�X
	\*****************************************************************************/
	static String GetRemoveExtPath(const TCHAR* const fullpath)
	{
		TCHAR drive[_MAX_DRIVE];
		TCHAR dir[_MAX_DIR];
		TCHAR fname[_MAX_FNAME];
		TCHAR ext[_MAX_EXT];
		#ifdef UNICODE
			_wsplitpath(fullpath,drive,dir,fname,ext);
		#else
			_splitpath(fullpath,drive,dir,fname,ext);
		#endif
		String dst = drive;
		dst += dir;
		dst += fname;
		return dst;
	}


	/*****************************************************************************\
		[Function]
			DeleteDirectory
		[Purpose]
			�f�B���N�g���Ƃ��̒��̑S�Ẵt�@�C�����폜����
		[Parameter1] lpPathName
			�f�B���N�g���p�X
		[Returns]
			�����FTRUE   ���s�FFALSE
	\*****************************************************************************/
	static BOOL DeleteDirectory(LPCTSTR lpPathName)
	{
		try
		{
			if(!lpPathName) return FALSE;
			// �t�@�C����������
			const ULONG size = _MAX_PATH * 0x0F;
			// �f�B���N�g�����̕ۑ��i�I�[��'\'���Ȃ��Ȃ�t����j
			TCHAR szDirectoryPathName[size];
			_tcsncpy_s(szDirectoryPathName,size,lpPathName,_TRUNCATE );
			// ��ԍŌ��'\'���Ȃ��Ȃ�t������B
			if('\\' != szDirectoryPathName[_tcslen(szDirectoryPathName)-1])
				_tcsncat_s(szDirectoryPathName,size,_T("\\"),_TRUNCATE);

			// �f�B���N�g�����̃t�@�C�������p�̃t�@�C�����쐬
			TCHAR szFindFilePathName[size];
			_tcsncpy_s(szFindFilePathName,size,szDirectoryPathName,_TRUNCATE);
			_tcsncat_s(szFindFilePathName,size,_T("*"),_TRUNCATE);

			// �f�B���N�g�����̃t�@�C������
			WIN32_FIND_DATA	fd;
			HANDLE hFind = FindFirstFile(szFindFilePathName,&fd);
			// �����Ώۃt�H���_�����݂��Ȃ��B
			if(hFind == INVALID_HANDLE_VALUE) return FALSE;
			do{// �S�Ẵt�@�C���𑖍�
				if('.' != fd.cFileName[0])
				{
					TCHAR szFoundFilePathName[size];
					_tcsncpy_s(szFoundFilePathName,size,szDirectoryPathName,_TRUNCATE);
					_tcsncat_s(szFoundFilePathName,size,fd.cFileName,_TRUNCATE);
					if( FILE_ATTRIBUTE_DIRECTORY & fd.dwFileAttributes )
					{// �f�B���N�g��
						if(!DeleteDirectory(szFoundFilePathName)){
							FindClose(hFind);
							return FALSE;
						}
					}
					else
					{// �t�@�C��
						if(!DeleteFile(szFoundFilePathName)){
							FindClose(hFind);
							return FALSE;
						}
					}
				}
			}while(FindNextFile(hFind,&fd));
			FindClose(hFind);
			
			return RemoveDirectory(lpPathName);
		}
		catch(...)
		{
			return FALSE;
		}
	}


	/**************************************************************************
		[Function]
			GetIniParam
		[Purpose]
			Init�t�@�C���̃p�����[�^���擾����
		[Parameter1] filename
			ini�t�@�C����
		[Parameter2] section
			�Z�N�V������
		[Parameter3] param
			�p�����[�^��
		[Parameter4] specdir
			���s�t�@�C���ȊO�̏ꏊ����ini�t�@�C����ǂݍ��ޏꍇ�͂����Ńf�B���N�g�����w��(���f�B���N�g���̍Ō��"\"��t����)
		[Returns]
			��������Ǝ擾�p�����[�^�𕶎���ŕԋp����
	**************************************************************************/
	static String GetIniParam(const TCHAR* const filename, const TCHAR* const section, const TCHAR* const param, const TCHAR* const specdir = NULL)
	{
		try
		{
			String dir = _T("");
			if(!specdir)
			{// ���s�t�@�C���̑��݂���f�B���N�g�����擾
				TCHAR pathbuf[MAX_PATH * 0x0F];
				if(!GetModuleFileName(NULL, pathbuf, MAX_PATH*0x0F))
					return _T("");
				dir = GetDir(pathbuf);
			}
			else
			{
				dir = specdir;
			}

			const String path = dir + filename;
			TCHAR prmbuf[MAX_PATH * 0x0F] = {0};
			// ��3�����͌�����Ȃ������ꍇ�ɕԋp����l���w��
			GetPrivateProfileString(section, param, _T(""), prmbuf, MAX_PATH*0x0F, path.data());
			return prmbuf;
		}
		catch(...)
		{
			return _T("");
		}
	}


	/**************************************************************************
		[Function]
			WriteIniParam
		[Purpose]
			Init�t�@�C���փp�����[�^����������
		[Parameter1] filename
			ini�t�@�C����
		[Parameter2] section
			�Z�N�V������
		[Parameter3] param
			�p�����[�^��
		[Parameter4] val
			�������ޒl
		[Parameter5] specdir
			���s�t�@�C���ȊO�̏ꏊ����ini�t�@�C���֏������ޏꍇ�͂����Ńf�B���N�g�����w��(���f�B���N�g���̍Ō��"\"��t����)
		[Returns]
			���������TRUE��ԋp����
	**************************************************************************/
	static BOOL WriteIniParam(const TCHAR* const filename, const TCHAR* const section, const TCHAR* const param, const TCHAR* const val, const TCHAR* const specdir = NULL)
	{
		try
		{
			String dir = _T("");
			if(!specdir)
			{// ���s�t�@�C���̑��݂���f�B���N�g�����擾
				TCHAR pathbuf[MAX_PATH * 0x0F];
				if(!GetModuleFileName(NULL, pathbuf, MAX_PATH*0x0F))
					return FALSE;
				dir = GetDir(pathbuf);
			}
			else
			{
				dir = specdir;
			}
			const String path = dir + filename;
			return WritePrivateProfileString(section, param, val, path.data());
		}
		catch(...)
		{
			return FALSE;
		}
	}


	/*****************************************************************************\
		[Function]
			AddListItem
		[Purpose]
			���X�g�R���g���[���փA�C�e����ǉ�����
		[Parameter1] hList
			�E�C���h�E�n���h��
		[Parameter2] dstpath
			�i�[�p�X
		[Parameter3] srcpath
			�ǉ��p�X
	\*****************************************************************************/
	static void AddListItem(HWND& hList, std::vector<String>& dstpath, const std::vector<String>& srcpath)
	{
		for(UINT i=0; i<srcpath.size(); i++)
		{// �d�����Ȃ��p�X�̂ݒǉ�
			BOOL find = FALSE;
			for(UINT j=0; j<dstpath.size(); j++)
			{
				if(srcpath[i] == dstpath[j]){
					find = TRUE;
					break;
				}
			}
			if(!find)
				dstpath.push_back(srcpath[i]);
		}

		// �X�V
		ListView_DeleteAllItems(hList);
		for(UINT i=0; i<dstpath.size(); i++)
		{
			InsertSubItem(hList,i,0,GFunc::GetFileName(dstpath[i].data()).data());
			InsertSubItem(hList,i,1,GFunc::GetDir(dstpath[i].data()).data());
		}
	}

	/* ��4�����ɂ��A�ʉߊg���q���w�肷�� */
	static void AddListItem(HWND& hList, std::vector<String>& dstpath, const std::vector<String>& srcpath, const std::vector<String>& ext)
	{
		std::vector<String> pathsort(0,_T(""));
		{// �g���q�`�F�b�N
			for(ULONG i=0; i<srcpath.size(); i++)
			{
				for(ULONG j=0; j<ext.size(); j++)
				{
					const String srcext = GFunc::GetExt(srcpath[i].data());
					if(!lstrcmpi(srcext.data(),ext[j].data()))
					{
						pathsort.push_back(srcpath[i]);
						break;
					}
				}
			}
		}
		AddListItem(hList, dstpath, pathsort);
	}


	/*****************************************************************************\
		[Function]
			InsertSubItem
		[Purpose]
			���X�g�R���g���[���փT�u�A�C�e����}������
		[Parameter1] hWnd
			�E�C���h�E�n���h��
		[Parameter2] iItem
			�A�C�e���ԍ�
		[Parameter3] iSubItem
			�T�u�A�C�e���ԍ�
		[Parameter4] Text
			�}���e�L�X�g
	\*****************************************************************************/
	static void InsertSubItem(HWND& hWnd, const int& iItem, const int& iSubItem, const TCHAR* const Text)
	{
		LVITEM item;
		{
			item.mask = LVIF_TEXT;
			item.iItem = iItem;
			item.iSubItem = iSubItem;
			#ifdef UNICODE
				item.pszText = (LPWSTR)Text;
			#else
				item.pszText = (LPCSTR)Text;
			#endif
		}
		if(!iSubItem)
			ListView_InsertItem(hWnd,&item);
		else
			ListView_SetItem(hWnd,&item);
	}


private:
	/*----------------------------------------------------------------------------\
		[Function]
			GetDummyFilePath
		[Purpose]
			�f�B���N�g���ɑ��݂��Ȃ��_�~�[�t�@�C���p�X�擾
			(�f�B���N�g���̒�����w��t�@�C����+(1�`�̎��ʔԍ�)+�g���q��������������Ȃ��ꍇ�݂̂��̃t�@�C������Ԃ�)
		[Parameter1] path
			�f�B���N�g���̂�
		[Parameter2] fname
			�����t�@�C����
		[Parameter3] ext
			�����g���q
		[Returns]
			���� : empty    ������Ȃ� : ���̃t�@�C����
	\----------------------------------------------------------------------------*/
	static String GetDummyFilePath(const TCHAR* const path, const TCHAR* const fname = NULL, const TCHAR* const ext = NULL)
	{
		String dst = _T("");
		{// proc
			const String Path = path;
			const String FileName = !fname? _T("log"):fname;
			const String Ext = !ext? _T(".txt"):ext;
			long i  = 1;
			while(1)
			{// filepath fix loop
				const String pathtmp = Path + _T("\\") + FileName + LToStr(i) + Ext;
				// file not find
				if(!PathFileExists(pathtmp.data())){
					dst = pathtmp;
					break;
				}
				else{
					i++;
					continue;
				}
				// loop break
				if(i > 0x1FF) return dst;
			}
		}
		return dst;
	}

}; // End GFunc
