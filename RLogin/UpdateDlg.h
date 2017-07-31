#if !defined(AFX_UPDATEDLG_H__AB223F2C_26CF_470A_949A_3FFB6683F923__INCLUDED_)
#define AFX_UPDATEDLG_H__AB223F2C_26CF_470A_949A_3FFB6683F923__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdateDlg.h : �w�b�_�[ �t�@�C��
//

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
// �R���X�g���N�V����
public:
	int m_DoExec;
	int m_DoResume;
	CUpdateDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CUpdateDlg)
	enum { IDD = IDD_UPDATEDLG };
	CString	m_FileName;
	int		m_Jobs;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CUpdateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CUpdateDlg)
	afx_msg void OnExec();
	afx_msg void OnAllExec();
	afx_msg void OnAbort();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_UPDATEDLG_H__AB223F2C_26CF_470A_949A_3FFB6683F923__INCLUDED_)
