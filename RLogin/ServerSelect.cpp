// ServerSelect.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "RLogin.h"
#include "MainFrm.h"
#include "RLoginDoc.h"
#include "RLoginView.h"
#include "ServerSelect.h"
#include "OptDlg.h"
#include "Data.h"
#include "EditDlg.h"
#include "InitAllDlg.h"
#include "MsgChkDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerSelect ダイアログ

IMPLEMENT_DYNAMIC(CServerSelect, CDialogExt)

CServerSelect::CServerSelect(CWnd* pParent /*=NULL*/)
	: CDialogExt(CServerSelect::IDD, pParent)
{
	m_EntryNum = (-1);
	m_pData = NULL;
	m_Group.Empty();
	m_ShowTabWnd = TRUE;
	m_DefaultEntryUid = (-1);

	m_pTextRam  = new CTextRam;
	m_pKeyTab   = new CKeyNodeTab;
	m_pKeyMac   = new CKeyMacTab;
	m_pParamTab = new CParamTab;
}
CServerSelect::~CServerSelect()
{
	delete m_pTextRam;
	delete m_pKeyTab;
	delete m_pKeyMac;
	delete m_pParamTab;
}

void CServerSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogExt::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SERVERLIST, m_List);
	DDX_Control(pDX, IDC_SERVERTAB, m_Tab);
}

BEGIN_MESSAGE_MAP(CServerSelect, CDialogExt)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_SIZING()

	ON_NOTIFY(NM_DBLCLK, IDC_SERVERLIST, OnDblclkServerlist)
	ON_NOTIFY(TCN_SELCHANGE, IDC_SERVERTAB, &CServerSelect::OnTcnSelchangeServertab)

	ON_BN_CLICKED(IDC_NEWENTRY, OnNewEntry)
	ON_BN_CLICKED(IDC_EDITENTRY, OnEditEntry)
	ON_BN_CLICKED(IDC_DELENTRY, OnDelEntry)

	ON_COMMAND(ID_EDIT_NEW, OnNewEntry)
	ON_COMMAND(ID_EDIT_UPDATE, OnEditEntry)
	ON_COMMAND(ID_EDIT_DELETE, OnDelEntry)
	ON_COMMAND(ID_EDIT_DUPS, OnEditCopy)
	ON_COMMAND(ID_EDIT_CHECK, OnEditCheck)

	ON_COMMAND(IDM_SERV_INPORT, &CServerSelect::OnServInport)
	ON_COMMAND(IDM_SERV_EXPORT, &CServerSelect::OnServExport)
	ON_COMMAND(IDM_SERV_PROTO, &CServerSelect::OnServProto)
	ON_COMMAND(IDC_SAVEDEFAULT, &CServerSelect::OnSaveDefault)
	ON_COMMAND(IDM_SERV_EXCHNG, &CServerSelect::OnServExchng)
	ON_COMMAND(IDC_LOADDEFAULT, &CServerSelect::OnLoaddefault)
	ON_COMMAND(IDM_SHORTCUT, &CServerSelect::OnShortcut)

	ON_UPDATE_COMMAND_UI(ID_EDIT_UPDATE, OnUpdateEditEntry)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditEntry)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DUPS, OnUpdateEditEntry)
	ON_UPDATE_COMMAND_UI(IDM_SERV_EXPORT, OnUpdateEditEntry)
	ON_UPDATE_COMMAND_UI(IDM_SERV_EXCHNG, OnUpdateServExchng)
	ON_UPDATE_COMMAND_UI(IDC_SAVEDEFAULT, OnUpdateSaveDefault)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_NOTIFY(NM_RCLICK, IDC_SERVERTAB, &CServerSelect::OnNMRClickServertab)
END_MESSAGE_MAP()

