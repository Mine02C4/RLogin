#pragma once

/////////////////////////////////////////////////////////////////////////////
// CPassDlg �_�C�A���O

class CPassDlg : public CDialog
{
	DECLARE_DYNAMIC(CPassDlg)

// �R���X�g���N�V����
public:
	CPassDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PASSDLG };

public:
	CProgressCtrl m_TimeLimit;
	CString m_HostAddr;
	CString	m_UserName;
	CString	m_PassName;
	CString	m_Prompt;

	CString m_Title;
	int m_Counter;
	int m_MaxTime;

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();

// �C���v�������e�[�V����
protected:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
};
