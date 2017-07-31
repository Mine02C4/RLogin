#pragma once

/////////////////////////////////////////////////////////////////////////////
// CProtoPage �_�C�A���O

class CProtoPage : public CTreePropertyPage
{
	DECLARE_DYNCREATE(CProtoPage)

// �R���X�g���N�V����
public:
	CProtoPage();
	~CProtoPage();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PROTOPAGE };

public:
	UINT m_KeepAlive;
	BOOL m_Check[18];
	CStringArrayExt m_AlgoTab[12];
	CStringArrayExt m_IdKeyList;
	CStringArrayExt m_PortFwd;
	CString m_XDisplay;

public:
	void DoInit();

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();

public:
	virtual BOOL OnApply();
	virtual void OnReset();

// �C���v�������e�[�V����
protected:
	afx_msg void OnSshAlgo();
	afx_msg void OnSshIdkey();
	afx_msg void OnSshPfd();
	afx_msg void OnUpdateCheck(UINT nId);
	afx_msg void OnUpdateEdit();
	DECLARE_MESSAGE_MAP()
};
