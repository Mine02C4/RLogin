#if !defined(AFX_PROGDLG_H__04AEE5BF_73E6_479A_9221_42DC9C407DBA__INCLUDED_)
#define AFX_PROGDLG_H__04AEE5BF_73E6_479A_9221_42DC9C407DBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CProgDlg �_�C�A���O

class CProgDlg : public CDialog
{
// �R���X�g���N�V����
public:
	int m_Div;
	LONGLONG m_LastSize;
	LONGLONG m_ResumeSize;
	clock_t m_StartClock;
	BOOL m_AbortFlag;
	class CExtSocket *m_pSock;

	void SetRange(LONGLONG max, LONGLONG rem);
	void SetPos(LONGLONG pos);
	void SetFileName(LPCSTR file);
	void SetMessage(LPCSTR msg);

	CProgDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CProgDlg)
	enum { IDD = IDD_PROGDLG };
	CProgressCtrl	m_FileSize;
	CString	m_EndTime;
	CString	m_TotalSize;
	CString	m_TransRate;
	CString	m_FileName;
	CString m_Message;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CProgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CProgDlg)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PROGDLG_H__04AEE5BF_73E6_479A_9221_42DC9C407DBA__INCLUDED_)
