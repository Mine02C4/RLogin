#pragma once

#include "DialogExt.h"

/////////////////////////////////////////////////////////////////////////////
// CPfdParaDlg �_�C�A���O

class CPfdParaDlg : public CDialogExt
{
	DECLARE_DYNAMIC(CPfdParaDlg)

// �R���X�g���N�V����
public:
	CPfdParaDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PFDPARADLG };

public:
	CPfdData m_Data;
	class CServerEntry *m_pEntry;

	void DisableWnd();

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();
	virtual void OnOK();

// �C���v�������e�[�V����
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedListen(UINT nID);
};
