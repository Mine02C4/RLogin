// TtyModeDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "RLogin.h"
#include "MainFrm.h"
#include "Data.h"
#include "TextRam.h"
#include "TtyModeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CTtyModeDlg ダイアログ

IMPLEMENT_DYNAMIC(CTtyModeDlg, CDialogExt)

CTtyModeDlg::CTtyModeDlg(CWnd* pParent /*=NULL*/)
	: CDialogExt(CTtyModeDlg::IDD, pParent)
{
	m_pParamTab = NULL;
}

CTtyModeDlg::~CTtyModeDlg()
{
}

void CTtyModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogExt::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODE_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CTtyModeDlg, CDialogExt)
	ON_WM_SIZE()
	ON_WM_SIZING()
END_MESSAGE_MAP()

// CTtyModeDlg メッセージ ハンドラー

static const LV_COLUMN InitListTab[4] = {
	{ LVCF_TEXT | LVCF_WIDTH, 0,  40, _T("No."),	0, 0 },
	{ LVCF_TEXT | LVCF_WIDTH, 0,  80, _T("Name"),	0, 0 },
	{ LVCF_TEXT | LVCF_WIDTH, 0,  80, _T("Value"),	0, 0 },
	{ LVCF_TEXT | LVCF_WIDTH, 0, 200, _T("Memo"),	0, 0 },
};

static const struct _ttymode_name {
	BYTE		opcode;
	LPCTSTR		name;
	int			memo;
} ttymode_name[] = {
		{	1,		_T("VINTR"),	IDS_TTYMODE_LIST01		},
		{	2,		_T("VQUIT"),	IDS_TTYMODE_LIST02		},
		{	3,		_T("VERASE"),	IDS_TTYMODE_LIST03		},
		{	4,		_T("VKILL"),	IDS_TTYMODE_LIST04		},
		{	5,		_T("VEOF"),		IDS_TTYMODE_LIST05		},
		{	6,		_T("VEOL"),		IDS_TTYMODE_LIST06		},
		{	7,		_T("VEOL2"),	IDS_TTYMODE_LIST07		},
		{	8,		_T("VSTART"),	IDS_TTYMODE_LIST08		},
		{	9,		_T("VSTOP"),	IDS_TTYMODE_LIST09		},
		{	10,		_T("VSUSP"),	IDS_TTYMODE_LIST10		},
		{	11,		_T("VDSUSP"),	IDS_TTYMODE_LIST11		},
		{	12,		_T("VREPRINT"),	IDS_TTYMODE_LIST12		},
		{	13,		_T("VWERASE"),	IDS_TTYMODE_LIST13		},
		{	14,		_T("VLNEXT"),	IDS_TTYMODE_LIST14		},
		{	15,		_T("VFLUSH"),	IDS_TTYMODE_LIST15		},
		{	16,		_T("VSWTCH"),	IDS_TTYMODE_LIST16		},
		{	17,		_T("VSTATUS"),	IDS_TTYMODE_LIST17		},
		{	18,		_T("VDISCARD"),	IDS_TTYMODE_LIST18		},
		{	30,		_T("IGNPAR"),	IDS_TTYMODE_LIST19		},
		{	31,		_T("PARMRK"),	IDS_TTYMODE_LIST20		},
		{	32,		_T("INPCK"),	IDS_TTYMODE_LIST21		},
		{	33,		_T("ISTRIP"),	IDS_TTYMODE_LIST22		},
		{	34,		_T("INLCR"),	IDS_TTYMODE_LIST23		},
		{	35,		_T("IGNCR"),	IDS_TTYMODE_LIST24		},
		{	36,		_T("ICRNL"),	IDS_TTYMODE_LIST25		},
		{	37,		_T("IUCLC"),	IDS_TTYMODE_LIST26		},
		{	38,		_T("IXON"),		IDS_TTYMODE_LIST27		},
		{	39,		_T("IXANY"),	IDS_TTYMODE_LIST28		},
		{	40,		_T("IXOFF"),	IDS_TTYMODE_LIST29		},
		{	41,		_T("IMAXBEL"),	IDS_TTYMODE_LIST30		},
		{	42,		_T("IUTF8"),	IDS_TTYMODE_LIST56		},		// RFC 8160
		{	50,		_T("ISIG"),		IDS_TTYMODE_LIST31		},
		{	51,		_T("ICANON"),	IDS_TTYMODE_LIST32		},
		{	52,		_T("XCASE"),	IDS_TTYMODE_LIST33		},
		{	53,		_T("ECHO"),		IDS_TTYMODE_LIST34		},
		{	54,		_T("ECHOE"),	IDS_TTYMODE_LIST35		},
		{	55,		_T("ECHOK"),	IDS_TTYMODE_LIST36		},
		{	56,		_T("ECHONL"),	IDS_TTYMODE_LIST37		},
		{	57,		_T("NOFLSH"),	IDS_TTYMODE_LIST38		},
		{	58,		_T("TOSTOP"),	IDS_TTYMODE_LIST39		},
		{	59,		_T("IEXTEN"),	IDS_TTYMODE_LIST40		},
		{	60,		_T("ECHOCTL"),	IDS_TTYMODE_LIST41		},
		{	61,		_T("ECHOKE"),	IDS_TTYMODE_LIST42		},
		{	62,		_T("PENDIN"),	IDS_TTYMODE_LIST43		},
		{	70,		_T("OPOST"),	IDS_TTYMODE_LIST44		},
		{	71,		_T("OLCUC"),	IDS_TTYMODE_LIST45		},
		{	72,		_T("ONLCR"),	IDS_TTYMODE_LIST46		},
		{	73,		_T("OCRNL"),	IDS_TTYMODE_LIST47		},
		{	74,		_T("ONOCR"),	IDS_TTYMODE_LIST48		},
		{	75,		_T("ONLRET"),	IDS_TTYMODE_LIST49		},
		{	90,		_T("CS7"),		IDS_TTYMODE_LIST50		},
		{	91,		_T("CS8"),		IDS_TTYMODE_LIST51		},
		{	92,		_T("PARENB"),	IDS_TTYMODE_LIST52		},
		{	93,		_T("PARODD"),	IDS_TTYMODE_LIST53		},
		{	128,	_T("ISPEED"),	IDS_TTYMODE_LIST54		},
		{	129,	_T("OSPEED"),	IDS_TTYMODE_LIST55		},
		{	0,		NULL,			0						}
	};

