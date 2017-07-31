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
		{ LVCF_TEXT | LVCF_WIDTH, 0,  60,	_T("�ԍ�"),				0, 0 },
		{ LVCF_TEXT | LVCF_WIDTH, 0,  150,	_T("�Z�b�g���̓���"),	0, 0 },
		{ LVCF_TEXT | LVCF_WIDTH, 0,  150,	_T("���Z�b�g���̓���"),	0, 0 },
	};

static const struct _OptListTab {
	int		num;
	LPCTSTR	ename;
	LPCTSTR	dname;
} OptListTab[] = {
	// ANSI Screen Option	0-99(200-299)
	{	TO_ANSIKAM,		_T("�L�[���͂𖳎�"),				_T("�L�[���͂�L��")				},
	{	TO_ANSIIRM,		_T("�}�����[�h"),					_T("�㏑�����[�h")					},
	{	TO_ANSIERM,		_T("SPA�̕ی�𖳌�"),				_T("SPA�̕ی��L��")				},
	{	TO_ANSISRM,		_T("���[�J���G�R�[�𖳌�"),			_T("���[�J���G�R�[��L��")			},
	{	TO_ANSITSM,		_T("�e�s�ʂ̃^�u�ݒ�"),				_T("�S�s�œ����^�u�ݒ�")			},
	{	TO_ANSILNM,		_T("LF/VT/FF�ōs���Ɉړ�"),			_T("LF/VT/FF�Œʏ퓮��")			},

	// DEC Terminal Option	0-199
	{	TO_DECCKM,		_T("CKM�L���̃L�[�R�[�h�𑗐M"),	_T("CKM�����̃L�[�R�[�h�𑗐M")		},
	{	TO_DECANM,		_T("VT100(ANSI)���[�h"),			_T("VT52���[�h")					},
	{	TO_DECCOLM,		_T("132�����\�����[�h"),			_T("80�����\�����[�h")				},
	{	TO_DECSCLM,		_T("�X���[�Y�X�N���[�����[�h"),		_T("�W�����v�X�N���[�����[�h")		},
	{	TO_DECSCNM,		_T("���]�\�����[�h"),				_T("�ʏ�\�����[�h")				},
	{	TO_DECOM,		_T("CUP��STBM�̉e�����󂯂�"),		_T("CUP�ŏ�ɓ������_")				},
	{	TO_DECAWM,		_T("�s���̃I�[�g���[�v��L��"),		_T("�s���𒴂���ړ����s��Ȃ�")	},
	{	TO_XTMOSREP,	_T("�}�E�X���|�[�g��L��"),			_T("�}�E�X���|�[�g�𖳌�")			},
	{	TO_DECPEX,		_T("MC��STBM�̉e�����󂯂Ȃ�"),		_T("MC��STRM�̉e�����󂯂�")		},
	{	TO_DECTCEM,		_T("�J�[�\���̕\��"),				_T("�J�[�\�����\��")				},
//	{	TO_DECTEK,		_T("Tek���[�h�Ɉڍs"),				_T("Tek���[�h���甲����")			},
	{	TO_XTMCSC,		_T("132�������[�h�L��"),			_T("132�������[�h����")				},
	{	TO_XTMCUS,		_T("�^�u(HT)�̃o�O�C�����[�h"),		_T("xterm�^�u�o�O�݊����[�h")		},
	{	TO_XTMRVW,		_T("�s��BS�ɂ���s�E�[�ړ�"),		_T("�s����BS�ňړ����Ȃ�")			},
	{	TO_XTMABUF,		_T("�S��ʂ̕ۑ�"),					_T("�ۑ�������ʂ̕��A")			},
	{	TO_DECBKM,		_T("BS�L�[�ϊ����s��Ȃ�"),			_T("BS�L�[��DEL�L�[�ɕϊ�")			},
	{	TO_DECECM,		_T("SGR�ŋ󔒕�����ݒ肵�Ȃ�"),	_T("SGR�ŋ󔒕����J���[��ݒ�")		},

	// XTerm Option			1000-1099(300-379)
	{	TO_XTNOMTRK,	_T("Normal mouse tracking"),		_T("Mouse tracking ����")			},
	{	TO_XTHILTRK,	_T("Hilite mouse tracking"),		_T("Mouse tracking ����")			},
	{	TO_XTBEVTRK,	_T("Button-event mouse tracking"),	_T("Mouse tracking ����")			},
	{	TO_XTAEVTRK,	_T("Any-event mouse tracking"),		_T("Mouse tracking ����")			},
	{	TO_XTFOCEVT,	_T("�t�H�[�J�X�C�x���g�̗L��"),		_T("�t�H�[�J�X�C�x���g����")		},
	{	TO_XTEXTMOS,	_T("Extended Mouse Mode"),			_T("Disable Extended Mode")			},
	{	TO_XTSGRMOS,	_T("SGR Mouse Mode"),				_T("Disable SGR Mode")				},
	{	TO_XTURXMOS,	_T("URXVT Mouse Mode"),				_T("Disable URXVT Mode")			},
	{	TO_XTALTSCR,	_T("�S��ʂ̕ۑ�"),					_T("�ۑ�������ʂ̕��A")			},
	{	TO_XTSRCUR,		_T("�J�[�\���ʒu�̕ۑ�"),			_T("�ۑ������J�[�\���ʒu�̕��A")	},
	{	TO_XTALTCLR,	_T("�g����ʂɐ؂芷��"),			_T("�W����ʂɐ؂芷��")			},

	// XTerm Option 2		2000-2019(380-399)
	{	TO_XTBRPAMD,	_T("Bracketed Paste Mode �L��"),	_T("Bracketed Paste Mode ����")		},

	// RLogin Option		8400-8511(400-511)
//	{	TO_RLGCWA,		_T("SGR�ŋ󔒑�����ݒ肵�Ȃ�"),	_T("SGR�ŋ󔒕���������ݒ�")		},
//	{	TO_RLGNDW,		_T("�s���ł̒x�����s����"),			_T("�s���ł̒x�����s�L��")			},
//	{	TO_RLGAWL,		_T("�����u���E�U�N��������"),		_T("�����u���E�U�N������")			},
//	{	TO_RLBOLD,		_T("�{�[���h�����L��"),				_T("�{�[���h��������")				},
//	{	TO_RLBPLUS,		_T("BPlus/ZModem/Kermit����"),		_T("�����t�@�C���]������")			},
//	{	TO_RLUNIAWH,	_T("A�^�C�v�𔼊p�ŕ\��"),			_T("A�^�C�v��S�p�ŕ\��")			},
//	{	TO_RLNORESZ,	_T("DECCOLM�Ń��T�C�Y"),			_T("�E�B���h�E�����T�C�Y���Ȃ�")	},
//	{	TO_RLKANAUTO,	_T("�����R�[�h�������Ǐ]"),			_T("�����R�[�h��ύX���Ȃ�")		},
	{	TO_RLPNAM,		_T("�m�[�}�����[�h(DECPNM)"),		_T("�A�v�����[�h(DECPAM)")			},
	{	TO_IMECTRL,		_T("IME�I�[�v��"),					_T("IME�N���[�X")					},
	{	TO_RLCKMESC,	_T("7727 ESC�L�[��CKM�L��"),		_T("ESC�L�[��CKM����")				},
//	{	TO_RLMSWAPE,	_T("7786 �z�C�[���̃L�[�ϊ�"),		_T("�z�C�[���̒ʏ퓮��")			},

	{	0,				NULL,								NULL							}
};

