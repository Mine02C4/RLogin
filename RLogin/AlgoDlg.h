#if !defined(AFX_ALGODLG_H__E8F1EDB4_475E_4080_860F_4743CEE9751F__INCLUDED_)
#define AFX_ALGODLG_H__E8F1EDB4_475E_4080_860F_4743CEE9751F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlgoDlg.h : �w�b�_�[ �t�@�C��
//
#include "ListCtrlMove.h"
#include "Data.h"

/////////////////////////////////////////////////////////////////////////////
// CAlgoDlg �_�C�A���O

class CAlgoDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CParamTab *m_pData;
	
	CAlgoDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAlgoDlg)
	enum { IDD = IDD_ALGOPARADLG };
	//}}AFX_DATA
	CListCtrlMove m_List[12];
	BOOL m_EncShuffle;
	BOOL m_MacShuffle;

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAlgoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAlgoDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ALGODLG_H__E8F1EDB4_475E_4080_860F_4743CEE9751F__INCLUDED_)
