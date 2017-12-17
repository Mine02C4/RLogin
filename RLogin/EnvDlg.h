#pragma once

#include "afxcmn.h"
#include "ListCtrlExt.h"
#include "DialogExt.h"

// CEnvDlg �_�C�A���O

class CEnvDlg : public CDialogExt
{
	DECLARE_DYNAMIC(CEnvDlg)

// �R���X�g���N�V����
public:
	CEnvDlg(CWnd* pParent = NULL);
	virtual ~CEnvDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ENVDLG };

public:
	CStringIndex m_Env;
	CListCtrlExt m_List;
	BOOL m_ListUpdate;

	void InitList();

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();
	virtual void OnOK();

// �C���v�������e�[�V����
protected:
	afx_msg void OnBnClickedInfocap();
	afx_msg void OnHdnItemchangedEnvList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEditNew();
	afx_msg void OnEditUpdate();
	afx_msg void OnEditDelete();
	afx_msg void OnEditDups();
	DECLARE_MESSAGE_MAP()
};
