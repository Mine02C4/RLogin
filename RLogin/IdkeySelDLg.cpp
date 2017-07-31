// IdkeySelDLg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "RLogin.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "RLoginDoc.h"
#include "IdkeySelDLg.h"
#include "IdKeyFileDlg.h"
#include "EditDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIdkeySelDLg �_�C�A���O

CIdkeySelDLg::CIdkeySelDLg(CWnd* pParent /*=NULL*/)
	: CDialog(CIdkeySelDLg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIdkeySelDLg)
	m_Type = _T("DSA2");
	m_Bits = _T("1024");
	m_Name = _T("");
	//}}AFX_DATA_INIT
	m_pIdKeyTab = NULL;
	m_pParamTab = NULL;
	m_EntryNum = (-1);
	m_pKeyGenEvent = new CEvent(FALSE, TRUE);
	m_KeyGenFlag = 0;
	m_GenIdKeyTimer = NULL;
}
CIdkeySelDLg::~CIdkeySelDLg()
{
	EndofKeyGenThead();
	delete m_pKeyGenEvent;
}

void CIdkeySelDLg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIdkeySelDLg)
	DDX_Control(pDX, IDC_IDKEY_PROG, m_KeyGenProg);
	DDX_Control(pDX, IDC_IDKEY_LIST, m_List);
	DDX_CBString(pDX, IDC_IDKEY_TYPE, m_Type);
	DDX_CBString(pDX, IDC_IDKEY_BITS, m_Bits);
	DDX_Text(pDX, IDC_IDKEY_NAME, m_Name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIdkeySelDLg, CDialog)
	//{{AFX_MSG_MAP(CIdkeySelDLg)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_IDKEY_UP, OnIdkeyUp)
	ON_BN_CLICKED(IDC_IDKEY_DOWN, OnIdkeyDown)
	ON_BN_CLICKED(IDC_IDKEY_DEL, OnIdkeyDel)
	ON_BN_CLICKED(IDC_IDKEY_INPORT, OnIdkeyInport)
	ON_BN_CLICKED(IDC_IDKEY_EXPORT, OnIdkeyExport)
	ON_BN_CLICKED(IDC_IDKEY_CREATE, OnIdkeyCreate)
	ON_NOTIFY(NM_DBLCLK, IDC_IDKEY_LIST, OnDblclkIdkeyList)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_EDIT_UPDATE, OnEditUpdate)
	ON_COMMAND(ID_EDIT_DELETE, OnIdkeyDel)
	ON_COMMAND(ID_EDIT_COPY, OnIdkeyCopy)
	ON_COMMAND(ID_EDIT_CHECK, OnEditCheck)
	ON_UPDATE_COMMAND_UI(IDC_IDKEY_UP, OnUpdateEditEntry)
	ON_UPDATE_COMMAND_UI(IDC_IDKEY_DOWN, OnUpdateEditEntry)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UPDATE, OnUpdateEditEntry)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditEntry)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditEntry)
	ON_UPDATE_COMMAND_UI(IDC_IDKEY_EXPORT, OnUpdateEditEntry)
END_MESSAGE_MAP()

