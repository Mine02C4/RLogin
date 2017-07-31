#pragma once
#include "afxcmn.h"
#include "RegEx.h"
#include "Data.h"
#include "afxwin.h"


// CChatDlg �_�C�A���O

class CChatDlg : public CDialog
{
	DECLARE_DYNAMIC(CChatDlg)

public:
	CChatDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CChatDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_CHATDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_NodeTree;
	CString m_RecvStr;
	CString m_SendStr;
	CButton m_UpdNode;
	CButton m_DelNode;
	CStrScript m_Script;

	virtual BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedNewnode();
	afx_msg void OnBnClickedNextnode();
	afx_msg void OnBnClickedUpdatenode();
	afx_msg void OnBnClickedDelnode();
	afx_msg void OnTvnSelchangedNodetree(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL m_MakeChat;
	afx_msg void OnTvnDeleteitemNodetree(NMHDR *pNMHDR, LRESULT *pResult);
};
