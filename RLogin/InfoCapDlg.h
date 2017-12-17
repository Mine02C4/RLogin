#pragma once

#include "afxcmn.h"
#include "afxwin.h"
#include "ListCtrlExt.h"
#include "Data.h"
#include "DialogExt.h"

// CInfoCapDlg �_�C�A���O

class CInfoCapDlg : public CDialogExt
{
	DECLARE_DYNAMIC(CInfoCapDlg)

// �R���X�g���N�V����
public:
	CInfoCapDlg(CWnd* pParent = NULL);
	virtual ~CInfoCapDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_INFOCAPDLG };

public:
	CComboBox m_Entry;
	CListCtrlExt m_List;

public:
	CString m_TermCap;
	CString m_TermInfo;
	CStringBinary m_InfoIndex;
	CStringBinary m_CapIndex;
	CString m_EntryName;
	CStringBinary *m_pIndex;
	CStringBinary m_CapName;
	CStringArray m_CapNode;
	CString m_WorkStr;
	
	void SetNode(CStringIndex &cap, LPCTSTR p);
	void SetEntry(CStringIndex &cap, LPCTSTR entry);
	void SetCapName(CStringIndex &cap, LPCTSTR name);
	void LoadCapFile(LPCTSTR filename);
	void LoadInfoFile(LPCTSTR filename);
	void SetList(CStringIndex &cap, CStringBinary &index);
	LPCTSTR InfoToCap(LPCTSTR p, BOOL *pe);
	LPCTSTR CapToInfo(LPCTSTR p, BOOL *pe);
	int GetOneChar(LPCTSTR *pp, BOOL bPar = TRUE);
	void SetEscStr(LPCTSTR str, CBuffer &out);
	void SetCapStr(BOOL lf = FALSE);
	void SetInfoStr(BOOL lf = FALSE);

	void InfoNameToCapName(CStringBinary &tab);

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();
	virtual void OnOK();

// �C���v�������e�[�V����
protected:
	afx_msg void OnBnClickedLoadcap();
	afx_msg void OnBnClickedLoadinfo();
	afx_msg void OnCbnSelchangeEntry();
	afx_msg void OnCapInport();
	afx_msg void OnCapExport();
	afx_msg void OnCapClipbord();
	afx_msg void OnInfoInport();
	afx_msg void OnInfoExport();
	afx_msg void OnInfoClipbord();
	DECLARE_MESSAGE_MAP()
};
