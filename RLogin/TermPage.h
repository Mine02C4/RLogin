#include "afxwin.h"
#if !defined(AFX_TERMPAGE_H__2EBB49D9_A9BC_47C5_BF83_CB0E6952429B__INCLUDED_)
#define AFX_TERMPAGE_H__2EBB49D9_A9BC_47C5_BF83_CB0E6952429B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TermPage.h : �w�b�_�[ �t�@�C��
//

#include "ListCtrlExt.h"

/////////////////////////////////////////////////////////////////////////////
// CTermPage �_�C�A���O

class CTermPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CTermPage)

// �R���X�g���N�V����
public:
	class COptDlg *m_pSheet;
	CTermPage();
	~CTermPage();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CTermPage)
	enum { IDD = IDD_TERMPAGE };
	//}}AFX_DATA
	BOOL m_Check[10];
	CString m_LogFile;
	int m_LogMode;
	int m_LogCode;
	CProcTab m_ProcTab;
	CListCtrlExt m_List;
	int m_TtlMode;
	BOOL m_TtlRep;
	BOOL m_TtlCng;

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CTermPage)
	public:
	virtual BOOL OnApply();
	virtual void OnReset();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CTermPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg void OnUpdateCheck(UINT nId);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAutologSel();
	afx_msg void OnBnClickedEscedit();
	afx_msg void OnNMClickEsclist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCombo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_TERMPAGE_H__2EBB49D9_A9BC_47C5_BF83_CB0E6952429B__INCLUDED_)
