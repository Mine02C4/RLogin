#if !defined(AFX_IDKEYDLG_H__EC4DF700_9033_47DC_919B_2F324A15997C__INCLUDED_)
#define AFX_IDKEYDLG_H__EC4DF700_9033_47DC_919B_2F324A15997C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IDKeyDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CIdKeyFileDlg �_�C�A���O

class CIdKeyFileDlg : public CDialog
{
// �R���X�g���N�V����
public:
	int m_OpenMode;
	CString m_Title;
	CIdKeyFileDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CIdKeyFileDlg)
	enum { IDD = IDD_IDKEYFILEDLG };
	CString	m_IdkeyFile;
	CString	m_PassName;
	CString	m_PassName2;
	CString	m_Message;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CIdKeyFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CIdKeyFileDlg)
	afx_msg void OnIdkeysel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_IDKEYDLG_H__EC4DF700_9033_47DC_919B_2F324A15997C__INCLUDED_)