void CTtyModeDlg::InitList()
{
	int n, i;
	CString str;

	m_List.DeleteAllItems();

	for ( n = 0 ; ttymode_name[n].opcode != 0 ; n++ ) {
		str.Format(_T("%d"), ttymode_name[n].opcode);
		m_List.InsertItem(LVIF_TEXT | LVIF_PARAM, n, str, 0, 0, 0, n);
		m_List.SetItemText(n, 1, ttymode_name[n].name);
		m_List.SetItemText(n, 3, CStringLoad(ttymode_name[n].memo));
		m_List.SetItemData(n, n);

		for ( i = 0 ; i < m_pParamTab->m_TtyMode.GetSize() ; i++ ) {
			if ( ttymode_name[n].opcode == m_pParamTab->m_TtyMode[i].opcode ) {
				if ( m_pParamTab->m_TtyMode[i].opcode < 30 && m_pParamTab->m_TtyMode[i].param < 32 )
					str.Format(_T("^%c"), _T('@') + m_pParamTab->m_TtyMode[i].param);
				else
					str.Format(_T("%d"), m_pParamTab->m_TtyMode[i].param);
				m_List.SetItemText(n, 2, str);
			}
		}
	}
}

#define	ITM_LEFT_HALF	0001
#define	ITM_LEFT_RIGHT	0002
#define	ITM_RIGHT_HALF	0004
#define	ITM_RIGHT_RIGHT	0010
#define	ITM_TOP_BTM		0020
#define	ITM_BTM_BTM		0040

static	int		ItemTabInit = FALSE;
static	struct	_SftpDlgItem	{
	UINT	id;
	int		mode;
	RECT	rect;
} ItemTab[] = {
	{ IDOK,				ITM_LEFT_HALF | ITM_RIGHT_HALF | ITM_TOP_BTM | ITM_BTM_BTM },
	{ IDCANCEL,			ITM_LEFT_HALF | ITM_RIGHT_HALF | ITM_TOP_BTM | ITM_BTM_BTM },
	{ IDC_MODE_LIST,	ITM_RIGHT_RIGHT | ITM_BTM_BTM },
	{ 0,	0 },
};

