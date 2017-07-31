#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CChatStatDlg �_�C�A���O

class CChatStatDlg : public CDialog
{
	DECLARE_DYNAMIC(CChatStatDlg)

public:
	CChatStatDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CChatStatDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_CHATSTAT };

protected:
	virtual void OnOK();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()

public:
	int m_Counter;
	CEdit m_Status;
	CStatic m_Title;
	CProgressCtrl m_TimeProg;

	void SetStaus(LPCSTR str);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