void CServerSelect::InitList()
{
	int n, i;
	int idx;
	CString str;

RETRY:
	idx = (-1);
	m_TabEntry.RemoveAll();
	m_Tab.DeleteAllItems();
	m_List.DeleteAllItems();

	if ( m_EntryNum >= 0 && m_EntryNum < m_pData->GetSize() )
		m_Group = m_pData->GetAt(m_EntryNum).m_Group;

	for ( n = i = 0 ; n < m_pData->GetSize() ; n++ ) {
		if ( m_Group.Compare(m_pData->GetAt(n).m_Group) == 0 ) {
#ifdef	USE_DEFENTRYMARK
			if ( m_DefaultEntryUid == m_pData->GetAt(n).m_Uid ) {
				str.Format(_T("%s (*)"), m_pData->GetAt(n).m_EntryName);
				m_List.InsertItem(LVIF_TEXT | LVIF_PARAM, i, str, 0, 0, 0, n);
			} else
#endif
				m_List.InsertItem(LVIF_TEXT | LVIF_PARAM, i, m_pData->GetAt(n).m_EntryName, 0, 0, 0, n);

			m_List.SetItemText(i, 1, m_pData->GetAt(n).m_HostName);
			m_List.SetItemText(i, 2, m_pData->GetAt(n).m_UserName);
			m_List.SetItemText(i, 3, m_pData->GetAt(n).m_TermName);
			m_List.SetItemText(i, 4, m_pData->GetAt(n).GetKanjiCode());
			m_List.SetItemText(i, 5, m_pData->GetAt(n).m_PortName);

			if ( m_pData->GetAt(n).m_bSelFlag ) {
				m_List.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
				m_pData->GetAt(n).m_bSelFlag = FALSE;
			}

			if ( n == m_EntryNum )
				idx = i;
			i++;
		}
		m_TabEntry[m_pData->GetAt(n).m_Group].m_Value = 1;
	}

	if ( m_TabEntry.GetSize() == 0 )
		m_TabEntry[_T("")].m_Value = 1;

	for ( n = 0 ; n < m_TabEntry.GetSize() ; n++ )
		m_Tab.InsertItem(n, m_TabEntry[n].m_nIndex);

	if ( (n = m_TabEntry.Find(m_Group)) != (-1) )
		m_Tab.SetCurSel(n);
	else {
		m_Group = m_TabEntry[0].m_nIndex;
		goto RETRY;
	}

	if ( idx != (-1) )
		m_List.SetItemState(idx, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

	m_List.DoSortItem();
}

#define	ITM_LEFT_HALF	0001
#define	ITM_LEFT_RIGHT	0002
#define	ITM_RIGHT_HALF	0004
#define	ITM_RIGHT_RIGHT	0010
#define	ITM_TOP_BTM		0020
#define	ITM_BTM_BTM		0040
#define	ITM_TOP_SAVE	0100
#define	ITM_TOP_LOAD	0200

static	int		ItemTabInit = FALSE;
static	struct	_SftpDlgItem	{
	UINT	id;
	int		mode;
	RECT	rect;
} ItemTab[] = {
	{ IDOK,				ITM_LEFT_RIGHT | ITM_RIGHT_RIGHT },
	{ IDCANCEL,			ITM_LEFT_RIGHT | ITM_RIGHT_RIGHT },
	{ IDC_NEWENTRY,		ITM_LEFT_RIGHT | ITM_RIGHT_RIGHT | ITM_TOP_BTM | ITM_BTM_BTM },
	{ IDC_EDITENTRY,	ITM_LEFT_RIGHT | ITM_RIGHT_RIGHT | ITM_TOP_BTM | ITM_BTM_BTM },
	{ IDC_DELENTRY,		ITM_LEFT_RIGHT | ITM_RIGHT_RIGHT | ITM_TOP_BTM | ITM_BTM_BTM },
	{ IDC_SERVERTAB,	ITM_RIGHT_RIGHT | ITM_TOP_SAVE },
	{ IDC_SERVERLIST,	ITM_RIGHT_RIGHT | ITM_BTM_BTM | ITM_TOP_LOAD },
	{ 0,	0 },
};

void CServerSelect::InitItemOffset()
{
	int n;
	int cx, mx, cy;
	CRect rect;
	WINDOWPLACEMENT place;
	CWnd *pWnd;

	//if ( ItemTabInit )
	//	return;
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

		if ( ItemTab[n].mode & ITM_TOP_SAVE )
			ItemTab[n].rect.top = place.rcNormalPosition.top;
		if ( ItemTab[n].mode & ITM_TOP_LOAD )
			ItemTab[n].rect.top = place.rcNormalPosition.top;
	}
}
void CServerSelect::SetItemOffset(int cx, int cy)
{
	int n, sy;
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

		if ( ItemTab[n].mode & ITM_TOP_SAVE )
			sy = ItemTab[n].rect.top;
		if ( ItemTab[n].mode & ITM_TOP_LOAD ) {
			if ( m_Tab.GetItemCount() <= 1 ) {
				place.rcNormalPosition.top = sy;
				m_Tab.ShowWindow(SW_HIDE);
				m_ShowTabWnd = FALSE;
			} else {
				place.rcNormalPosition.top = ItemTab[n].rect.top;
				m_Tab.ShowWindow(SW_NORMAL);
				m_ShowTabWnd = TRUE;
			}
		}

		pWnd->SetWindowPlacement(&place);
	}
}
void CServerSelect::UpdateTabWnd()
{
	CRect rect;
	BOOL req = (m_Tab.GetItemCount() <= 1 ? FALSE : TRUE);

	if ( req != m_ShowTabWnd ) {
		GetClientRect(rect);
		SetItemOffset(rect.Width(), rect.Height());
	}
}
void CServerSelect::UpdateDefaultEntry(int num)
{
	CServerEntry *pEntry;

	if ( m_DefaultEntryUid == (-1) )
		return;

	pEntry = &(m_pData->GetAt(num));

	if ( pEntry->m_Uid != m_DefaultEntryUid )
		return;

	if ( MessageBox(CStringLoad(IDS_DEFENTRYEDITMSG), _T("Question"), MB_ICONQUESTION | MB_YESNO) != IDYES )
		return;

	CRLoginDoc::LoadOption(*pEntry, *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);
	CRLoginDoc::SaveDefOption(*m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);
}