void CTtyModeDlg::InitItemOffset()
{
	int n;
	int cx, mx, cy;
	CRect rect;
	WINDOWPLACEMENT place;
	CWnd *pWnd;

	if ( ItemTabInit )
		return;
	ItemTabInit = TRUE;

	GetClientRect(rect);
	cx = rect.Width();
	mx = cx / 2;
	cy = rect.Height();

	for ( n = 0 ; ItemTab[n].id != 0 ; n++ ) {
		if ( (pWnd = GetDlgItem(ItemTab[n].id)) == NULL )
			continue;

		pWnd->GetWindowPlacement(&place);

		if ( ItemTab[n].mode & ITM_LEFT_HALF )
			ItemTab[n].rect.left = place.rcNormalPosition.left - mx;
		if ( ItemTab[n].mode & ITM_LEFT_RIGHT )
			ItemTab[n].rect.left = cx - place.rcNormalPosition.left;
		if ( ItemTab[n].mode & ITM_RIGHT_HALF )
			ItemTab[n].rect.right = place.rcNormalPosition.right - mx;
		if ( ItemTab[n].mode & ITM_RIGHT_RIGHT )
			ItemTab[n].rect.right = cx - place.rcNormalPosition.right;

		if ( ItemTab[n].mode & ITM_TOP_BTM )
			ItemTab[n].rect.top = cy - place.rcNormalPosition.top;
		if ( ItemTab[n].mode & ITM_BTM_BTM )
			ItemTab[n].rect.bottom = cy - place.rcNormalPosition.bottom;
	}
}
void CTtyModeDlg::SetItemOffset(int cx, int cy)
{
	int n;
	int mx = cx / 2;
	WINDOWPLACEMENT place;
	CWnd *pWnd;

	if ( !ItemTabInit )
		return;

	for ( n = 0 ; ItemTab[n].id != 0 ; n++ ) {
		if ( (pWnd = GetDlgItem(ItemTab[n].id)) == NULL )
			continue;

		pWnd->GetWindowPlacement(&place);

		if ( ItemTab[n].mode & ITM_LEFT_HALF )
			place.rcNormalPosition.left = mx + ItemTab[n].rect.left;
		if ( ItemTab[n].mode & ITM_LEFT_RIGHT )
			place.rcNormalPosition.left = cx - ItemTab[n].rect.left;
		if ( ItemTab[n].mode & ITM_RIGHT_HALF )
			place.rcNormalPosition.right = mx + ItemTab[n].rect.right;
		if ( ItemTab[n].mode & ITM_RIGHT_RIGHT )
			place.rcNormalPosition.right = cx - ItemTab[n].rect.right;

		if ( ItemTab[n].mode & ITM_TOP_BTM )
			place.rcNormalPosition.top = cy - ItemTab[n].rect.top;
		if ( ItemTab[n].mode & ITM_BTM_BTM )
			place.rcNormalPosition.bottom = cy - ItemTab[n].rect.bottom;

		pWnd->SetWindowPlacement(&place);
	}
}

BOOL CTtyModeDlg::OnInitDialog()
{
	CDialogExt::OnInitDialog();

	InitItemOffset();

	CRect rect;
	GetWindowRect(rect);
	m_MinWidth = rect.Width();
	m_MinHeight = rect.Height();

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_List.InitColumn(_T("TtyModeDlg"), InitListTab, 4);
	m_List.m_EditSubItem = 0x04;

	InitList();

	return TRUE;
}

void CTtyModeDlg::OnOK()
{
	int n, i;
	CString str;
	LPCTSTR p;
	ttymode_node node;

	m_pParamTab->m_TtyMode.RemoveAll();

	for ( n = 0 ; n < m_List.GetItemCount() ; n++ ) {
		i = (int)m_List.GetItemData(n);
		str = m_List.GetItemText(n, 2);

		p = str;
		node.opcode = ttymode_name[i].opcode;

		if ( p[0] == _T('^') && p[1] >= _T('@') && p[1] <= _T('_') )
			node.param  = p[1] - _T('@');
		else if ( *p != _T('\0') )
			node.param  = _tstoi(p);
		else
			node.opcode = 0;

		if ( node.opcode != 0 )
			m_pParamTab->m_TtyMode.Add(node);
	}

	CDialogExt::OnOK();
}

