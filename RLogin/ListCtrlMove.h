#pragma once

/////////////////////////////////////////////////////////////////////////////
// CListCtrlMove �E�B���h�E

class CListCtrlMove : public CListCtrl
{
// �R���X�g���N�V����
public:
	CListCtrlMove();
	virtual ~CListCtrlMove();

// �I�y���[�V����
public:

// �I�[�o�[���C�h
protected:

// �C���v�������e�[�V����
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
};