/////////////////////////////////////////////////////////////////////////////
// CServerSelect メッセージ ハンドラ

static const LV_COLUMN InitListTab[6] = {
		{ LVCF_TEXT | LVCF_WIDTH, 0,  80, _T("Entry"),  0, 0 }, 
		{ LVCF_TEXT | LVCF_WIDTH, 0,  60, _T("Server"), 0, 0 }, 
		{ LVCF_TEXT | LVCF_WIDTH, 0,  50, _T("User"),   0, 0 }, 
		{ LVCF_TEXT | LVCF_WIDTH, 0,  50, _T("Term"),   0, 0 }, 
		{ LVCF_TEXT | LVCF_WIDTH, 0,  40, _T("Kanji"),  0, 0 }, 
		{ LVCF_TEXT | LVCF_WIDTH, 0,  40, _T("Socket"), 0, 0 }, 
	};

BOOL CServerSelect::OnInitDialog() 
{
	int cx, cy;
	CRect rect;

	ASSERT(m_pData != NULL);

	CDialogExt::OnInitDialog();

	m_TabEntry.SetNoCase(FALSE);
	m_TabEntry.SetNoSort(FALSE);

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_List.InitColumn(_T("ServerSelect"), InitListTab, 6);
	m_List.SetPopUpMenu(IDR_POPUPMENU, 0);

	if ( m_EntryNum == (-1) ) {
		m_EntryNum = AfxGetApp()->GetProfileInt(_T("ServerSelect"), _T("LastAccess"), (-1));
		if ( m_EntryNum >= m_pData->GetSize() )
			m_EntryNum = (-1);
	}

	if ( m_EntryNum < 0 && m_pData->GetSize() > 0 )
		m_Group = m_pData->GetAt(0).m_Group;

	m_DefaultEntryUid = ::AfxGetApp()->GetProfileInt(_T("ServerSelect"), _T("DefaultEntry"), (-1));

	InitList();
	InitItemOffset();

	GetWindowRect(rect);
	m_MinWidth = rect.Width();
	m_MinHeight = rect.Height();
	cx = AfxGetApp()->GetProfileInt(_T("ServerSelect"), _T("cx"), rect.Width());
	cy = AfxGetApp()->GetProfileInt(_T("ServerSelect"), _T("cy"), rect.Height());
	if ( cx < rect.Width() )
		cx = rect.Width();
	if ( cy < rect.Height() )
		cy = rect.Height();
	MoveWindow(rect.left, rect.top, cx, cy, FALSE);
	UpdateTabWnd();

	return TRUE;
}
void CServerSelect::OnOK()
{
	CRect rect;
	GetWindowRect(rect);
	AfxGetApp()->WriteProfileInt(_T("ServerSelect"), _T("cx"), rect.Width());
	AfxGetApp()->WriteProfileInt(_T("ServerSelect"), _T("cy"), rect.Height());

	m_EntryNum = m_List.GetSelectMarkData();
	AfxGetApp()->WriteProfileInt(_T("ServerSelect"), _T("LastAccess"), m_EntryNum);
	m_List.SaveColumn(_T("ServerSelect"));

	int n, i;

	for ( n = 0 ; n < m_pData->GetSize() ; n++ )
		m_pData->GetAt(n).m_CheckFlag = FALSE;

	for ( n = 0 ; n < m_List.GetItemCount() ; n++ ) {
		if ( m_List.GetItemState(n, LVIS_SELECTED) != 0 ) {
			i = (int)m_List.GetItemData(n);
			m_pData->GetAt(i).m_CheckFlag = TRUE;
		}
	}

	CDialogExt::OnOK();
}

void CServerSelect::OnDblclkServerlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	PostMessage(WM_COMMAND, IDOK);
	*pResult = 0;
}

