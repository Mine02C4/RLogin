// TermPage.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "RLogin.h"
#include "RLoginDoc.h"
#include "RLoginView.h"
#include "TextRam.h"
#include "Data.h"
#include "OptDlg.h"
#include "TermPage.h"
#include "EscDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTermPage �v���p�e�B �y�[�W

IMPLEMENT_DYNCREATE(CTermPage, CPropertyPage)

#define	CHECKOPTMAX		5
#define	IDC_CHECKFAST	IDC_TERMCHECK1
static const int CheckOptTab[] = { TO_RLBOLD, TO_RLGNDW, TO_RLGCWA, TO_RLUNIAWH, TO_RLKANAUTO };

static const LV_COLUMN InitListTab[3] = {
		{ LVCF_TEXT | LVCF_WIDTH, 0,  60,	"�ԍ�",				0, 0 },
		{ LVCF_TEXT | LVCF_WIDTH, 0,  150,	"�Z�b�g���̓���",	0, 0 },
		{ LVCF_TEXT | LVCF_WIDTH, 0,  150,	"���Z�b�g���̓���",	0, 0 },
	};

static const struct _OptListTab {
	int		num;
	LPCSTR	ename;
	LPCSTR	dname;
} OptListTab[] = {
	// ANSI Screen Option	0-99(200-299)
	{	TO_ANSIKAM,		"�L�[���͂𖳎�",				"�L�[���͂�L��"				},
	{	TO_ANSIIRM,		"�}�����[�h",					"�㏑�����[�h"					},
	{	TO_ANSIERM,		"SPA�̕ی�𖳌�",				"SPA�̕ی��L��"				},
	{	TO_ANSISRM,		"���[�J���G�R�[�𖳌�",			"���[�J���G�R�[��L��"			},
	{	TO_ANSITSM,		"�e�s�ʂ̃^�u�ݒ�",				"�S�s�œ����^�u�ݒ�"			},
	{	TO_ANSILNM,		"LF/VT/FF�ōs���Ɉړ�",			"LF/VT/FF�Œʏ퓮��"			},

	// DEC Terminal Option	0-199
	{	TO_DECCKM,		"CKM�L���̃L�[�R�[�h�𑗐M",	"CKM�����̃L�[�R�[�h�𑗐M"		},
	{	TO_DECANM,		"VT100(ANSI)���[�h",			"VT52���[�h"					},
	{	TO_DECCOLM,		"132�����\�����[�h",			"80�����\�����[�h"				},
	{	TO_DECSCLM,		"�X���[�Y�X�N���[�����[�h",		"�W�����v�X�N���[�����[�h"		},
	{	TO_DECSCNM,		"���]�\�����[�h",				"�ʏ�\�����[�h"				},
	{	TO_DECOM,		"CUP��STBM�̉e�����󂯂�",		"CUP�ŏ�ɓ������_"				},
	{	TO_DECAWM,		"�s���̃I�[�g���[�v��L��",		"�s���𒴂���ړ����s��Ȃ�"	},
	{	TO_XTMOSREP,	"�}�E�X���|�[�g��L��",			"�}�E�X���|�[�g�𖳌�"			},
	{	TO_DECPEX,		"MC��STBM�̉e�����󂯂Ȃ�",		"MC��STRM�̉e�����󂯂�"		},
	{	TO_DECTCEM,		"�J�[�\���̕\��",				"�J�[�\�����\��"				},
//	{	TO_DECTEK,		"Tek���[�h�Ɉڍs",				"Tek���[�h���甲����"			},
	{	TO_XTMCSC,		"132�������[�h�L��",			"132�������[�h����"				},
	{	TO_XTMCUS,		"�^�u(HT)�̃o�O�C�����[�h",		"xterm�^�u�o�O�݊����[�h"		},
	{	TO_XTMRVW,		"�s��BS�ɂ���s�E�[�ړ�",		"�s����BS�ňړ����Ȃ�"			},
	{	TO_XTMABUF,		"�S��ʂ̕ۑ�",					"�ۑ�������ʂ̕��A"			},
	{	TO_DECBKM,		"BS�L�[�ϊ����s��Ȃ�",			"BS�L�[��DEL�L�[�ɕϊ�"			},
	{	TO_DECECM,		"SGR�ŋ󔒕�����ݒ肵�Ȃ�",	"SGR�ŋ󔒕����J���[��ݒ�"		},

	// XTerm Option			1000-1099(300-379)
	{	TO_XTNOMTRK,	"Normal mouse tracking",		"Mouse tracking ����"			},
	{	TO_XTHILTRK,	"Hilite mouse tracking",		"Mouse tracking ����"			},
	{	TO_XTBEVTRK,	"Button-event mouse tracking",	"Mouse tracking ����"			},
	{	TO_XTAEVTRK,	"Any-event mouse tracking",		"Mouse tracking ����"			},
	{	TO_XTFOCEVT,	"�t�H�[�J�X�C�x���g�̗L��",		"�t�H�[�J�X�C�x���g����"		},
	{	TO_XTALTSCR,	"�S��ʂ̕ۑ�",					"�ۑ�������ʂ̕��A"			},
	{	TO_XTSRCUR,		"�J�[�\���ʒu�̕ۑ�",			"�ۑ������J�[�\���ʒu�̕��A"	},
	{	TO_XTALTCLR,	"�g����ʂɐ؂芷��",			"�W����ʂɐ؂芷��"			},

	// XTerm Option 2		2000-2019(380-399)
	{	TO_XTBRPAMD,	"Bracketed Paste Mode �L��",	"Bracketed Paste Mode ����"		},

	// RLogin Option		8400-8511(400-511)
	{	TO_RLGCWA,		"SGR�ŋ󔒑�����ݒ肵�Ȃ�",	"SGR�ŋ󔒕���������ݒ�"		},
	{	TO_RLGNDW,		"�s���ł̒x�����s����",			"�s���ł̒x�����s�L��"			},
	{	TO_RLGAWL,		"�����u���E�U�N��������",		"�����u���E�U�N������"			},
	{	TO_RLBOLD,		"�{�[���h�����L��",				"�{�[���h��������"				},
	{	TO_RLBPLUS,		"BPlus/ZModem/Kermit����",		"�����t�@�C���]������"			},
	{	TO_RLUNIAWH,	"A�^�C�v�𔼊p�ŕ\��",			"A�^�C�v��S�p�ŕ\��"			},
	{	TO_RLNORESZ,	"DECCOLM�Ń��T�C�Y",			"�E�B���h�E�����T�C�Y���Ȃ�"	},
	{	TO_RLKANAUTO,	"�����R�[�h�������Ǐ]",			"�����R�[�h��ύX���Ȃ�"		},
	{	TO_RLMOSWHL,	"�z�C�[���̒ʏ퓮��",			"�z�C�[�����k���k���ɂ���"		},
	{	TO_RLMSWAPP,	"�z�C�[���ŃX�N���[���̂�",		"�z�C�[���ŃL�[�R�[�h����"		},
	{	TO_RLPNAM,		"�m�[�}�����[�h(DECPNM)",		"�A�v�����[�h(DECPAM)"			},
	{	TO_IMECTRL,		"IME�I�[�v��",					"IME�N���[�X"					},

	{	0,				NULL	}
};

