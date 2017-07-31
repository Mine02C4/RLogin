// EditDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "rlogin.h"
#include "EditDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CEditDlg �_�C�A���O

IMPLEMENT_DYNAMIC(CEditDlg, CDialog)

CEditDlg::CEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditDlg::IDD, pParent)
{
	m_Edit.Empty();
	m_Title.Empty();
	m_WinText.Empty();
}

void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_Edit);
	DDX_Text(pDX, IDC_TITLE, m_Title);
}

BEGIN_MESSAGE_MAP(CEditDlg, CDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDlg ���b�Z�[�W �n���h��

BOOL CEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if ( !m_WinText.IsEmpty() )
		SetWindowText(m_WinText);

	return TRUE;
}
