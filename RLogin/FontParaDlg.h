#if !defined(AFX_FONTPARADLG_H__9F95C64C_47CC_4607_857E_1936DAB498AC__INCLUDED_)
#define AFX_FONTPARADLG_H__9F95C64C_47CC_4607_857E_1936DAB498AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FontParaDlg.h : �w�b�_�[ �t�@�C��
//

#include "TextRam.h"
#include "Data.h"

/////////////////////////////////////////////////////////////////////////////
// CFontParaDlg �_�C�A���O

class CFontParaDlg : public CDialog
{
// �R���X�g���N�V����
public:
	int m_CodeSet;
	class CFontNode *m_pData;
	CString m_FontNameTab[16];

	static int CharSetNo(LPCSTR name);
	static LPCSTR CharSetName(int code);
	static LPCSTR IConvName(int code);
	static int CodeSetNo(LPCSTR bank, LPCSTR code);
	static void CodeSetName(int num, CString &bank, CString &code);

	CFontParaDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CFontParaDlg)
	enum { IDD = IDD_FONTPARADLG };
	BOOL	m_ShiftTemp;
	CString	m_CharSetTemp;
	CString	m_ZoomTemp[2];
	CString	m_OffsTemp;
	CString	m_BankTemp;
	CString	m_CodeTemp;
	CString m_IContName;
	CString m_EntryName;
	CString m_FontName;
	int m_FontNum;
	int m_FontQuality;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CFontParaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CFontParaDlg)
	afx_msg void OnFontsel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeFontnum();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_FONTPARADLG_H__9F95C64C_47CC_4607_857E_1936DAB498AC__INCLUDED_)
