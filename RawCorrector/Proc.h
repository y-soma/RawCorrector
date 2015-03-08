#pragma once

#include "ProcBase.h"

/* �e�����N���X��`�ꏊ */
// ���N���X"CProcBase"���p�����Ċe�����N���X���`


// �e���� ini�t�@�C���Z�N�V��������`
#define INI_SECTION_PHASEDIFF	_T("PHASEDIFF")
#define INI_SECTION_GAINCOMPE	_T("GAIN_COMPE")
#define INI_SECTION_FHD_MONITOR	_T("FHD_MONITOR")
#define INI_SECTION_PIXELCOMPE	_T("PIXEL_COMPE")
#define INI_SECTION_OPTICAXIS	_T("OPTICAXIS")
#define INI_SECTION_DEVELOP		_T("DEVELOP")



/*################################## (1) ####################################*/

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CProcPhasediff
	[Purpose]
		�ʑ���RAW�����N���X
\////////////////////////////////////////////////////////////////////////////*/
class CProcPhasediff : public CProcBase
{
public:
	CProcPhasediff(void)
	{
		LoadParam();
	};
	~CProcPhasediff(void)
	{
		delete this;
	};

private:
	
	
public:
	/*****************************************************************************\
		[Function]
			Execution
		[Purpose]
			�������s
		[Returns]
			���������ꍇ��TRUE��ԋp����
	\*****************************************************************************/
	virtual BOOL Execution(void)
	{
		MessageBox(NULL, _T("�ʑ���RAW����"), _T("�m�F"), MB_OK);
		return TRUE;
	}

	/*****************************************************************************\
		[Function]
			GetProckind
		[Purpose]
			�������ʂ��擾����
		[Returns]
			�������ʔԍ�
	\*****************************************************************************/
	inline virtual const int GetProckind(void) const { return PK_PHASEDIFF; }


protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			GetIniSectionName
		[Purpose]
			ini�t�@�C���Z�N�V���������擾����
		[Returns]
			�Z�N�V������
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	inline virtual const TCHAR* const GetIniSectionName(void) const { return INI_SECTION_PHASEDIFF; }


};// End CProcPhasediff



/*################################## (2) ####################################*/

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CProcGaincompe
	[Purpose]
		�Q�C���␳�����N���X
\////////////////////////////////////////////////////////////////////////////*/
class CProcGaincompe : public CProcBase
{
public:
	CProcGaincompe(void)
	{
		LoadParam();
	};
	~CProcGaincompe(void)
	{
		delete this;
	};

private:
	
	
public:
	/*****************************************************************************\
		[Function]
			Execution
		[Purpose]
			�������s
		[Returns]
			���������ꍇ��TRUE��ԋp����
	\*****************************************************************************/
	virtual BOOL Execution(void)
	{
		MessageBox(NULL, _T("�Q�C���␳����"), _T("�m�F"), MB_OK);
		return TRUE;
	}

	/*****************************************************************************\
		[Function]
			GetProckind
		[Purpose]
			�������ʂ��擾����
		[Returns]
			�������ʔԍ�
	\*****************************************************************************/
	inline virtual const int GetProckind(void) const { return PK_GAIN_COMPE; }


protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			GetIniSectionName
		[Purpose]
			ini�t�@�C���Z�N�V���������擾����
		[Returns]
			�Z�N�V������
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	inline virtual const TCHAR* const GetIniSectionName(void) const { return INI_SECTION_GAINCOMPE; }


};// End CProcGaincompe



/*################################## (3) ####################################*/

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CProcPixelcompe
	[Purpose]
		��f�␳�����N���X
\////////////////////////////////////////////////////////////////////////////*/
class CProcPixelcompe : public CProcBase
{
public:
	CProcPixelcompe(void)
	{
		LoadParam();
	};
	~CProcPixelcompe(void)
	{
		delete this;
	};

private:
	
	
public:
	/*****************************************************************************\
		[Function]
			Execution
		[Purpose]
			�������s
		[Returns]
			���������ꍇ��TRUE��ԋp����
	\*****************************************************************************/
	virtual BOOL Execution(void)
	{
		MessageBox(NULL, _T("��f�␳����"), _T("�m�F"), MB_OK);
		return TRUE;
	}

