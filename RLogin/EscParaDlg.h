#pragma once

#include "afxwin.h"
#include "DialogExt.h"

// CEscParaDlg �_�C�A���O

class CEscParaDlg : public CDialogExt
{
	DECLARE_DYNAMIC(CEscParaDlg)

// �R���X�g���N�V����
public:
	CEscParaDlg(CWnd* pParent = NULL);
	virtual ~CEscParaDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ESCPARADLG };

public:
	CComboBox m_CodeCombo;
	CComboBox m_NameCombo;

	int m_Code;
	CString m_Name;
	class CTextRam *m_pTextRam;

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	// �C���v�������e�[�V����
protected:
	DECLARE_MESSAGE_MAP()
};
