#pragma once

#include "DialogExt.h"

// CComInitDlg �_�C�A���O

class CComInitDlg : public CDialogExt
{
	DECLARE_DYNAMIC(CComInitDlg)

public:
	CComInitDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CComInitDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_COMINITDLG };

public:
	class CComSock *m_pSock;
	int m_ComIndex;
	CString m_BaudRate;
	int m_DataBits;
	int m_ParityBit;
	int m_StopBits;
	int m_FlowCtrl;
	CString m_UserDef;
	WORD m_XoffLim;
	WORD m_XonLim;
	char m_XonChar;
	char m_XoffChar;
	int m_SendWait[2];
	CStringIndex m_ComDevList;

	BOOL CComInitDlg::GetComDeviceList();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();
	virtual void OnOK();

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedUserflow();
	afx_msg void OnBnClickedDefconf();
	afx_msg void OnCbnSelchangeComdevlist();
};
