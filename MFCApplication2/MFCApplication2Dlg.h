﻿
// MFCApplication2Dlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CMFCApplication2Dlg
class CMFCApplication2Dlg : public CDialogEx
{
// Создание
public:
	CMFCApplication2Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdd();
	afx_msg void OnEnChangeFile();
	afx_msg void OnEnChangeName();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedRec();
	afx_msg void OnBnClickedSenddir();
	afx_msg void OnBnClickedRecdir();
	afx_msg void OnBnClickedSendneither();
	afx_msg void OnBnClickedRecneither();
	afx_msg void OnBnClickedSendbuf();
	afx_msg void OnBnClickedRecbuf();

	afx_msg void OnBnClickedBtunk();
};
