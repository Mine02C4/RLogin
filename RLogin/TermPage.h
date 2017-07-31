#pragma once

#include "afxwin.h"
#include "ListCtrlExt.h"

/////////////////////////////////////////////////////////////////////////////
// CTermPage �_�C�A���O

class CTermPage : public CTreePage
{
	DECLARE_DYNCREATE(CTermPage)

// �R���X�g���N�V����
public:
	CTermPage();
	~CTermPage();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_TERMPAGE };

public:
	CProcTab m_ProcTab;
	CListCtrlExt m_OptList;

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
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedEscedit();
	afx_msg void OnNMClickOptlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnGetInfoTipEsclist(NMHDR *pNMHDR, LRESULT *pResult);
};