void CServerSelect::OnNewEntry() 
{
	CServerEntry Entry;
	COptDlg dlg(_T("Server New Entry"), this);

	Entry.m_Group = m_Group;
	CRLoginDoc::LoadDefOption(*m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);

	dlg.m_pEntry    = &Entry;
	dlg.m_pTextRam  = m_pTextRam;
	dlg.m_pKeyTab   = m_pKeyTab;
	dlg.m_pKeyMac   = m_pKeyMac;
	dlg.m_pParamTab = m_pParamTab;
	dlg.m_psh.dwFlags |= PSH_NOAPPLYNOW;

	if ( dlg.DoModal() != IDOK )
		return;

	m_pTextRam->InitDefParam(FALSE);
	CRLoginDoc::SaveOption(Entry, *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);

	m_EntryNum = m_pData->AddEntry(Entry);
	InitList();
	UpdateTabWnd();
}
void CServerSelect::OnEditEntry() 
{
	int n;
	int num;
	CServerEntry Entry;
	CStringIndex index;
	int Count = 0;

	for ( n = 0 ; n < m_List.GetItemCount() ; n++ ) {
		if ( m_List.GetItemState(n, LVIS_SELECTED) != 0 )
			Count++;
	}

	if ( Count <= 0 || (m_EntryNum = m_List.GetSelectMarkData()) < 0 )
		return;

	Entry = m_pData->GetAt(m_EntryNum);
	CRLoginDoc::LoadOption(Entry, *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);

	COptDlg dlg(_T("Server Edit Entry"), this);

	dlg.m_pEntry    = &Entry;
	dlg.m_pTextRam  = m_pTextRam;
	dlg.m_pKeyTab   = m_pKeyTab;
	dlg.m_pKeyMac   = m_pKeyMac;
	dlg.m_pParamTab = m_pParamTab;
	dlg.m_psh.dwFlags |= PSH_NOAPPLYNOW;

	if ( dlg.DoModal() != IDOK )
		return;

	m_pTextRam->InitDefParam(FALSE);
	CRLoginDoc::SaveOption(Entry, *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);

	if ( Count > 1 ) {
		CRLoginDoc::DiffIndex(Entry, *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab, m_pData->GetAt(m_EntryNum), index);

		CStringLoad str(IDS_ENTRYMULTIEDIT);
		index.MsgStr(str);

		if ( MessageBox(str, _T("Edit Multiple Entries"), MB_ICONQUESTION | MB_YESNO) != IDYES )
			return;

		for ( n = 0 ; n < m_List.GetItemCount() ; n++ ) {
			if ( m_List.GetItemState(n, LVIS_SELECTED) == 0 )
				continue;

			Entry.Init();
			CRLoginDoc::LoadInitOption(*m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);

			num = (int)m_List.GetItemData(n);
			Entry = m_pData->GetAt(num);

			CRLoginDoc::LoadOption(Entry, *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);
			CRLoginDoc::LoadIndex(Entry, *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab, index);
			CRLoginDoc::SaveOption(Entry, *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);

			Entry.m_bSelFlag = TRUE;
			m_pData->m_Data[num] = Entry;
			m_pData->UpdateAt(num);
			UpdateDefaultEntry(num);
		}

	} else {
		m_pData->m_Data[m_EntryNum] = Entry;
		m_pData->UpdateAt(m_EntryNum);
		UpdateDefaultEntry(m_EntryNum);
	}

	InitList();
	UpdateTabWnd();
}
void CServerSelect::OnDelEntry() 
{
	int n, i;
	CString tmp, msg;
	CDWordArray tab;

	for ( n = 0 ; n < m_List.GetItemCount() ; n++ ) {
		if ( m_List.GetItemState(n, LVIS_SELECTED) == 0 )
			continue;
		i = (int)m_List.GetItemData(n);

		if ( !tmp.IsEmpty() )
			tmp += _T(',');
		tmp += m_pData->m_Data[i].m_EntryName;

		if ( m_pData->m_Data[i].m_Uid >= 0 )
			tab.Add(m_pData->m_Data[i].m_Uid);
	}

	if ( (n = tmp.GetLength()) > 50 )
		tmp.Delete(40, n - 40);

	if ( (n = (int)tab.GetSize()) <= 0 )
		return;
	else if ( n > 1 ) {
		msg.Format(_T("...[%d]"), n);
		tmp += msg;
	}
	
	msg.LoadString(IDS_SERVERENTRYDELETE);
	msg += tmp;

	if ( MessageBox(msg, _T("Question"), MB_YESNO | MB_ICONQUESTION ) != IDYES )
		return;

	for ( n = 0 ; n < tab.GetSize() ; n++ ) {
		for ( i = 0 ; i < m_pData->GetSize() ; i++ ) {
			if ( tab[n] == m_pData->m_Data[i].m_Uid ) {
				m_pData->RemoveAt(i);
				break;
			}
		}
	}

	InitList();
	UpdateTabWnd();
}
void CServerSelect::OnEditCopy() 
{
	if ( (m_EntryNum = m_List.GetSelectMarkData()) < 0 )
		return;
	int n, i;
	CServerEntry tmp;
	tmp = m_pData->GetAt(m_EntryNum);
	for ( i = 2 ; ; i++ ) {
		tmp.m_EntryName.Format(_T("%s(%d)"), m_pData->GetAt(m_EntryNum).m_EntryName, i);
		for ( n = 0 ; n < m_pData->GetSize() ; n++ ) {
			if ( tmp.m_EntryName.Compare(m_pData->GetAt(n).m_EntryName) == 0 )
				break;
		}
		if ( n >= m_pData->GetSize() )
			break;
	}
	tmp.m_Uid = (-1);
	m_EntryNum = m_pData->AddEntry(tmp);
	InitList();
	UpdateTabWnd();
}
void CServerSelect::OnEditCheck()
{
	int n, i;
	CServerEntryTab tab;
	CBuffer nbuf, obuf;
	CWordArray apend, remove, update;

	tab.Serialize(FALSE);

	for ( n = 0 ; n < tab.GetSize() ; n++ ) {
		for ( i = 0 ; i < m_pData->GetSize() ; i++ ) {
			if ( tab.GetAt(n).m_Uid == m_pData->GetAt(i).m_Uid )
				break;
		}
		if ( i < m_pData->GetSize() ) {
			nbuf.Clear();
			tab.GetAt(n).SetBuffer(nbuf);
			obuf.Clear();
			m_pData->GetAt(i).SetBuffer(obuf);
			if ( nbuf.GetSize() != obuf.GetSize() || memcmp(nbuf.GetPtr(), obuf.GetPtr(), nbuf.GetSize()) != 0 ) {
				update.Add(i);
				update.Add(n);
			}
		} else
			apend.Add(n);
	}
	for ( i = 0 ; i < m_pData->GetSize() ; i++ ) {
		for ( n = 0 ; n < tab.GetSize() ; n++ ) {
			if ( tab.GetAt(n).m_Uid == m_pData->GetAt(i).m_Uid )
				break;
		}
		if ( n >= tab.GetSize() )
			remove.Add(i);
	}

	for ( n = 0 ; n < apend.GetSize() ; n++ )
		m_pData->m_Data.Add(tab.GetAt(apend[n]));
	for ( n = 0 ; n < update.GetSize() ; n += 2 )
		m_pData->m_Data[update[n]] = tab.GetAt(update[n + 1]);
	for ( n = 0 ; n < remove.GetSize() ; n++ )
		m_pData->m_Data.RemoveAt(remove[n]);

	m_DefaultEntryUid = ::AfxGetApp()->GetProfileInt(_T("ServerSelect"), _T("DefaultEntry"), (-1));

	InitList();
	UpdateTabWnd();
}

