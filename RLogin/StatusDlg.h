#pragma once

#include "Data.h"
#include "DialogExt.h"

// CStatusDlg �_�C�A���O

class CStatusDlg : public CDialogExt
{
	DECLARE_DYNAMIC(CStatusDlg)

// �R���X�g���N�V����
public:
	CStatusDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CStatusDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_STATUS_DLG };

public:
	CString m_Title;
	CString m_Status;
	CFont m_StatusFont;
	void *m_pValue;

	void GetStatusText(CString &status);
	void SetStatusText(LPCTSTR status);
	void AddStatusText(LPCTSTR status);

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();

// �C���v�������e�[�V����
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg void OnClose();
};