void CIdkeySelDLg::InitList()
{
	int n;
	CString str;
	CIdKey *pKey;

	m_List.DeleteAllItems();
	for ( n = 0 ; n < m_Data.GetSize() ; n++ ) {
		if ( (pKey = m_pIdKeyTab->GetUid(m_Data[n])) == NULL )
			continue;
		switch(pKey->m_Type) {
		case IDKEY_NONE:  str = ""; break;
		case IDKEY_RSA1:  str = "RSA1"; break;
		case IDKEY_RSA2:  str = "RSA2"; break;
		case IDKEY_DSA2:  str = "DSA2"; break;
		case IDKEY_ECDSA: str = "ECDSA"; break;
		}
		m_List.InsertItem(LVIF_TEXT | LVIF_PARAM, n, str, 0, 0, 0, n);
		m_List.SetItemText(n, 1, pKey->m_Name);
		m_List.SetLVCheck(n, pKey->m_Flag);
	}
	m_List.SetItemState(m_EntryNum, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
}
void CIdkeySelDLg::CopyToClipBorad(LPCSTR str)
{
	LPSTR pData;
	HGLOBAL hClipData;
	int size = (int)strlen(str) + 1;

	if ( (hClipData = GlobalAlloc(GMEM_MOVEABLE, size)) == NULL )
		return;

	if ( (pData = (char *)GlobalLock(hClipData)) == NULL ) {
		GlobalFree(hClipData);
		return;
	}

	strcpy(pData, str);

	GlobalUnlock(hClipData);
	
	if ( !OpenClipboard() ) {
		GlobalFree(hClipData);
		return;
	}

	if ( !EmptyClipboard() ) {
		GlobalFree(hClipData);
		CloseClipboard();
		return;
	}

	SetClipboardData(CF_TEXT, hClipData);

	CloseClipboard();
}
UINT KeyGenThread(LPVOID pParam)
{
	CIdkeySelDLg *pWnd = (CIdkeySelDLg *)pParam;
	pWnd->ProcKeyGenThead();
	pWnd->m_KeyGenFlag = 2;
	pWnd->m_pKeyGenEvent->SetEvent();
	return 0;
}
void CIdkeySelDLg::StartKeyGenThead()
{
	if ( m_KeyGenFlag != 0 )
		return;
	m_KeyGenFlag = 1;
	m_pKeyGenEvent->ResetEvent();
	AfxBeginThread(KeyGenThread, this, THREAD_PRIORITY_LOWEST);
	m_GenIdKeyTimer = (UINT)SetTimer(1024, 200, NULL);
}
void CIdkeySelDLg::ProcKeyGenThead()
{
	m_GenIdKeyStat = m_GenIdKey.Generate(m_GenIdKeyType, m_GenIdKeyBits);
}
void CIdkeySelDLg::EndofKeyGenThead()
{
	if ( m_KeyGenFlag == 0 )
		return;
	m_KeyGenFlag = FALSE;
	WaitForSingleObject(m_pKeyGenEvent->m_hObject, INFINITE);
	m_KeyGenFlag = 0;
	OnKeyGenEndof();
}

/////////////////////////////////////////////////////////////////////////////
// CIdkeySelDLg ���b�Z�[�W �n���h��

static const LV_COLUMN InitListTab[2] = {
		{ LVCF_TEXT | LVCF_WIDTH, 0,  80, "Type", 0, 0 }, 
		{ LVCF_TEXT | LVCF_WIDTH, 0,  160, "Name",   0, 0 }, 
	};

BOOL CIdkeySelDLg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ASSERT(m_pIdKeyTab);
	ASSERT(m_pParamTab);

	int n, i, a;
	CIdKey *pKey;

	m_Data.RemoveAll();
	for ( n = 0 ; n < m_pIdKeyTab->GetSize() ; n++ ) {
		m_Data.Add(m_pIdKeyTab->GetAt(n).m_Uid);
		m_pIdKeyTab->GetAt(n).m_Flag = FALSE;
	}

	m_pParamTab->m_IdKeyList.SetString(m_OldIdKeyList);
	for ( n = (int)m_pParamTab->m_IdKeyList.GetSize() - 1 ; n >= 0 ; n-- ) {
		a = m_pParamTab->m_IdKeyList.GetVal(n);
		if ( (pKey = m_pIdKeyTab->GetUid(a)) == NULL )
			continue;
		for ( i = 0 ; i < m_Data.GetSize() ; i++ ) {
			if ( a == m_Data[i] ) {
				m_Data.RemoveAt(i);
				m_Data.InsertAt(0, a);
				pKey->m_Flag = TRUE;
				break;
			}
		}
	}

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_List.InitColumn("IdkeySelDLg", InitListTab, 2);
	m_List.SetPopUpMenu(IDR_POPUPMENU, 2);
	InitList();

	m_KeyGenProg.EnableWindow(FALSE);

	return TRUE;
}
void CIdkeySelDLg::OnOK() 
{
	if ( m_KeyGenFlag != 0 ) {
		MessageBox("�F�؃L�[���쐬���ł�");
		return;
	}
	m_pParamTab->m_IdKeyList.RemoveAll();
	for ( int n = 0 ; n < m_Data.GetSize() ; n++ ) {
		if ( m_List.GetLVCheck(n) )
			m_pParamTab->m_IdKeyList.AddVal(m_Data[n]);
	}
	m_List.SaveColumn("IdkeySelDLg");

	CString str;
	m_pParamTab->m_IdKeyList.SetString(str);
	if ( str.Compare(m_OldIdKeyList) != 0 )
		CDialog::OnOK();
	else
		CDialog::OnCancel();
}

