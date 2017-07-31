// ChatStatDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "RLogin.h"
#include "ChatStatDlg.h"


// CChatStatDlg �_�C�A���O

IMPLEMENT_DYNAMIC(CChatStatDlg, CDialog)

CChatStatDlg::CChatStatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatStatDlg::IDD, pParent)
{
	m_Counter = 0;
}

CChatStatDlg::~CChatStatDlg()
{
}

void CChatStatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATUS, m_Status);
	DDX_Control(pDX, IDC_TIMEPROG, m_TimeProg);
	DDX_Control(pDX, IDC_TITLE, m_Title);
}


BEGIN_MESSAGE_MAP(CChatStatDlg, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CChatStatDlg ���b�Z�[�W �n���h��

BOOL CChatStatDlg::OnInitDialog()
{
	int x, y;
	CRect rect, box;

	GetParent()->GetWindowRect(box);
	GetWindowRect(rect);
	x = (box.Width() - rect.Width()) / 2;
	y = (box.Height() - rect.Height()) / 2;
	rect.left   += x;
	rect.right  += x;
	rect.top    += y;
	rect.bottom += y;
	MoveWindow(rect);

	CDialog::OnInitDialog();

	m_TimeProg.SetRange(0, 180);
	SetTimer(1028, 1000, NULL);
	m_Counter = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

void CChatStatDlg::OnTimer(UINT_PTR nIDEvent)
{
	if ( nIDEvent == 1028 ) {
		m_TimeProg.SetPos(++m_Counter);
		if ( m_Counter >= 180 )
			OnOK();
	}
	CDialog::OnTimer(nIDEvent);
}

void CChatStatDlg::OnOK()
{
	CWnd *pWnd = GetParent();
	if ( pWnd != NULL )
		pWnd->PostMessage(WM_COMMAND, ID_CHARSCRIPT_END);
	CDialog::OnOK();
}

void CChatStatDlg::SetStaus(LPCTSTR str)
{
	m_Status.SetWindowText(str);
}
