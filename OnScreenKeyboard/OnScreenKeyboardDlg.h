#pragma once

#include "key.h"

class COnScreenKeyboardDlg : public CDialog
{
public:
	COnScreenKeyboardDlg(CWnd* pParent = NULL);
	enum {IDD = IDD_ONSCREENKEYBOARD_DIALOG};
	keyboard* kb;
	//void setup_kblayout();
	//void show_keyboard();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	
	afx_msg void	OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void	OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void	OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void	OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void	OnBnClickedSendX();
	afx_msg LRESULT OnMessageShiftChanged(WPARAM, LPARAM);	
	afx_msg LRESULT OnMessageCapsChanged(WPARAM, LPARAM);
	afx_msg LRESULT OnMessageHideApp(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()	

	HWND m_hForegroundWnd;
	HICON m_hIcon;

	class CAboutDlg : public CDialog
	{
	public:
		CAboutDlg();
		enum {IDD = IDD_ABOUTBOX};

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);

		DECLARE_MESSAGE_MAP()
	};
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
};
