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

IMPLEMENT_DYNCREATE(CTermPage, CTreePage)

static const LV_COLUMN InitListTab[3] = {
		{ LVCF_TEXT | LVCF_WIDTH, 0,  60,	_T("�ԍ�"),				0, 0 },
		{ LVCF_TEXT | LVCF_WIDTH, 0,  150,	_T("�Z�b�g���̓���"),	0, 0 },
		{ LVCF_TEXT | LVCF_WIDTH, 0,  150,	_T("���Z�b�g���̓���"),	0, 0 },
	};

static const struct _OptListTab {
	int		num;
	LPCTSTR	ename;
	LPCTSTR	dname;
	LPCTSTR tip;
} OptListTab[] = {
	// ANSI Screen Option	0-99(200-299)
	{	TO_ANSIKAM,		_T("�L�[���͂𖳎�"),				_T("�L�[���͂�L��"),				NULL	},
	{	TO_ANSIIRM,		_T("�}�����[�h"),					_T("�㏑�����[�h"),					NULL	},
	{	TO_ANSIERM,		_T("SPA�̕ی�𖳌�"),				_T("SPA�̕ی��L��"),				NULL	},
	{	TO_ANSISRM,		_T("���[�J���G�R�[�𖳌�"),			_T("���[�J���G�R�[��L��"),			NULL	},
	{	TO_ANSITSM,		_T("�e�s�ʂ̃^�u�ݒ�"),				_T("�S�s�œ����^�u�ݒ�"),			NULL	},
	{	TO_ANSILNM,		_T("LF/VT/FF�ōs���Ɉړ�"),			_T("LF/VT/FF�Œʏ퓮��"),			NULL	},

	// DEC Terminal Option	0-199
	{	TO_DECCKM,		_T("CKM�L���̃L�[�R�[�h�𑗐M"),	_T("CKM�����̃L�[�R�[�h�𑗐M"),	NULL	},
	{	TO_DECANM,		_T("VT100(ANSI)���[�h"),			_T("VT52���[�h"),					NULL	},
	{	TO_DECCOLM,		_T("132�����\�����[�h"),			_T("80�����\�����[�h"),				NULL	},
	{	TO_DECSCLM,		_T("�X���[�Y�X�N���[�����[�h"),		_T("�W�����v�X�N���[�����[�h"),		NULL	},
	{	TO_DECSCNM,		_T("���]�\�����[�h"),				_T("�ʏ�\�����[�h"),				NULL	},
	{	TO_DECOM,		_T("CUP��STBM�̉e�����󂯂�"),		_T("CUP�ŏ�ɓ������_"),			NULL	},
	{	TO_DECAWM,		_T("�s���̃I�[�g���[�v��L��"),		_T("�s���𒴂���ړ����s��Ȃ�"),	NULL	},
	{	TO_DECARM,		_T("�L�[���s�[�g��L��"),			_T("�L�[���s�[�g���Ȃ�"),			NULL	},
	{	TO_XTMOSREP,	_T("�}�E�X���|�[�g��L��"),			_T("�}�E�X���|�[�g�𖳌�"),			NULL	},
	{	TO_XTCBLINK,	_T("�J�[�\���̓_�ł��֎~"),			_T("�J�[�\���̓_�ł��s��"),			NULL	},
	{	TO_DECPEX,		_T("MC��STBM�̉e�����󂯂Ȃ�"),		_T("MC��STRM�̉e�����󂯂�"),		NULL	},
	{	TO_DECTCEM,		_T("�J�[�\���̕\��"),				_T("�J�[�\�����\��"),				NULL	},
//	{	TO_DECTEK,		_T("Tek���[�h�Ɉڍs"),				_T("Tek���[�h���甲����"),			NULL	},
	{	TO_XTMCSC,		_T("132�������[�h�L��"),			_T("132�������[�h����"),			NULL	},
	{	TO_XTMCUS,		_T("�^�u(HT)�̃o�O�C�����[�h"),		_T("xterm�^�u�o�O�݊����[�h"),		NULL	},
	{	TO_XTMRVW,		_T("�s��BS�ɂ���s�E�[�ړ�"),		_T("�s����BS�ňړ����Ȃ�"),			NULL	},
	{	TO_XTMABUF,		_T("���݂̉�ʂ̕ۑ�"),				_T("�ۑ�������ʂ̕��A"),			NULL	},
	{	TO_DECBKM,		_T("BS�L�[�ϊ����s��Ȃ�"),			_T("BS�L�[��DEL�L�[�ɕϊ�"),		NULL	},
	{	TO_DECLRMM,		_T("���E�}�[�W���L��"),				_T("���E�}�[�W������"),				NULL	},
	{	TO_DECSDM,		_T("Sixel��ʃE�B���h�E�ŕ\��"),	_T("Sixel�X�N���[�����[�h�\��"),	NULL	},
	{	TO_DECNCSM,		_T("��ʃT�C�Y�ύX�ŃN���A���Ȃ�"),	_T("��ʃT�C�Y�ύX�ŃN���A����"),	NULL	},
	{	TO_DECECM,		_T("SGR�ŋ󔒕�����ݒ肵�Ȃ�"),	_T("SGR�ŋ󔒕����J���[��ݒ�"),	NULL	},

	// XTerm Option			1000-1099(300-379)
	{	TO_XTNOMTRK,	_T("Normal mouse tracking"),		_T("Mouse tracking ����"),			NULL	},
	{	TO_XTHILTRK,	_T("Hilite mouse tracking"),		_T("Mouse tracking ����"),			NULL	},
	{	TO_XTBEVTRK,	_T("Button-event mouse tracking"),	_T("Mouse tracking ����"),			NULL	},
	{	TO_XTAEVTRK,	_T("Any-event mouse tracking"),		_T("Mouse tracking ����"),			NULL	},
	{	TO_XTFOCEVT,	_T("�t�H�[�J�X�C�x���g�̗L��"),		_T("�t�H�[�J�X�C�x���g����"),		NULL	},
	{	TO_XTEXTMOS,	_T("Extended Mouse Mode"),			_T("Disable Extended Mode"),		NULL	},
	{	TO_XTSGRMOS,	_T("SGR Mouse Mode"),				_T("Disable SGR Mode"),				NULL	},
	{	TO_XTURXMOS,	_T("URXVT Mouse Mode"),				_T("Disable URXVT Mode"),			NULL	},
	{	TO_XTALTSCR,	_T("���݉�ʂƊg����ʂ̐؊�"),		_T("�g����ʂƕۑ���ʂ̐؊�"),		NULL	},
	{	TO_XTSRCUR,		_T("�J�[�\���ʒu�̕ۑ�"),			_T("�ۑ������J�[�\���ʒu�̕��A"),	NULL	},
	{	TO_XTALTCLR,	_T("���݂̉�ʂ̕ۑ���ɃN���A"),	_T("�ۑ�������ʂ̕��A"),			NULL	},
	{	TO_XTPRICOL,	_T("ReGIS/Sixel�ʃJ���[�}�b�v"),	_T("���ʃJ���[�}�b�v"),				NULL	},

	// XTerm Option 2		2000-2019(380-399)
	{	TO_XTBRPAMD,	_T("Bracketed Paste Mode �L��"),	_T("Bracketed Paste Mode ����"),	NULL	},

	// RLogin Option		8400-8511(400-511)
	{	TO_RLGCWA,		_T("SGR�ŋ󔒑�����ݒ肵�Ȃ�"),	_T("SGR�ŋ󔒕���������ݒ�"),		_T("SGR(ESC[m)�ɂ��ύX����镶���������󔒕����ɂ��K�p���܂��B\n���̐ݒ�́AFreeBSD��cons25�̎d�l�ɍ��킹�镨�ł�")	},
	{	TO_RLGNDW,		_T("�s���ł̒x�����s����"),			_T("�s���ł̒x�����s�L��"),			_T("�s���ŕ����\���̎������s�����̕����\���܂Œx�点�܂�\n���̐ݒ�́AFreeBSD��cons25�̎d�l�ɍ��킹�镨�ł�")	},
//	{	TO_RLGAWL,		_T("�����u���E�U�N��������"),		_T("�����u���E�U�N������"),			NULL	},
	{	TO_RLBOLD,		_T("�d�ˏ����Ń{�[���h��\��"),		_T("���P�x�Ń{�[���h��\��"),		_T("�d�ˏ����Ń{�[���h(������)��\�����܂��B\n���������̂�����ĕ\������Ă��܂��܂�")	},
//	{	TO_RLBPLUS,		_T("BPlus/ZModem/Kermit����"),		_T("�����t�@�C���]������"),			NULL	},
	{	TO_RLALTBDIS,	_T("��ʂ̃X�^�b�N���֎~"),			_T("��ʂ̃X�^�b�N���L��"),			_T("DECSET/DECRST(CSI?47h/l)�Ō��݂̉�ʂ��X�^�b�N�ɐς݂܂��B\n�I�����̓���(�P�̊g����ʂ̐؂�ւ�)��xterm�̓���ł�")	},
	{	TO_RLUNIAWH,	_T("A�^�C�v�𔼊p�ŕ\��"),			_T("A�^�C�v��S�p�ŕ\��"),			_T("UNICODE�d�l����EastAsianWidth.txt��A�^�C�v(Ambiguous)�Œ�`���ꂽ�����̕\������ݒ肵�܂��B�t�H���g�ɂ�肩�Ȃ�Ⴂ������܂�")	},
//	{	TO_RLNORESZ,	_T("DECCOLM�Ń��T�C�Y"),			_T("�E�B���h�E�����T�C�Y���Ȃ�"),	NULL	},
	{	TO_RLKANAUTO,	_T("�����R�[�h�������Ǐ]"),			_T("�����R�[�h��ύX���Ȃ�"),		_T("�����R�[�h���G���[���N�������ꍇ�Ɏ����ŕύX���܂��B\n�G���[���N�����܂ŕύX���Ȃ��̂ŕ��������́A�N����܂�")	},
	{	TO_RLPNAM,		_T("�m�[�}�����[�h(DECPNM)"),		_T("�A�v�����[�h(DECPAM)"),			NULL	},
	{	TO_IMECTRL,		_T("IME�I�[�v��"),					_T("IME�N���[�X"),					NULL	},
	{	TO_RLCKMESC,	_T("7727 ESC�L�[��CKM�L��"),		_T("ESC�L�[��CKM����"),				_T("DECCKM�ɂ��L�[�R�[�h�̕ύX��ESC�L�[���܂߂܂��B\n�{��ESC�̃L�[�R�[�h��'\\033'������Ԃ��܂���CKM����'\\0330['��Ԃ��悤�ɂ��܂�")	},
//	{	TO_RLMSWAPE,	_T("7786 �z�C�[���̃L�[�ϊ�"),		_T("�z�C�[���̒ʏ퓮��"),			NULL	},
	{	TO_RLTEKINWND,	_T("Tek���R���\�[���ŕ\��"),		_T("Tek�R���\�[���𖳌�"),			NULL	},
	{	TO_RLUNINOM,	_T("UTF-8�m�[�}���C�Y���֎~"),		_T("UTF-8�m�[�}���C�Y���s��"),		_T("UNICODE�̕����ϊ����������Ȃ��ł��̂܂܂̌`�ŕ\������悤�ɂ��܂��B")	},
	{	TO_RLUNIAHF,	_T("Unicde���p�̒��������Ȃ�"),		_T("Unicde���p�̒���������"),		_T("�ꕔ�̃t�H���g�Ŕ��p�E�S�p�ɂȂ�悤�ɒ������ĕ\���܂�")	},
//	{	TO_RLMODKEY,	_T("modifyKeys��D�悷��"),			_T("�V���[�g�J�b�g��D��"),			NULL	},
	{	TO_RLDRWLINE,	_T("�r���𕶎��ŕ\������"),			_T("�r������ŕ\������"),			_T("�r������ŕ`�悹���Ƀt�H���g�̎��{���̕����Ƃ��ĕ\�����܂�")	},
	{	TO_RLSIXPOS,	_T("Sixel�摜�̉E�ɃJ�[�\��"),		_T("Sixel�摜�̉��ɃJ�[�\��"),		_T("�X�N���[�����[�h����Sixel�摜�\����̃J�[�\���ʒu��ݒ肵�܂�")	},
	{	TO_DRCSMMv1,	_T("8800 Unicode�}�b�s���O�L��"),	_T("Unicode�}�b�s���O����"),		_T("ISO-2022�R�[�h�Z�b�g��Unicode16�ʂɃ}�b�s���O��L���E�����ɂ��܂�")	},
	{	TO_RLC1DIS,		_T("C1���䕶���𖳎�����"),			_T("C1���䕶������������"),			_T("C1���䕶��(80-9F)�𖳎�����E���Ȃ�")	},
	{	TO_RLCLSBACK,	_T("�X�N���[�����ď���"),			_T("�ʏ�̑S��ʏ���"),				_T("�S��ʏ������X�N���[���ōs��")	},
	{	0,				NULL,								NULL,								NULL	}
};