void CIdkeySelDLg::OnClose()
{
	if ( m_KeyGenFlag != 0 ) {
		MessageBox("�F�؃L�[���쐬���ł�");
		return;
	}
	CDialog::OnClose();
}
void CIdkeySelDLg::OnTimer(UINT_PTR nIDEvent) 
{
	switch(nIDEvent) {
	case 1024:
		if ( m_KeyGenFlag == 2 ) {
			KillTimer(m_GenIdKeyTimer);
			EndofKeyGenThead();
		} else {
			m_KeyGenProg.SetPos(m_GenIdKeyCount++);
			if ( m_GenIdKeyCount > m_GenIdKeyMax )
				m_GenIdKeyCount = 0;
		}
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CIdkeySelDLg::OnIdkeyUp() 
{
	int n1, n2, d;
	if ( (m_EntryNum = m_List.GetSelectionMark()) <= 0 )
		return;
	n1 = (int)m_List.GetItemData(m_EntryNum - 1);
	n2 = (int)m_List.GetItemData(m_EntryNum);
	d = m_Data[n1];
	m_Data[n1] = m_Data[n2];
	m_Data[n2] = d;
	m_EntryNum -= 1;
	InitList();
}
void CIdkeySelDLg::OnIdkeyDown() 
{
	int n1, n2, d;
	if ( (m_EntryNum = m_List.GetSelectionMark()) < 0 )
		return;
	else if ( m_EntryNum >= (m_List.GetItemCount() - 1) )
		return;
	n1 = (int)m_List.GetItemData(m_EntryNum + 1);
	n2 = (int)m_List.GetItemData(m_EntryNum);
	d = m_Data[n1];
	m_Data[n1] = m_Data[n2];
	m_Data[n2] = d;
	m_EntryNum += 1;
	InitList();
}
void CIdkeySelDLg::OnIdkeyDel() 
{
	if ( (m_EntryNum = m_List.GetSelectionMark()) < 0 )
		return;
	if ( MessageBox("���Ɏg�p���Ă���G���g���[�����邩������܂���\n�ق�Ƃ��ɍ폜���Ă悢�ł����H", "Warning", MB_ICONWARNING | MB_OKCANCEL) != IDOK )
		return;
	int n = (int)m_List.GetItemData(m_EntryNum);
	m_pIdKeyTab->RemoveUid(m_Data[n]);
	m_Data.RemoveAt(n);
	InitList();
}
void CIdkeySelDLg::OnIdkeyCopy() 
{
	if ( (m_EntryNum = m_List.GetSelectionMark()) < 0 )
		return;
	int n = (int)m_List.GetItemData(m_EntryNum);
	CIdKey *pKey = m_pIdKeyTab->GetUid(m_Data[n]);
	if ( pKey == NULL )
		return;
	CString str;
	pKey->WritePublicKey(str);
	CopyToClipBorad(str);
}
void CIdkeySelDLg::OnIdkeyInport() 
{
	CIdKey key;
	CIdKeyFileDlg dlg;

	dlg.m_OpenMode = 1;
	dlg.m_Title = "SSH���t�@�C���̓ǂݍ���";
	dlg.m_Message = "�쐬���ɐݒ肵���p�X�t���[�Y����͂��Ă��������B";

	if ( dlg.DoModal() != IDOK )
		return;

	if ( dlg.m_PassName.IsEmpty() || dlg.m_IdkeyFile.IsEmpty() ) {
		MessageBox("�p�X�t���[�Y�ƌ��t�@�C�����w�肵�Ă�������");
		return;
	}

	if ( !key.LoadPrivateKey(dlg.m_IdkeyFile, dlg.m_PassName) ) {
		MessageBox("���t�@�C����ǂݍ��߂܂���ł���");
		return;
	}

	key.m_Pass = dlg.m_PassName;
	key.m_Flag = TRUE;

	if ( !m_pIdKeyTab->AddEntry(key) ) {
		MessageBox("�������t�@�C�������łɓo�^�ς݂ł�");
		return;
	}
	m_Data.InsertAt(0, key.m_Uid);

	m_EntryNum = 0;
	InitList();
}
void CIdkeySelDLg::OnIdkeyExport() 
{
	if ( (m_EntryNum = m_List.GetSelectionMark()) < 0 )
		return;

	int n = (int)m_List.GetItemData(m_EntryNum);
	CIdKey *pKey = m_pIdKeyTab->GetUid(m_Data[n]);
	if ( pKey == NULL )
		return;

	CIdKeyFileDlg dlg;
	dlg.m_OpenMode = 1;
	dlg.m_Title = "SSH���t�@�C���̕ۑ�";
	dlg.m_Message = "�쐬���ɐݒ肵���p�X�t���[�Y����͂��Ă��������B"\
					"�p�X�t���[�Y����v���Ȃ��ƕۑ��ł��܂���";

	if ( dlg.DoModal() != IDOK )
		return;

	if ( dlg.m_PassName.IsEmpty() || dlg.m_IdkeyFile.IsEmpty() ) {
		MessageBox("�p�X�t���[�Y�ƌ��t�@�C�����w�肵�Ă�������");
		return;
	}

	if ( dlg.m_PassName.Compare(pKey->m_Pass) != 0 ) {
		MessageBox("�쐬���Ɏw�肵���p�X�t���[�Y�ƈ�v���܂���");
		return;
	}

	if ( !pKey->SavePrivateKey(pKey->m_Type, dlg.m_IdkeyFile, dlg.m_PassName) )
		MessageBox("���t�@�C���ɕۑ��ł��܂���ł���");
}
void CIdkeySelDLg::OnIdkeyCreate() 
{
	CWnd *pWnd;
	CIdKeyFileDlg dlg;
	CString tmp;

	UpdateData(TRUE);

	dlg.m_OpenMode = 3;
	dlg.m_Title = "���̍쐬";
	dlg.m_Message = "�p�X�t���[�Y�́A���ɏd�v�ł��B�쐬���ɐݒ肷��"\
					"�p�X�t���[�Y�́A�t�@�C���ɕۑ�����ꍇ��T�[�o�["\
					"�ڑ��Ŏg�p����ꍇ�ɂ����͂��K�v�ɂȂ�܂��B";

	if ( dlg.DoModal() != IDOK )
		return;

	if ( dlg.m_PassName.IsEmpty() ) {
		MessageBox("�p�X�t���[�Y���w�肵�Ă�������");
		return;
	}

	m_GenIdKey.Close();
	m_GenIdKey.m_Pass = dlg.m_PassName;
	m_GenIdKey.m_Name = m_Name;
	m_GenIdKey.m_Flag = TRUE;
	m_GenIdKeyType = IDKEY_DSA2;
	m_GenIdKeyBits = atoi(m_Bits);
	m_GenIdKeyStat = FALSE;

	if ( m_Type.Compare("RSA1") == 0 )
		m_GenIdKeyType = IDKEY_RSA1;
	else if ( m_Type.Compare("RSA2") == 0 )
		m_GenIdKeyType = IDKEY_RSA2;
	else if ( m_Type.Compare("ECDSA") == 0 )
		m_GenIdKeyType = IDKEY_ECDSA;

	if ( (pWnd = GetDlgItem(IDC_IDKEY_TYPE)) != NULL )
		pWnd->EnableWindow(FALSE);
	if ( (pWnd = GetDlgItem(IDC_IDKEY_BITS)) != NULL )
		pWnd->EnableWindow(FALSE);
	if ( (pWnd = GetDlgItem(IDC_IDKEY_NAME)) != NULL )
		pWnd->EnableWindow(FALSE);
	if ( (pWnd = GetDlgItem(IDC_IDKEY_CREATE)) != NULL )
		pWnd->EnableWindow(FALSE);

	m_GenIdKeyMax = (int)(pow(1.5, (double)m_GenIdKeyBits / 256.0) * 2.56);
	m_GenIdKeyCount = 0;

	m_KeyGenProg.EnableWindow(TRUE);
	m_KeyGenProg.SetRange(0, m_GenIdKeyMax);
	m_KeyGenProg.SetPos(m_GenIdKeyCount);

	StartKeyGenThead();
}
void CIdkeySelDLg::OnKeyGenEndof()
{
	CWnd *pWnd;

	if ( (pWnd = GetDlgItem(IDC_IDKEY_TYPE)) != NULL )
		pWnd->EnableWindow(TRUE);
	if ( (pWnd = GetDlgItem(IDC_IDKEY_BITS)) != NULL )
		pWnd->EnableWindow(TRUE);
	if ( (pWnd = GetDlgItem(IDC_IDKEY_NAME)) != NULL )
		pWnd->EnableWindow(TRUE);
	if ( (pWnd = GetDlgItem(IDC_IDKEY_CREATE)) != NULL )
		pWnd->EnableWindow(TRUE);

	m_KeyGenProg.SetPos(0);
	m_KeyGenProg.EnableWindow(FALSE);

	if ( !m_GenIdKeyStat || !m_pIdKeyTab->AddEntry(m_GenIdKey) ) {
		MessageBox("���t�@�C�����쐬�ł��܂���ł���");
		return;
	}
	m_Data.InsertAt(0, m_GenIdKey.m_Uid);

	m_EntryNum = 0;
	InitList();
}
void CIdkeySelDLg::OnEditUpdate() 
{
	if ( (m_EntryNum = m_List.GetSelectionMark()) < 0 )
		return;
	int n = (int)m_List.GetItemData(m_EntryNum);
	CIdKey *pKey = m_pIdKeyTab->GetUid(m_Data[n]);
	if ( pKey == NULL )
		return;
	CEditDlg dlg;
	dlg.m_Title = "�F�؃L�[�̖��O���ύX�ł��܂�";
	dlg.m_Edit  = pKey->m_Name;
	if ( dlg.DoModal() != IDOK )
		return;
	pKey->m_Name = dlg.m_Edit;
	m_pIdKeyTab->UpdateUid(pKey->m_Uid);
	InitList();
}
void CIdkeySelDLg::OnEditCheck()
{
	int n, i;
	CIdKeyTab tab;
	CString nstr, ostr;
	CWordArray apend, remove, update;

	for ( n = 0 ; n < tab.GetSize() ; n++ ) {
		for ( i = 0 ; i < m_pIdKeyTab->GetSize() ; i++ ) {
			if ( tab.GetAt(n).m_Uid == m_pIdKeyTab->GetAt(i).m_Uid )
				break;
		}
		if ( i < m_pIdKeyTab->GetSize() ) {
			tab.GetAt(n).SetString(nstr);
			m_pIdKeyTab->GetAt(i).SetString(ostr);
			if ( nstr.Compare(ostr) != 0 ) {
				update.Add(i);
				update.Add(n);
			}
		} else
			apend.Add(n);
	}
	for ( i = 0 ; i < m_pIdKeyTab->GetSize() ; i++ ) {
		for ( n = 0 ; n < tab.GetSize() ; n++ ) {
			if ( tab.GetAt(n).m_Uid == m_pIdKeyTab->GetAt(i).m_Uid )
				break;
		}
		if ( n >= tab.GetSize() )
			remove.Add(i);
	}

	for ( n = 0 ; n < update.GetSize() ; n += 2 )
		m_pIdKeyTab->m_Data[update[n]] = tab.GetAt(update[n + 1]);

	for ( n = 0 ; n < apend.GetSize() ; n++ ) {
		m_pIdKeyTab->m_Data.Add(tab.GetAt(apend[n]));
		m_Data.Add(tab.GetAt(apend[n]).m_Uid);
	}

	for ( n = 0 ; n < remove.GetSize() ; n++ ) {
		for ( i = 0 ; i < m_Data.GetSize() ; i++ ) {
			if ( m_Data[i] == m_pIdKeyTab->GetAt(remove[n]).m_Uid ) {
				m_Data.RemoveAt(i);
				break;
			}
		}
		m_pIdKeyTab->m_Data.RemoveAt(remove[n]);
	}

	InitList();
}
void CIdkeySelDLg::OnDblclkIdkeyList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	OnEditUpdate();
}
void CIdkeySelDLg::OnUpdateEditEntry(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_List.GetSelectMarkData() >= 0);
}
