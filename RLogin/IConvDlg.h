#pragma once

#include "DialogExt.h"

/////////////////////////////////////////////////////////////////////////////
// CIConvDlg �_�C�A���O

class CIConvDlg : public CDialogExt
{
	DECLARE_DYNAMIC(CIConvDlg)

// �R���X�g���N�V����
public:
	CIConvDlg(CWnd* pParent = NULL);

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ICONVDLG };

public:
	CString	m_CharSet[4];

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();

// �C���v�������e�[�V����
protected:
	DECLARE_MESSAGE_MAP()
};
