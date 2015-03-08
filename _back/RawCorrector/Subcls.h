#pragma once

#include "GFunc.h"

#define PROP_NAME _T("SubclsProp")


/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CBaseSubcls
	[Purpose]
		�R���g���[�����T�u�N���X�����邽�߂̊��N���X
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


/* �R�s�[�֎~ */
private:
	CBaseSubcls(CBaseSubcls& obj){};
	CBaseSubcls& operator = (const CBaseSubcls& obj);


protected:
	// �R���g���[���̃E�C���h�E�n���h��
	HWND m_hWnd;
	// �T�u�N���X���p�n���h��
	WNDPROC m_DefStaticProc;
	// �h���b�O���h���b�v�œǂݍ��񂾃p�X�Ǘ�
	std::vector<String> m_DropPath;


public:
	/*****************************************************************************\
		[Function]
			InitSubcls
		[Purpose]
			�T�u�N���X��
		[Parameter1] hWnd
			�I�[�i�[�E�C���h�E�n���h��
		[Parameter2] hID
			�R���g���[��ID
		[Returns]
			��������TRUE��ԋp
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
			�R���g���[���փh���b�O���h���b�v���ꂽ�p�X�̎Q�Ƃ𓾂�
		[Returns]
			�t�@�C���p�X��ԋp
	\*****************************************************************************/
	inline const std::vector<String>& GetDropPath(void) const { return m_DropPath; }

	/*****************************************************************************\
		[Function]
			SetDropPath
		[Purpose]
			�h���b�v�p�X���������o�̕ύX
	\*****************************************************************************/
	inline void SetDropPath(const std::vector<String>& src) { m_DropPath = src; }


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
	}

	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			OnMouseMove
		[Purpose]
			�}�E�X���[�u�C�x���g
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual void OnMouseMove(void)
	{
	}

	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			OnLButtonDown
		[Purpose]
			�}�E�X���{�^���N���b�N�C�x���g
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual void OnLButtonDown(void)
	{
	}

	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			OnSetFocus
		[Purpose]
			�t�H�[�J�X�擾�C�x���g
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual void OnSetFocus(void)
	{
	}
	
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			OnKillFocus
		[Purpose]
			�t�H�[�J�X�����C�x���g
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	virtual void OnKillFocus(void)
	{
	}


private:
	/*----------------------------------------------------------------------------\
		[Function]
			WndProc
		[Purpose]
			�E�C���h�֑g�ݍ��ރR�[���o�b�N�֐�
		[Parameter1] hWnd
			�_�C�A���O�̃E�C���h�E�n���h��
		[Parameter2] uMsg
			�擾���b�Z�[�W
		[Parameter3] wParam
			���b�Z�[�W�̍ŏ��̃p�����[�^
		[Parameter4] lParam
			���b�Z�[�W��2�Ԗڂ̃p�����[�^
		[Returns]
			���b�Z�[�W�����̌��ʂ��Ԃ�܂��B
			�߂�l�̈Ӗ��́A���M���ꂽ���b�Z�[�W�ɂ���ĈقȂ�܂��B
			���������������AFalse���Ԃ�܂�
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
			���b�Z�[�W�����R�[���o�b�N�֐�
		[Parameter1] hDlg
			�E�C���h�E�n���h��
		[Parameter2] uMsg
			���b�Z�[�W
		[Parameter3] wParam
			���b�Z�[�W�̍ŏ��̃p�����[�^
		[Parameter4] lParam
			���b�Z�[�W��2�Ԗڂ̃p�����[�^
		[Returns]
			���b�Z�[�W�����̌��ʂ��Ԃ�܂��B
			�߂�l�̈Ӗ��́A���M���ꂽ���b�Z�[�W�ɂ���ĈقȂ�܂��B
			���������������AFalse���Ԃ�܂�
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
			�t�@�C���h���b�O���h���b�v�C�x���g����
		[Parameter1] wParam
			���b�Z�[�W�p�����[�^
		[Description]
			�h���b�v�t�@�C������t�@�C�������擾����@�\�͋��ʂ̂��ߌŒ菈���Ƃ���
	\----------------------------------------------------------------------------*/
	void OnDropFile(const WPARAM wParam)
	{
		try
		{
			TCHAR FileName[MAX_PATH] = _T("");
			HDROP hDrop = (HDROP)wParam;

			int ic = 0;
			{// �h���b�v�t�@�C�������擾
				ic = DragQueryFile(hDrop,0xFFFFFFFF,FileName,MAX_PATH);
				if(ic < 1){
					MessageBox(NULL,_T("�t�@�C�����h���b�v�ł��܂���ł���"),_T("Error"), MB_OK|MB_ICONERROR);
					return;
				}
			}
			
			std::vector<String> path(0,_T(""));
			{// �擾
				POINT pDrop;
				DragQueryPoint(hDrop,&pDrop);
				for(int i=0; i<ic; i++)
				{// �t�@�C������
					const int StrLength = DragQueryFile(hDrop,i,FileName,MAX_PATH);
					FileName[StrLength] = '\0';
					path.push_back(FileName);
				}
				DragFinish(hDrop);
				std::sort(path.begin(),path.end());
			}
			// �h���b�v�t�@�C�����R���g���[���֓W�J
			DeployDropFile(path);
		}
		catch(...)
		{
			MessageBox(NULL,_T("�t�@�C�����h���b�v���ɃG���[���������܂���"),_T("Error"), MB_OK|MB_ICONERROR);
		}
	}

};// End CBaseSubcls
