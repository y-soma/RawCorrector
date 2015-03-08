#pragma once

#include "Interface.h"

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		GFunc
	[Purpose]
		汎用関数実装クラス
	[Description]
		クラス内にメンバ変数を設けず、メンバ関数は全てstaticとする
\////////////////////////////////////////////////////////////////////////////*/
class GFunc
{
private:
	GFunc(void){}; ~GFunc(void){};	//! インスタンスの禁止

public:
	/*****************************************************************************\
		[Function]
			LToStr()
		[Purpose]
			数値を文字列に変換する
		[Parameter1] val
			変換対象
		[Returns]
			変換後の文字列
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
			文字列の数値を整数型に変換する
		[Parameter1] str
			変換対象
		[Returns]
			変換結果
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
			少数を文字列に変換する
		[Parameter1] val
			変換対象
		[Parameter2] precision
			少数点以下の精度(小数点第[precision]位)
		[Returns]
			変換後の文字列
	\*****************************************************************************/
	static inline String DToStr(const double& val, const int& precision = -1)
	{ 
		TCHAR buf[MAX_PATH] = {0};
		if(precision == -1)
		{// 小数点指定無し
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
			文字列の数値を少数型に変換する
		[Parameter1] str
			変換対象
		[Returns]
			変換後の浮動小数
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
			文字列ポインタへ指定した文字をコピーする
		[Parameter1] src
			コピー元
		[Parameter2] size
			コピーサイズ
		[Returns]
			文字列の確保に成功したポインタを返却
		[Description]
			std::stringなどで文字列を扱う場合には不要となる
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
			整数の四捨五入
		[Parameter1] src
			値
		[Parameter2] precision
			切り捨てる桁の位(precisionの位)
		[Returns]
			四捨五入後の値  失敗すると元の値を返す
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
			ファイル選択ダイアログ
		[Parameter1] hwndOwner
			オーナーウインドウハンドル
		[Parameter2] lpstrTitle
			ダイアログタイトル
		[Parameter3] lpstrFilter
			拡張子フィルタ
		[Parameter4] lpstrDefExt
			デフォルト拡張子
		[Returns]
			取得したファイルパスを返却
	\*****************************************************************************/
	static std::vector<String> FileSelectDlg(
		const HWND hwndOwner,
		const LPCTSTR lpstrTitle = _T("ファイルを開く"),
		const LPCTSTR lpstrFilter = TEXT("JPEG {*.JPG}\0*.JPG;*.JPEG;*.JPE\0")TEXT("ORF {*.ORF}\0*.ORF\0")TEXT("All files {*.*}\0*.*\0\0"),
		const LPCTSTR lpstrDefExt = _T("JPG"))
	{
		try
		{
			std::vector<String> dst(0,_T(""));
			TCHAR filename_full[MAX_PATH*0x0F];
			WORD nFileOffset = 0;
			WORD nMaxFile = 0;
			{// ダイアログからユーザーが選択したファイル情報取得
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
			{// OFN_ALLOWMULTISELECTの形式に合わせて複数ファイル名を取得
				if(filename_full[i])
					continue;
				if(filename_full[i+1] != NULL)
				{// 1つ先のポインタがNULLじゃない場合、複数のファイル情報が続いている
					ULONG cp = i+1;
					String fNameTemp = _T("");
					while(filename_full[cp] != NULL)
					{// 次のNULLポインタまでを1文字単位で結合させる
						fNameTemp += filename_full[cp];
						cp++;
					}
					dst.push_back(path + _T('\\') + fNameTemp);
				}
				else
				{// NULLの場合、終了
					break;
				}
			}
			// 選択されたファイルが1つのみ
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
			ディレクトリの存在確認
			(標準PathIsDirectory関数は見つからないときに処理が激重になるので高速化を図ったもの)
		[Parameter1] dir
			ディレクトリ
		[Returns]
			発見 : 1   見つからない : 0   処理中にエラー ： -1
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
			フルパスからディレクトリのみを取り出だす
		[Parameter1] fullpath
			フルパス
		[Returns]
			ディレクトリ
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
			フルパスからファイル名のみを取り出だす
		[Parameter1] fullpath
			フルパス
		[Returns]
			ファイル名
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
			フルパスから拡張子のみを取り出だす
		[Parameter1] fullpath
			フルパス
		[Returns]
			ファイル名
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
			フルパスから拡張子のみを取り除く
		[Parameter1] fullpath
			フルパス
		[Returns]
			拡張子を取り除いたパス
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
			ディレクトリとその中の全てのファイルを削除する
		[Parameter1] lpPathName
			ディレクトリパス
		[Returns]
			成功：TRUE   失敗：FALSE
	\*****************************************************************************/
	static BOOL DeleteDirectory(LPCTSTR lpPathName)
	{
		try
		{
			if(!lpPathName) return FALSE;
			// ファイル名文字列長
			const ULONG size = _MAX_PATH * 0x0F;
			// ディレクトリ名の保存（終端に'\'がないなら付ける）
			TCHAR szDirectoryPathName[size];
			_tcsncpy_s(szDirectoryPathName,size,lpPathName,_TRUNCATE );
			// 一番最後に'\'がないなら付加する。
			if('\\' != szDirectoryPathName[_tcslen(szDirectoryPathName)-1])
				_tcsncat_s(szDirectoryPathName,size,_T("\\"),_TRUNCATE);

			// ディレクトリ内のファイル走査用のファイル名作成
			TCHAR szFindFilePathName[size];
			_tcsncpy_s(szFindFilePathName,size,szDirectoryPathName,_TRUNCATE);
			_tcsncat_s(szFindFilePathName,size,_T("*"),_TRUNCATE);

			// ディレクトリ内のファイル走査
			WIN32_FIND_DATA	fd;
			HANDLE hFind = FindFirstFile(szFindFilePathName,&fd);
			// 走査対象フォルダが存在しない。
			if(hFind == INVALID_HANDLE_VALUE) return FALSE;
			do{// 全てのファイルを走査
				if('.' != fd.cFileName[0])
				{
					TCHAR szFoundFilePathName[size];
					_tcsncpy_s(szFoundFilePathName,size,szDirectoryPathName,_TRUNCATE);
					_tcsncat_s(szFoundFilePathName,size,fd.cFileName,_TRUNCATE);
					if( FILE_ATTRIBUTE_DIRECTORY & fd.dwFileAttributes )
					{// ディレクトリ
						if(!DeleteDirectory(szFoundFilePathName)){
							FindClose(hFind);
							return FALSE;
						}
					}
					else
					{// ファイル
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
			Initファイルのパラメータを取得する
		[Parameter1] filename
			iniファイル名
		[Parameter2] section
			セクション名
		[Parameter3] param
			パラメータ名
		[Parameter4] specdir
			実行ファイル以外の場所からiniファイルを読み込む場合はここでディレクトリを指定(※ディレクトリの最後に"\"を付ける)
		[Returns]
			成功すると取得パラメータを文字列で返却する
	**************************************************************************/
	static String GetIniParam(const TCHAR* const filename, const TCHAR* const section, const TCHAR* const param, const TCHAR* const specdir = NULL)
	{
		try
		{
			String dir = _T("");
			if(!specdir)
			{// 実行ファイルの存在するディレクトリを取得
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
			// 第3引数は見つからなかった場合に返却する値を指定
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
			Initファイルへパラメータを書き込む
		[Parameter1] filename
			iniファイル名
		[Parameter2] section
			セクション名
		[Parameter3] param
			パラメータ名
		[Parameter4] val
			書き込む値
		[Parameter5] specdir
			実行ファイル以外の場所からiniファイルへ書き込む場合はここでディレクトリを指定(※ディレクトリの最後に"\"を付ける)
		[Returns]
			成功するとTRUEを返却する
	**************************************************************************/
	static BOOL WriteIniParam(const TCHAR* const filename, const TCHAR* const section, const TCHAR* const param, const TCHAR* const val, const TCHAR* const specdir = NULL)
	{
		try
		{
			String dir = _T("");
			if(!specdir)
			{// 実行ファイルの存在するディレクトリを取得
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
			リストコントロールへアイテムを追加する
		[Parameter1] hList
			ウインドウハンドル
		[Parameter2] dstpath
			格納パス
		[Parameter3] srcpath
			追加パス
	\*****************************************************************************/
	static void AddListItem(HWND& hList, std::vector<String>& dstpath, const std::vector<String>& srcpath)
	{
		for(UINT i=0; i<srcpath.size(); i++)
		{// 重複しないパスのみ追加
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

		// 更新
		ListView_DeleteAllItems(hList);
		for(UINT i=0; i<dstpath.size(); i++)
		{
			InsertSubItem(hList,i,0,GFunc::GetFileName(dstpath[i].data()).data());
			InsertSubItem(hList,i,1,GFunc::GetDir(dstpath[i].data()).data());
		}
	}

	/* 第4引数により、通過拡張子を指定する */
	static void AddListItem(HWND& hList, std::vector<String>& dstpath, const std::vector<String>& srcpath, const std::vector<String>& ext)
	{
		std::vector<String> pathsort(0,_T(""));
		{// 拡張子チェック
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
			リストコントロールへサブアイテムを挿入する
		[Parameter1] hWnd
			ウインドウハンドル
		[Parameter2] iItem
			アイテム番号
		[Parameter3] iSubItem
			サブアイテム番号
		[Parameter4] Text
			挿入テキスト
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
			ディレクトリに存在しないダミーファイルパス取得
			(ディレクトリの中から指定ファイル名+(1～の識別番号)+拡張子を検索し見つからない場合のみそのファイル名を返す)
		[Parameter1] path
			ディレクトリのみ
		[Parameter2] fname
			検索ファイル名
		[Parameter3] ext
			検索拡張子
		[Returns]
			発見 : empty    見つからない : そのファイル名
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
