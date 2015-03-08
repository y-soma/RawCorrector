#pragma once

#include "Subcls.h"

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CListSubcls
	[Purpose]
		���X�g�R���g���[�����T�u�N���X�����邽�߂̃N���X
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
			�h���b�O���h���b�v���ꂽ�t�@�C�����R���g���[���֓W�J����
		[Parameter1] path
			�h���b�O���h���b�v�Ŏ擾�����t�@�C���p�X
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
		�G�f�B�b�g�R���g���[�����T�u�N���X�����邽�߂̃N���X
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
			�h���b�O���h���b�v���ꂽ�t�@�C�����R���g���[���֓W�J����
		[Parameter1] path
			�h���b�O���h���b�v�Ŏ擾�����t�@�C���p�X
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual void DeployDropFile(const std::vector<String>& path)
	{
		if(path.size() < 1) return;
		SetWindowText(m_hWnd, path[0].data());
	}

};// End CEditSubcls

