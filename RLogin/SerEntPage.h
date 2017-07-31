#if !defined(AFX_SERENTPAGE_H__2E276794_7C77_47D8_A0C3_64C182B45077__INCLUDED_)
#define AFX_SERENTPAGE_H__2E276794_7C77_47D8_A0C3_64C182B45077__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SerEntPage.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CSerEntPage �_�C�A���O

class CSerEntPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSerEntPage)

// �R���X�g���N�V����
public:
	class CServerEntryTab *m_pTab;
	class COptDlg *m_pSheet;
	CString m_DefComPort;
	CString m_IdkeyName;
	int m_ProxyMode;
	CString m_ProxyHost;
	CString m_ProxyPort;
	CString m_ProxyUser;
	CString m_ProxyPass;
	CString m_ExtEnvStr;

	void SetEnableWind();
	CSerEntPage();
	~CSerEntPage();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSerEntPage)
	enum { IDD = IDD_SERENTPAGE };
	CString	m_EntryName;
	CString	m_HostName;
	CString	m_PortName;
	CString	m_UserName;
	CString	m_PassName;
	CString	m_TermName;
	int		m_KanjiCode;
	int		m_ProtoType;
	CString m_Memo;
	//}}AFX_DATA

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CSerEntPage)
	public:
	virtual BOOL OnApply();
	virtual void OnReset();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSerEntPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnComconfig();
	afx_msg void OnKeyfileselect();
	//}}AFX_MSG
	afx_msg void OnProtoType(UINT nID);
	afx_msg void OnUpdateCheck(UINT nId);
	afx_msg void OnUpdateEdit();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnChatEdit();
	afx_msg void OnProxySet();
	afx_msg void OnBnClickedTermcap();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SERENTPAGE_H__2E276794_7C77_47D8_A0C3_64C182B45077__INCLUDED_)
