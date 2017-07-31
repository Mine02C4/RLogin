#if !defined(AFX_COLPARADLG_H__B7BC0C15_B28B_47B6_847C_98B453BC8506__INCLUDED_)
#define AFX_COLPARADLG_H__B7BC0C15_B28B_47B6_847C_98B453BC8506__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColParaDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CColParaDlg �_�C�A���O

class CColParaDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CColParaDlg)

// �R���X�g���N�V����
public:
	class COptDlg *m_pSheet;
	COLORREF m_ColTab[16];
	BOOL m_Attrb[24];
	CImageList m_ImageList[8];

	CColParaDlg();
	~CColParaDlg();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CColParaDlg)
	enum { IDD = IDD_COLORPARADLG };
	CSliderCtrl	m_TransSlider;
	int		m_ColSet;
	CString	m_BitMapFile;
	int		m_WakeUpSleep;
	//}}AFX_DATA
	CStatic	m_ColBox[18];
	int m_FontCol[2];

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CColParaDlg)
	public:
	virtual BOOL OnApply();
	virtual void OnReset();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CColParaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnReleasedcaptureTransparent(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelendokColset();
	afx_msg void OnBitMapFileSel();
	//}}AFX_MSG
	afx_msg void OnUpdateEdit();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_COLPARADLG_H__B7BC0C15_B28B_47B6_847C_98B453BC8506__INCLUDED_)