	/*****************************************************************************\
		[Function]
			GetProckind
		[Purpose]
			�������ʂ��擾����
		[Returns]
			�������ʔԍ�
	\*****************************************************************************/
	inline virtual const int GetProckind(void) const { return PK_PIXEL_COMPE; }


protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			GetIniSectionName
		[Purpose]
			ini�t�@�C���Z�N�V���������擾����
		[Returns]
			�Z�N�V������
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	inline virtual const TCHAR* const GetIniSectionName(void) const { return INI_SECTION_PIXELCOMPE; }


};// End CProcPixelcompe



/*################################## (4) ####################################*/

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CProcFHDMonitor
	[Purpose]
		FHD_MonitorRAW�����N���X
\////////////////////////////////////////////////////////////////////////////*/
class CProcFHDMonitor : public CProcBase
{
public:
	CProcFHDMonitor(void)
	{
		LoadParam();
	};
	~CProcFHDMonitor(void)
	{
		delete this;
	};

private:
	
	
public:
	/*****************************************************************************\
		[Function]
			Execution
		[Purpose]
			�������s
		[Returns]
			���������ꍇ��TRUE��ԋp����
	\*****************************************************************************/
	virtual BOOL Execution(void)
	{
		MessageBox(NULL, _T("FHD_Monitor����"), _T("�m�F"), MB_OK);
		return TRUE;
	}

	/*****************************************************************************\
		[Function]
			GetProckind
		[Purpose]
			�������ʂ��擾����
		[Returns]
			�������ʔԍ�
	\*****************************************************************************/
	inline virtual const int GetProckind(void) const { return PK_FHD_MONITOR; }


protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			GetIniSectionName
		[Purpose]
			ini�t�@�C���Z�N�V���������擾����
		[Returns]
			�Z�N�V������
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	inline virtual const TCHAR* const GetIniSectionName(void) const { return INI_SECTION_FHD_MONITOR; }


};// End CProcFHDMonitor



/*################################## (5) ####################################*/

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CProcOpticaxis
	[Purpose]
		�����␳�����N���X
\////////////////////////////////////////////////////////////////////////////*/
class CProcOpticaxis : public CProcBase
{
public:
	CProcOpticaxis(void)
	{
		LoadParam();
	};
	~CProcOpticaxis(void)
	{
		delete this;
	};

private:
	
	
public:
	/*****************************************************************************\
		[Function]
			Execution
		[Purpose]
			�������s
		[Returns]
			���������ꍇ��TRUE��ԋp����
	\*****************************************************************************/
	virtual BOOL Execution(void)
	{
		MessageBox(NULL, _T("�����␳����"), _T("�m�F"), MB_OK);
		return TRUE;
	}

	/*****************************************************************************\
		[Function]
			GetProckind
		[Purpose]
			�������ʂ��擾����
		[Returns]
			�������ʔԍ�
	\*****************************************************************************/
	inline virtual const int GetProckind(void) const { return PK_OPTICAXIS; }


protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			GetIniSectionName
		[Purpose]
			ini�t�@�C���Z�N�V���������擾����
		[Returns]
			�Z�N�V������
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	inline virtual const TCHAR* const GetIniSectionName(void) const { return INI_SECTION_OPTICAXIS; }


};// End CProcOpticaxis



/*################################## (6) ####################################*/

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CProcDevelop
	[Purpose]
		���������N���X
\////////////////////////////////////////////////////////////////////////////*/
class CProcDevelop : public CProcBase
{
public:
	CProcDevelop(void)
	{
		LoadParam();
	};
	~CProcDevelop(void)
	{
		delete this;
	};

private:
	
	
public:
	/*****************************************************************************\
		[Function]
			Execution
		[Purpose]
			�������s
		[Returns]
			���������ꍇ��TRUE��ԋp����
	\*****************************************************************************/
	virtual BOOL Execution(void)
	{
		MessageBox(NULL, _T("��������"), _T("�m�F"), MB_OK);
		return TRUE;
	}

	/*****************************************************************************\
		[Function]
			GetProckind
		[Purpose]
			�������ʂ��擾����
		[Returns]
			�������ʔԍ�
	\*****************************************************************************/
	inline virtual const int GetProckind(void) const { return PK_DEVELOP; }
	
	
protected:
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\
		[Function]
			GetIniSectionName
		[Purpose]
			ini�t�@�C���Z�N�V���������擾����
		[Returns]
			�Z�N�V������
	\*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	inline virtual const TCHAR* const GetIniSectionName(void) const { return INI_SECTION_DEVELOP; }


};// End CProcDevelop

