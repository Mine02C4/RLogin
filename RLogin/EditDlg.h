#if !defined(AFX_EDITDLG_H__3257BE5A_3B06_4EF0_A85E_E1784808AA58__INCLUDED_)
#define AFX_EDITDLG_H__3257BE5A_3B06_4EF0_A85E_E1784808AA58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CEditDlg �_�C�A���O

class CEditDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CEditDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CEditDlg)
	enum { IDD = IDD_EDITDLG };
	CString	m_Edit;
	CString	m_Title;
	CString m_WinText;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CEditDlg)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_EDITDLG_H__3257BE5A_3B06_4EF0_A85E_E1784808AA58__INCLUDED_)