void CServerSelect::OnUpdateEditEntry(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_List.GetSelectMarkData() >= 0);
}

void CServerSelect::OnServInport()
{
	CFileDialog dlg(TRUE, _T("rlg"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, CStringLoad(IDS_FILEDLGRLOGIN), this);

	if ( dlg.DoModal() != IDOK )
		return;

	CFile File;

	if ( !File.Open(dlg.GetPathName(), CFile::modeRead | CFile::shareExclusive) ) {
		MessageBox(_T("File Open Error"));
		return;
	}

	CWaitCursor wait;
	CArchive Archive(&File, CArchive::load);

	int n;
	CHAR tmp[32];
	CServerEntry Entry;
	int ver = 0;

	TRY {
		memset(tmp, 0, 16);
		for ( n = 0 ; n < 16 && Archive.Read(&(tmp[n]), 1) == 1 ; n++ ) {
			if ( tmp[n] == '\n' )
				break;
		}

		if ( strncmp((LPSTR)tmp, "RLG4", 4) == 0 )
			ver = 4;
		else if ( strncmp((LPSTR)tmp, "RLG3", 4) == 0 )
			ver = 3;
		else if ( strncmp((LPSTR)tmp, "RLG2", 4) == 0 )
			ver = 2;

		if ( ver == 3 || ver == 4 ) {
			for ( ; ; ) {
				CStringIndex index;

				index.RemoveAll();
				index.SetNoCase(TRUE);
				index.SetNoSort(TRUE);
				index.Serialize(Archive, NULL, ver);

				CRLoginDoc::LoadIndex(Entry, *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab, index);

				Entry.m_Uid = (-1);
				m_pParamTab->m_IdKeyList.RemoveAll();
				CRLoginDoc::SaveOption(Entry, *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);

				m_EntryNum = m_pData->AddEntry(Entry);

				memset(tmp, 0, 16);
				for ( n = 0 ; n < 16 && Archive.Read(&(tmp[n]), 1) == 1 ; n++ ) {
					if ( tmp[n] == '\n' )
						break;
				}
				if ( (ver == 3 && strncmp((LPSTR)tmp, "RLG31", 5) != 0) ||
					 (ver == 4 && strncmp((LPSTR)tmp, "RLG41", 5) != 0) )
					break;

				Entry.Init();
				CRLoginDoc::LoadInitOption(*m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);
			}

		} else if ( ver == 2 ) {
			for ( ; ; ) {
				Entry.Serialize(Archive);
				m_pTextRam->Serialize(Archive);
				m_pKeyTab->Serialize(Archive);
				m_pKeyMac->Serialize(Archive);
				m_pParamTab->Serialize(Archive);

				Entry.m_Uid = (-1);
				m_pParamTab->m_IdKeyList.RemoveAll();
				CRLoginDoc::SaveOption(Entry, *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);

				m_EntryNum = m_pData->AddEntry(Entry);

				memset(tmp, 0, 16);
				for ( n = 0 ; n < 16 && Archive.Read(&(tmp[n]), 1) == 1 ; n++ ) {
					if ( tmp[n] == '\n' )
						break;
				}
				if ( strncmp((LPSTR)tmp, "RLG21", 5) != 0 )
					break;

				Entry.Init();
				CRLoginDoc::LoadInitOption(*m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);
			}
		} else
			AfxThrowArchiveException(CArchiveException::badIndex, Archive.GetFile()->GetFileTitle());

	} CATCH_ALL(e) {
		MessageBox(_T("File Read Error"));
	} END_CATCH_ALL

	Archive.Close();
	File.Close();

	InitList();
	UpdateTabWnd();
}
void CServerSelect::OnServExport()
{
	int n;
	CFile File;
	CStringIndex index;
	CServerEntry Entry;

	if ( (m_EntryNum = m_List.GetSelectMarkData()) < 0 )
		return;

	CFileDialog dlg(FALSE, _T("rlg"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, CStringLoad(IDS_FILEDLGRLOGIN), this);

	if ( dlg.DoModal() != IDOK )
		return;

	if ( !File.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive) ) {
		MessageBox(_T("File Crate Error"));
		return;
	}

	CWaitCursor wait;
	CArchive Archive(&File, CArchive::store | CArchive::bNoFlushOnDelete);

	TRY {
		for ( n = 0 ; n < m_List.GetItemCount() ; n++ ) {
			if ( m_List.GetItemState(n, LVIS_SELECTED) == 0 )
				continue;

			m_EntryNum = (int)m_List.GetItemData(n);
			Entry = m_pData->GetAt(m_EntryNum);
			CRLoginDoc::LoadOption(Entry, *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);

			index.RemoveAll();
			index.SetNoCase(TRUE);
			index.SetNoSort(TRUE);

			CRLoginDoc::SaveIndex(Entry, *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab, index);

			Archive.Write("RLG310\r\n", 8);
			index.Serialize(Archive, NULL);
			Archive.Write("ENDOF\r\n", 7);
		}

	} CATCH_ALL(e) {
		MessageBox(_T("File Write Error"));
	} END_CATCH_ALL

	Archive.Close();
	File.Close();
}
void CServerSelect::OnServExchng()
{
	CFileDialog dlg(TRUE, _T("rlg"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, CStringLoad(IDS_FILEDLGRLOGIN), this);

	if ( dlg.DoModal() != IDOK )
		return;

	CFile File;

	if ( !File.Open(dlg.GetPathName(), CFile::modeRead | CFile::shareExclusive) ) {
		MessageBox(_T("File Open Error"));
		return;
	}

	CWaitCursor wait;
	CArchive Archive(&File, CArchive::load);

	int n;
	CServerEntry Entry;
	CStringIndex index;

	index.SetNoCase(TRUE);
	index.SetNoSort(TRUE);

	TRY {
		index.Serialize(Archive, NULL);
	} CATCH_ALL(e) {
		MessageBox(_T("File Read Error"));
	} END_CATCH_ALL

	Archive.Close();
	File.Close();

	if ( index.GetSize() == 0 )
		return;

	for ( n = 0 ; n < m_List.GetItemCount() ; n++ ) {
		if ( m_List.GetItemState(n, LVIS_SELECTED) == 0 )
			continue;

		m_EntryNum = (int)m_List.GetItemData(n);
		Entry = m_pData->GetAt(m_EntryNum);
		CRLoginDoc::LoadOption(Entry, *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);
		CRLoginDoc::LoadIndex(Entry, *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab, index);
		CRLoginDoc::SaveOption(Entry, *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);

		m_pData->m_Data[m_EntryNum] = Entry;
		m_pData->UpdateAt(m_EntryNum);
		UpdateDefaultEntry(m_EntryNum);
	}

	InitList();
	UpdateTabWnd();
}
void CServerSelect::OnUpdateServExchng(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_List.GetSelectMarkData() >= 0);
}

void CServerSelect::OnServProto()
{
	CString proto, option;
	CServerEntry *pEntry;
	CRLoginApp *pApp = (CRLoginApp *)AfxGetApp();
	CEditDlg dlg;

	if ( (m_EntryNum = m_List.GetSelectMarkData()) < 0 || pApp == NULL )
		return;

	pEntry = &(m_pData->m_Data[m_EntryNum]);

	switch(pEntry->m_ProtoType) {
	case PROTO_LOGIN:
		proto = _T("login");
		break;
	case PROTO_TELNET:
		proto = _T("telnet");
		break;
	case PROTO_SSH:
		proto = _T("ssh");
		break;
	default:
		MessageBox(CStringLoad(IDE_PROTOCOLENTRY));
		return;
	}

	if ( pEntry->m_EntryName.IsEmpty() ) {
		MessageBox(CStringLoad(IDE_USESERVERENTRY));
		return;
	}
	option.Format(_T("/entry \"%s\" /inuse"), pEntry->m_EntryName);

	dlg.m_WinText.LoadString(IDS_PROTODLGTITLE);
	dlg.m_Title = proto;
	dlg.m_Title += CStringLoad(IDS_PRORODLGCOMM);
	dlg.m_Edit = option;

	if ( dlg.DoModal() != IDOK )
		return;
	option = dlg.m_Edit;

	pApp->RegisterShellProtocol(proto, option);
}

void CServerSelect::OnClose()
{
	CRect rect;

	GetWindowRect(rect);
	AfxGetApp()->WriteProfileInt(_T("ServerSelect"), _T("cx"), rect.Width());
	AfxGetApp()->WriteProfileInt(_T("ServerSelect"), _T("cy"), rect.Height());

	CDialogExt::OnClose();
}
void CServerSelect::OnSize(UINT nType, int cx, int cy)
{
	SetItemOffset(cx, cy);
	CDialogExt::OnSize(nType, cx, cy);
	Invalidate(TRUE);
}
void CServerSelect::OnSizing(UINT fwSide, LPRECT pRect)
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

void CServerSelect::OnTcnSelchangeServertab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int n = m_Tab.GetCurSel();

	if ( n >= 0 && n < m_TabEntry.GetSize() ) {
		m_Group = m_TabEntry[n].m_nIndex;
		m_EntryNum = (-1);
		InitList();
	}
	*pResult = 0;
}

