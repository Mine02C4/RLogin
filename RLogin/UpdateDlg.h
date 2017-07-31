#pragma once

#define	UDO_OVERWRITE		0
#define	UDO_MTIMECHECK		1
#define	UDO_UPDCHECK		2
#define	UDO_RESUME			3
#define	UDO_NOUPDATE		4
#define	UDO_ABORT			10

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg �_�C�A���O

class CUpdateDlg : public CDialog
{
	DECLARE_DYNAMIC(CUpdateDlg)

// �R���X�g���N�V����
public:
	CUpdateDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_UPDATEDLG };

public:
	CString	m_FileName;
	int		m_Jobs;

	int m_DoExec;
	int m_DoResume;

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();

// �C���v�������e�[�V����
protected:
	afx_msg void OnExec();
	afx_msg void OnAllExec();
	afx_msg void OnAbort();
	DECLARE_MESSAGE_MAP()
};
