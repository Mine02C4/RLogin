#if !defined(AFX_KEYPARADLG_H__7F65EA92_9A49_421E_BCB6_54D6E763AE37__INCLUDED_)
#define AFX_KEYPARADLG_H__7F65EA92_9A49_421E_BCB6_54D6E763AE37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KeyParaDlg.h : �w�b�_�[ �t�@�C��
//

#include "Data.h"

/////////////////////////////////////////////////////////////////////////////
// CKeyParaDlg �_�C�A���O

class CKeyParaDlg : public CDialog
{
// �R���X�g���N�V����
public:
	class CKeyNode *m_pData;

	CKeyParaDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CKeyParaDlg)
	enum { IDD = IDD_KEYPARADLG };
	BOOL	m_WithShift;
	BOOL	m_WithCtrl;
	BOOL	m_WithAlt;
	BOOL	m_WithAppli;
	CString	m_KeyCode;
	CString	m_Maps;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CKeyParaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CKeyParaDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_KEYPARADLG_H__7F65EA92_9A49_421E_BCB6_54D6E763AE37__INCLUDED_)
