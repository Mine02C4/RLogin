#if !defined(AFX_LISTCTRLMOVE_H__4197EC8E_98EE_4FB3_8322_AE8CFB79AB1F__INCLUDED_)
#define AFX_LISTCTRLMOVE_H__4197EC8E_98EE_4FB3_8322_AE8CFB79AB1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrlMove.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CListCtrlMove �E�B���h�E

class CListCtrlMove : public CListCtrl
{
// �R���X�g���N�V����
public:
	CListCtrlMove();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CListCtrlMove)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CListCtrlMove();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CListCtrlMove)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_LISTCTRLMOVE_H__4197EC8E_98EE_4FB3_8322_AE8CFB79AB1F__INCLUDED_)
