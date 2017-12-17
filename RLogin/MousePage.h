#pragma once

// CMousePage �_�C�A���O

class CMousePage : public CTreePage
{
	DECLARE_DYNAMIC(CMousePage)

public:
	CMousePage();
	virtual ~CMousePage();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_MOUSEPAGE };

public:
	BOOL m_Check[10];
	CString	m_WheelSize;
	int m_MouseMode[4];
	int m_DropMode;
	CString m_DropCmd[8];
	CString m_CmdWork;

	void DoInit();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();

public:
	virtual BOOL OnApply();
	virtual void OnReset();

protected:
	afx_msg void OnUpdateCheck(UINT nId);
	afx_msg void OnUpdateEdit();
	afx_msg void OnUpdateChangeDropMode();
	afx_msg void OnCbnSelchangeDropMode();
	DECLARE_MESSAGE_MAP()
};
