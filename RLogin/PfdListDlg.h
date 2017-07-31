#pragma once

#include "ListCtrlExt.h"

/////////////////////////////////////////////////////////////////////////////
// CPfdListDlg �_�C�A���O

class CPfdListDlg : public CDialog
{
	DECLARE_DYNAMIC(CPfdListDlg)

// �R���X�g���N�V����
public:
	CPfdListDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PFDLISTDLG };

public:
	class CServerEntry *m_pEntry;
	CListCtrlExt	m_List;
	CStringArrayExt m_PortFwd;
	BOOL m_X11PortFlag;
	CString m_XDisplay;

	void InitList();

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();
	virtual void OnOK();

// �C���v�������e�[�V����
protected:
	afx_msg void OnPfdNew();
	afx_msg void OnPfdEdit();
	afx_msg void OnPfdDel();
	afx_msg void OnDblclkPfdlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditDups();
	afx_msg void OnUpdateEditEntry(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};
