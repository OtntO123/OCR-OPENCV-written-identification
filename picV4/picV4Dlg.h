
// picV4Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\imgproc\types_c.h>
#include <opencv2\objdetect\objdetect_c.h>
#include <string>
#include <io.h>
#include <vector>
#include <iostream>
#include <windows.h>
#include <fcntl.h>
#include <sstream>
#include <direct.h>
#include <stdlib.h>
#include <fstream>
#include <atlimage.h> 
#include "ximage.h" 
#include "ximatif.h"
#include <math.h>

// CpicV4Dlg dialog
class CpicV4Dlg : public CDialogEx
{
// Construction
public:
	CpicV4Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PICV4_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoadPicButton();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButtonTesspath();
	afx_msg void OnBnClickedButton_Extmtrpath();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButton5Backtotrain();
	afx_msg void OnBnClickedButtonMakebox();
	afx_msg void OnBnClickedButtonRetraining();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonLoadbox();
	afx_msg void OnBnClickedButtonListinfo();
	afx_msg void OnBnClickedButtonExceladname();
	afx_msg void OnBnClickedButtonCopytifs();
	bool ShowEdit(int Sort);
	int ShowMat(cv::Mat img, HWND hWndDisplay);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void equalizeHistFunction(cv::Mat Ori, cv::Mat& OUP);
	void MyCvtColor(cv::Mat& src);
	void sobelTIDU(cv::Mat src, cv::Mat& res);
	CProgressCtrl* pProg;
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
};
