#pragma once

/////////////////////////////////////////////////////////////////////////////
// CEditDlg �_�C�A���O

class CEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditDlg)

// �R���X�g���N�V����
public:
	CEditDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_EDITDLG };

public:
	CString	m_Edit;
	CString	m_Title;

	CString m_WinText;

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();

// �C���v�������e�[�V����
protected:
	DECLARE_MESSAGE_MAP()
};
