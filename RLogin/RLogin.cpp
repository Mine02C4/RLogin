// RLogin.cpp : �A�v���P�[�V�����̃N���X������`���܂��B
//

#include "stdafx.h"
#include "RLogin.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "RLoginDoc.h"
#include "RLoginView.h"
#include "ExtSocket.h"

#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CCommandLineInfoEx

CCommandLineInfoEx::CCommandLineInfoEx()
{
	m_PasStat = 0;
	m_Proto = (-1);
	m_Addr.Empty();
	m_Port.Empty();
	m_User.Empty();
	m_Pass.Empty();
	m_Term.Empty();
	m_InUse = FALSE;
}
void CCommandLineInfoEx::ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast)
{
	switch(m_PasStat) {
	case 0:
		if ( !bFlag )
			break;
		if ( _tcsicmp("ip", pszParam) == 0 )
			m_PasStat = 1;
		else if ( _tcsicmp("port", pszParam) == 0 )
			m_PasStat = 2;
		else if ( _tcsicmp("user", pszParam) == 0 )
			m_PasStat = 3;
		else if ( _tcsicmp("pass", pszParam) == 0 )
			m_PasStat = 4;
		else if ( _tcsicmp("term", pszParam) == 0 )
			m_PasStat = 5;
		else if ( _tcsicmp("direct", pszParam) == 0 )
			m_Proto = PROTO_DIRECT;
		else if ( _tcsicmp("login", pszParam) == 0 ) {
			m_Proto = PROTO_LOGIN;
			m_Port  = "login";
		} else if ( _tcsicmp("telnet", pszParam) == 0 ) {
			m_Proto = PROTO_TELNET;
			m_Port  = "telnet";
		} else if ( _tcsicmp("ssh", pszParam) == 0 ) {
			m_Proto = PROTO_SSH;
			m_Port  = "ssh";
		} else if ( _tcsicmp("inuse", pszParam) == 0 )
			m_InUse = TRUE;
		else
			break;
		ParseLast(bLast);
		return;
	case 1:
		m_PasStat = 0;
		if ( bFlag )
			break;
		m_Addr = pszParam;
		ParseLast(bLast);
		return;
	case 2:
		m_PasStat = 0;
		if ( bFlag )
			break;
		m_Port = pszParam;
		ParseLast(bLast);
		return;
	case 3:
		m_PasStat = 0;
		if ( bFlag )
			break;
		m_User = pszParam;
		ParseLast(bLast);
		return;
	case 4:
		m_PasStat = 0;
		if ( bFlag )
			break;
		m_Pass = pszParam;
		ParseLast(bLast);
		return;
	case 5:
		m_PasStat = 0;
		if ( bFlag )
			break;
		m_Term = pszParam;
		ParseLast(bLast);
		return;
	}
	CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
}
void CCommandLineInfoEx::GetString(CString &str)
{
	CStringArrayExt ary;

	ary.AddVal(m_Proto);
	ary.Add(m_Addr);
	ary.Add(m_Port);
	ary.Add(m_User);
	ary.Add(m_Pass);
	ary.Add(m_Term);
	ary.AddVal(m_InUse);
	ary.Add(m_strFileName);
	ary.AddVal(m_nShellCommand);

	ary.SetString(str);
}
void CCommandLineInfoEx::SetString(LPCSTR str)
{
	CStringArrayExt ary;

	ary.GetString(str);

	if ( ary.GetSize() <= 8 )
		return;

	m_Proto = ary.GetVal(0);
	m_Addr  = ary.GetAt(1);
	m_Port  = ary.GetAt(2);
	m_User  = ary.GetAt(3);
	m_Pass  = ary.GetAt(4);
	m_Term  = ary.GetAt(5);
	m_InUse = ary.GetVal(6);
	m_strFileName = ary.GetAt(7);
	switch(ary.GetVal(8)) {
	case FileNew:  m_nShellCommand = FileNew;  break;
	case FileOpen: m_nShellCommand = FileOpen; break;
	}
}

//////////////////////////////////////////////////////////////////////
// CRLoginApp

