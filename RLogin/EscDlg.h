#pragma once

#include "afxcmn.h"
#include "ListCtrlExt.h"
#include "DialogExt.h"

// CEscDlg �_�C�A���O

class CEscDlg : public CDialogExt
{
	DECLARE_DYNAMIC(CEscDlg)

// �R���X�g���N�V����
public:
	CEscDlg(CWnd* pParent = NULL);
	virtual ~CEscDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ESCDLG };

public:
	CListCtrlExt m_EscList;
	CListCtrlExt m_CsiList;
	CListCtrlExt m_DcsList;
	CListCtrlExt m_ParaList;

public:
	CTextRam *m_pTextRam;
	CProcTab *m_pProcTab;
	LPCTSTR *m_DefEsc;
	LPCTSTR *m_DefCsi;
	LPCTSTR *m_DefDcs;
	CString *m_NewEsc;
	CString *m_NewCsi;
	CString *m_NewDcs;
	int m_TermPara[5];

	void InitEscList();
	void InitCsiList();
	void InitDcsList();
	void InitParaList();

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();
	virtual void OnOK();

// �C���v�������e�[�V����
protected:
	afx_msg void OnNMDblclkEsclist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkCsilist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkDcslist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedReset();
	DECLARE_MESSAGE_MAP()
};
