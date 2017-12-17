#pragma once

#include "afxwin.h"
#include "DialogExt.h"

// CCsiParaDlg �_�C�A���O

class CCsiParaDlg : public CDialogExt
{
	DECLARE_DYNAMIC(CCsiParaDlg)

// �R���X�g���N�V����
public:
	CCsiParaDlg(CWnd* pParent = NULL);
	virtual ~CCsiParaDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_CSIPARADLG };

public:
	CComboBox m_Ext1Combo;
	CComboBox m_Ext2Combo;
	CComboBox m_CodeCombo;
	CComboBox m_NameCombo;

	int m_Type;
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
