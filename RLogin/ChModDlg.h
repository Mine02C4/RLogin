#if !defined(AFX_CHMODDLG_H__BAB8AA2E_642D_432D_8AA9_577E07A2C736__INCLUDED_)
#define AFX_CHMODDLG_H__BAB8AA2E_642D_432D_8AA9_577E07A2C736__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChModDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CChModDlg �_�C�A���O

class CChModDlg : public CDialog
{
// �R���X�g���N�V����
public:
	int m_Attr;
	CChModDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CChModDlg)
	enum { IDD = IDD_CHMODDLG };
	//}}AFX_DATA
	BOOL	m_Mode[9];


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CChModDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CChModDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CHMODDLG_H__BAB8AA2E_642D_432D_8AA9_577E07A2C736__INCLUDED_)
