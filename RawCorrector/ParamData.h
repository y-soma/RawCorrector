#pragma once

/*////////////////////////////////////////////////////////////////////////////\
	[Class]
		CParamData
	[Purpose]
		�p�����[�^�f�[�^�Ǘ��N���X
\////////////////////////////////////////////////////////////////////////////*/
class CParamData
{
public:
	CParamData(void):
	  m_ProcName(NULL),
	  m_LoadFlg(FALSE),
	  m_IniSection(NULL)
	{};
	~CParamData(void){};

private:
	// ������
	const TCHAR* m_ProcName;
	// �p�����[�^�ǂݍ��݃t���O
	BOOL m_LoadFlg;
	// �p�����[�^�f�[�^
	std::vector<ParamValue> m_Data;
	// ini�t�@�C���Z�N�V������
	const TCHAR* m_IniSection;

public:
	/*****************************************************************************\
		[Function]
			IsLoadParam
		[Purpose]
			�p�����[�^�ǂݍ��݃t���O���擾����
		[Returns]
			�t���O
	\*****************************************************************************/
	inline const BOOL IsLoadParam(void) const { return m_LoadFlg; }

	
	/*****************************************************************************\
		[Function]
			SetProcname
		[Purpose]
			��������o�^����
		[Parameter1] name
			������
	\*****************************************************************************/
	inline void SetProcname(const String& name) { m_ProcName = GFunc::StrCopy(name.c_str(), name.length()); }
	
	
	/*****************************************************************************\
		[Function]
			GetProcname
		[Purpose]
			���������擾����
		[Returns]
			������
	\*****************************************************************************/
	inline const TCHAR* const GetProcname(void) const { return m_ProcName; }


	/*****************************************************************************\
		[Function]
			GetSectionName
		[Purpose]
			���������擾����
		[Returns]
			������
	\*****************************************************************************/
	inline const TCHAR* const GetSectionName(void) const { return m_IniSection; }


	/*****************************************************************************\
		[Function]
			GetParam
		[Purpose]
			�p�����[�^�f�[�^���擾����
		[Returns]
			�p�����[�^�f�[�^
	\*****************************************************************************/
	inline const std::vector<ParamValue>& GetParamValue(void) const { return m_Data; }


	/*****************************************************************************\
		[Function]
			LoadParam
		[Purpose]
			ini�t�@�C������p�����[�^��ǂݍ��݁A�f�[�^���i�[����
			�f�[�^�͓ǂݍ��񂾕������ǉ�����Ă���
		[Parameter1] section
			�Z�N�V������
		\*****************************************************************************/
	void LoadParam(const String& section)
	{
		m_IniSection = GFunc::StrCopy(section.c_str(), section.length());
		// 1�Z�N�V�������̑S�Ẵp�����[�^��ǂݍ���
		const std::vector<String> prm = GFunc::GetIniAllSection(INI_FILENAME, m_IniSection);
		if(prm.size() < 1) return;
		int add = 0;
		for(UINT i=0; i<prm.size(); i++)
		{
			const std::vector<String> split_str = GFunc::Split(prm[i].c_str(), _T("="));
			if(split_str.size() > 1)
			{
				ParamValue dummy;
				m_Data.push_back(dummy);
				m_Data[add].param_name = GFunc::StrCopy(split_str[0].c_str(), split_str[0].length());
				m_Data[add].val = GFunc::StrCopy(split_str[1].c_str(), split_str[1].length());
				++add;
			}
		}
		m_LoadFlg = TRUE;
	}


	/*****************************************************************************\
		[Function]
			ReLoadParam
		[Purpose]
			ini�t�@�C������p�����[�^��ǂݍ��݁A�f�[�^���i�[����
			������͈�x���܂ł̃f�[�^���폜���Ă���A�V�������̂�ǂ݂���
		[Parameter1] section
			�Z�N�V������
	\*****************************************************************************/
	void ReLoadParam(const String& section)
	{
		m_Data.clear();
		LoadParam(section);
	}


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
		for(UINT i=0; i<m_Data.size(); i++)
		{
			if(!lstrcmpi(m_Data[i].param_name, param_name))
			{
				m_Data[i].val = GFunc::StrCopy(val.c_str(), val.length());
				break;
			}
		}
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
		if(m_Data.size() < index+1)
			return;
		m_Data[index].val = GFunc::StrCopy(val.c_str(), val.length());
	}


	/*****************************************************************************\
		[Function]
			UpdateIni
		[Purpose]
			���ݕێ����Ă���f�[�^��ini�t�@�C�����X�V����
	\*****************************************************************************/
	void UpdateIni(void)
	{
		for(UINT i=0; i<m_Data.size(); i++)
			GFunc::WriteIniParam(INI_FILENAME, m_IniSection, m_Data[i].param_name, m_Data[i].val);
	}


};// End CParamData