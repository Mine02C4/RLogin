#if !defined(AFX_CHARSETPAGE_H__D11C4465_3725_4437_A251_DA9869F56412__INCLUDED_)
#define AFX_CHARSETPAGE_H__D11C4465_3725_4437_A251_DA9869F56412__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CharSetPage.h : �w�b�_�[ �t�@�C��
//

#include "ListCtrlExt.h"

/////////////////////////////////////////////////////////////////////////////
// CCharSetPage �_�C�A���O

class CCharSetPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCharSetPage)

// �R���X�g���N�V����
public:
	class COptDlg *m_pSheet;
	class CTextRam *m_pData;
	class CFontTab m_FontTab;
	void InitList();
	CCharSetPage();
	~CCharSetPage();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CCharSetPage)
	enum { IDD = IDD_CHARSETPAGE };
	CListCtrlExt	m_List;
	int		m_KanjiCode;
	int		m_CharBankGL;
	int		m_CharBankGR;
	CString	m_CharBank1;
	CString	m_CharBank2;
	CString	m_CharBank3;
	CString	m_CharBank4;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CCharSetPage)
	public:
	virtual BOOL OnApply();
	virtual void OnReset();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CCharSetPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnFontListNew();
	afx_msg void OnFontListEdit();
	afx_msg void OnFontListDel();
	afx_msg void OnIconvSet();
	afx_msg void OnDblclkFontlist(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg void OnCharSet(UINT nId);
	afx_msg void OnUpdateCheck(UINT nId);
	afx_msg void OnEditDups();
	afx_msg void OnUpdateEditEntry(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CHARSETPAGE_H__D11C4465_3725_4437_A251_DA9869F56412__INCLUDED_)