void CServerSelect::OnNMRClickServertab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int n;
	TCHITTESTINFO info;
	
	*pResult = 0;

	if ( !GetCursorPos(&info.pt) )
		return;

	m_Tab.ScreenToClient(&info.pt);

	if ( (n = m_Tab.HitTest(&info)) < 0 || n >= m_TabEntry.GetSize() )
		return;

	m_Tab.SetCurSel(n);
	m_Group = m_TabEntry[n].m_nIndex;
	m_EntryNum = (-1);
	InitList();

	m_List.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

	for ( n = 1 ; n < m_List.GetItemCount() ; n++ )
		m_List.SetItemState(n, LVIS_SELECTED, LVIS_SELECTED);
}

void CServerSelect::OnSaveDefault()
{
	if ( (m_EntryNum = m_List.GetSelectMarkData()) < 0 )
		return;

	CServerEntry *pEntry;

	pEntry = &(m_pData->GetAt(m_EntryNum));
	CRLoginDoc::LoadOption(*pEntry,*m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);
	CRLoginDoc::SaveDefOption(*m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);

	if ( pEntry->m_Uid != (-1) )
		::AfxGetApp()->WriteProfileInt(_T("ServerSelect"), _T("DefaultEntry"), pEntry->m_Uid);

	m_DefaultEntryUid = pEntry->m_Uid;

	InitList();
	UpdateTabWnd();
}
void CServerSelect::OnUpdateSaveDefault(CCmdUI *pCmdUI)
{
	int n = m_List.GetSelectMarkData();

	if ( n >= 0 && m_List.GetSelectMarkCount() == 1 && !m_pData->GetAt(n).m_bOptFixed )
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}
void CServerSelect::OnLoaddefault()
{
	int n;
	CBuffer ProBuffer;
	CInitAllDlg dlg;

	if ( dlg.DoModal() != IDOK )
		return;

	switch(dlg.m_InitType) {
	case 0:		// Init Default Entry
		CRLoginDoc::LoadDefOption(*m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);
		break;

	case 1:		// Init Program Default
		CRLoginDoc::LoadInitOption(*m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);
		break;

	case 2:		// Copy Entry option
		ASSERT(dlg.m_pInitEntry != NULL);
		CRLoginDoc::LoadOption(*(dlg.m_pInitEntry), *m_pTextRam, *m_pKeyTab, *m_pKeyMac, *m_pParamTab);
		break;
	}

	m_pTextRam->Serialize(TRUE,  ProBuffer);
	m_pKeyTab->Serialize(TRUE,   ProBuffer);
	m_pKeyMac->Serialize(TRUE,   ProBuffer);
	m_pParamTab->Serialize(TRUE, ProBuffer);

	for ( n = 0 ; n < m_List.GetItemCount() ; n++ ) {
		if ( m_List.GetItemState(n, LVIS_SELECTED) == 0 )
			continue;

		m_EntryNum = (int)m_List.GetItemData(n);
		m_pData->GetAt(m_EntryNum).m_ProBuffer = ProBuffer;
		m_pData->UpdateAt(m_EntryNum);
	}
}
void CServerSelect::OnShortcut()
{
	int n, i;

	for ( n = 0 ; n < m_List.GetItemCount() ; n++ ) {
		if ( m_List.GetItemState(n, LVIS_SELECTED) == 0 )
			continue;

		i = (int)m_List.GetItemData(n);
		if ( m_pData->GetAt(i).m_EntryName.IsEmpty() )
			continue;

		if ( !((CRLoginApp *)AfxGetApp())->CreateDesktopShortcut(m_pData->GetAt(i).m_EntryName) ) {
			MessageBox(_T("Can't Create Desktop Shortcut"));
			break;
		}
	}
}