CTermPage::CTermPage() : CTreePropertyPage(CTermPage::IDD)
{
	for ( int n = 0 ; n < CHECKOPTMAX ; n++ )
		m_Check[n] = FALSE;
}

CTermPage::~CTermPage()
{
}

void CTermPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	for ( int n = 0 ; n < CHECKOPTMAX ; n++ )
		DDX_Check(pDX, IDC_TERMCHECK1 + n, m_Check[n]);
	DDX_Control(pDX, IDC_ESCLIST, m_List);
}

BEGIN_MESSAGE_MAP(CTermPage, CPropertyPage)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHECKFAST, IDC_CHECKFAST + CHECKOPTMAX - 1, OnUpdateCheck)
	ON_BN_CLICKED(IDC_ESCEDIT, &CTermPage::OnBnClickedEscedit)
	ON_NOTIFY(NM_CLICK, IDC_ESCLIST, &CTermPage::OnNMClickEsclist)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTermPage ���b�Z�[�W �n���h��

void CTermPage::DoInit()
{
	int n;

	for ( n = 0 ; n < CHECKOPTMAX ; n++ )
		m_Check[n] = (m_pSheet->m_pTextRam->IsOptEnable(CheckOptTab[n]) ? TRUE : FALSE);

	m_ProcTab = m_pSheet->m_pTextRam->m_ProcTab;

	for ( n = 0 ; OptListTab[n].ename != NULL ; n++ )
		m_List.SetLVCheck(n,  m_pSheet->m_pTextRam->IsOptEnable(OptListTab[n].num) ? TRUE : FALSE);

	UpdateData(FALSE);
}
BOOL CTermPage::OnInitDialog() 
{
	ASSERT(m_pSheet);
	ASSERT(m_pSheet->m_pTextRam);

	CPropertyPage::OnInitDialog();

	int n;
	CString str;

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_List.InitColumn(_T("TermPageOpt"), InitListTab, 3);

	m_List.DeleteAllItems();
	for ( n = 0 ; OptListTab[n].ename != NULL ; n++ ) {
		if ( OptListTab[n].num < 200) {				// DEC Terminal Option	0-199
			str.Format(_T("?%d"), OptListTab[n].num);
		} else if ( OptListTab[n].num < 300 ) {		// ANSI Screen Option	0-99(200-299)
			str.Format(_T("%d"), OptListTab[n].num - 200);
		} else if ( OptListTab[n].num < 380 ) {		// XTerm Option			1000-1079(300-379)
			str.Format(_T("?%d"), OptListTab[n].num + 700);
		} else if ( OptListTab[n].num < 400 ) {		// XTerm Option 2		2000-2019(380-399)
			str.Format(_T("?%d"), OptListTab[n].num + 1620);
		} else if ( OptListTab[n].num < 512 ) {		// RLogin Option		8400-8511(400-511)
			str.Format(_T("?%d"), OptListTab[n].num + 8000);
		}
		m_List.InsertItem(LVIF_TEXT | LVIF_PARAM, n, str, 0, 0, 0, n);
		m_List.SetItemText(n, 1, OptListTab[n].ename);
		m_List.SetItemText(n, 2, OptListTab[n].dname);
	}

	DoInit();

	return TRUE;
}
BOOL CTermPage::OnApply() 
{
	ASSERT(m_pSheet);
	ASSERT(m_pSheet->m_pTextRam);

	UpdateData(TRUE);

	m_pSheet->m_pTextRam->m_ProcTab = m_ProcTab;

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

	for ( int n = 0 ; n < CHECKOPTMAX ; n++ ) {
		if ( m_Check[n] )
			m_pSheet->m_pTextRam->EnableOption(CheckOptTab[n]);
		else
			m_pSheet->m_pTextRam->DisableOption(CheckOptTab[n]);
	}

	return TRUE;
}
void CTermPage::OnReset() 
{
	ASSERT(m_pSheet);
	ASSERT(m_pSheet->m_pTextRam);

	DoInit();
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