CTermPage::CTermPage() : CTreePage(CTermPage::IDD)
{
}
CTermPage::~CTermPage()
{
}

void CTermPage::DoDataExchange(CDataExchange* pDX)
{
	CTreePage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ESCLIST, m_OptList);
}

BEGIN_MESSAGE_MAP(CTermPage, CTreePage)
	ON_BN_CLICKED(IDC_ESCEDIT, &CTermPage::OnBnClickedEscedit)
	ON_NOTIFY(NM_CLICK, IDC_ESCLIST, &CTermPage::OnNMClickOptlist)
	ON_NOTIFY(LVN_GETINFOTIP, IDC_ESCLIST, &CTermPage::OnLvnGetInfoTipEsclist)
END_MESSAGE_MAP()

void CTermPage::DoInit()
{
	int n, i;

	m_ProcTab = m_pSheet->m_pTextRam->m_ProcTab;

	for ( i = 0 ; i < m_OptList.GetItemCount() ; i++ ) {
		n = (int)m_OptList.GetItemData(i);
		m_OptList.SetLVCheck(i,  m_pSheet->m_pTextRam->IsOptEnable(OptListTab[n].num) ? TRUE : FALSE);
	}

	UpdateData(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CTermPage ���b�Z�[�W �n���h��

BOOL CTermPage::OnInitDialog() 
{
	int n;
	CString str;

	ASSERT(m_pSheet != NULL && m_pSheet->m_pTextRam != NULL);

	CTreePage::OnInitDialog();

	m_OptList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES | LVS_EX_INFOTIP);
	m_OptList.InitColumn(_T("TermPageOpt"), InitListTab, 3);

	m_OptList.DeleteAllItems();
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
		m_OptList.InsertItem(LVIF_TEXT | LVIF_PARAM, n, str, 0, 0, 0, n);
		m_OptList.SetItemText(n, 1, OptListTab[n].ename);
		m_OptList.SetItemText(n, 2, OptListTab[n].dname);
	}

	DoInit();

	return TRUE;
}
BOOL CTermPage::OnApply() 
{
	int n, i;

	ASSERT(m_pSheet != NULL && m_pSheet->m_pTextRam != NULL);

	UpdateData(TRUE);

	m_pSheet->m_pTextRam->m_ProcTab = m_ProcTab;

	for ( i = 0 ; i < m_OptList.GetItemCount() ; i++ ) {
		n = (int)m_OptList.GetItemData(i);

		if ( m_OptList.GetLVCheck(i) ) {
			if ( m_pSheet->m_pTextRam->IsOptEnable(OptListTab[n].num) )
				continue;
			if ( !m_pSheet->m_pTextRam->IsInitText() || m_pSheet->m_pTextRam->m_pDocument == NULL ) {
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
			if ( !m_pSheet->m_pTextRam->IsInitText() || m_pSheet->m_pTextRam->m_pDocument == NULL ) {
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
	ASSERT(m_pSheet != NULL && m_pSheet->m_pTextRam != NULL);

	DoInit();
	SetModified(FALSE);
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
void CTermPage::OnNMClickOptlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if ( pNMItemActivate->iSubItem == 0 ) {
		SetModified(TRUE);
		m_pSheet->m_ModFlag |= (UMOD_TEXTRAM | UMOD_ANSIOPT);
	}

	*pResult = 0;
}
void CTermPage::OnLvnGetInfoTipEsclist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVGETINFOTIP pGetInfoTip = reinterpret_cast<LPNMLVGETINFOTIP>(pNMHDR);
	int n = (int)m_OptList.GetItemData(pGetInfoTip->iItem);
	CString str;

	if ( OptListTab[n].tip != NULL )
		str = OptListTab[n].tip;
	else
		str.Format(_T("%s/%s"), OptListTab[n].ename, OptListTab[n].dname);

	if ( (n = str.GetLength() + sizeof(TCHAR)) > pGetInfoTip->cchTextMax )
		n = pGetInfoTip->cchTextMax;

	lstrcpyn(pGetInfoTip->pszText, str, n);

	*pResult = 0;
}
