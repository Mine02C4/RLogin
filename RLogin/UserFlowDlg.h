#pragma once

#include "DialogExt.h"

// CUserFlowDlg �_�C�A���O

class CUserFlowDlg : public CDialogExt
{
	DECLARE_DYNAMIC(CUserFlowDlg)

public:
	CUserFlowDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CUserFlowDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_USERFLOWDLG };

	DCB *m_pDCB;
	int m_Value[6];
	BOOL m_Check[6];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();
	virtual void OnOK();

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnUpdate(UINT nID);
};
