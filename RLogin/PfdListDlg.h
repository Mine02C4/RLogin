#if !defined(AFX_PFDLISTDLG_H__05A17F54_1C87_49D0_AB61_2836AABF3FDC__INCLUDED_)
#define AFX_PFDLISTDLG_H__05A17F54_1C87_49D0_AB61_2836AABF3FDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PfdListDlg.h : �w�b�_�[ �t�@�C��
//

#include "ListCtrlExt.h"

/////////////////////////////////////////////////////////////////////////////
// CPfdListDlg �_�C�A���O

class CPfdListDlg : public CDialog
{
// �R���X�g���N�V����
public:
	class CParamTab *m_pData;
	class CServerEntry *m_pEntry;
	BOOL m_ModifiedFlag;
	void InitList();
	CPfdListDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CPfdListDlg)
	enum { IDD = IDD_PFDLISTDLG };
	CListCtrlExt	m_List;
	//}}AFX_DATA
	BOOL m_X11PortFlag;
	CString m_XDisplay;

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CPfdListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CPfdListDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPfdNew();
	afx_msg void OnPfdEdit();
	afx_msg void OnPfdDel();
	afx_msg void OnDblclkPfdlist(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg void OnEditDups();
	afx_msg void OnUpdateEditEntry(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdateItem();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PFDLISTDLG_H__05A17F54_1C87_49D0_AB61_2836AABF3FDC__INCLUDED_)