BEGIN_MESSAGE_MAP(CRLoginApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CRLoginApp::OnAppAbout)
	// �W���̃t�@�C����{�h�L�������g �R�}���h
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CRLoginApp �R���X�g���N�V����

CRLoginApp::CRLoginApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
	m_NextSock = 0;
}


// �B��� CRLoginApp �I�u�W�F�N�g�ł��B

CRLoginApp theApp;

// CRLoginApp ������

BOOL CRLoginApp::InitInstance()
{
	//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// �A�v���P�[�V���� �}�j�t�F�X�g�� visual �X�^�C����L���ɂ��邽�߂ɁA
	// ComCtl32.dll Version 6 �ȍ~�̎g�p���w�肷��ꍇ�́A
	// Windows XP �� InitCommonControlsEx() ���K�v�ł��B�����Ȃ���΁A�E�B���h�E�쐬�͂��ׂĎ��s���܂��B
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	// �A�v���P�[�V�����Ŏg�p���邷�ׂẴR���� �R���g���[�� �N���X���܂߂�ɂ́A
	// �����ݒ肵�܂��B
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

#ifdef	WINSOCK11
	if ( !AfxSocketInit() ) {
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
#else
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD( 2, 2 );
	if ( WSAStartup( wVersionRequested, &wsaData ) != 0 ) {
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
#endif

	// �W��������
	// �����̋@�\���g�킸�ɍŏI�I�Ȏ��s�\�t�@�C����
	// �T�C�Y���k���������ꍇ�́A�ȉ�����s�v�ȏ�����
	// ���[�`�����폜���Ă��������B
	// �ݒ肪�i�[����Ă��郌�W�X�g�� �L�[��ύX���܂��B
	// TODO: ��Ж��܂��͑g�D���Ȃǂ̓K�؂ȕ������
	// ���̕������ύX���Ă��������B
	SetRegistryKey(_T("Culti"));
	LoadStdProfileSettings(4);  // �W���� INI �t�@�C���̃I�v�V���������[�h���܂� (MRU ���܂�)

	// �A�v���P�[�V�����p�̃h�L�������g �e���v���[�g��o�^���܂��B�h�L�������g �e���v���[�g
	//  �̓h�L�������g�A�t���[�� �E�B���h�E�ƃr���[���������邽�߂ɋ@�\���܂��B
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_RLOGINTYPE,
		RUNTIME_CLASS(CRLoginDoc),
		RUNTIME_CLASS(CChildFrame), // �J�X�^�� MDI �q�t���[��
		RUNTIME_CLASS(CRLoginView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// ���C�� MDI �t���[�� �E�B���h�E���쐬���܂��B
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// �ڔ��������݂���ꍇ�ɂ̂� DragAcceptFiles ���Ăяo���܂��B
	//  MDI �A�v���P�[�V�����ł́A���̌Ăяo���́Am_pMainWnd ��ݒ肵������ɔ������Ȃ���΂Ȃ�܂���B
	// �h���b�O/�h���b�v �I�[�v���������܂��B
	m_pMainWnd->DragAcceptFiles(FALSE);

	// DDE Execute open ���g�p�\�ɂ��܂��B

	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// DDE�Afile open �ȂǕW���̃V�F�� �R�}���h�̃R�}���h ���C������͂��܂��B
	CCommandLineInfoEx cmdInfo;
	ParseCommandLine(cmdInfo);
	m_pCmdInfo = &cmdInfo;

	if ( cmdInfo.m_InUse && InUseCheck() )
		return FALSE;

	::SetWindowLongPtr(m_pMainWnd->GetSafeHwnd(), GWLP_USERDATA, 0x524c4f47);

	// �R�}���h ���C���Ŏw�肳�ꂽ�f�B�X�p�b�` �R�}���h�ł��B�A�v���P�[�V������
	// /RegServer�A/Register�A/Unregserver �܂��� /Unregister �ŋN�����ꂽ�ꍇ�AFalse ��Ԃ��܂��B
	// if (!ProcessShellCommand(cmdInfo))
	//	return FALSE;

	char tmp[_MAX_DIR];
	if ( _getcwd(tmp, _MAX_DIR) != NULL )
		m_BaseDir = tmp;
	else {
		int n;
		m_BaseDir = _pgmptr;
		if ( (n = m_BaseDir.ReverseFind('\\')) >= 0 )
			m_BaseDir = m_BaseDir.Left(n);
	}

	// ���C�� �E�B���h�E�����������ꂽ�̂ŁA�\���ƍX�V���s���܂��B
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	switch(cmdInfo.m_nShellCommand) {
	case CCommandLineInfo::FileNew:
		OnFileNew();
		break;
	case CCommandLineInfo::FileOpen:
		if ( OpenDocumentFile(cmdInfo.m_strFileName) == NULL )
			OnFileNew();
		break;
	}
	m_pCmdInfo = NULL;

	return TRUE;
}

void CRLoginApp::OpenProcsCmd(CCommandLineInfoEx *pCmdInfo)
{
	m_pCmdInfo = pCmdInfo;
	switch(pCmdInfo->m_nShellCommand) {
	case CCommandLineInfo::FileNew:
		OnFileNew();
		break;
	case CCommandLineInfo::FileOpen:
		if ( OpenDocumentFile(pCmdInfo->m_strFileName) == NULL )
			OnFileNew();
		break;
	}
	m_pCmdInfo = NULL;
}
BOOL CALLBACK RLoginEnumFunc(HWND hwnd, LPARAM lParam)
{
	CWnd wnd;
	CRLoginApp *pApp = (CRLoginApp *)lParam;
	TCHAR title[1024];
	CString cmdLine;

	::GetWindowText(hwnd, title, 1024);

	if ( _tcsncmp(title, "RLogin", 6) == 0 && ::GetWindowLongPtr(hwnd, GWLP_USERDATA) == 0x524c4f47 ) {
		pApp->m_pCmdInfo->m_InUse = FALSE;
		pApp->m_pCmdInfo->GetString(cmdLine);
		COPYDATASTRUCT copyData;
		copyData.dwData = 0x524c4f31;
		copyData.cbData = cmdLine.GetAllocLength();
		copyData.lpData = cmdLine.GetBuffer();
		::SendMessage(hwnd, WM_COPYDATA, (WPARAM)(pApp->m_pMainWnd->GetSafeHwnd()), (LPARAM)&copyData);
		return FALSE;
	}

	return TRUE;
}
BOOL CRLoginApp::InUseCheck()
{
	::EnumWindows(RLoginEnumFunc, (LPARAM)this);
	return (m_pCmdInfo == NULL || m_pCmdInfo->m_InUse ? FALSE : TRUE);
}
void CRLoginApp::SetSocketIdle(class CExtSocket *pSock)
{
	for ( int n = 0 ; n < m_SocketIdle.GetSize() ; n++ ) {
		if ( m_SocketIdle[n] == (void *)pSock )
			return;
	}
	m_SocketIdle.Add((void *)pSock);
}
void CRLoginApp::DelSocketIdle(class CExtSocket *pSock)
{
	for ( int n = 0 ; n < m_SocketIdle.GetSize() ; n++ ) {
		if ( m_SocketIdle[n] == (void *)pSock ) {
			m_SocketIdle.RemoveAt(n);
			break;
		}
	}
}
void CRLoginApp::GetProfileData(LPCTSTR lpszSection, LPCTSTR lpszEntry, void *lpBuf, int nBufLen, void *lpDef)
{
	LPBYTE pData;
	UINT len;

	if ( GetProfileBinary(lpszSection, lpszEntry, &pData, &len) ) {
		if ( len == (UINT)nBufLen )
			memcpy(lpBuf, pData, nBufLen);
		else
			memcpy(lpBuf, lpDef, nBufLen);
		delete pData;
	} else if ( lpDef != NULL )
		memcpy(lpBuf, lpDef, nBufLen);
}
void CRLoginApp::GetProfileBuffer(LPCTSTR lpszSection, LPCTSTR lpszEntry, CBuffer &Buf)
{
	LPBYTE pData;
	UINT len;

	Buf.Clear();
	if ( GetProfileBinary(lpszSection, lpszEntry, &pData, &len) ) {
		Buf.Apend(pData, len);
		delete pData;
	}
}
void CRLoginApp::GetProfileArray(LPCTSTR lpszSection, CStringArrayExt &array)
{
	int n, mx;
	CString entry;
	
	array.RemoveAll();
	mx = GetProfileInt(lpszSection, "ListMax", 0);
	for ( n = 0 ; n < mx ; n++ ) {
		entry.Format("List%02d", n);
		array.Add(GetProfileString(lpszSection, entry, ""));
	}
}
void CRLoginApp::WriteProfileArray(LPCTSTR lpszSection, CStringArrayExt &array)
{
	int n;
	CString entry;

	for ( n = 0 ; n < array.GetSize() ; n++ ) {
		entry.Format("List%02d", n);
		WriteProfileString(lpszSection, entry, array.GetAt(n));
	}
	WriteProfileInt(lpszSection, "ListMax", n);
}
int CRLoginApp::GetProfileSeqNum(LPCTSTR lpszSection, LPCTSTR lpszEntry)
{
	CMutexLock Mutex(lpszEntry);
	int num = GetProfileInt(lpszSection, lpszEntry, 0) ;
	WriteProfileInt(lpszSection, lpszEntry, num + 1);
	return num;
}
void CRLoginApp::GetProfileKeys(LPCTSTR lpszSection, CStringArrayExt &array)
{
	array.RemoveAll();
	HKEY hAppKey;
	if ( (hAppKey = GetAppRegistryKey()) == NULL )
		return;
	HKEY hSecKey;
	if ( RegOpenKeyEx(hAppKey, lpszSection, 0, KEY_READ, &hSecKey) == ERROR_SUCCESS && hSecKey != NULL ) {
		TCHAR name[1024];
		DWORD len = 1024;
		for ( int n = 0 ; RegEnumValue(hSecKey, n, name, &len, NULL, NULL, NULL, NULL) != ERROR_NO_MORE_ITEMS ; n++, len = 1024 )
			array.Add(name);
		RegCloseKey(hSecKey);
	}
	RegCloseKey(hAppKey);
}
void CRLoginApp::DelProfileEntry(LPCTSTR lpszSection, LPCTSTR lpszEntry)
{
	HKEY hSecKey;
	if ( (hSecKey = GetSectionKey(lpszSection)) == NULL )
		return;
	RegDeleteValue(hSecKey, lpszEntry);
	RegCloseKey(hSecKey);
}



// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �_�C�A���O�����s���邽�߂̃A�v���P�[�V���� �R�}���h
void CRLoginApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CRLoginApp ���b�Z�[�W �n���h��

BOOL CRLoginApp::OnIdle(LONG lCount) 
{
	if ( CWinApp::OnIdle(lCount) )
		return TRUE;

	if ( m_NextSock >= m_SocketIdle.GetSize() )
		m_NextSock = 0;

	for ( int n = 0 ; n < m_SocketIdle.GetSize() ; n++ ) {
		CExtSocket *pSock = (CExtSocket *)(m_SocketIdle[m_NextSock]);
		if ( ++m_NextSock >= m_SocketIdle.GetSize() )
			m_NextSock = 0;
		if ( pSock->OnIdle() )
			return TRUE;
	}

	return FALSE;
}

int CRLoginApp::ExitInstance() 
{
	CRYPTO_cleanup_all_ex_data();
#ifndef	WINSOCK11
	WSACleanup();
#endif

#ifdef	_DEBUGXXX
	CBuffer tmp;
	tmp.Report();
#endif
	return CWinApp::ExitInstance();
}

BOOL CRLoginApp::SaveAllModified() 
{
	CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();
	if ( pMain != NULL && !pMain->SaveModified() )
		return FALSE;

	return CWinApp::SaveAllModified();
}
void CRLoginApp::SSL_Init()
{
	static BOOL bLoadAlgo = FALSE;

	if ( bLoadAlgo )
		return;
	bLoadAlgo = TRUE;

	SSLeay_add_all_algorithms();
}