void CTtyModeDlg::OnSize(UINT nType, int cx, int cy)
{
	SetItemOffset(cx, cy);
	CDialogExt::OnSize(nType, cx, cy);
	Invalidate(TRUE);
}
void CTtyModeDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	//case WMSZ_LEFT:			// 1 Left edge
	//case WMSZ_RIGHT:			// 2 Right edge
	//case WMSZ_TOP:			// 3 Top edge
	//case WMSZ_TOPLEFT:		// 4 Top-left corner
	//case WMSZ_TOPRIGHT:		// 5 Top-right corner
	//case WMSZ_BOTTOM:			// 6 Bottom edge
	//case WMSZ_BOTTOMLEFT:		// 7 Bottom-left corner
	//case WMSZ_BOTTOMRIGHT:	// 8 Bottom-right corner

	if ( (pRect->right - pRect->left) < m_MinWidth ) {
		if ( fwSide == WMSZ_LEFT || fwSide == WMSZ_TOPLEFT || fwSide == WMSZ_BOTTOMLEFT )
			pRect->left = pRect->right - m_MinWidth;
		else
			pRect->right = pRect->left + m_MinWidth;
	}

	if ( (pRect->bottom - pRect->top) < m_MinHeight ) {
		if ( fwSide == WMSZ_TOP || fwSide == WMSZ_TOPLEFT || fwSide == WMSZ_TOPRIGHT )
			pRect->top = pRect->bottom - m_MinHeight;
		else
			pRect->bottom = pRect->top + m_MinHeight;
	}

	CDialogExt::OnSizing(fwSide, pRect);
}

/////////////////////////////////////////////////////////////////////////////
// CColEditDlg

IMPLEMENT_DYNAMIC(CColEditDlg, CTtyModeDlg)

CColEditDlg::CColEditDlg()
{
	memset(m_ColTab, 0, sizeof(m_ColTab));
}
CColEditDlg::~CColEditDlg()
{
}

BEGIN_MESSAGE_MAP(CColEditDlg, CTtyModeDlg)
	ON_COMMAND(ID_EDIT_COPY_ALL, &CColEditDlg::OnEditCopyAll)
	ON_COMMAND(ID_EDIT_PASTE_ALL, &CColEditDlg::OnEditPasteAll)
END_MESSAGE_MAP()

static const LV_COLUMN InitColListTab[8] = {
	{ LVCF_FMT | LVCF_TEXT | LVCF_WIDTH, LVCFMT_RIGHT,  40, _T("No."),	0, 0 },
	{ LVCF_FMT | LVCF_TEXT | LVCF_WIDTH, LVCFMT_RIGHT,  60, _T("Red"),	0, 0 },
	{ LVCF_FMT | LVCF_TEXT | LVCF_WIDTH, LVCFMT_RIGHT,  60, _T("Green"),	0, 0 },
	{ LVCF_FMT | LVCF_TEXT | LVCF_WIDTH, LVCFMT_RIGHT,  60, _T("Blue"),	0, 0 },
	{ LVCF_FMT | LVCF_TEXT | LVCF_WIDTH, LVCFMT_RIGHT,  40, _T("No."),	0, 0 },
	{ LVCF_FMT | LVCF_TEXT | LVCF_WIDTH, LVCFMT_RIGHT,  60, _T("Red"),	0, 0 },
	{ LVCF_FMT | LVCF_TEXT | LVCF_WIDTH, LVCFMT_RIGHT,  60, _T("Green"),	0, 0 },
	{ LVCF_FMT | LVCF_TEXT | LVCF_WIDTH, LVCFMT_RIGHT,  60, _T("Blue"),	0, 0 },
};

