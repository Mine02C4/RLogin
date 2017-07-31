#pragma once


// CProxyDlg �_�C�A���O

class CProxyDlg : public CDialog
{
	DECLARE_DYNAMIC(CProxyDlg)

public:
	CProxyDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CProxyDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PROXYDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	DECLARE_MESSAGE_MAP()

public:
	CString m_ServerName;
	CString m_PortName;
	CString m_UserName;
	CString m_PassWord;
	int m_ProxyMode;
	int m_SSLMode;

	afx_msg void OnProtoType(UINT nID);
	virtual BOOL OnInitDialog();
};
