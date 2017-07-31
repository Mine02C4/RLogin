#pragma once

#include "afxwin.h"
#include "ListCtrlExt.h"

/////////////////////////////////////////////////////////////////////////////
// CTermPage �_�C�A���O

class CTermPage : public CTreePropertyPage
{
	DECLARE_DYNCREATE(CTermPage)

// �R���X�g���N�V����
public:
	CTermPage();
	~CTermPage();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_TERMPAGE };

public:
	BOOL m_Check[10];
	CProcTab m_ProcTab;
	CListCtrlExt m_List;

public:
	void DoInit();

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();

public:
	virtual BOOL OnApply();
	virtual void OnReset();

// �C���v�������e�[�V����
protected:
	afx_msg void OnUpdateCheck(UINT nId);
	afx_msg void OnBnClickedEscedit();
	afx_msg void OnNMClickEsclist(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
};