void CColEditDlg::InitList()
{
	int n;
	CString str;

	m_List.DeleteAllItems();

	for ( n = 0 ; n < 8 ; n++ ) {
		str.Format(_T("%d"), n);
		m_List.InsertItem(LVIF_TEXT | LVIF_PARAM, n, str, 0, 0, 0, n);
		str.Format(_T("%d"), GetRValue(m_ColTab[n]));
		m_List.SetItemText(n, 1, str);
		str.Format(_T("%d"), GetGValue(m_ColTab[n]));
		m_List.SetItemText(n, 2, str);
		str.Format(_T("%d"), GetBValue(m_ColTab[n]));
		m_List.SetItemText(n, 3, str);

		str.Format(_T("%d"), n + 8);
		m_List.SetItemText(n, 4, str);
		str.Format(_T("%d"), GetRValue(m_ColTab[n + 8]));
		m_List.SetItemText(n, 5, str);
		str.Format(_T("%d"), GetGValue(m_ColTab[n + 8]));
		m_List.SetItemText(n, 6, str);
		str.Format(_T("%d"), GetBValue(m_ColTab[n + 8]));
		m_List.SetItemText(n, 7, str);

		m_List.SetItemData(n, n);
	}
}

BOOL CColEditDlg::OnInitDialog()
{
	CDialogExt::OnInitDialog();

	InitItemOffset();

	CRect rect;
	GetWindowRect(rect);
	m_MinWidth = rect.Width();
	m_MinHeight = rect.Height() / 2;

//	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_List.InitColumn(_T("ColEditDlg"), InitColListTab, 8);
	m_List.m_EditSubItem = 0xEE;
	m_List.SetPopUpMenu(IDR_POPUPMENU, 4);

	InitList();

	SetWindowText(_T("Color Table Edit"));

	return TRUE;
}

void CColEditDlg::OnOK()
{
	int n, i;

	for ( n = 0 ; n < m_List.GetItemCount() ; n++ ) {
		i = (int)m_List.GetItemData(n);
		m_ColTab[i]     = RGB(_tstoi(m_List.GetItemText(n, 1)), _tstoi(m_List.GetItemText(n, 2)), _tstoi(m_List.GetItemText(n, 3)));
		m_ColTab[i + 8] = RGB(_tstoi(m_List.GetItemText(n, 5)), _tstoi(m_List.GetItemText(n, 6)), _tstoi(m_List.GetItemText(n, 7)));
	}

	CDialogExt::OnOK();
}


void CColEditDlg::OnEditCopyAll()
{
	int n, i;
	CString tmp, str;

	for ( n = 0 ; n < m_List.GetItemCount() ; n++ ) {
		i = (int)m_List.GetItemData(n);
		m_ColTab[i]     = RGB(_tstoi(m_List.GetItemText(n, 1)), _tstoi(m_List.GetItemText(n, 2)), _tstoi(m_List.GetItemText(n, 3)));
		m_ColTab[i + 8] = RGB(_tstoi(m_List.GetItemText(n, 5)), _tstoi(m_List.GetItemText(n, 6)), _tstoi(m_List.GetItemText(n, 7)));
	}

	for ( n = 0 ; n < 16 ; n++ ) {
		str.Format(_T("%d\t"), GetRValue(m_ColTab[n]));
		tmp += str;
		str.Format(_T("%d\t"), GetGValue(m_ColTab[n]));
		tmp += str;
		str.Format(_T("%d\r\n"), GetBValue(m_ColTab[n]));
		tmp += str;
	}

	((CMainFrame *)::AfxGetMainWnd())->SetClipboardText(tmp);
}

void CColEditDlg::OnEditPasteAll()
{
	int n;
	LPCTSTR p;
	CString str, tmp;
	CStringArrayExt line, pam;

	if ( !((CMainFrame *)::AfxGetMainWnd())->CopyClipboardData(str) )
		return;

	for ( p = str ; *p != _T('\0') ; p++ ) {
		if ( *p == _T('\n') ) {
			if ( !tmp.IsEmpty() )
				line.Add(tmp);
			tmp.Empty();
		} else if ( *p != _T('\r') ) {
			tmp += *p;
		}
	}
	if ( !tmp.IsEmpty() )
		line.Add(tmp);

	for ( n = 0 ; n < 16 && n < line.GetSize() ; n++ ) {
		pam.GetString(line[n]);
		if ( pam.GetSize() >= 3 )
			m_ColTab[n] = RGB(pam.GetVal(0), pam.GetVal(1), pam.GetVal(2));
	}

	InitList();
}
