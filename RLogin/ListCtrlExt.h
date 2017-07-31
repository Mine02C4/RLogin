#pragma once

/////////////////////////////////////////////////////////////////////////////
// CListCtrlExt �E�B���h�E

class CListCtrlExt : public CListCtrl
{
// �R���X�g���N�V����
public:
	CListCtrlExt();
	virtual ~CListCtrlExt();

// �I�y���[�V����
public:
	int m_SortSubItem;
	int m_SortReverse;
	int m_SortDupItem;
	CMenu m_PopUpMenu;
	CMenu *m_pSubMenu;

	int m_EditSubItem;
	int m_EditFlag;
	int m_EditItem;
	int m_EditNum;
	CEdit m_EditWnd;
	CString m_EditOld;
	BOOL m_bSort;

	int GetParamItem(int para);
	int GetSelectMarkData();
	void DoSortItem();
	void InitColumn(LPCTSTR lpszSection, const LV_COLUMN *lpColumn, int nMax);
	void SaveColumn(LPCTSTR lpszSection);
	void SetLVCheck(WPARAM ItemIndex, BOOL bCheck);
	BOOL GetLVCheck(WPARAM ItemIndex);
	void SetPopUpMenu(UINT nIDResource, int Pos);
	void OpenEditBox(int item, int num, int fmt, CRect &rect);
	void EditItem(int item, int num);

// �I�[�o�[���C�h
protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// �C���v�������e�[�V����
protected:
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillfocusEditBox();
	DECLARE_MESSAGE_MAP()
};
