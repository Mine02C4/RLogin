#pragma once

#include "ListCtrlExt.h"
#include "Data.h"
#include "afxcmn.h"

/////////////////////////////////////////////////////////////////////////////
// CServerSelect �_�C�A���O

class CServerSelect : public CDialog
{
	DECLARE_DYNAMIC(CServerSelect)

// �R���X�g���N�V����
	CServerSelect(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SERVERLIST };

public:
	CListCtrlExt m_List;
	CTabCtrl m_Tab;

// �N���X�f�[�^
public:
	int m_EntryNum;
	int m_MinWidth;
	int m_MinHeight;
	CString m_Group;
	CStringIndex m_TabEntry;
	class CServerEntryTab *m_pData;
	BOOL m_ShowTabWnd;

// �N���X�t�@���N�V����
public:
	void InitList();
	void InitItemOffset();
	void SetItemOffset(int cx, int cy);
	void UpdateTabWnd();

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();
	virtual void OnOK();

// �C���v�������e�[�V����
protected:
	afx_msg void OnNewentry();
	afx_msg void OnEditentry();
	afx_msg void OnDelentry();
	afx_msg void OnDblclkServerlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditCopy();
	afx_msg void OnEditCheck();
	afx_msg void OnServInport();
	afx_msg void OnServExport();
	afx_msg void OnUpdateEditEntry(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnTcnSelchangeServertab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnServProto();
	afx_msg void OnSavedefault();
	afx_msg void OnServExchng();
	afx_msg void OnUpdateServExchng(CCmdUI *pCmdUI);
	DECLARE_MESSAGE_MAP()
};
