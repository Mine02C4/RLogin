#if !defined(AFX_PASSDLG_H__C6105632_C787_472B_8B8A_70302DB393EE__INCLUDED_)
#define AFX_PASSDLG_H__C6105632_C787_472B_8B8A_70302DB393EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PassDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CPassDlg �_�C�A���O

class CPassDlg : public CDialog
{
// �R���X�g���N�V����
public:
	int m_Counter;
	int m_MaxTime;
	CString m_Title;
	CPassDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CPassDlg)
	enum { IDD = IDD_PASSDLG };
	CProgressCtrl	m_TimeLimit;
	CString m_HostAddr;
	CString	m_UserName;
	CString	m_PassName;
	CString	m_Prompt;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CPassDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CPassDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PASSDLG_H__C6105632_C787_472B_8B8A_70302DB393EE__INCLUDED_)
