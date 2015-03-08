#pragma once

#include "ParamData.h"


/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CProcBase
	[Purpose]
		��{�����N���X
\////////////////////////////////////////////////////////////////////////////*/
class CProcBase
{
// ��protected�w��ɂ��A�h���N���X�̃C���X�^���X�̂݋�����܂�
protected:
	CProcBase(void){};
	virtual ~CProcBase(void){};

public:
	/*****************************************************************************\
		[Enumeration]
			PROC_KIND
		[Purpose]
			�������ڂ̎��ʗ�
	\*****************************************************************************/
	enum PROC_KIND
	{
		PK_NONE			= 0x00,	// �s��
		PK_PHASEDIFF	= 0x01,	// �ʑ���RAW
		PK_GAIN_COMPE	= 0x02,	// �Q�C���␳
		PK_FHD_MONITOR	= 0x03,	// FHD_Monitor RAW
		PK_PIXEL_COMPE	= 0x04,	// ��f�␳
		PK_OPTICAXIS	= 0x05,	// �����␳
		PK_DEVELOP		= 0x06,	// ����
	};


protected:
	// �p�����[�^�f�[�^
	CParamData m_clParamdt;


// �������z�֐��͕K���h����ōĒ�`(�I�[�o�[���C�h)
public:
	/*****************************************************************************\
		[Function]
			Execution
		[Purpose]
			�������s
		[Returns]
			���������ꍇ��TRUE��ԋp
	\*****************************************************************************/
	virtual BOOL Execution(void) = 0;

	/*****************************************************************************\
		[Function]
			GetProckind
		[Purpose]
			�������ʂ��擾����
		[Returns]
			�������ʔԍ�
	\*****************************************************************************/
	inline virtual const int GetProckind(void) const = 0;


	/*****************************************************************************\
		[Function]
			GetParam
		[Purpose]
			�p�����[�^�f�[�^���擾����
		[Parameter1] name
			������
		[Returns]
			�t���O
	\*****************************************************************************/
	inline const CParamData& GetParam(void) const { return m_clParamdt; }


	/*****************************************************************************\
		[Function]
			SetParam
		[Purpose]
			�p�����[�^�̒l����ύX����
		[Parameter1] param_name
			�p�����[�^��
		[Parameter2] val
			�ύX�l
	\*****************************************************************************/
	void SetParam(const TCHAR* const param_name, const String& val)
	{
		m_clParamdt.SetParam(param_name, val);
	}


	/*****************************************************************************\
		[Function]
			SetProcname
		[Purpose]
			��������o�^����
		[Parameter1] name
			������
	\*****************************************************************************/
	inline void SetProcname(const String& name)
	{
		m_clParamdt.SetProcname(name);
	}


	/*****************************************************************************\
		[Function]
			SetParam
		[Purpose]
			�p�����[�^�̒l����ύX����
		[Parameter1] index
			�C���f�b�N�X�ԍ�
		[Parameter2] val
			�ύX�l
	\*****************************************************************************/
	void SetParam(const UINT& index, const String& val)
	{
		m_clParamdt.SetParam(index, val);
	}


protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			GetIniSectionName
		[Purpose]
			ini�t�@�C���Z�N�V���������擾����
		[Returns]
			�Z�N�V������
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	inline virtual const TCHAR* const GetIniSectionName(void) const = 0;


	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			LoadParam
		[Purpose]
			�p�����[�^�ǂݍ���
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	void LoadParam(void)
	{
		m_clParamdt.LoadParam(GetIniSectionName());
	}


};// End CProcBase