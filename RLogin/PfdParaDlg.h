#if !defined(AFX_PFDDLG_H__0088D685_A5BA_46E4_BACC_95E3762F079C__INCLUDED_)
#define AFX_PFDDLG_H__0088D685_A5BA_46E4_BACC_95E3762F079C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PfdDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CPfdParaDlg �_�C�A���O

class CPfdParaDlg : public CDialog
{
// �R���X�g���N�V����
public:
	int m_EntryNum;
	class CParamTab *m_pData;
	class CServerEntry *m_pEntry;
	CPfdParaDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CPfdParaDlg)
	enum { IDD = IDD_PFDPARADLG };
	CString	m_ListenHost;
	CString	m_ListenPort;
	CString	m_ConnectHost;
	CString	m_ConnectPort;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CPfdParaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CPfdParaDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PFDDLG_H__0088D685_A5BA_46E4_BACC_95E3762F079C__INCLUDED_)