BOOL CServerSelect::PreTranslateMessage(MSG* pMsg)
{
	int n;
	CWnd *pWnd = GetFocus();

	if ( m_ShowTabWnd && pMsg->message == WM_KEYDOWN && (pWnd != NULL && pWnd->GetSafeHwnd() == m_List.GetSafeHwnd()) ) {
		if ( (pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT) ) {
			n = m_Tab.GetCurSel() + (pMsg->wParam == VK_LEFT ? (-1) : 1);

			if ( n < 0 )
				n = m_Tab.GetItemCount() - 1;
			else if ( n >= m_Tab.GetItemCount() )
				n = 0;

			m_Tab.SetCurSel(n);
			m_Group = m_TabEntry[n].m_nIndex;
			m_EntryNum = (-1);
			InitList();
			return TRUE;
		}
	}

	return CDialogExt::PreTranslateMessage(pMsg);
}

#ifdef	USE_DEFENTRYMARK
void CServerSelect::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if ( nIDCtl != IDC_SERVERLIST ) {
		CDialogExt::OnDrawItem(nIDCtl, lpDrawItemStruct);
		return;
	}

	LV_ITEM lvi;
	ZeroMemory(&lvi, sizeof(lvi));
    lvi.mask = LVIF_STATE | LVIF_PARAM;
	lvi.iItem = lpDrawItemStruct->itemID;
	lvi.stateMask = 0xFFFF;

	if ( !m_List.GetItem(&lvi) ) {
		CDialogExt::OnDrawItem(nIDCtl, lpDrawItemStruct);
		return;
	}

	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	COLORREF bkc, txc;

	if ( (lvi.state & LVIS_SELECTED) != 0 ) {
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_HIGHLIGHT));
		bkc = pDC->SetBkColor(GetSysColor(COLOR_HIGHLIGHT));
		txc = pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
	} else {
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_WINDOW));
		bkc = pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
		if ( m_DefaultEntryUid == m_pData->GetAt((int)lvi.lParam).m_Uid )
			txc = pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
		else
			txc = pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
	}

	CString str;
	CRect rect(lpDrawItemStruct->rcItem);
	LVCOLUMN lvc;
	ZeroMemory(&lvc, sizeof(lvc));
	lvc.mask = LVCF_WIDTH | LVCF_FMT;

	m_List.GetItemRect(lpDrawItemStruct->itemID, rect, LVIR_LABEL);

	rect.left -= m_List.GetScrollPos(SB_HORZ);
	for ( int i = 0 ; m_List.GetColumn(i, &lvc) ; i++ ) {
		str = m_List.GetItemText(lpDrawItemStruct->itemID, i);

		rect.right = rect.left + lvc.cx - 4;
		pDC->DrawText(str, rect,
			(lvc.fmt == LVCFMT_LEFT   ? DT_LEFT : 0) |
			(lvc.fmt == LVCFMT_RIGHT  ? DT_RIGHT : 0) |
			(lvc.fmt == LVCFMT_CENTER ? DT_CENTER : 0) | DT_SINGLELINE | DT_NOPREFIX | DT_WORD_ELLIPSIS | DT_VCENTER);

		rect.left = rect.right + 4;
	}

	if ( (lvi.state & LVIS_FOCUSED) != 0 && GetFocus()->GetSafeHwnd() == m_List.GetSafeHwnd() )
		pDC->DrawFocusRect(&lpDrawItemStruct->rcItem);

	pDC->SetBkColor(bkc);
	pDC->SetTextColor(txc);
}
void CServerSelect::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if ( nIDCtl == IDC_SERVERLIST )
		lpMeasureItemStruct->itemHeight = m_FontSize * 96 / 72 + 4;

	CDialogExt::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}
#endif	// USE_DEFENTRYMARK
