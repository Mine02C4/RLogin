#if !defined(AFX_PROTOPAGE_H__E5EE664E_A0AF_4FF7_ADDD_49EC824E1D55__INCLUDED_)
#define AFX_PROTOPAGE_H__E5EE664E_A0AF_4FF7_ADDD_49EC824E1D55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProtoPage.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CProtoPage �_�C�A���O

class CProtoPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CProtoPage)

// �R���X�g���N�V����
public:
	class COptDlg *m_pSheet;
	CParamTab ParamTabTemp;
	CProtoPage();
	~CProtoPage();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CProtoPage)
	enum { IDD = IDD_PROTOPAGE };
	UINT	m_DelayMsec;
	UINT	m_KeepAlive;
	//}}AFX_DATA
	BOOL m_Check[18];


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CProtoPage)
	public:
	virtual BOOL OnApply();
	virtual void OnReset();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CProtoPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSshAlgo();
	afx_msg void OnSshIdkey();
	afx_msg void OnSshPfd();
	//}}AFX_MSG
	afx_msg void OnUpdateCheck(UINT nId);
	afx_msg void OnUpdateEdit();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PROTOPAGE_H__E5EE664E_A0AF_4FF7_ADDD_49EC824E1D55__INCLUDED_)
