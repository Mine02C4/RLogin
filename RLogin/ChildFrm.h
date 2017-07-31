// ChildFrm.h : CChildFrame �N���X�̃C���^�[�t�F�C�X
//

#pragma once

#include "TextRam.h"
#include "Data.h"

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// ����
protected:
	CSplitterWnd m_wndSplitter;
public:

// ����
public:

// �I�[�o�[���C�h
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ActivateFrame(int nCmdShow);

// ����
public:
	int m_Width, m_Height;
	int m_Cols, m_Lines;

	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnWindowClose();
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	DECLARE_MESSAGE_MAP()
};