CTermPage::CTermPage() : CPropertyPage(CTermPage::IDD)
{
	//{{AFX_DATA_INIT(CTermPage)
	//}}AFX_DATA_INIT
	for ( int n = 0 ; n < CHECKOPTMAX ; n++ )
		m_Check[n] = FALSE;
	m_pSheet = NULL;
	m_TtlMode = 0;
	m_TtlRep = m_TtlCng = FALSE;
}

CTermPage::~CTermPage()
{
}

void CTermPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTermPage)
	//}}AFX_DATA_MAP
	for ( int n = 0 ; n < CHECKOPTMAX ; n++ )
		DDX_Check(pDX, IDC_TERMCHECK1 + n, m_Check[n]);
	DDX_Control(pDX, IDC_ESCLIST, m_List);
	DDX_CBIndex(pDX, IDC_COMBO3, m_TtlMode);
	DDX_Check(pDX, IDC_TERMCHECK6, m_TtlRep);
	DDX_Check(pDX, IDC_TERMCHECK7, m_TtlCng);
}

BEGIN_MESSAGE_MAP(CTermPage, CPropertyPage)
	//{{AFX_MSG_MAP(CTermPage)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHECKFAST, IDC_CHECKFAST + CHECKOPTMAX - 1, OnUpdateCheck)
	ON_BN_CLICKED(IDC_ESCEDIT, &CTermPage::OnBnClickedEscedit)
	ON_NOTIFY(NM_CLICK, IDC_ESCLIST, &CTermPage::OnNMClickEsclist)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_TERMCHECK6, IDC_TERMCHECK7, OnUpdateCheck)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CTermPage::OnCbnSelchangeCombo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTermPage ���b�Z�[�W �n���h��

BOOL CTermPage::OnInitDialog() 
{
	int n;
	CString str;

	ASSERT(m_pSheet);
	ASSERT(m_pSheet->m_pTextRam);

	CPropertyPage::OnInitDialog();
	for ( n = 0 ; n < CHECKOPTMAX ; n++ )
		m_Check[n] = (m_pSheet->m_pTextRam->IsOptEnable(CheckOptTab[n]) ? TRUE : FALSE);

	m_ProcTab = m_pSheet->m_pTextRam->m_ProcTab;

	m_TtlMode = m_pSheet->m_pTextRam->m_TitleMode & 7;
	m_TtlRep  = (m_pSheet->m_pTextRam->m_TitleMode & WTTL_REPORT) ? TRUE : FALSE;
	m_TtlCng  = (m_pSheet->m_pTextRam->m_TitleMode & WTTL_CHENG)  ? TRUE : FALSE;

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_List.InitColumn("TermPageOpt", InitListTab, 3);

	m_List.DeleteAllItems();
	for ( n = 0 ; OptListTab[n].ename != NULL ; n++ ) {
		if ( OptListTab[n].num < 200) {				// DEC Terminal Option	0-199
			str.Format("?%d", OptListTab[n].num);
		} else if ( OptListTab[n].num < 300 ) {		// ANSI Screen Option	0-99(200-299)
			str.Format("%d", OptListTab[n].num - 200);
		} else if ( OptListTab[n].num < 380 ) {		// XTerm Option			1000-1079(300-379)
			str.Format("?%d", OptListTab[n].num + 700);
		} else if ( OptListTab[n].num < 400 ) {		// XTerm Option 2		2000-2019(380-399)
			str.Format("?%d", OptListTab[n].num + 1620);
		} else if ( OptListTab[n].num < 512 ) {		// RLogin Option		8400-8511(400-511)
			str.Format("?%d", OptListTab[n].num + 8000);
		}
		m_List.InsertItem(LVIF_TEXT | LVIF_PARAM, n, str, 0, 0, 0, n);
		m_List.SetItemText(n, 1, OptListTab[n].ename);
		m_List.SetItemText(n, 2, OptListTab[n].dname);
		m_List.SetLVCheck(n,  m_pSheet->m_pTextRam->IsOptEnable(OptListTab[n].num) ? TRUE : FALSE);
	}

	UpdateData(FALSE);
	return TRUE;
}
BOOL CTermPage::OnApply() 
{
	ASSERT(m_pSheet);
	ASSERT(m_pSheet->m_pTextRam);

	UpdateData(TRUE);
	for ( int n = 0 ; n < CHECKOPTMAX ; n++ ) {
		if ( m_Check[n] )
			m_pSheet->m_pTextRam->EnableOption(CheckOptTab[n]);
		else
			m_pSheet->m_pTextRam->DisableOption(CheckOptTab[n]);
	}

	m_pSheet->m_pTextRam->m_ProcTab = m_ProcTab;

	m_pSheet->m_pTextRam->m_TitleMode = m_TtlMode;
	if ( m_TtlRep )
		m_pSheet->m_pTextRam->m_TitleMode |= WTTL_REPORT;
	if ( m_TtlCng )
		m_pSheet->m_pTextRam->m_TitleMode |= WTTL_CHENG;

	for ( int n = 0 ; OptListTab[n].ename != NULL ; n++ ) {
		if ( m_List.GetLVCheck(n) ) {
			if ( m_pSheet->m_pTextRam->IsOptEnable(OptListTab[n].num) )
				continue;
			if ( m_pSheet->m_pTextRam->m_VRam == NULL || m_pSheet->m_pTextRam->m_pDocument == NULL ) {
				m_pSheet->m_pTextRam->EnableOption(OptListTab[n].num);
				continue;
			}
			m_pSheet->m_pTextRam->m_AnsiPara.RemoveAll();
			if ( OptListTab[n].num < 200) {				// DEC Terminal Option	0-199
				m_pSheet->m_pTextRam->m_AnsiPara.Add(OptListTab[n].num);
				m_pSheet->m_pTextRam->fc_Push(STAGE_CSI);
				m_pSheet->m_pTextRam->fc_DECSRET('h');
			} else if ( OptListTab[n].num < 300 ) {		// ANSI Screen Option	0-99(200-299)
				m_pSheet->m_pTextRam->EnableOption(OptListTab[n].num);
			} else if ( OptListTab[n].num < 380 ) {		// XTerm Option			1000-1079(300-379)
				m_pSheet->m_pTextRam->m_AnsiPara.Add(OptListTab[n].num + 700);
				m_pSheet->m_pTextRam->fc_Push(STAGE_CSI);
				m_pSheet->m_pTextRam->fc_DECSRET('h');
			} else if ( OptListTab[n].num < 400 ) {		// XTerm Option 2		2000-2019(380-399)
				m_pSheet->m_pTextRam->m_AnsiPara.Add(OptListTab[n].num + 1620);
				m_pSheet->m_pTextRam->fc_Push(STAGE_CSI);
				m_pSheet->m_pTextRam->fc_DECSRET('h');
			} else if ( OptListTab[n].num < 512 ) {		// RLogin Option		8400-8511(400-511)
				m_pSheet->m_pTextRam->m_AnsiPara.Add(OptListTab[n].num + 8000);
				m_pSheet->m_pTextRam->fc_Push(STAGE_CSI);
				m_pSheet->m_pTextRam->fc_DECSRET('h');
			}
		} else {
			if ( !m_pSheet->m_pTextRam->IsOptEnable(OptListTab[n].num) )
				continue;
			if ( m_pSheet->m_pTextRam->m_VRam == NULL || m_pSheet->m_pTextRam->m_pDocument == NULL ) {
				m_pSheet->m_pTextRam->DisableOption(OptListTab[n].num);
				continue;
			}
			m_pSheet->m_pTextRam->m_AnsiPara.RemoveAll();
			if ( OptListTab[n].num < 200) {				// DEC Terminal Option	0-199
				m_pSheet->m_pTextRam->m_AnsiPara.Add(OptListTab[n].num);
				m_pSheet->m_pTextRam->fc_Push(STAGE_CSI);
				m_pSheet->m_pTextRam->fc_DECSRET('l');
			} else if ( OptListTab[n].num < 300 ) {		// ANSI Screen Option	0-99(200-299)
				m_pSheet->m_pTextRam->DisableOption(OptListTab[n].num);
			} else if ( OptListTab[n].num < 380 ) {		// XTerm Option			1000-1079(300-379)
				m_pSheet->m_pTextRam->m_AnsiPara.Add(OptListTab[n].num + 700);
				m_pSheet->m_pTextRam->fc_Push(STAGE_CSI);
				m_pSheet->m_pTextRam->fc_DECSRET('l');
			} else if ( OptListTab[n].num < 400 ) {		// XTerm Option 2		2000-2019(380-399)
				m_pSheet->m_pTextRam->m_AnsiPara.Add(OptListTab[n].num + 1620);
				m_pSheet->m_pTextRam->fc_Push(STAGE_CSI);
				m_pSheet->m_pTextRam->fc_DECSRET('l');
			} else if ( OptListTab[n].num < 512 ) {		// RLogin Option		8400-8511(400-511)
				m_pSheet->m_pTextRam->m_AnsiPara.Add(OptListTab[n].num + 8000);
				m_pSheet->m_pTextRam->fc_Push(STAGE_CSI);
				m_pSheet->m_pTextRam->fc_DECSRET('l');
			}
		}
	}

	return TRUE;
}
void CTermPage::OnReset() 
{
	if ( m_hWnd == NULL )
		return;

	for ( int n = 0 ; n < CHECKOPTMAX ; n++ )
		m_Check[n] = (m_pSheet->m_pTextRam->IsOptEnable(CheckOptTab[n]) ? TRUE : FALSE);

	m_ProcTab = m_pSheet->m_pTextRam->m_ProcTab;

	m_TtlMode = m_pSheet->m_pTextRam->m_TitleMode & 7;
	m_TtlRep  = (m_pSheet->m_pTextRam->m_TitleMode & WTTL_REPORT) ? TRUE : FALSE;
	m_TtlCng  = (m_pSheet->m_pTextRam->m_TitleMode & WTTL_CHENG)  ? TRUE : FALSE;

	for ( int n = 0 ; OptListTab[n].ename != NULL ; n++ )
		m_List.SetLVCheck(n,  m_pSheet->m_pTextRam->IsOptEnable(OptListTab[n].num) ? TRUE : FALSE);

	UpdateData(FALSE);
	SetModified(FALSE);
}
void CTermPage::OnUpdateCheck(UINT nID) 
{
	SetModified(TRUE);
	m_pSheet->m_ModFlag |= UMOD_TEXTRAM;
}

void CTermPage::OnBnClickedEscedit()
{
	CEscDlg dlg;

	dlg.m_pTextRam = m_pSheet->m_pTextRam;
	dlg.m_pProcTab = &m_ProcTab;

	if ( dlg.DoModal() != IDOK )
		return;

	SetModified(TRUE);
	m_pSheet->m_ModFlag |= UMOD_TEXTRAM;
}

void CTermPage::OnNMClickEsclist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if ( pNMItemActivate->iSubItem == 0 ) {
		SetModified(TRUE);
		m_pSheet->m_ModFlag |= UMOD_TEXTRAM;
	}

	*pResult = 0;
}

void CTermPage::OnCbnSelchangeCombo()
{
	SetModified(TRUE);
	m_pSheet->m_ModFlag |= UMOD_TEXTRAM;
}
