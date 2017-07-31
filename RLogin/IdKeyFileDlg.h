#pragma once

#include "DialogExt.h"

/////////////////////////////////////////////////////////////////////////////
// CIdKeyFileDlg �_�C�A���O

class CIdKeyFileDlg : public CDialogExt
{
	DECLARE_DYNAMIC(CIdKeyFileDlg)

// �R���X�g���N�V����
public:
	CIdKeyFileDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_IDKEYFILEDLG };

public:
	CString	m_IdkeyFile;
	CString	m_PassName;
	CString	m_PassName2;
	CStringLoad	m_Message;

	int m_OpenMode;
	CStringLoad m_Title;

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();
	virtual void OnOK();

// �C���v�������e�[�V����
protected:
	afx_msg void OnIdkeysel();
	DECLARE_MESSAGE_MAP()
};
