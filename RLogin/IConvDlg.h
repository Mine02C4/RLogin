#if !defined(AFX_ICONVDLG_H__D1B96FC1_A63B_43A5_9294_B35B09DA31EC__INCLUDED_)
#define AFX_ICONVDLG_H__D1B96FC1_A63B_43A5_9294_B35B09DA31EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IConvDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CIConvDlg �_�C�A���O

class CIConvDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CIConvDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CIConvDlg)
	enum { IDD = IDD_ICONVDLG };
	//}}AFX_DATA
	CString	m_CharSet[4];


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CIConvDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CIConvDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ICONVDLG_H__D1B96FC1_A63B_43A5_9294_B35B09DA31EC__INCLUDED_)
