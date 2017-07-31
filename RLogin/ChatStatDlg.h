#pragma once

#include "afxwin.h"
#include "afxcmn.h"

// CChatStatDlg �_�C�A���O

class CChatStatDlg : public CDialog
{
	DECLARE_DYNAMIC(CChatStatDlg)

// �R���X�g���N�V����
public:
	CChatStatDlg(CWnd* pParent = NULL);
	virtual ~CChatStatDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_CHATSTAT };

public:
	int m_Counter;
	CEdit m_Status;
	CStatic m_Title;
	CProgressCtrl m_TimeProg;

public:
	void SetStaus(LPCTSTR str);

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();
	virtual void OnOK();

// �C���v�������e�[�V����
protected:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
};
