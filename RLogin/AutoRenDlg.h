#pragma once

// CAutoRenDlg �_�C�A���O

class CAutoRenDlg : public CDialog
{
	DECLARE_DYNAMIC(CAutoRenDlg)

// �R���X�g���N�^
public:
	CAutoRenDlg(CWnd* pParent = NULL);
	virtual ~CAutoRenDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_AUTORENDLG };

public:
	int m_Exec;
	CString m_Name[3];
	CString m_NameOK;

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();

// �C���v�������e�[�V����
protected:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnUpdateEdit3();
	DECLARE_MESSAGE_MAP()
};
