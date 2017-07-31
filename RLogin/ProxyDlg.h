#pragma once

// CProxyDlg �_�C�A���O

class CProxyDlg : public CDialog
{
	DECLARE_DYNAMIC(CProxyDlg)

// �R���X�g���N�V����
public:
	CProxyDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CProxyDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PROXYDLG };

public:
	CString m_ServerName;
	CString m_PortName;
	CString m_UserName;
	CString m_PassWord;
	int m_ProxyMode;
	int m_SSLMode;

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();

// �C���v�������e�[�V����
protected:
	afx_msg void OnProtoType(UINT nID);
	DECLARE_MESSAGE_MAP()
};
