#pragma once

/////////////////////////////////////////////////////////////////////////////
// CChModDlg �_�C�A���O

class CChModDlg : public CDialog
{
	DECLARE_DYNAMIC(CChModDlg)

// �R���X�g���N�V����
public:
	CChModDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_CHMODDLG };

public:
	int m_Attr;
	BOOL	m_Mode[9];

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();
	virtual void OnOK();

// �C���v�������e�[�V����
protected:
	DECLARE_MESSAGE_MAP()
};
