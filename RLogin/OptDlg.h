#if !defined(AFX_OPTDLG_H__62A00652_C3C5_4FF6_8FDF_89A5AFB8EDBE__INCLUDED_)
#define AFX_OPTDLG_H__62A00652_C3C5_4FF6_8FDF_89A5AFB8EDBE__INCLUDED_

#include "SerEntPage.h"
#include "TermPage.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "ScrnPage.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "ProtoPage.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "CharSetPage.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "ColParaDlg.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "KeyPage.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "HisPage.h"	// ClassView �ɂ���Ēǉ�����܂����B

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// COptDlg

class COptDlg : public CPropertySheet
{
	DECLARE_DYNAMIC(COptDlg)

// �R���X�g���N�V����
public:
	COptDlg(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	COptDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(COptDlg)
	public:
	virtual BOOL OnInitDialog();
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	CButton m_DoInit;
	CButton m_DoAppDmy;

	CSerEntPage m_SerEntPage;
	CKeyPage m_KeyPage;
	CColParaDlg m_ColorPage;
	CCharSetPage m_CharSetPage;
	CProtoPage m_ProtoPage;
	CTermPage m_TermPage;
	CScrnPage m_ScrnPage;
	CHisPage m_HisPage;

	CServerEntry *m_pEntry;
	CTextRam *m_pTextRam;
	CKeyNodeTab *m_pKeyTab;
	CParamTab *m_pParamTab;
	class CRLoginDoc *m_pDocument;

#define	UMOD_ENTRY		001
#define	UMOD_TEXTRAM	002
#define	UMOD_KEYTAB		004
#define	UMOD_PARAMTAB	010
	int m_ModFlag;

	virtual ~COptDlg();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(COptDlg)
	//}}AFX_MSG
	afx_msg void OnDoInit();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_OPTDLG_H__62A00652_C3C5_4FF6_8FDF_89A5AFB8EDBE__INCLUDED_)
