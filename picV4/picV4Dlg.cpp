#include "stdafx.h"
#include "picV4.h"
#include "picV4Dlg.h"
#include "afxdialogex.h"
using namespace cv;
using namespace std;

static char CtargetPath[MAX_PATH] = "C:\\Users\\OtntO\\Desktop\\training samples\\teset2";
static char *Ctar = CtargetPath;
static char ExtMtrPath[MAX_PATH] = "";
static char *CExt = ExtMtrPath;
static char OriMtrPath[MAX_PATH] = "";
static char *COri = OriMtrPath;
static char TesOcrPath[MAX_PATH] = "";
static char *CTes = TesOcrPath;
static string ExTifFolder="\\TifFolder";
static vector<string> files;
static vector<string> BackToTrain;
static vector<string> TempFile;
static vector<string> language;
static vector<string> commandcommand;
static int size;
static bool havePath = 0;
static bool havefolders = 0;
static bool havePics = 0;
static bool haveInfos = 0;
static bool haveCTesPath = 0;
static bool haveCExtPath = 0;
static bool haveCOriPath = 0;
static string slash = "/";
static int list[1][2];
int ProgPos = 0;
int ProgRange = 100;
float Pic2Data[25][2][2] = { { { 443, 624 }, { 887, 423 } }, { { 443, 823 }, { 887, 625 } }, { { 443, 823 }, { 885, 1001 } }, { { 893, 425 }, { 2293, 1181 } }, { { 2631, 559 }, { 3021, 497 } }, { { 387, 1413 }, { 563, 1495 } }, { { 563, 1417 }, { 739, 1495 } }, { { 739, 1417 }, { 915, 1495 } }, { { 915, 1417 }, { 1123, 1495 } }, { { 1123, 1417 }, { 1325, 1495 } }, { { 1325, 1417 }, { 1533, 1495 } }, { { 1533, 1417 }, { 1739, 1495 } }, { { 1739, 1417 }, { 1943, 1495 } }, { { 1943, 1417 }, { 2145, 1495 } }, { { 387, 1494 }, { 563, 1574 } }, { { 563, 1494 }, { 739, 1574 } }, { { 739, 1494 }, { 915, 1574 } }, { { 915, 1494 }, { 1123, 1574 } }, { { 1123, 1494 }, { 1325, 1574 } }, { { 1325, 1494 }, { 1533, 1574 } }, { { 1533, 1494 }, { 1739, 1574 } }, { { 1739, 1494 }, { 1943, 1574 } }, { { 1943, 1494 }, { 2145, 1574 } }, { { 897, 2324 }, { 1185, 2290 } } };
float Pic2Ratio[25][2][2];
string Pic2Diction[25] = { "arn.font1.exp0.jpeg", "chn.font1.exp0.jpeg", "anu.font1.exp0.jpeg", "san.font1.exp0.jpeg", "rnu.font1.exp0.jpeg", "cna.font1.exp0.jpeg", "cnb.font1.exp0.jpeg", "cnc.font1.exp0.jpeg", "num.font1.exp0.jpeg", "num.font1.exp1.jpeg", "num.font1.expw.jpeg", "cnd.font1.exp0.jpeg", "rnu.font1.exp1.jpeg", "rnu.font2.exp0.jpeg", "cna.font1.exp1.jpeg", "cnb.font1.exp1.jpeg", "cnc.font1.exp1.jpeg", "num.font1.exp3.jpeg", "num.font1.exp4.jpeg", "num.font5.exp0.jpeg", "cnd.font1.exp1.jpeg", "rnu.font1.exp3.jpeg", "rnu.font1.exp4.jpeg", "nch.font1.exp0.jpeg" };
//a-alphabet r-rod n-number nu-number chn-chinese nch-num&chinese cna,b,c,d-chinese s-symbol
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About 
//    CONTROL         "",IDC_PICTURE_STATIC,"Static",SS_BITMAP,223,148,15,13
//	_CRT_SECURE_NO_WARNINGS

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CpicV4Dlg dialog

CpicV4Dlg::CpicV4Dlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CpicV4Dlg::IDD, pParent)
, pProg(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CpicV4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CpicV4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD_PIC_BUTTON, &CpicV4Dlg::OnBnClickedLoadPicButton)
	ON_BN_CLICKED(IDC_BUTTON2, &CpicV4Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CpicV4Dlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON3, &CpicV4Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_TessPath, &CpicV4Dlg::OnBnClickedButtonTesspath)
	ON_BN_CLICKED(IDC_BUTTON11, &CpicV4Dlg::OnBnClickedButton_Extmtrpath)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CpicV4Dlg::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON5_BackToTrain, &CpicV4Dlg::OnBnClickedButton5Backtotrain)
	ON_BN_CLICKED(IDC_BUTTON_MakeBox, &CpicV4Dlg::OnBnClickedButtonMakebox)
	ON_BN_CLICKED(IDC_BUTTON_RETRAINING, &CpicV4Dlg::OnBnClickedButtonRetraining)
	ON_BN_CLICKED(IDC_BUTTON_Next, &CpicV4Dlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_LoadBox, &CpicV4Dlg::OnBnClickedButtonLoadbox)
	ON_BN_CLICKED(IDC_BUTTON_ListInfo, &CpicV4Dlg::OnBnClickedButtonListinfo)
	ON_BN_CLICKED(IDC_BUTTON_ExcelADName, &CpicV4Dlg::OnBnClickedButtonExceladname)
	ON_BN_CLICKED(IDC_BUTTON_CopyTifs, &CpicV4Dlg::OnBnClickedButtonCopytifs)
	ON_BN_CLICKED(IDC_BUTTON15, &CpicV4Dlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CpicV4Dlg::OnBnClickedButton16)
END_MESSAGE_MAP()


// CpicV4Dlg message handlers

BOOL CpicV4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	pProg = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	pProg->SetRange(0, ProgRange);
	pProg->SetPos(ProgPos);
	GetDlgItem(IDC_PROGRESS_1)->ShowWindow(0);	//隐藏ProgressCtrl

	for (int kkk = 0; kkk < 25; kkk++){
		Pic2Ratio[kkk][0][0] = (Pic2Data[kkk][0][0] - 265) / (float)3076;
		Pic2Ratio[kkk][1][0] = (Pic2Data[kkk][0][0] - 265) / (float)3076;
		Pic2Ratio[kkk][0][1] = (1239 - Pic2Data[kkk][0][1]) / (float)998;
		Pic2Ratio[kkk][1][1] = (1239 - Pic2Data[kkk][1][1]) / (float)998;
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CpicV4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CpicV4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		CRect rect;
		CPaintDC dc(this);
		GetClientRect(rect);
		dc.FillSolidRect(rect, RGB( 255, 255, 255)); //设置RGB背景
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
// the minimized window.

//std::string strStl = "test";	//string转cstring
////CString strMfc = strStl.c_str();
//CString wstg3(strStl.c_str());
//SetDlgItemText(IDC_EDIT, wstg3);
//CString asda;	//cstring转string
//GetDlgItemText(IDC_EDIT, asda);
//char *chr = new char[asda.GetLength() + 1];
//WideCharToMultiByte(CP_ACP, 0, asda.GetBuffer(), -1, chr, asda.GetLength() + 1, NULL, NULL);
//string pathName = chr;

///////////////////////////////////////////////////
////int 转 CString 转 LPCTSTR
//CString str; 
//str.Format(_T("ghjggj%d"), files[i]);
//LPCTSTR pStr = LPCTSTR(str);
//MessageBox(pStr, TEXT("结果"), MB_OK);
////////////////////////////////////////////////////

//////////////////////////////////////////////////////
////int 转string
//string a=to_string(int n);
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////
///////char 转string
//char c;
//string str;
//stringstream stream;
//stream << c;
//str = stream.str();
//////////////////////////////////////

/////////////////////////
////string转char 
//char* cc; //string转char 
//const int len = ss.length();
//cc = new char[len + 1];
//strcpy(cc, ss.c_str());
////////////////////////

///////////////////////////////////////////////////////////////////////////////////
////tchar 转 char 
//int Cilength;
//Cilength = WideCharToMultiByte(CP_ACP, 0, targetPath, -1, NULL, 0, NULL, NULL);
//WideCharToMultiByte(CP_ACP, 0, targetPath, -1, CtargetPath, Cilength, NULL, NULL);
////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
////Char 转 TChar
//int TCLeng;
//TCHAR TCtar[MAX_PATH];
//TCLeng = MultiByteToWideChar(CP_ACP, 0, Ctar, strlen(Ctar) + 1, NULL, 0);
//MultiByteToWideChar(CP_ACP, 0, Ctar, strlen(Ctar) + 1, TCtar, TCLeng);
//MessageBox(TCtar, TEXT("文件地址"), MB_OK);
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////
////string 转 LPCTSTR
//wstring wstg3(newname.begin(), newname.end()); 
//MessageBox(wstg3.c_str(), TEXT("更改后文件名"), MB_OK);
///////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
////string 转换Tchar
//std::string STDDELFILEPATH = std::string(DELFILEPATH);
//TCHAR TCDELFILEPATH[MAX_PATH];
//_stprintf_s(TCDELFILEPATH, MAX_PATH, _T("%S"), STDDELFILEPATH.c_str());
//////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
////unicode cstring 转string
//char *chr = new char[FilePath.GetLength() + 1];	
//WideCharToMultiByte(CP_ACP, 0, FilePath.GetBuffer(), -1, chr, FilePath.GetLength() + 1, NULL, NULL);
//string pathName = chr;
//////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////iplimage与mat相互转换
//IplImage->cv::Mat
//這個範例程式裡 image.cpp有啊，做個簡單的範例。
//Ex.
//IplImage* pImg = cvLoadImage("lena.jpg");
//cv::Mat img(pImg, 0); //0是不複製影像，也就是pImg與img的data共用同個記憶體位置，header各自有
//
//cv::Mat->IplImage
//cxcore.hpp裡，class cv::Mat裡面第831、832有寫 
//// converts header to IplImage; no data is copied
//operator IplImage() const;
//範例接上面的過來..
//Ex.
//IplImage* pImg = cvLoadImage("lena.jpg");
//cv::Mat img(pImg, 0); //img拿到pImg的data
//IplImage qImg;
//qImg = IplImage(img); //一樣檔案沒複製，所以qImg.imageData就是指向pImg->imageData
////////////////////////////////////////////////////////////////////////////////////////////////

HCURSOR CpicV4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CpicV4Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)	//EDIT设置 背景透明 文字
{
	// Call the base class implementation first! Otherwise, it may  
	// undo what we're trying to accomplish here.  
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// Are we painting the IDC_MYSTATIC control? We can use  
	// CWnd::GetDlgCtrlID() to perform the most efficient test.  
	if (pWnd->GetDlgCtrlID() == IDC_EDIT)
	{
		// Set the text color to red  
		pDC->SetTextColor(RGB(255, 0, 0));

		// Set the background mode for text to transparent   
		// so background will show thru.  
		pDC->SetBkMode(TRANSPARENT);

		// Return handle to our CBrush object  
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	return hbr;
	return HBRUSH();
}

void getFiles(string path, string exd, vector<string>& files)
{
	//文件句柄
	long hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string pathName, exdName;

	if (0 != strcmp(exd.c_str(), ""))
	{
		exdName = "\\*." + exd;
	}
	else
	{
		exdName = "\\*";
	}

	if ((hFile = _findfirst(pathName.assign(path).append(exdName).c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是文件夹中仍有文件夹,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(pathName.assign(path).append("\\").append(fileinfo.name), exd, files);
			}
			else
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					files.push_back(pathName.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

bool DeleteEntireDir(const TCHAR * sPath, bool bDelDir/*=true*/)
{
	CFileFind ff;
	BOOL bFound;
	bFound = ff.FindFile(CString(sPath) + "\\*.*");
	while (bFound)
	{
		bFound = ff.FindNextFile();
		CString sFilePath = ff.GetFilePath();

		if (ff.IsDirectory())
		{
			if (!ff.IsDots())
			{
				DeleteEntireDir(sFilePath, 1);
			}
		}
		else
		{
			if (ff.IsReadOnly())
			{
				SetFileAttributes(sFilePath, FILE_ATTRIBUTE_NORMAL);
			}
			DeleteFile(sFilePath);
		}
	}
	ff.Close();

	if (bDelDir)
	{
		SetFileAttributes(sPath, FILE_ATTRIBUTE_NORMAL);  //设置文件夹的属性 
		RemoveDirectory(sPath);
	}
	return true;
}

int CopyFile(char *SourceFile, char *NewFile)
{
	ifstream in;
	ofstream out;
	in.open(SourceFile, ios::binary);//打开源文件
	if (in.fail())//打开源文件失败
	{
		MessageBox(NULL, TEXT("Error 1: Fail to open the source file."), TEXT("Error 1: Fail to open the source file."), MB_OK);
		in.close();
		out.close();
		return 0;
	}
	out.open(NewFile, ios::binary);//创建目标文件 
	if (out.fail())//创建文件失败
	{
		MessageBox(NULL, TEXT("Error 2: Fail to create the new file."), TEXT("Error 2: Fail to create the new file."), MB_OK);
		out.close();
		in.close();
		return 0;
	}
	else//复制文件
	{
		out << in.rdbuf();
		out.close();
		in.close();
		return 1;
	}
}

bool CpicV4Dlg::ShowEdit(int Sort)
{
	int TeMpNum = 0;
	if (Sort == 1){	//显示第一类
		TeMpNum = 1;
		GetDlgItem(IDC_EDIT1)->ShowWindow(TeMpNum);
	}
	else{
		TeMpNum = 0;
		GetDlgItem(IDC_EDIT1)->ShowWindow(TeMpNum);
	}

	if (Sort == 2){	//显示第二类
		GetDlgItem(IDC_EDIT1)->ShowWindow(TeMpNum);
	}
	else{
		GetDlgItem(IDC_EDIT1)->ShowWindow(TeMpNum);
	}

	if (Sort == 3){	//显示第三类
		GetDlgItem(IDC_EDIT1)->ShowWindow(TeMpNum);
	}
	else{
		GetDlgItem(IDC_EDIT1)->ShowWindow(TeMpNum);
	}

	if (Sort == 4){	//显示第四类
		GetDlgItem(IDC_EDIT1)->ShowWindow(TeMpNum);
	}
	else{
		GetDlgItem(IDC_EDIT1)->ShowWindow(TeMpNum);
	}
	return true;
}

int CpicV4Dlg::ShowMat(cv::Mat img, HWND hWndDisplay)
{
	if (img.channels()<3)
	{
		return  -1;
	}

	//构造将要显示的Mat版本图片  
	RECT rect;
	::GetClientRect(hWndDisplay, &rect);
	cv::Mat imgShow(abs(rect.top - rect.bottom), abs(rect.right - rect.left), CV_8UC3);
	resize(img, imgShow, imgShow.size(), 0, 0, INTER_LINEAR);

	//在控件上显示要用到的CImage类图片  
	ATL::CImage CI;
	int w = imgShow.cols;//宽    
	int h = imgShow.rows;//高    
	int channels = imgShow.channels();//通道数    
	CI.Create(w, h, 8 * channels);

	//CI像素的复制  
	uchar *pS;
	uchar *pImg = (uchar *)CI.GetBits();//得到CImage数据区地址    
	int step = CI.GetPitch();
	for (int i = 0; i<h; i++)
	{
		pS = imgShow.ptr<uchar>(i);
		for (int j = 0; j<w; j++)
		{
			for (int k = 0; k<3; k++)
				*(pImg + i*step + j * 3 + k) = pS[j * 3 + k];
			//注意到这里的step不用乘以3    
		}
	}

	//在控件显示图片  
	HDC dc;
	dc = ::GetDC(hWndDisplay);
	CI.Draw(dc, 0, 0);
	//::ReleaseDC(hWndDisplay, dc);
	//CI.Destroy();

	return 0;
}

void CpicV4Dlg::equalizeHistFunction(Mat Ori, Mat& OUP)
{
	//用来存储各通道图片的向量  
	vector<Mat> splitBGR(Ori.channels());
	//分割通道，存储到splitBGR中  
	split(Ori, splitBGR);
	//对各个通道分别进行直方图均衡化  
	for (int i = 0; i<Ori.channels(); i++)
		equalizeHist(splitBGR[i], splitBGR[i]);
	//合并通道  
	merge(splitBGR, OUP);
}
//直方图均衡化
void medeanFilter(Mat& src, int win_size) {
	int rows = src.rows, cols = src.cols;
	int start = win_size / 2;
	for (int m = start; m <rows - start; m++) {
		for (int n = start; n < cols - start; n++) {
			vector<uchar> model;
			for (int i = -start + m; i <= start + m; i++) {
				for (int j = -start + n; j <= start + n; j++) {
					//cout << int(src.at<uchar>(i, j)) << endl;
					model.push_back(src.at<uchar>(i, j));
				}
			}
			sort(model.begin(), model.end());     //采用快速排序进行
			src.at<uchar>(m, n) = model[win_size*win_size / 2];
		}
	}
}
//中值滤波
void meanFilter(Mat& src, int win_size) {
	int rows = src.rows, cols = src.cols;
	int start = win_size / 2;
	for (int m = start; m <rows - start; m++) {
		for (int n = start; n < cols - start; n++) {
			int sum = 0;
			for (int i = -start + m; i <= start + m; i++) {
				for (int j = -start + n; j <= start + n; j++) {
					sum += src.at<uchar>(i, j);
				}
			}
			src.at<uchar>(m, n) = uchar(sum / win_size / win_size);
		}
	}
}
//均值滤波
const float pi = 3.1415;




//Get Path
void CpicV4Dlg::OnBnClickedButton3() //scan path
{
	CFileFind finder;
	CString path;
	//unidentified		BOOL fileExist;
	// 获取特定文件夹的LPITEMIDLIST，可以将之理解为HANDLE  
	// 所谓的特定文件夹,你可以用CSIDL_XXX来检索之。  
	LPITEMIDLIST rootLoation;
	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &rootLoation);
	if (rootLoation == NULL) {
		// unkown error  
		return;
	}
	// 配置对话框  
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(bi));
	bi.hwndOwner = m_hWnd; //主窗口
	bi.pidlRoot = rootLoation; // 文件夹对话框之根目录，不指定的话则为我的电脑  
	bi.lpszTitle = _T("选择图片集的文件夹"); // 可以不指定  
	// bi.ulFlags = BIF_EDITBOX | BIF_RETURNONLYFSDIRS;  
	// 打开对话框, 有点像DoModal 
	LPITEMIDLIST targetLocation = SHBrowseForFolder(&bi);
	TCHAR targetPath[MAX_PATH]; //路径地址
	if (targetLocation != NULL) {
		SHGetPathFromIDList(targetLocation, targetPath);
		havePath = 1;
		//		MessageBox(targetPath, TEXT("文件地址"), MB_OK );
		//		GetDlgItem(IDC_STATIC_NEW)->SetWindowText(targetPath);//将路径显示到IDC_STATIC_NEW的label上

		///////////////////////////////////////////////
		//////tchar targetPath 转换 char CtargetPath
		int Cilength;
		Cilength = WideCharToMultiByte(CP_ACP, 0, targetPath, -1, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, targetPath, -1, CtargetPath, Cilength, NULL, NULL);
		///////////////////////////////////////////////

		///////////////////////////////////////////////////
		////////循环查询char CtargetPath 字符串内"/"转换为"\"
		for (int i = 0; Ctar[i]; i++)
		{
			if (Ctar[i] == '\\')  
			{
				Ctar[i] = '/';
			}
		}
		///////////////////////////////////////////////////

		///////////////////////////////////////////////
		////Char转换TChar， 在messagebox中显示
		int TCLeng;
		TCHAR TCtar[MAX_PATH];
		TCLeng = MultiByteToWideChar(CP_ACP, 0, Ctar, strlen(Ctar) + 1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, Ctar, strlen(Ctar) + 1, TCtar, TCLeng);
		//		MessageBox(TCtar, TEXT("文件地址"), MB_OK);
		GetDlgItem(IDC_STATIC_NEW)->SetWindowText(TCtar);//将路径显示到IDC_STATIC_NEW的label上
		/////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////////////
		//////////读取tesseract系统变量
		if (getenv("TESSDATA_PREFIX") != NULL){
			CTes = getenv("TESSDATA_PREFIX");
			int TCLeng;
			TCHAR TCtar[MAX_PATH];
			TCLeng = MultiByteToWideChar(CP_ACP, 0, CTes, strlen(CTes) + 1, NULL, 0);
			MultiByteToWideChar(CP_ACP, 0, CTes, strlen(CTes) + 1, TCtar, TCLeng);
			//		MessageBox(TCtar, TEXT("文件地址"), MB_OK);
			GetDlgItem(IDC_STATIC_NEW2)->SetWindowText(TCtar);//将路径显示到IDC_STATIC_NEW的label上
		}
		else{
			MessageBox(TEXT("未发现Tesseract-OCR 环境变量"), TEXT("WARNING"), MB_OK);
		}
		/////////////////////////////////////////////////////////////////////////////////////////

		files.clear();//初始化files,list.
		getFiles(CtargetPath, "jpeg", files);
		size = files.size();
		list[size][2];//重置list,list[i][0]=图片类型，[i][1]=Tif分类
		
		for (int i = 0; i < size; i++){
			list[i][0] = 0;
			list[i][1] = 0;
		}
		//string listshowall = "";
		//for (int i = 0; i < size; i++){
		//	listshowall += to_string(list[i][0]) + " ";
		//	listshowall += to_string(list[i][1]) + "\n";
		//}
		//wstring listshow(listshowall.begin(), listshowall.end());
		//MessageBox(listshow.c_str(), TEXT("遍历list数组"), MB_OK);
	}
}
//scan path
void CpicV4Dlg::OnBnClickedButtonTesspath()//Tesspath
{
	CFileFind finder;
	CString path;
	LPITEMIDLIST rootLoation;
	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &rootLoation);
	if (rootLoation == NULL) {
		return;
	}
	// 配置对话框  
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(bi));
	bi.hwndOwner = m_hWnd; //主窗口
	bi.pidlRoot = rootLoation; // 文件夹对话框之根目录，不指定的话则为我的电脑  
	bi.lpszTitle = _T("选择图片集的文件夹"); // 可以不指定  
	// bi.ulFlags = BIF_EDITBOX | BIF_RETURNONLYFSDIRS;  
	// 打开对话框, 有点像DoModal 
	LPITEMIDLIST targetLocation = SHBrowseForFolder(&bi);
	TCHAR targetPath[MAX_PATH]; //路径地址
	if (targetLocation != NULL) {
		SHGetPathFromIDList(targetLocation, targetPath);
		haveCTesPath = 1;
		//		MessageBox(targetPath, TEXT("文件地址"), MB_OK );
		//		GetDlgItem(IDC_STATIC_NEW)->SetWindowText(targetPath);//将路径显示到IDC_STATIC_NEW的label上

		///////////////////////////////////////////////
		//////tchar targetPath 转换 char TesOcrPath
		int Cilength;
		Cilength = WideCharToMultiByte(CP_ACP, 0, targetPath, -1, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, targetPath, -1, TesOcrPath, Cilength, NULL, NULL);
		///////////////////////////////////////////////

		///////////////////////////////////////////////////
		////////循环查询char TesOcrPath 字符串内"/"转换为"\"
		int i;
		for (i = 0; CTes[i]; i++)
		{
			if (CTes[i] == '\\')  
			{
				CTes[i] = '/';
			}
		}
		///////////////////////////////////////////////////

		///////////////////////////////////////////////
		////Char转换TChar， 在messagebox中显示
		int TCLeng;
		TCHAR TCtar[MAX_PATH];
		TCLeng = MultiByteToWideChar(CP_ACP, 0, CTes, strlen(CTes) + 1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, CTes, strlen(CTes) + 1, TCtar, TCLeng);
		//		MessageBox(TCtar, TEXT("文件地址"), MB_OK);
		GetDlgItem(IDC_STATIC_NEW2)->SetWindowText(TCtar);//将路径显示到IDC_STATIC_NEW的label上
		/////////////////////////////////////////////////
	}
}
//Tesspath
void CpicV4Dlg::OnBnClickedButton_Extmtrpath()  //Extmtrpath
{
	CFileFind finder;
	CString path;
	LPITEMIDLIST rootLoation;
	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &rootLoation);
	if (rootLoation == NULL) {
		return;
	}
	// 配置对话框  
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(bi));
	bi.hwndOwner = m_hWnd; //主窗口
	bi.pidlRoot = rootLoation; // 文件夹对话框之根目录，不指定的话则为我的电脑  
	bi.lpszTitle = _T("选择图片集的文件夹"); // 可以不指定  
	// bi.ulFlags = BIF_EDITBOX | BIF_RETURNONLYFSDIRS;  
	// 打开对话框, 有点像DoModal 
	LPITEMIDLIST targetLocation = SHBrowseForFolder(&bi);
	TCHAR targetPath[MAX_PATH]; //路径地址
	if (targetLocation != NULL) {
		SHGetPathFromIDList(targetLocation, targetPath);
		haveCExtPath = 1;
		//		MessageBox(targetPath, TEXT("文件地址"), MB_OK );
		//GetDlgItem(IDC_STATIC_NEW)->SetWindowText(targetPath);//将路径显示到IDC_STATIC_NEW的label上

		///////////////////////////////////////////////
		//////tchar targetPath 转换 char ExtMtrPath
		int Cilength;
		Cilength = WideCharToMultiByte(CP_ACP, 0, targetPath, -1, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, targetPath, -1, ExtMtrPath, Cilength, NULL, NULL);
		///////////////////////////////////////////////

		/////////////////////////////////////////////////////
		//////////循环查询char ExtMtrPath 字符串内"/"转换为"\"
		//int i;
		//for (i = 0; CExt[i]; i++)
		//{
		//	if (CExt[i] == '\\')  
		//	{
		//		CExt[i] = '/';
		//	}
		//}
		/////////////////////////////////////////////////////

		/////////////////////////////////////////////////
		////Char转换TChar， 在messagebox中显示
		int TCLeng;
		TCHAR TCtar[MAX_PATH];
		TCLeng = MultiByteToWideChar(CP_ACP, 0, CExt, strlen(CExt) + 1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, CExt, strlen(CExt) + 1, TCtar, TCLeng);
		//		MessageBox(TCtar, TEXT("文件地址"), MB_OK);
		GetDlgItem(IDC_STATIC_NEW4)->SetWindowText(TCtar);//将路径显示到IDC_STATIC_NEW的label上
		///////////////////////////////////////////////////
	}
}
//Extmtrpath
void CpicV4Dlg::OnBnClickedLoadPicButton() //扫描jpeg并新建文件夹
{
	if (havePath){
		//////////////////////////////////////////创建文件夹
		int s = 0;
		int d = 0;
		for (int i = 0; i < size; i++){
			havefolders = 1;
			string imgfiles = files[i].substr(0, files[i].size() - 5);// -5 =".jpeg"
			int CreateImgfiles = mkdir(imgfiles.c_str());
			if (CreateImgfiles != 0)
			{
				//				wstring CPwstzxc(CPFILEPATH.begin(), CPFILEPATH.end()); //string转换LPCTSTR
				//				MessageBox(CPwstzxc.c_str(), TEXT("创建失败"), MB_OK);
				++d;
			}
			else{
				++s;
			}
		}

		string imgfiles = CtargetPath + ExTifFolder;//Tif文件
		int CreateImgfiles = mkdir(imgfiles.c_str());
		if (CreateImgfiles != 0)
		{
			++d;
		}
		else{
			++s;
		}
		CString CResult;
		CResult.Format(_T("一共有%d个jpeg文件,成功创建%d个文件夹，失败%d个"), size, s, d);
		LPCTSTR pCResult = LPCTSTR(CResult);
		MessageBox(pCResult, TEXT("结果"), MB_OK);
		////////////////////////////////////////////////////
	}
	else{
		if (!havePath){
			MessageBox(TEXT("先选择扫描路径"), TEXT("ERROR"), MB_OK);
		}
	}
}
//新建文件夹
void CpicV4Dlg::OnBnClickedButtonDelete() //删除文件夹
{
	if (havePath){
		int d = 0;
		int s = 0;
		for (int i = 0; i < size; i++){
			string DELFILEPATH = files[i].substr(0, files[i].size() - 5);// -5 =".jpeg" 路径地址
			//wstring wstzxc(DELFILEPATH.begin(), DELFILEPATH.end()); //string转换LPCTSTR
			//MessageBox(wstzxc.c_str(), TEXT("删除文件名"), MB_OK);
			havefolders = 0;
			havePics = 0;
			haveInfos = 0;
			std::string STDDELFILEPATH = std::string(DELFILEPATH);//string 转换Tchar
			TCHAR TCDELFILEPATH[MAX_PATH];
			_stprintf_s(TCDELFILEPATH, MAX_PATH, _T("%S"), STDDELFILEPATH.c_str());

			int DLPTlen; //char TCDELFILEPATH 转换Tchar CDELFILEPATH
			char CDELFILEPATH[MAX_PATH];
			DLPTlen = WideCharToMultiByte(CP_ACP, 0, TCDELFILEPATH, -1, NULL, 0, NULL, NULL);
			WideCharToMultiByte(CP_ACP, 0, TCDELFILEPATH, -1, CDELFILEPATH, DLPTlen, NULL, NULL);

			if (access(CDELFILEPATH, 0) + 1) {
				//				MessageBox(wstzxc.c_str(), TEXT("存在文件夹"), MB_OK);
				DeleteEntireDir(TCDELFILEPATH, 1);
				++s;
			}
			else {
				++d;
			}
		}
		string imgfiles = CtargetPath + ExTifFolder;//Tif文件
		char* CExTifFolder; //string转char 
		const int ExTifFolderlen = imgfiles.length();
		CExTifFolder = new char[ExTifFolderlen + 1];
		strcpy(CExTifFolder, imgfiles.c_str());
		std::string FILEPATH = std::string(imgfiles);//string 转换Tchar
		TCHAR LEPATH[MAX_PATH];
		_stprintf_s(LEPATH, MAX_PATH, _T("%S"), FILEPATH.c_str());
		if (access(CExTifFolder, 0) + 1) {	// 
			//				MessageBox(wstzxc.c_str(), TEXT("存在文件夹"), MB_OK);
			DeleteEntireDir(LEPATH, 1);
			++s;
		}
		else {
			++d;
		}

		CString DResult;
		DResult.Format(_T("成功删除%d个文件夹，失败%d个"), s, d);
		LPCTSTR pDResult = LPCTSTR(DResult);
		MessageBox(pDResult, TEXT("结果"), MB_OK);
	}
	else {
		MessageBox(TEXT("先选择扫描路径"), TEXT("ERROR"), MB_OK);
	}
}
//删除文件夹


static int threshold_num=120;
static int threshold_max=255;
void CpicV4Dlg::OnBnClickedButtonListinfo()//图片类型分类
{
	//static int list[n][2];
	if (havePath){
		int ShortPicColTimes = 4;	//图像向左剪切4倍
		int ShortPicRowTimes = 4;	//图像向上剪切4倍
		int markpix = 8000;	//商标大致pix总数
		haveInfos = 1;
		int partnum = 1;	//初始化文件集序列
		float linegradient = 0;
		CButton* pButtonLoadbox = (CButton*)GetDlgItem(IDC_BUTTON_ListInfo);	//IDC_Button
		pButtonLoadbox->EnableWindow(FALSE);	//当开始的时候,按钮不可用
		GetDlgItem(IDC_PROGRESS_1)->ShowWindow(1);	//显示ProgressCtrl

		int ProcessTimes = files.size();	//Progress显示处理过程
		ProgPos = 0; pProg->SetRange(0, ProcessTimes - 1);	//Process初始化

		vector<Vec4i> lines;
		Vec4i toppestline;
		Vec4i l;
		int dist = 0, disttopline = 0;
		bool checkfirsttype=1;
		cv::Mat src;
		cv::Mat img;	//输出图片
		for (int sizei = 0; sizei < files.size(); sizei++){
			src = cv::imread(files[sizei], IMREAD_ANYCOLOR);	//Mat读取图片地址 & Unchanged
			src.cols = src.cols / ShortPicColTimes;	//缩小范围4倍->分类
			src.rows = src.rows / ShortPicRowTimes;	//缩小范围4倍->分类

			cvtColor(src, img, CV_BGR2GRAY);	//直线检测-HoughLinesP	1.灰度化处理	imread->( ,IMREAD_UNCHANGED)
			sobelTIDU(img, img); //2.Sobel算子边缘检测
			threshold(img, img, threshold_num, threshold_max, THRESH_BINARY_INV);	//3.二值图处理
			img = img < 127;	//4.二值图翻转颜色
			lines.clear();	//5.HoughLinesP 累计概率霍夫变换 线段检测	//初始化lines
			HoughLinesP(img, lines, 1, CV_PI / 180 / 5, 450, 480, 160); //所有横线
			//for (size_t i = 0; i < lines.size(); i++)	//划线显示测试
			//{
			//	Vec4i l = lines[i];
			//	line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 0), 1);
			//}
			//imshow("结果", src);
			for (int j0 = 0; j0 < 4; j0++){	//初始化toppestline
				toppestline[j0] = 0;
			}
			toppestline[1] = src.rows;

			dist = 0; disttopline = 0;
			cvtColor(img, img, CV_GRAY2BGR);
			for (size_t ik = 0; ik < lines.size(); ik++)	//扫描最上长线段
			{
				l = lines[ik];
				dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
				dist = sqrtf(dist);
				linegradient = abs(((float)l[1] - l[3]) / (l[0] - l[2]));	//角度小于+-arctan(1/2)
				if (dist>450 && toppestline[1] > l[1] && linegradient < 0.5){
					for (int j = 0; j < 4; j++){
						toppestline[j] = l[j];
					}
					disttopline = dist;
				}
			}
			if (lines.size() != 0){	//计算thld
				int thld = 0;
				int colorpix;
				for (int rowcal = 0; rowcal < toppestline[1]; rowcal++){
					for (int colcal = 0; colcal < img.cols; colcal++){
						colorpix = img.at<Vec3b>(rowcal, colcal)[0];
						if (colorpix == 255){
							thld++;
						}
					}
				}
				if (thld < markpix){
					if (sizei == 0){
						checkfirsttype = 0;
						partnum--;
					}
					if (checkfirsttype){
						list[sizei][0] = 2;
						list[sizei][1] = partnum;
						partnum++;
					}
					else{
						list[sizei][0] = 2;
						partnum++;
						list[sizei][1] = partnum;
					}
				}
				else{
					list[sizei][0] = 3;
					list[sizei][1] = partnum;
				} 
			}
			else{
				list[sizei][0] = 4;
				list[sizei][1] = partnum;
			}

			pProg->SetPos(ProgPos);
			ProgPos++;
		}
		pButtonLoadbox->EnableWindow(TRUE);
		pProg->SetPos(0);
		GetDlgItem(IDC_PROGRESS_1)->ShowWindow(0);	//隐藏ProgressCtrl

		string listshowall = "";	//显示list
		for (int i = 0; i < size; i++){
			listshowall += to_string(list[i][0]) + " ";
			listshowall += to_string(list[i][1]) + "\n";
		}
		wstring listshow(listshowall.begin(), listshowall.end());
		MessageBox(listshow.c_str(), TEXT("遍历list数组"), MB_OK);
	}
	else{
		if (!havePath){
			MessageBox(TEXT("先选择扫描路径"), TEXT("ERROR"), MB_OK);
		}
	}
}
//图片类型分类

void CpicV4Dlg::OnBnClickedButton2() //图片切割 Assemble Pics
{
	//if (havePath && havefolders && haveInfos){
	//	// TODO:  在此添加控件通知处理程序代码
	//	havePics = 1;
	//	string pathName = "C:\\Users\\OtntO\\Desktop\\training samples\\No\\IMG_0009.JPEG";
	//	cv::Mat orgImg = cv::imread(pathName, IMREAD_UNCHANGED);
	//	MyCvtColor(orgImg);
	//	cv::Mat imgShow(2488 / 2, 3264 / 2, CV_8UC3);
	//	resize(orgImg, imgShow, imgShow.size(), 0, 0, INTER_LINEAR);
	//	namedWindow("结果");	//显示图片
	//	imshow("结果", imgShow);
	//}
	//else{
	//	if (!havePath){
	//		MessageBox(TEXT("先选择扫描路径"), TEXT("ERROR"), MB_OK);
	//	}
	//	if (!havefolders){
	//		MessageBox(TEXT("先创建文件夹"), TEXT("ERROR"), MB_OK);
	//	}
	//	if (!haveInfos){
	//		MessageBox(TEXT("先设置图片类型"), TEXT("ERROR"), MB_OK);
	//	}
	//}


	int ShortPicColTimes = 4;	//图像向左4倍
	int ShortPicRowTimes = 4;	//图像向上压缩4倍
	int markpix = 8000;	//商标大致pix总数
	haveInfos = 1;
	int partnum = 1;	//初始化文件集序列
	CButton* pButtonLoadbox = (CButton*)GetDlgItem(IDC_BUTTON_ListInfo);	//IDC_Button
	pButtonLoadbox->EnableWindow(FALSE);	//当开始的时候,按钮不可用
	GetDlgItem(IDC_PROGRESS_1)->ShowWindow(1);	//显示ProgressCtrl

	int ProcessTimes = files.size();	//Progress显示处理过程
	ProgPos = 0; pProg->SetRange(0, ProcessTimes - 1);	//Process初始化

	vector<Vec4i> lines;
	Vec4i toppestline;
	Vec4i l;
	int dist = 0, disttopline = 0;
	bool checkfirsttype = 1;
	cv::Mat src;
	cv::Mat img;	//输出图片
	for (int sizei = 0; sizei < files.size(); sizei++){
		src = cv::imread(files[sizei], IMREAD_ANYCOLOR);	//Mat读取图片地址 & Unchanged
		src.cols = src.cols / ShortPicColTimes;	//缩小范围4倍->分类
		src.rows = src.rows / ShortPicRowTimes;	//缩小范围4倍->分类

		cvtColor(src, img, CV_BGR2GRAY);	//直线检测-HoughLinesP	1.灰度化处理	imread->( ,IMREAD_UNCHANGED)
		sobelTIDU(img, img); //2.Sobel算子边缘检测
		threshold(img, img, threshold_num, threshold_max, THRESH_BINARY_INV);	//3.二值图处理
		img = img < 127;	//4.二值图翻转颜色
		lines.clear();	//5.HoughLinesP 累计概率霍夫变换 线段检测	//初始化lines
		HoughLinesP(img, lines, 1, CV_PI / 180 / 5, 450, 480, 160); //所有横线
		//for (size_t i = 0; i < lines.size(); i++)	//划线显示测试
		//{
		//	Vec4i l = lines[i];
		//	line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 0), 1);
		//}
		//imshow("结果", src);
		for (int j0 = 0; j0 < 4; j0++){	//初始化toppestline
			toppestline[j0] = 0;
		}
		toppestline[1] = src.rows;

		dist = 0; disttopline = 0;
		cvtColor(img, img, CV_GRAY2BGR);
		for (size_t ik = 0; ik < lines.size(); ik++)	//扫描最上长线段
		{
			l = lines[ik];
			dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
			dist = sqrtf(dist);
			if (dist>450 && toppestline[1] > l[1]){
				for (int j = 0; j < 4; j++){
					toppestline[j] = l[j];
				}
				disttopline = dist;
			}
		}
		if (lines.size() != 0){	//计算thld
			int thld = 0;
			int colorpix;
			for (int rowcal = 0; rowcal < toppestline[1]; rowcal++){
				for (int colcal = 0; colcal < img.cols; colcal++){
					colorpix = img.at<Vec3b>(rowcal, colcal)[0];
					if (colorpix == 255){
						thld++;
					}
				}
			}
			if (thld < markpix){
				if (sizei == 0){
					checkfirsttype = 0;
					partnum--;
				}
				if (checkfirsttype){
					list[sizei][0] = 2;
					list[sizei][1] = partnum;
					partnum++;
				}
				else{
					list[sizei][0] = 2;
					partnum++;
					list[sizei][1] = partnum;
				}
			}
			else{
				list[sizei][0] = 3;
				list[sizei][1] = partnum;
			}
		}
		else{
			list[sizei][0] = 4;
			list[sizei][1] = partnum;
		}

		pProg->SetPos(ProgPos);
		ProgPos++;
	}
	pButtonLoadbox->EnableWindow(TRUE);
	pProg->SetPos(0);
	GetDlgItem(IDC_PROGRESS_1)->ShowWindow(0);	//隐藏ProgressCtrl

	string listshowall = "";	//显示list
	for (int i = 0; i < size; i++){
		listshowall += to_string(list[i][0]) + " ";
		listshowall += to_string(list[i][1]) + "\n";
	}
	wstring listshow(listshowall.begin(), listshowall.end());
	MessageBox(listshow.c_str(), TEXT("遍历list数组"), MB_OK);
}
//图片切割

void CpicV4Dlg::OnBnClickedButtonMakebox()	//制作box文件
{
	if (havePath && havefolders && havePics){
		int s = 0;
		int d = 0;
		string testimgfiles;
		int sizetest;
		string systemcommand = "";
		char* Csystemcommand;
		int systemcommandlen = 0;
		int file_len = 0;
		int divpic_len = 0;
		char* picfiles_path;
		char* pic_path;

		for (int i = 0; i < size; i++){
			picfiles_path = new char[strlen(files[i].c_str()) + 1];//string file路径转换char
			strcpy(picfiles_path, files[i].c_str());
			for (int l = 0; picfiles_path[l]; l++)//char files路径fix
			{
				if (picfiles_path[l] == '\\')
				{
					picfiles_path[l] = '/';
				}
			}

			string Spicfiles_path;//改后路径char转string
			stringstream stream2;
			stream2 << picfiles_path;
			Spicfiles_path = stream2.str();

			TempFile.clear();//初始化TempFile
			testimgfiles = Spicfiles_path.substr(0, files[i].size() - 5);// -5 =".jpeg"
			getFiles(testimgfiles, "jpeg", TempFile);
			sizetest = TempFile.size();
			systemcommand = "cd " + testimgfiles;
			for (int j = 0; j < sizetest; j++){ //file list
				//wstring ws1w1(TempFile[j].begin(), TempFile[j].end());
				//MessageBox(ws1w1.c_str(), TEXT("TempFiles"), MB_OK);
				divpic_len = TempFile[j].length();//string转char*
				pic_path = new char[divpic_len + 1];
				strcpy(pic_path, TempFile[j].c_str());
				for (int k = 0; pic_path[k]; k++)//char TempFile路径fix
				{
					if (pic_path[k] == '\\')
					{
						pic_path[k] = '/';
					}
				}
				int nu = 0;//末斜杠位置
				for (int ij = 0; pic_path[ij]; ij++){ //从Char寻找文件名
					if (pic_path[ij] == '/'){
						nu = ij;
					}
				}
				string pictestname(TempFile[j].substr(nu + 1, strlen(pic_path) - nu - 1));//文件名
				int nd1 = 0;//斜杠后第一点位置
				for (unsigned int jk = nu + 1; jk < strlen(pic_path); jk++){
					if (pic_path[jk] == '.'){
						nd1 = jk;
						jk = strlen(pic_path);
					}
				}
				string pictestnamend1(TempFile[j].substr(nu + 1, nd1 - 1 - nu));//"num"
				int nd2 = 0;//斜杠后第二点位置
				for (unsigned int jkl = nd1 + 1; jkl < strlen(pic_path); jkl++){
					if (pic_path[jkl] == '.'){
						nd2 = jkl;
						jkl = strlen(pic_path);
					}
				}
				string pictestnamend2(TempFile[j].substr(nd1 + 1, nd2 - 1 - nd1));//"font"
				int nd3 = 0;//斜杠后第三点位置
				for (unsigned int kl = nd2 + 1; kl < strlen(pic_path); kl++){
					if (pic_path[kl] == '.'){
						nd3 = kl;
						kl = strlen(pic_path);
					}
				}
				string pictestnamend3(TempFile[j].substr(nd2 + 1, nd3 - 1 - nd2));//"exp0"
				string pictestnamend4(TempFile[j].substr(nu + 1, nd3 - 1 - nu));//num.font.exp0

				systemcommand += " &  tesseract.exe " + pictestname + " " + pictestnamend4 + " -l " + pictestnamend1 + " batch.nochop makebox";
				//定制指令
			}
			systemcommandlen = systemcommand.length();//string转char*	//执行指令合集
			Csystemcommand = new char[systemcommandlen + 1];
			strcpy(Csystemcommand, systemcommand.c_str());
			system(Csystemcommand);


			for (int j = 0; j < sizetest; j++){ //file list
				//wstring ws1w1(TempFile[j].begin(), TempFile[j].end());
				//MessageBox(ws1w1.c_str(), TEXT("TempFiles"), MB_OK);
				divpic_len = TempFile[j].length();//string转char*
				pic_path = new char[divpic_len + 1];
				strcpy(pic_path, TempFile[j].c_str());
				for (int k = 0; pic_path[k]; k++)//char TempFile路径fix
				{
					if (pic_path[k] == '\\')
					{
						pic_path[k] = '/';
					}
				}
				int nu = 0;//末斜杠位置
				for (int ij = 0; pic_path[ij]; ij++){ //从Char寻找文件名
					if (pic_path[ij] == '/'){
						nu = ij;
					}
				}
				string pictestname(TempFile[j].substr(nu + 1, strlen(pic_path) - nu - 1));//文件名
				int nd1 = 0;//斜杠后第一点位置
				for (unsigned int jk = nu + 1; jk < strlen(pic_path); jk++){
					if (pic_path[jk] == '.'){
						nd1 = jk;
						jk = strlen(pic_path);
					}
				}
				string pictestnamend1(TempFile[j].substr(nu + 1, nd1 - 1 - nu));//"num"
				int nd2 = 0;//斜杠后第二点位置
				for (unsigned int jkl = nd1 + 1; jkl < strlen(pic_path); jkl++){
					if (pic_path[jkl] == '.'){
						nd2 = jkl;
						jkl = strlen(pic_path);
					}
				}
				string pictestnamend2(TempFile[j].substr(nd1 + 1, nd2 - 1 - nd1));//"font"
				int nd3 = 0;//斜杠后第三点位置
				for (unsigned int kl = nd2 + 1; kl < strlen(pic_path); kl++){
					if (pic_path[kl] == '.'){
						nd3 = kl;
						kl = strlen(pic_path);
					}
				}
				string pictestnamend3(TempFile[j].substr(nd2 + 1, nd3 - 1 - nd2));//"exp0"
				string pictestnamend4(TempFile[j].substr(nu + 1, nd3 - 1 - nu));//num.font.exp0

				char* checkfile; //检查box
				string Scheckfiles;
				int checkfilelen;
				Scheckfiles = testimgfiles + "/" + pictestnamend4 + ".box";
				checkfilelen = Scheckfiles.length();//string转char*
				checkfile = new char[checkfilelen + 1];
				strcpy(checkfile, Scheckfiles.c_str());
				const char* Ccheckfile = checkfile;
				if (access(Ccheckfile, 00) + 1){
					s++;
				}
				else{
					d++;
				}
			}

		}
		CString MakeBoxResult;
		MakeBoxResult.Format(_T("创建%d个box，存在%d个box，缺少%d个box"), sizetest, s, d);
		LPCTSTR pMakeBoxResult = LPCTSTR(MakeBoxResult);
		MessageBox(pMakeBoxResult, TEXT("结果"), MB_OK);
	}
	else{
		if (!havePath){
			MessageBox(TEXT("先选择扫描路径"), TEXT("ERROR"), MB_OK);
		}
		if (!havefolders){
			MessageBox(TEXT("先创建文件夹"), TEXT("ERROR"), MB_OK);
		}
		if (!havePics){
			MessageBox(TEXT("先分配图片"), TEXT("ERROR"), MB_OK);
		}
	}
}
//制作box文件


//#include <afxdb.h>
#include <afx.h>
void CpicV4Dlg::OnBnClickedButtonLoadbox()
{
	// TODO:  在此添加控件通知处理程序代码 Excel 输入
	CStdioFile Filasde;
	CString st132r;
	st132r.Format(TEXT("asd\tsda\tasf\t\n1w1w1ww"));	//%s (string)	\n回车	\tTAB
	Filasde.Open(TEXT("E:\\1.xls"), CFile::modeReadWrite);
	Filasde.SeekToEnd(); //将指针移至文件末尾进行追加
	Filasde.Write(st132r, st132r.GetLength());
	//http://blog.csdn.net/tanqiuwei/article/details/7380012
	Filasde.Close();
}
//读取box文件

void CpicV4Dlg::OnBnClickedButtonBack()
{
	// TODO:  在此添加控件通知处理程序代码 jpg转tif
	//CxImage cxMulti;
	//cxMulti.Load(TEXT("C:/Users/ZK-PC/Desktop/training samples/num.font.exp2.tif"), CXIMAGE_FORMAT_TIF);//加载一个多页tiff文件
	//int nPageCount = cxMulti.GetNumFrames();//得到tiff文件的页数
	//CxImage *pImageData = new CxImage[nPageCount + 1];
	//for (int i = 0; i<nPageCount; i++)
	//{
	//	cxMulti.SetFrame(i);//设置当前帧为i编号图像
	//	cxMulti.Load(TEXT("C:/Users/ZK-PC/Desktop/training samples/num.font.exp2.tif"), CXIMAGE_FORMAT_TIF);
	//	pImageData[i].Copy(cxMulti);//将此页图像复制到pImageData[i]中
	//}
	//if (pImageData)
	//{
	//	delete[]pImageData;
	//	pImageData = NULL;
	//}

	CxImage image1, image2, image3;
	image1.Load(TEXT("C:/Users/ZK-PC/Desktop/training samples/test/num.font.exp0.JPEG"), CXIMAGE_FORMAT_JPG);
	image2.Load(TEXT("C:/Users/ZK-PC/Desktop/training samples/test/num.font.exp1.JPEG"), CXIMAGE_FORMAT_JPG);
	image3.Load(TEXT("C:/Users/ZK-PC/Desktop/training samples/test/num.font.exp2.JPEG"), CXIMAGE_FORMAT_JPG);
	CxImage * pimage[3];
	pimage[0] = &image1;
	pimage[1] = &image2;
	pimage[2] = &image3;
	FILE * hFile;
	hFile = fopen("C:/Users/ZK-PC/Desktop/training samples/test/multipage.tif", " w+b ");
	CxImageTIF multiimage;
	multiimage.Encode(hFile, pimage, 3);
	fclose(hFile);
	//FILE * hFile;
	//hFile = fopen(" c://multi.tif ", " w+b ");
	//CxImageTIF image;
	//image.Load(" c://1.tif ", CXIMAGE_FORMAT_TIF);
	//image.Encode(hFile, true);
	//image.Load(" c://2.bmp ", CXIMAGE_FORMAT_BMP);
	//image.Encode(hFile, true);
	//image.Load(" c://3.png ", CXIMAGE_FORMAT_PNG);
	//image.Encode(hFile);
	//fclose(hFile);
}
//back

void CpicV4Dlg::OnBnClickedButtonNext()
{
	// TODO:  在此添加控件通知处理程序代码 载入box文件
	//string imgfiles = files[i].substr(0, files[i].size() - 5);	list[1][2];
	string jpgfiles = "C:\\Users\\OtntO\\Desktop\\training samples\\test\\num.font.exp0";
	TempFile.clear();
	getFiles(jpgfiles, "box", TempFile);
	int tempsize = files.size();
	vector<string> TempDatas[1][1][2];
	//TempDatas[][][1].push_back(string line);
	int files_line_size = TempDatas[0][0][1].size();
	int files_pic_size = sizeof(TempDatas) / sizeof(TempDatas[0]);
	int files_box_size = sizeof(TempDatas[0]) / sizeof(TempDatas[0][0]);
	//TempDatas[][][1] = lines*;
	//TempDatas[][][0] = EditBoxName*;

	int No_listGroup = 1; 
	int Groupsize = 0;
	string SecondPic[1][26];
	string ThirdPic[1][50];
	for (int listi = 0; listi < sizeof(list) / sizeof(list[0]); listi++){
		if (list[listi][1] = 1)
			Groupsize++;
	}
}
//next

void CpicV4Dlg::OnBnClickedButtonExceladname()
{
	//// TODO:  在此添加控件通知处理程序代码 分割图片
	//string filenames = "C:\\Users\\ZK-PC\\Desktop\\training samples\\No\\IMG_0001.JPEG";
	Mat src;
	Mat img;
	vector<Vec4i> lines;
	Vec4i BorderXline;
	Vec4i BorderYline;
	int fourpoint[4][2];
	Vec4i l;
	int SecPosX;
	int SecPosY;
	int dist = 0, disttoplineX = 0, disttoplineY = 0;
	list[0][0] = 2;
	int InterSpace = 4;
	for (int filestep = 0; filestep < files.size(); filestep++){	//切割files里图片
		string filenames = files[filestep];
		src = cv::imread(filenames, IMREAD_ANYCOLOR);	//Mat读取图片地址 & Unchanged
		if (list[filestep][0] != 4){
			for (int foursection = 0; foursection < 4; foursection++){	//扫描图片外四点
				img = src(Range(src.rows / 4 * 3 * (foursection / 2), src.rows / 4 * 3 * (foursection / 2) + src.rows / 4), Range(src.cols / 4 * 3 * ((foursection + 2) % 2), src.cols / 4 * 3 * ((foursection + 2) % 2) + src.cols / 4));	//第一个range是行始终，第二个是列始终

				for (int j0 = 0; j0 < 4; j0++){	//初始化toppestline
					BorderXline[j0] = 0;
				}
				for (int j1 = 0; j1 < 4; j1++){	//初始化toppestline
					BorderYline[j1] = 0;
				}
				if (foursection == 0){
					BorderXline[1] = src.rows;
					BorderYline[0] = src.cols;
				}
				if (foursection == 1){
					BorderXline[3] = src.rows;
					BorderYline[0] = 0;
				}
				if (foursection == 2){
					BorderXline[1] = 0;
					BorderYline[2] = src.cols;
				}
				if (foursection == 3){
					BorderXline[3] = 0;
					BorderYline[2] = 0;
				}

				/*list[filestep][0]*/
				/*foursection / 2*/	// =0 第一、二个图片  =1 第三、四个图片
				/*foursection / 2*/	//	=0 第一、三个图片	=1	第二、四个图片




				cvtColor(img, img, CV_BGR2GRAY);	//直线检测-HoughLinesP	1.灰度化处理	imread->( ,IMREAD_UNCHANGED)
				sobelTIDU(img, img); //2.Sobel算子边缘检测
				threshold(img, img, threshold_num, threshold_max, THRESH_BINARY_INV);	//3.二值图处理
				img = img < 127;	//4.二值图翻转颜色
				lines.clear();	//5.HoughLinesP 累计概率霍夫变换 线段检测	//初始化lines
				HoughLinesP(img, lines, 1, CV_PI / 180 / 5, 250, 280, 200); //所有横线
				//for (size_t i = 0; i < lines.size(); i++)	//划线显示测试
				//{
				//	Vec4i l = lines[i];
				//	line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 0), 1);
				//}
				//imshow("结果", src);

				float linegradient;
				int tempx = 0, tempy = 0;
				dist = 0; disttoplineX = 0; disttoplineY = 0;
				cvtColor(img, img, CV_GRAY2BGR);

				for (size_t ikl = 0; ikl < lines.size(); ikl++){	//修整线段
					linegradient = ((float)lines[ikl][1] - lines[ikl][3]) / (lines[ikl][0] - lines[ikl][2]);
					if (abs(linegradient) <= 1){
						if (lines[ikl][0] > lines[ikl][2]){
							tempx = lines[ikl][0];
							tempy = lines[ikl][1];
							lines[ikl][0] = lines[ikl][2];
							lines[ikl][1] = lines[ikl][3];
							lines[ikl][2] = tempx;
							lines[ikl][3] = tempy;
						}
					}
					if (abs(linegradient) > 1){
						if (lines[ikl][1] > lines[ikl][3]){
							tempx = lines[ikl][0];
							tempy = lines[ikl][1];
							lines[ikl][0] = lines[ikl][2];
							lines[ikl][1] = lines[ikl][3];
							lines[ikl][2] = tempx;
							lines[ikl][3] = tempy;
						}
					}
				}

				for (size_t ik = 0; ik < lines.size(); ik++)	//扫描线段
				{
					if (foursection == 0){	//第一区域检测
						if (lines[ik][1] < BorderXline[1]){	//寻找最靠上的横线
							l = lines[ik];
							dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
							dist = sqrtf(dist);
							linegradient = ((float)l[1] - l[3]) / (l[0] - l[2]);	//角度小于+-arctan(1/2)
							if (dist > 280 && abs(linegradient) < 0.5){
								for (int fs00 = 0; fs00 < 4; fs00++){
									BorderXline[fs00] = l[fs00];
								}
							}
						}
						if (lines[ik][0] < BorderYline[0]){	//寻找最靠左的横线
							l = lines[ik];
							dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
							dist = sqrtf(dist);
							linegradient = ((float)l[1] - l[3]) / (l[0] - l[2]);	//角度大于-arctan(2)
							if (dist > 280 && abs(linegradient) > 2){
								for (int fs01 = 0; fs01 < 4; fs01++){
									BorderYline[fs01] = l[fs01];
								}
							}
						}
					}

					if (foursection == 1){	//第二区域检测
						if (lines[ik][3] < BorderXline[3]){	//寻找最靠上的横线
							l = lines[ik];
							dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
							dist = sqrtf(dist);
							linegradient = ((float)l[1] - l[3]) / (l[0] - l[2]);	//角度小于+-arctan(1/2)
							if (dist > 280 && abs(linegradient) < 0.5){
								for (int fs10 = 0; fs10 < 4; fs10++){
									BorderXline[fs10] = l[fs10];
								}
							}
						}
						if (lines[ik][0] > BorderYline[0]){	//寻找最靠右的横线
							l = lines[ik];
							dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
							dist = sqrtf(dist);
							linegradient = ((float)l[1] - l[3]) / (l[0] - l[2]);	//角度大于-arctan(2)
							if (dist > 280 && abs(linegradient) > 2){
								for (int fs11 = 0; fs11 < 4; fs11++){
									BorderYline[fs11] = l[fs11];
								}
							}
						}
					}

					if (foursection == 2){	//第三区域检测
						if (lines[ik][1] > BorderXline[1]){	//寻找最靠下的横线
							l = lines[ik];
							dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
							dist = sqrtf(dist);
							linegradient = ((float)l[1] - l[3]) / (l[0] - l[2]);	//角度小于+-arctan(1/2)
							if (dist > 280 && abs(linegradient) < 0.5){
								for (int fs20 = 0; fs20 < 4; fs20++){
									BorderXline[fs20] = l[fs20];
								}
							}
						}
						if (lines[ik][2] < BorderYline[2]){	//寻找最靠左的横线
							l = lines[ik];
							dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
							dist = sqrtf(dist);
							linegradient = ((float)l[1] - l[3]) / (l[0] - l[2]);	//角度大于-arctan(2)
							if (dist > 280 && abs(linegradient) > 2){
								for (int fs21 = 0; fs21 < 4; fs21++){
									BorderYline[fs21] = l[fs21];
								}
							}
						}
					}

					if (foursection == 3){	//第四区域检测
						if (lines[ik][3] > BorderXline[3]){	//寻找最靠下的横线
							dist = sqrtf(powf((lines[ik][0] - lines[ik][2]), 2) + powf((lines[ik][1] - lines[ik][3]), 2));
							linegradient = ((float)l[1] - l[3]) / (l[0] - l[2]);	//角度小于+-arctan(1/2)
							if (dist > 450 && abs(linegradient) < 0.5){
								for (int fs30 = 0; fs30 < 4; fs30++){
									BorderXline[fs30] = l[fs30];
								}
							}
						}
						if (lines[ik][2] > BorderYline[2]){	//寻找最靠右的横线
							l = lines[ik];
							dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
							dist = sqrtf(dist);
							linegradient = ((float)l[1] - l[3]) / (l[0] - l[2]);	//角度大于-arctan(2)
							if (dist > 280 && abs(linegradient) > 2){
								for (int fs31 = 0; fs31 < 4; fs31++){
									BorderYline[fs31] = l[fs31];
								}
							}
						}
					}

					//if (foursection=0)	//test
					//imshow("resule1", src(Range(src.rows / 4 * 3 * (foursection / 2), src.rows / 4 * 3 * (foursection / 2) + src.rows / 4), Range(src.cols / 4 * 3 * ((foursection + 2) % 2), src.cols / 4 * 3 * ((foursection + 2) % 2) + src.cols / 4)));
					//if (foursection=1)
					//imshow("resule2", src(Range(src.rows / 4 * 3 * (foursection / 2), src.rows / 4 * 3 * (foursection / 2) + src.rows / 4), Range(src.cols / 4 * 3 * ((foursection + 2) % 2), src.cols / 4 * 3 * ((foursection + 2) % 2) + src.cols / 4)));
					//if (foursection=2)
					//imshow("resule3", src(Range(src.rows / 4 * 3 * (foursection / 2), src.rows / 4 * 3 * (foursection / 2) + src.rows / 4), Range(src.cols / 4 * 3 * ((foursection + 2) % 2), src.cols / 4 * 3 * ((foursection + 2) % 2) + src.cols / 4)));
					//if (foursection=3)
					//imshow("resule4", src(Range(src.rows / 4 * 3 * (foursection / 2), src.rows / 4 * 3 * (foursection / 2) + src.rows / 4), Range(src.cols / 4 * 3 * ((foursection + 2) % 2), src.cols / 4 * 3 * ((foursection + 2) % 2) + src.cols / 4)));
				}
				if (foursection == 0){	//获取端点坐标
					SecPosX = (BorderXline[0] + BorderYline[0]) / 2;
					SecPosY = (BorderXline[1] + BorderYline[1]) / 2;
				}
				if (foursection == 1){
					SecPosX = (BorderXline[2] + BorderYline[0]) / 2;
					SecPosY = (BorderXline[3] + BorderYline[1]) / 2;
				}
				if (foursection == 2){
					SecPosX = (BorderXline[0] + BorderYline[2]) / 2;
					SecPosY = (BorderXline[1] + BorderYline[3]) / 2;
				}
				if (foursection == 3){
					SecPosX = (BorderXline[2] + BorderYline[2]) / 2;
					SecPosY = (BorderXline[3] + BorderYline[3]) / 2;
				}
				fourpoint[foursection][0] = src.cols / 4 * 3 * (foursection % 2) + SecPosX;	//x全局坐标
				fourpoint[foursection][1] = src.rows / 4 * 3 * (foursection / 2) + SecPosY;	//y全局坐标
			}

			/*fourpoint[][];*/	//根据四点切割
			/*list[filestep][0]*/
			string filespicpath = files[filestep].substr(0, files[filestep].size() - 5);	// -5 =".jpeg"
			//LINE(POINT(fourpoint[0][0], fourpoint[0][1]), POINT(fourpoint[1][0], fourpoint[1][1]));
			//LINE(POINT(fourpoint[2][0], fourpoint[2][1]), POINT(fourpoint[3][0], fourpoint[3][1]));

			int radius = sqrt(abs(fourpoint[0][1] - fourpoint[2][1]) ^ 2 + abs(fourpoint[0][0] - fourpoint[2][0]) ^ 2);
			int length = sqrt(abs((fourpoint[3][1] + fourpoint[1][1]) / 2 - (fourpoint[2][1] + fourpoint[0][1]) / 2) ^ 2 + abs((fourpoint[3][0] + fourpoint[1][0]) / 2 - (fourpoint[0][0] + fourpoint[2][0]) / 2) ^ 2);
			int x1 = (fourpoint[3][0] + fourpoint[1][0]) / 2;
			int y1 = (fourpoint[1][1] + fourpoint[3][1]) / 2;
			int x0 = (fourpoint[0][0] + fourpoint[2][0]) / 2;
			int y0 = (fourpoint[0][1] + fourpoint[2][1]) / 2;
			float theta0 = atan(((float)fourpoint[0][1] - fourpoint[2][1]) / (fourpoint[0][0] - fourpoint[2][0]));
			float dtheta = (atan(((float)fourpoint[1][1] - fourpoint[3][1]) / (fourpoint[1][0] - fourpoint[3][0])) - atan((fourpoint[0][1] - fourpoint[2][1]) / (fourpoint[0][0] - fourpoint[2][0]))) / (x1 - x0);
			float r0 = sqrt(abs(fourpoint[0][1] - fourpoint[2][1]) ^ 2 + abs(fourpoint[0][0] - fourpoint[2][0]) ^ 2 ) / 2;
			float dr = (sqrt(abs(fourpoint[1][1] - fourpoint[3][1]) ^ 2 + abs(fourpoint[1][0] - fourpoint[3][0]) ^ 2 ) / 2 - sqrt((abs(fourpoint[0][1] - fourpoint[2][1]) ^ 2 + abs(fourpoint[0][0] - fourpoint[2][0]) ^ 2)) / 2) / (x1 - x0);
			float kx, ky;
			if (list[filestep][0] = 2){
				for (int stepstep = 0; stepstep < 24; stepstep++){	//Pic2Ratio[25][2][2]
					kx = Pic2Ratio[stepstep][0][0];
					ky = Pic2Ratio[stepstep][0][1];
					float fixedpoint1x = (x1 - x0)*kx + x0 + (r0 + dr*(x1 - x0)*kx)*ky*sin(theta0 + dtheta*(x1 - x0)*kx);
					float fixedpoint1y = y0 - (y0 - y1 )*kx + (r0 + dr*(x1 - x0)*kx)*ky*cos(theta0 + dtheta*(x1 - x0)*kx);
					kx = Pic2Ratio[stepstep][1][0];
					ky = Pic2Ratio[stepstep][1][1];
					float fixedpoint2x = (x1 - x0)*kx + x0 + (r0 + dr*(x1 - x0)*kx)*ky*sin(theta0 + dtheta*(x1 - x0)*kx);
					float fixedpoint2y = y0 - (y0 - y1 )*kx + (r0 + dr*(x1 - x0)*kx)*ky*cos(theta0 + dtheta*(x1 - x0)*kx);
					float temppoint;
					if (fixedpoint1x - fixedpoint2x>0){
						temppoint = fixedpoint1x;
						fixedpoint1x = fixedpoint2x;
						fixedpoint2x = temppoint;
					}
					if (fixedpoint1y - fixedpoint2y>0){
						temppoint = fixedpoint1y;
						fixedpoint1y = fixedpoint2y;
						fixedpoint2y = temppoint;
					}
					img = src(Range(fixedpoint1y + InterSpace / 2, fixedpoint2y - InterSpace / 2), Range(fixedpoint1x + InterSpace / 2, fixedpoint2x - InterSpace / 2));
					img = src(Range(1313 + 4 / 2, 1315 - 2 / 2), Range(fixedpoint1x + InterSpace / 2, fixedpoint2x - InterSpace / 2));
					imwrite(filespicpath + "\\" + Pic2Diction[0], img);
				}
			}

			if (list[filestep][0] = 3){
				MessageBox(TEXT("Not ready yet!"), TEXT("Error"), MB_OK);
			}

		}
	}
}
//excel输入 并重命名tif

void CpicV4Dlg::OnBnClickedButtonCopytifs()
{
	// TODO:  在此添加控件通知处理程序代码 载入box文件

	//std::string strStl = "test";	//string转cstring
	////CString strMfc = strStl.c_str();
	//CString wstg3(strStl.c_str());
	//SetDlgItemText(IDC_EDIT, wstg3);

	//CString asda;	//cstring转string
	//GetDlgItemText(IDC_EDIT, asda);
	//char *chr = new char[asda.GetLength() + 1];
	//WideCharToMultiByte(CP_ACP, 0, asda.GetBuffer(), -1, chr, asda.GetLength() + 1, NULL, NULL);
	//string pathName = chr;

	ifstream in;
	in.open("E:\\1.box");
	//ofstream out;
	//out.open("E:\\2.txt");
	string feature;
	string filename;
	string line;
	wstring wline;
	string PosX;	//左上角
	string PosY;	//左上角
	string PosWidth;	//宽
	string PosHeight;	//高

	int spacewhere[5];
	for (int spacestep = 0; spacestep < 5; spacestep++){
		spacewhere[spacestep] = 0;
	}
	int space_at = 0;
	string ShowAllChar = "";
	if (in) // 有该文件
	{
		while (getline (in, line)) // line中不包括每行的换行符
		{
			char* pic_path = new char[line.length() + 1];	//string转char*
			strcpy(pic_path, line.c_str());
			for (int spacestep = 0; spacestep < 5; spacestep++){
				spacewhere[spacestep] = 0;
			}
			space_at = 0;
			for (int i = 0; pic_path[i]; i++){
				if (pic_path[i] == ' '){
					spacewhere[space_at] = i;
					space_at++;
				}
			}
			string feature(line.substr(0, spacewhere[0]));
			string PosX(line.substr(spacewhere[0] + 1, spacewhere[1] - 1 - spacewhere[0]));
			string PosY(line.substr(spacewhere[1] + 1, spacewhere[2] - 1 - spacewhere[1]));
			string PosWidth(line.substr(spacewhere[2] + 1, spacewhere[3] - 1 - spacewhere[2]));
			string PosHeight(line.substr(spacewhere[3] + 1, spacewhere[4] - 1 - spacewhere[3]));
			////out  << line  << endl; // 输入到2.txt中  
			ShowAllChar += feature + " ";
		}
		wstring wstg3(ShowAllChar.begin(), ShowAllChar.end());
		MessageBox(wstg3.c_str(), TEXT("更改后文件名"), MB_OK);
	}
	else // 没有该文件  
	{
		MessageBox(TEXT("no such file"), TEXT("ERROR"), MB_OK);
	}
 	in.clear();
}
//整合tif文件

void CpicV4Dlg::OnBnClickedButton5Backtotrain()
{
		//string Retrainfile = "C:/Users/OtntO/Desktop/opencv/training samples/test2/IMG_0006.JPEG";
		//BackToTrain.push_back(Retrainfile);
	if (haveCExtPath && BackToTrain.size()!=0){
		int s = 0, d = 0,s2=0,d2=0, j = 0;
		/////////////////////////////////////////////////////////
		//////////先复制pic
		for (unsigned int i = 0; i < BackToTrain.size(); i++){
			j = 0;
			char* OriTrFile; //string BackToTrain转char 
			const int OriTrFilelen = BackToTrain[i].length();
			OriTrFile = new char[OriTrFilelen + 1];
			strcpy(OriTrFile, BackToTrain[i].c_str());

			string SExtMtrPath;//char 输出地址转string
			stringstream stream;
			stream << ExtMtrPath;

			for (int k = 0; OriTrFile[k]; k++){ //从Char寻找文件名
				if (OriTrFile[k] == '/'){
					j = k;
				}
			}

			string FiName(BackToTrain[i].substr(j + 1, strlen(OriTrFile) - j - 1-5));//-5=".jpeg"
			SExtMtrPath = stream.str() + slash + FiName+".jpeg";
//			wstring WSExtMtrPath(SExtMtrPath.begin(), SExtMtrPath.end());//string 转 LPCTSTR
//			MessageBox(WSExtMtrPath.c_str(), TEXT("输出路径与文件名"), MB_OK);

			char* CExtMtrPath; //string 改后输出地址转char 
			const int CExtMtrPathlen = SExtMtrPath.length();
			CExtMtrPath = new char[CExtMtrPathlen + 1];
			strcpy(CExtMtrPath, SExtMtrPath.c_str());

			if (CopyFile(OriTrFile, CExtMtrPath))//记录
			{
				s++;
			}
			else
			{
				d++;
			}
			///////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////
			////复制同pic文件名的BOX扩展名文件
			j = 0;
			for (int ij = 0; OriTrFile[ij]; i++){ //从Char寻找最末扩展名
				if (OriTrFile[ij] == '.'){
					j = ij;
				}
			}
			string SBoxOriTrFile(BackToTrain[i].substr(0, j));
			SBoxOriTrFile += ".box";//修改后的原始box地址与文件名
//			wstring asdth(SBoxOriTrFile.begin(), SBoxOriTrFile.end());//string 转 LPCTSTR
//			MessageBox(asdth.c_str(), TEXT("输入BOX路径与文件名"), MB_OK);

			char* BoxOriTrFile; //string SBoxOriTrFile转char 
			const int BoxOriTrFilelen = SBoxOriTrFile.length();
			BoxOriTrFile = new char[BoxOriTrFilelen + 1];
			strcpy(BoxOriTrFile, SBoxOriTrFile.c_str());

			string SBOXExtMtrPath;//输出地址与文件名修改
			SBOXExtMtrPath = stream.str() + slash + FiName + ".box"; 
//			wstring WSBOXExtMtrPath(SBOXExtMtrPath.begin(), SBOXExtMtrPath.end());//string 转 LPCTSTR
//			MessageBox(WSBOXExtMtrPath.c_str(), TEXT("输出BOX路径与文件名"), MB_OK);

			char* CBOXExtMtrPath; //string 改后输出地址转char 
			const int CBOXExtMtrPathlen = SBOXExtMtrPath.length();
			CBOXExtMtrPath = new char[CBOXExtMtrPathlen + 1];
			strcpy(CBOXExtMtrPath, SBOXExtMtrPath.c_str());

			if (CopyFile(BoxOriTrFile, CBOXExtMtrPath))//记录
			{
				s2++;
			}
			else
			{
				d2++;
			}
			/////////////////////////////////////////////////////////
		}
		CString CopyBOXResult;
		CopyBOXResult.Format(_T("成功创建%d个pic,%d个box;失败%d个pic,%d个box"), s, s2, d, d2);
		LPCTSTR pCopyBOXResult = LPCTSTR(CopyBOXResult);
		MessageBox(pCopyBOXResult, TEXT("结果"), MB_OK);
	}
	else{
		if (!haveCExtPath){
			MessageBox(TEXT("先选择外训练材料文件夹"), TEXT("ERROR"), MB_OK);
		}
		if (BackToTrain.size() == 0){
			MessageBox(TEXT("没有加入外训练库的资料"), TEXT("ERROR"), MB_OK);
		}
	}
}
//新字库复制（Vector BackToTrain）
void CpicV4Dlg::OnBnClickedButtonRetraining()
{
	if (haveCExtPath){
		int s = 0;
		int d = 0;
		TempFile.clear();//clean vector
		commandcommand.clear();
		language.clear();

		stringstream streamEXT;//clean files
		streamEXT << ExtMtrPath;
		string CleanOldFile;
		string cdfile = "@echo off & cd " + streamEXT.str() + " & ";
		CleanOldFile = "del *.inttemp *.txt *.normproto *.pffmtable *.unicharset *.shapetable inttemp normproto pffmtable unicharset shapetable";


		getFiles(ExtMtrPath, "jpeg", TempFile);
		int sizetemp = TempFile.size();
		string Training;	//echo Run Tesseract for Training..	tesseract.exe num.font.exp0.jpeg num.font.exp0 nobatch box.train	tesseract.exe num.font.exp1.JPEG num.font.exp1 nobatch box.train
		string unicharset;	//Compute the Character Set..	unicharset_extractor.exe num.font.exp0.box num.font.exp1.box
		unicharset = "unicharset_extractor.exe ";
		string mftraining;	//Compute the Character Set..	mftraining -F font_properties -U unicharset -O num.unicharset num.font.exp0.tr num.font.exp1.tr
		mftraining = "mftraining -F font_properties -U unicharset -O ";
		string cntraining;	//echo Clustering..	cntraining.exe num.font.exp0.tr num.font.exp1.tr
		cntraining = "cntraining.exe ";
		string rename;	//echo Rename Files..	rename normproto num.normproto	rename inttemp num.inttemp	rename pffmtable num.pffmtable	rename shapetable num.shapetable
		rename = "";
		string combine;	//echo Create Tessdata..	combine_tessdata.exe num.
		combine = "combine_tessdata.exe ";

		//int systemcommandlen;// = CleanOldFile.length();//string转char*
		//char *Csystemcommand;// = new char[systemcommandlen + 1];
		////strcpy(Csystemcommand, CleanOldFile.c_str());
		////system(Csystemcommand);
		Training = cdfile + CleanOldFile + " & ";
		for (int i = 0; i < sizetemp; i++){ //get all language.set unicharset,mftraining,cntraining,rename,combine syscommand.get .tr
			string allfilename(TempFile[i].substr(strlen(ExtMtrPath) + 1, strlen((TempFile[i].c_str())) - strlen(ExtMtrPath) - 1));//"num.font.exp0.jpeg"
			//wstring wstzxc0(allfilename.begin(), allfilename.end()); //string转换LPCTSTR
			//MessageBox(wstzxc0.c_str(), TEXT("文件名"), MB_OK);		
			string filename(TempFile[i].substr(strlen(ExtMtrPath) + 1, strlen((TempFile[i].c_str())) - strlen(ExtMtrPath) - 1 - 5));//"num.font.exp0"
			//wstring wstzxc1(filename.begin(), filename.end()); //string转换LPCTSTR
			//MessageBox(wstzxc1.c_str(), TEXT("文件名"), MB_OK);
			string langutype(TempFile[i].substr(strlen(ExtMtrPath) + 1, 3));//"num"
			//wstring wstzxc2(langutype.begin(), langutype.end()); //string转换LPCTSTR
			//MessageBox(wstzxc2.c_str(), TEXT("文件名"), MB_OK);
			//		string typeNo(TempFile[i].substr(strlen(ExtMtrPath) + 1+9, strlen((TempFile[i].c_str())) - strlen(ExtMtrPath) - 1 - 9-5));//"exp0"
			//wstring wstzxc3(typeNo.begin(), typeNo.end()); //string转换LPCTSTR
			//MessageBox(wstzxc3.c_str(), TEXT("文件名"), MB_OK);
			Training += "tesseract.exe " + allfilename + " " + filename + " nobatch box.train" + " & "; // 1.Create *.tr	//可替换加速语句
			//Training = "cd " + streamEXT.str() + " & tesseract.exe " + allfilename + " " + filename + " nobatch box.train"; // 1.Create *.tr 原始语句
			//wstring wstz3(Training.begin(), Training.end()); //string转换LPCTSTR
			//MessageBox(wstz3.c_str(), TEXT("文件名"), MB_OK);
			//int systemcommandlen = Training.length();//string转char*	//原始语句
			//char *Csystemcommand = new char[systemcommandlen + 1];	//原始语句
			//strcpy(Csystemcommand, Training.c_str());	//原始语句
			//system(Csystemcommand);	//原始语句

			int checkposition = 0; // 遍历language
			for (unsigned int j = 0; j < language.size(); j++){
				if (langutype == language[j]){
					checkposition = j;
				}
			}
			if (checkposition == 0){ //没有则创建,有则添加file
				language.push_back(langutype);
				commandcommand.push_back(unicharset);
				commandcommand.push_back(mftraining);
				commandcommand.push_back(cntraining);
				commandcommand.push_back(rename);
				commandcommand.push_back(combine);
				commandcommand[(5 * language.size() + 0 - 5)] += filename + ".box";
				//wstring wstzxc0(commandcommand[(5 * language.size() + 1)].begin(), commandcommand[(5 * language.size() + 1)].end()); //string转换LPCTSTR
				//MessageBox(wstzxc0.c_str(), TEXT("文件名"), MB_OK);	
				commandcommand[(5 * language.size() + 1 - 5)] += langutype + ".unicharset " + filename + ".tr";
				//wstring wstzxc1(commandcommand[(5 * language.size() + 2)].begin(), commandcommand[(5 * language.size() + 2)].end()); //string转换LPCTSTR
				//MessageBox(wstzxc1.c_str(), TEXT("文件名"), MB_OK);	
				commandcommand[(5 * language.size() + 2 - 5)] += filename + ".tr";
				//wstring wstzxc2(commandcommand[(5 * language.size() + 3)].begin(), commandcommand[(5 * language.size() + 3)].end()); //string转换LPCTSTR
				//MessageBox(wstzxc2.c_str(), TEXT("文件名"), MB_OK);	
				commandcommand[(5 * language.size() + 3 - 5)] += "rename normproto " + langutype + ".normproto & " + "rename inttemp " + langutype + ".inttemp & " + "rename pffmtable " + langutype + ".pffmtable & " + "rename shapetable " + langutype + ".shapetable";
				//wstring wstzxc3(commandcommand[(5 * language.size() + 4)].begin(), commandcommand[(5 * language.size() + 4)].end()); //string转换LPCTSTR
				//MessageBox(wstzxc3.c_str(), TEXT("文件名"), MB_OK);	
				commandcommand[(5 * language.size() + 4 - 5)] += langutype + ".";
				//wstring wstzxc4(commandcommand[(5 * language.size() + 5)].begin(), commandcommand[(5 * language.size() + 5)].end()); //string转换LPCTSTR
				//MessageBox(wstzxc4.c_str(), TEXT("文件名"), MB_OK);	
			}
			else{
				checkposition;
				commandcommand[(5 * checkposition)] += " " + filename + ".box";
				commandcommand[(5 * checkposition + 1)] += " " + filename + ".tr";
				commandcommand[(5 * checkposition + 2)] += " " + filename + ".tr";
			}
		}

		//int systemcommandlen = Training.length();//string转char*	//可替换加速语句
		//char *Csystemcommand = new char[systemcommandlen + 1];	//可替换加速语句
		//strcpy(Csystemcommand, Training.c_str());	//可替换加速语句
		//if (system(Csystemcommand) + 1){	//可替换加速语句
		//	d++;	//可替换加速语句
		//}	//可替换加速语句
		//wstring wstTraining(Training.begin(), Training.end()); //string转换LPCTSTR
		//MessageBox(wstTraining.c_str(), TEXT("文件名"), MB_OK);
		//for (int ki = 0; ki < language.size(); ki++){ //执行指令，生成字库		//原始语句
		//for (int kj = 0; kj < 5; kj++){	//原始语句
		//	int comcomlen = commandcommand[5 * ki + kj].length();//string转char*//原始语句
		//	char *Ccomcomlen = new char[comcomlen + 1];//原始语句
		//	strcpy(Ccomcomlen, commandcommand[5 * ki + kj].c_str());//原始语句
		//	if (system(Ccomcomlen)+1){//原始语句
		//		s++;//原始语句
		//	}//原始语句
		//	else{//原始语句
		//		d++;//原始语句
		//	}//原始语句
		//}//原始语句
		//	system(clearcommand);//clear for each language type//原始语句
		//}//原始语句

		string allto = Training; //执行指令，生成字库 //可替换加速运行
		for (unsigned int ki = 0; ki < commandcommand.size(); ki++){	//可替换加速运行	//合并命令行
			allto += commandcommand[ki] + " & ";//可替换加速运行
			if ((ki + 1) % 5 == 0){//可替换加速运行
				allto += CleanOldFile + " & ";		//可替换加速运行
			}//可替换加速运行
		}//可替换加速运行
		allto += "pause";
		///////////////////////////////////////////////////////////////检查指令
		//wstring wstallto(allto.begin(), allto.end()); //string转换LPCTSTR
		//MessageBox(wstallto.c_str(), TEXT("文件名"), MB_OK);
		////////////////////////////////////////////////////////////////////

		int alltolen = allto.length();//string转char* 执行commandcommand指令//可替换加速运行
		char *Calltolen = new char[alltolen + 1];//可替换加速运行
		strcpy(Calltolen, allto.c_str());//可替换加速运行
		if (system(Calltolen) + 1){//可替换加速运行
			s++;//可替换加速运行
		}
		else{
			d++;
		}//可替换加速运行


		////////////////////////////////////////////////////////////////////////////////////
		//////////////复制并替换字库
		string langutypepath;// (TempFile[i].substr(0, strlen(ExtMtrPath) + 1 + 3));//"../num"
		int s2 = 0, d2 = 0;
		for (int jkl = 0; jkl < language.size(); jkl++){
			langutypepath = streamEXT.str() + "\\" + language[jkl] + ".traineddata";
			//wstring wstlangutypepatho(langutypepath.begin(), langutypepath.end()); //string转换LPCTSTR
			//MessageBox(wstlangutypepatho.c_str(), TEXT("文件名"), MB_OK);

			char* fileposi; //string to char* 原始地址
			const int fileposilen = langutypepath.length();
			fileposi = new char[fileposilen + 1];
			strcpy(fileposi, langutypepath.c_str());

			stringstream streamTes;//char目标地址转string修改
			string Tespaaath;
			streamTes << TesOcrPath;
			Tespaaath = streamTes.str() + "\\" + "tessdata" + "\\" + language[jkl] + ".traineddata";
			//wstring wstlanguTespaaath(Tespaaath.begin(), Tespaaath.end()); //string转换LPCTSTR
			//MessageBox(wstlanguTespaaath.c_str(), TEXT("文件名"), MB_OK);
			char* filetoposi; //string to char* tess目标地址
			const int filetoposilen = Tespaaath.length();
			filetoposi = new char[filetoposilen + 1];
			strcpy(filetoposi, Tespaaath.c_str());

			if (CopyFile(fileposi, filetoposi))//记录
			{
				s2++;
			}
			else
			{
				d2++;
			}
		}
		////////////////////////////////////////////////////////////////////////////////
		CString BacktrainResult;
		BacktrainResult.Format(_T("成功执行%d指令,失败%d指令;替换成功%d个trainneddata,替换失败%d个trainneddata"), s, d, s2, d2);	//可替换加速运行
		//BacktrainResult.Format(_T("成功执行%d个命令，失败%d个命令，生成了%d个训练文件"), s, d, s / 5);//原始语句
		LPCTSTR pBacktrainResultt = LPCTSTR(BacktrainResult);
		MessageBox(pBacktrainResultt, TEXT("结果"), MB_OK);
	}
	else{
		if (!haveCExtPath){
			MessageBox(TEXT("先选择外训练材料文件夹"), TEXT("ERROR"), MB_OK);
		}
	}
}
//重训练字库并替换traindata

//生成字库//void changename(){
//	int s = 0;
//	int d = 0;
//	for (int i = 0; i < size; i++) //files[i]
//	{
//		////////////////////////////////////////////////
//		///int转换string
//		stringstream ss;//int i 转换 string ADDNAME
//		string ADDNAME;
//		ss << i;
//		ss >> ADDNAME;
//		///////////////////////////////////////////////
//
//		string newname = CtargetPath + slash + ADDNAME + ".jpeg";//更改的文件名=.../.../ADDNAME.jpeg
//
//		//////////////////////////////////////////////////////预命名与原始文件地址+名称 以messagebox显示
//		wstring ChangeN2(newname.begin(), newname.end()); //string转换LPCTSTR
//		MessageBox(ChangeN2.c_str(), TEXT("更改后文件名"), MB_OK);
//		wstring ChangeN1(files[i].begin(), files[i].end()); //file[i] 文件地址集转换LPCTSTR
//		MessageBox(ChangeN1.c_str(), TEXT("原始文件名"), MB_OK);
//		//////////////////////////////////////////////////////////
//
//		///////////////////////////////////////////
//		//////////////////////////string转换LPCTSTR
//		//wstring wstg(files[i].begin(), files[i].end()); //file[i] 文件地址集转换LPCTSTR
//		///////////////////////////////////////////
//		//GetDlgItem(IDC_STATIC_NEW)->SetWindowText(wstg.c_str());//IDC_STATIc_NEW中显示路径
//		//MessageBox(wstg.c_str(), TEXT("Title"), MB_OK);//消息提示路径
//
//		/////////////////////////////////////////////
//		/////////rename 文件名
//		char *p = new char[files[i].size() + 1];
//		strcpy(p, files[i].c_str());
//		char *q = new char[newname.size() + 1];
//		strcpy(q, newname.c_str());
//		if (rename(p, q) + 1){
//			s++;
//		}
//		else{
//			d++;
//		}
//		/////////////////////////////////////////////
//	}
//	CString CResult;
//	CResult.Format(_T("成功创建%d个文件夹，失败%d个"), s, d);
//	LPCTSTR pCResult = LPCTSTR(CResult);
//	MessageBox(pCResult, TEXT("结果"), MB_OK);
//}

//void CpicV4Dlg::OnBnClickedButton2() 
//{
//	int s = 0;
//	int d = 0;
//	if (havePath){
//		havefile = 1;
//		for (int i = 0; i < sizeof(CPfile) / sizeof(CPfile[0]); i++){
//			string tempfile = "temp";
//			//			wstring CPwstzxc(CPFILEPATH.begin(), CPFILEPATH.end()); //string转换LPCTSTR
//			//					MessageBox(CPwstzxc.c_str(), TEXT("创建文件名"), MB_OK);
//			string CPFILEPATH = Ctar + slash + tempfile;
//			int flag0 = mkdir(CPFILEPATH.c_str());
//			CPFILEPATH = Ctar + slash + tempfile + slash + CPfile[i];
//			int flag = mkdir(CPFILEPATH.c_str());
//			if (flag != 0)
//			{
//				//				wstring CPwstzxc(CPFILEPATH.begin(), CPFILEPATH.end()); //string转换LPCTSTR
//				//				MessageBox(CPwstzxc.c_str(), TEXT("创建失败"), MB_OK);
//				++d;
//			}
//			else{
//				++s;
//			}
//
//		}
//		CString CResult;
//		CResult.Format(_T("成功创建%d个文件夹，失败%d个"), s, d);
//		LPCTSTR pCResult = LPCTSTR(CResult);
//		MessageBox(pCResult, TEXT("结果"), MB_OK);
//	}
//	else {
//		MessageBox(TEXT("先选择文件夹"), TEXT("ERROR"), MB_OK);
//	}
//}
//static string CPfile[] = { "asd", "asdd", "asfd", "avcvv" };

//void CpicV4Dlg::OnBnClickedButtonListinfo()//图片类型分类
//{
//	// TODO:  在此添加控件通知处理程序代码
//	CString FilePath;
//
//	CFileDialog FileDlg(TRUE);
//
//	if (IDOK == FileDlg.DoModal())
//	{
//		////获取FileOpen对话框返回的路径名  
//		//FilePath = FileDlg.GetPathName();
//
//		////GetPathName返回的是CString类型，要经过转换为string类型才能使用imread打开图片  
//		//char *chr = new char[FilePath.GetLength() + 1];	//unicode cstring 转string
//		//WideCharToMultiByte(CP_ACP, 0, FilePath.GetBuffer(), -1, chr, FilePath.GetLength() + 1, NULL, NULL);
//
//		//读取图片
//		string pathName = chr;
//		cv::Mat orgImg = cv::imread(pathName);
//
//		//显示图片 
//		ShowMat(orgImg, GetDlgItem(IDC_STATIC_0)->GetSafeHwnd());	//修改背景图片
//		//ShowMat(orgImg, GetDlgItem(IDC_STATIC_ORI)->GetSafeHwnd());	//原始修改图片
//		//ShowMat(orgImg, GetDlgItem(IDC_STATIC_1)->GetSafeHwnd());	//图片集第1个
//		//ShowMat(orgImg, GetDlgItem(IDC_STATIC_2)->GetSafeHwnd());	//图片集第2个
//		//ShowMat(orgImg, GetDlgItem(IDC_STATIC_3)->GetSafeHwnd());	//图片集第3个
//		//ShowMat(orgImg, GetDlgItem(IDC_STATIC_4)->GetSafeHwnd());	//图片集第4个
//		//ShowMat(orgImg, GetDlgItem(IDC_STATIC_5)->GetSafeHwnd());	//图片集第5个
//	}
//}
//图片类型分类

//void CpicV4Dlg::OnBnClickedButtonNext()	//多尺度霍夫变换
//{
//	// TODO:  在此添加控件通知处理程序代码
//	string pathName = "C:\\Users\\ZK-PC\\Desktop\\training samples\\sample4.JPeG";	//图片地址
//	cv::Mat src = cv::imread(pathName, IMREAD_UNCHANGED);	//Mat读取图片 & Unchanged
//	cv::Mat img;
//
//
//	cvtColor(src, img, CV_RGB2GRAY);
//	GaussianBlur(img, img, Size(3, 3), 0, 0);
//	Canny(img, img, 100, 200, 3);
//
//	//int GaussKernalSize = 3; Mat G_kernel = getGaussianKernel(GaussKernalSize, 0.3*((GaussKernalSize - 1)*0.5 - 1) + 0.8);	//高斯滤波
//	//filter2D(src, img, -1, G_kernel);
//	//cvtColor(img, img, CV_BGR2GRAY); //灰度化处理	imread->( ,IMREAD_UNCHANGED)
//	//sobelTIDU(img, img); //Sobel算子边缘检测
//
//	vector<Vec2f> lines;
//	HoughLines(img, lines, 1, CV_PI / 180 / 2 / 5, 80, 0, 0);  // 返回直线坐标对
//	for (size_t i = 0; i<lines.size(); i++) {
//		float rho = lines[i][0];
//		float theta = lines[i][1];
//		Point pt1, pt2;
//		double a = cos(theta);
//		double b = sin(theta);
//		double x0 = rho*a;
//		double y0 = rho*b;
//		pt1.x = cvRound(x0 + 1000 * (-b));
//		pt1.y = cvRound(y0 + 1000 * a);
//		pt2.x = cvRound(x0 - 1000 * (-b));
//		pt2.y = cvRound(y0 - 1000 * a);
//		line(src, pt1, pt2, Scalar(55, 100, 195), 1);
//	}
//
//	//cvtColor(src, src, CV_GRAY2BGR);
//	cvtColor(img, img, CV_GRAY2BGR);
//
//	ShowMat(img, GetDlgItem(IDC_STATIC_0)->GetSafeHwnd());	//显示图片	//修改背景图片
//	ShowMat(src, GetDlgItem(IDC_STATIC_ORI)->GetSafeHwnd());	//原始修改图片
//	//	ShowMat(ResultImg, GetDlgItem(IDC_STATIC_1)->GetSafeHwnd());	//图片集第1个
//	//	ShowMat(ResultImg, GetDlgItem(IDC_STATIC_2)->GetSafeHwnd());	//图片集第2个
//	//	ShowMat(ResultImg, GetDlgItem(IDC_STATIC_3)->GetSafeHwnd());	//图片集第3个
//	//	ShowMat(ResultImg, GetDlgItem(IDC_STATIC_4)->GetSafeHwnd());	//图片集第4个
//	//	ShowMat(ResultImg, GetDlgItem(IDC_STATIC_5)->GetSafeHwnd());	//图片集第5个
//}

//CButton* pButtonLoadbox = (CButton*)GetDlgItem(IDC_BUTTON_LoadBox);	//IDC_Button
//pButtonLoadbox->EnableWindow(FALSE);	//当开始的时候,按钮不可用
//int ProcessTimes = circles.size();	//Progress显示处理过程
//ProgPos = 0; pProg->SetRange(0, ProcessTimes - 1);	//Process初始化
//for (ProgPos; ProgPos < ProcessTimes; ProgPos++)
//	pProg->SetPos(ProgPos);
////MessageBox(TEXT("完成"), TEXT("处理结果"), MB_OK);
//pProg->SetPos(0);
//pButtonLoadbox->EnableWindow(TRUE);

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////直线检测-HoughLinesP
//////GaussianBlur(img, img, Size(9, 9), 3,3);
////Canny(src, img, 100, 200, 3); 
////cvtColor(img, img, CV_GRAY2RGB);
//GaussianBlur(img, img, Size(5, 5), 0, 0);
//cvtColor(src, img, CV_BGR2GRAY); //灰度化处理	imread->( ,IMREAD_UNCHANGED)
//sobelTIDU(img, img); //Sobel算子边缘检测
//threshold(img, img, threshold_num, threshold_max, THRESH_BINARY_INV);//二值图处理
//img = img < 127;//二值图翻转颜色
//vector<Vec4i> lines;//HoughLinesP 累计概率霍夫变换 线段检测
////HoughLinesP(img, lines, 1, CV_PI / 180 / 10, 320, 480, 60); //rho,theta,threshold, minLineLength, maxLineGap)
//HoughLinesP(img, lines, 1, CV_PI / 180 / 5, 450, 480, 160); //所有横线
////HoughLinesP(img, lines, 1, CV_PI / 180 /10 , 800/4, 160/4, 100/4); //rho,theta,threshold, minLineLength, maxLineGap)
//for (size_t i = 0; i < lines.size(); i++)
//{
//	Vec4i l = lines[i];
//	line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 0), 1);
//}
////cvtColor(src, src, CV_GRAY2BGR);
////imshow("结果", img);
////imshow("结果2", src);
//cvtColor(img, img, CV_GRAY2BGR);
//////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////圆检测-HoughCircles 已调试
////cvtColor(src, img, CV_BGR2GRAY);//转化边缘检测后的图为灰度图
////GaussianBlur(img, img, Size(5, 5), 0, 0);
////vector<Vec3f> circles;	//进行霍夫圆变换
////HoughCircles(img, circles, CV_HOUGH_GRADIENT, 1.5, 10000, 200, 2*CV_PI*100*5/9, 100 * 5, 300 * 5);  // http://blog.csdn.net/zhaocj/article/details/50454847
////for (size_t i = 0; i < circles.size(); i++)//依次在图中绘制出圆
////{
////	Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
////	int radius = cvRound(circles[i][2]);		//绘制圆心
////	circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);		//绘制圆轮廓
////	circle(src, center, radius, Scalar(155, 50, 255), 3, 8, 0);
////}
/////*cvtColor(src, src, CV_GRAY2BGR);*/
////cvtColor(img, img, CV_GRAY2BGR);
////////////////////////////////////////////////////////////////////////////////////////////////


void CpicV4Dlg::MyCvtColor(Mat& src)
{
	int l;
	for (int i = 0; i<src.rows; i++)
	{
		for (int j = 0; j<src.cols; j++)
		{
			l = 0;
			for (int k = 0; k < 3; k++)
			{
				l+=src.at<Vec3b>(i, j)[k];

			}
			if (l < 200){
				for (int k = 0; k < 3; k++)
				{
					src.at<Vec3b>(i, j)[k]=0;

				}
			}
			else{
				for (int k = 0; k < 3; k++)
				{
					src.at<Vec3b>(i, j)[k] = 255;

				}
			}
		}
	}
} 
//自制算法
void CpicV4Dlg::sobelTIDU(cv::Mat src, cv::Mat& res)
{
	//Sobel算子（x方向和y方向）
	Mat sobel_x, sobel_y;
	Sobel(src, sobel_x, CV_16S, 1, 0, 3);
	Sobel(src, sobel_y, CV_16S, 0, 1, 3);
	Mat abs_x, abs_y;
	convertScaleAbs(sobel_x, abs_x);
	convertScaleAbs(sobel_y, abs_y);
	addWeighted(abs_x, 0.5, abs_y, 0.5, 0, res);
}
//sobel算法


void CpicV4Dlg::OnBnClickedButton15()
{
	// TODO: Add your control notification handler code here
	//string filesnames = "C:\\Users\\ZK-PC\\Desktop\\training samples\\test\\num.font.exp0.JPEG";
	//string filespicpath = "C:\\Users\\ZK-PC\\Desktop\\training samples\\test";
	//Mat src = imread(filesnames, IMREAD_ANYCOLOR);
	//Mat img;
	//imwrite(filespicpath + "\\asdasd.jpeg", src);
	files.clear();//初始化files,list.
	getFiles(CtargetPath, "jpeg", files);
	size = files.size();
	list[size][2];//重置list,list[i][0]=图片类型，[i][1]=Tif分类

	for (int i = 0; i < size; i++){
		list[i][0] = 0;
		list[i][1] = 0;
	}
	list[0][0] = 2;
	list[0][1] = 1;
	Mat src;
	Mat img;
	vector<Vec4i> lines;
	Vec4i BorderXline;
	Vec4i BorderYline;
	int fourpoint[4][2];
	Vec4i l;
	int SecPosX;
	int SecPosY;
	int dist = 0, disttoplineX = 0, disttoplineY = 0;
	list[0][0] = 2;
	int InterSpace = 4;
	for (int filestep = 0; filestep < files.size(); filestep++){	//切割files里图片
		string filenames = files[filestep];
		src = cv::imread(filenames, IMREAD_ANYCOLOR);	//Mat读取图片地址 & Unchanged
		if (list[filestep][0] != 4){
			for (int foursection = 0; foursection < 4; foursection++){	//扫描图片外四点
				img = src(Range(src.rows / 4 * 3 * (foursection / 2), src.rows / 4 * 3 * (foursection / 2) + src.rows / 4), Range(src.cols / 4 * 3 * ((foursection + 2) % 2), src.cols / 4 * 3 * ((foursection + 2) % 2) + src.cols / 4));	//第一个range是行始终，第二个是列始终
				
				for (int j0 = 0; j0 < 4; j0++){	//初始化toppestline
					BorderXline[j0] = 0;
				}
				for (int j1 = 0; j1 < 4; j1++){	//初始化toppestline
					BorderYline[j1] = 0;
				}
				if (foursection == 0){
					BorderXline[1] = src.rows;
					BorderYline[0] = src.cols;
				}
				if (foursection == 1){
					BorderXline[3] = src.rows;
					BorderYline[0] = 0;
				}
				if (foursection == 2){
					BorderXline[1] = 0;
					BorderYline[2] = src.cols;
				}
				if (foursection == 3){
					BorderXline[3] = 0;
					BorderYline[2] = 0;
				}

				/*list[filestep][0]*/
				/*foursection / 2*/	// =0 第一、二个图片  =1 第三、四个图片
				/*foursection / 2*/	//	=0 第一、三个图片	=1	第二、四个图片




				cvtColor(img, img, CV_BGR2GRAY);	//直线检测-HoughLinesP	1.灰度化处理	imread->( ,IMREAD_UNCHANGED)
				sobelTIDU(img, img); //2.Sobel算子边缘检测
				threshold(img, img, threshold_num, threshold_max, THRESH_BINARY_INV);	//3.二值图处理
				img = img < 127;	//4.二值图翻转颜色
				lines.clear();	//5.HoughLinesP 累计概率霍夫变换 线段检测	//初始化lines
				HoughLinesP(img, lines, 1, CV_PI / 180 / 5, 250, 280, 200); //所有横线
				//for (size_t i = 0; i < lines.size(); i++)	//划线显示测试
				//{
				//	Vec4i l = lines[i];
				//	line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 0), 1);
				//}
				//imshow("结果", src);

				float linegradient;
				int tempx = 0, tempy = 0;
				dist = 0; disttoplineX = 0; disttoplineY = 0;
				cvtColor(img, img, CV_GRAY2BGR);

				for (size_t ikl = 0; ikl < lines.size(); ikl++){	//修整线段
					linegradient = ((float)lines[ikl][1] - lines[ikl][3]) / (lines[ikl][0] - lines[ikl][2]);
					if (abs(linegradient) <= 1){
						if (lines[ikl][0] > lines[ikl][2]){
							tempx = lines[ikl][0];
							tempy = lines[ikl][1];
							lines[ikl][0] = lines[ikl][2];
							lines[ikl][1] = lines[ikl][3];
							lines[ikl][2] = tempx;
							lines[ikl][3] = tempy;
						}
					}
					if (abs(linegradient) > 1){
						if (lines[ikl][1] > lines[ikl][3]){
							tempx = lines[ikl][0];
							tempy = lines[ikl][1];
							lines[ikl][0] = lines[ikl][2];
							lines[ikl][1] = lines[ikl][3];
							lines[ikl][2] = tempx;
							lines[ikl][3] = tempy;
						}
					}
				}

				for (size_t ik = 0; ik < lines.size(); ik++)	//扫描线段
				{
					if (foursection == 0){	//第一区域检测
						if (lines[ik][1] < BorderXline[1]){	//寻找最靠上的横线
							l = lines[ik];
							dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
							dist = sqrtf(dist);
							linegradient = ((float)l[1] - l[3]) / (l[0] - l[2]);	//角度小于+-arctan(1/2)
							if (dist > 280 && abs(linegradient) < 0.5){
								for (int fs00 = 0; fs00 < 4; fs00++){
									BorderXline[fs00] = l[fs00];
								}
							}
						}
						if (lines[ik][0] < BorderYline[0]){	//寻找最靠左的横线
							l = lines[ik];
							dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
							dist = sqrtf(dist);
							linegradient = ((float)l[1] - l[3]) / (l[0] - l[2]);	//角度大于-arctan(2)
							if (dist > 280 && abs(linegradient) > 2){
								for (int fs01 = 0; fs01 < 4; fs01++){
									BorderYline[fs01] = l[fs01];
								}
							}
						}
					}

					if (foursection == 1){	//第二区域检测
						if (lines[ik][3] < BorderXline[3]){	//寻找最靠上的横线
							l = lines[ik];
							dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
							dist = sqrtf(dist);
							linegradient = ((float)l[1] - l[3]) / (l[0] - l[2]);	//角度小于+-arctan(1/2)
							if (dist > 280 && abs(linegradient) < 0.5){
								for (int fs10 = 0; fs10 < 4; fs10++){
									BorderXline[fs10] = l[fs10];
								}
							}
						}
						if (lines[ik][0] > BorderYline[0]){	//寻找最靠右的横线
							l = lines[ik];
							dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
							dist = sqrtf(dist);
							linegradient = ((float)l[1] - l[3]) / (l[0] - l[2]);	//角度大于-arctan(2)
							if (dist > 280 && abs(linegradient) > 2){
								for (int fs11 = 0; fs11 < 4; fs11++){
									BorderYline[fs11] = l[fs11];
								}
							}
						}
					}

					if (foursection == 2){	//第三区域检测
						if (lines[ik][1] > BorderXline[1]){	//寻找最靠下的横线
							l = lines[ik];
							dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
							dist = sqrtf(dist);
							linegradient = ((float)l[1] - l[3]) / (l[0] - l[2]);	//角度小于+-arctan(1/2)
							if (dist > 280 && abs(linegradient) < 0.5){
								for (int fs20 = 0; fs20 < 4; fs20++){
									BorderXline[fs20] = l[fs20];
								}
							}
						}
						if (lines[ik][2] < BorderYline[2]){	//寻找最靠左的横线
							l = lines[ik];
							dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
							dist = sqrtf(dist);
							linegradient = ((float)l[1] - l[3]) / (l[0] - l[2]);	//角度大于-arctan(2)
							if (dist > 280 && abs(linegradient) > 2){
								for (int fs21 = 0; fs21 < 4; fs21++){
									BorderYline[fs21] = l[fs21];
								}
							}
						}
					}

					if (foursection == 3){	//第四区域检测
						if (lines[ik][3] > BorderXline[3]){	//寻找最靠下的横线
							l = lines[ik];
							dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
							dist = sqrtf(dist);
							linegradient = ((float)l[1] - l[3]) / (l[0] - l[2]);	//角度小于+-arctan(1/2)
							if (dist > 450 && abs(linegradient) < 0.5){
								for (int fs30 = 0; fs30 < 4; fs30++){
									BorderXline[fs30] = l[fs30];
								}
							}
						}
						if (lines[ik][2] > BorderYline[2]){	//寻找最靠右的横线
							l = lines[ik];
							dist = powf((l[0] - l[2]), 2) + powf((l[1] - l[3]), 2);
							dist = sqrtf(dist);
							linegradient = ((float)l[1] - l[3]) / (l[0] - l[2]);	//角度大于-arctan(2)
							if (dist > 280 && abs(linegradient) > 2){
								for (int fs31 = 0; fs31 < 4; fs31++){
									BorderYline[fs31] = l[fs31];
								}
							}
						}
					}

					//if (foursection=0)	//test
					//imshow("resule1", src(Range(src.rows / 4 * 3 * (foursection / 2), src.rows / 4 * 3 * (foursection / 2) + src.rows / 4), Range(src.cols / 4 * 3 * ((foursection + 2) % 2), src.cols / 4 * 3 * ((foursection + 2) % 2) + src.cols / 4)));
					//if (foursection=1)
					//imshow("resule2", src(Range(src.rows / 4 * 3 * (foursection / 2), src.rows / 4 * 3 * (foursection / 2) + src.rows / 4), Range(src.cols / 4 * 3 * ((foursection + 2) % 2), src.cols / 4 * 3 * ((foursection + 2) % 2) + src.cols / 4)));
					//if (foursection=2)
					//imshow("resule3", src(Range(src.rows / 4 * 3 * (foursection / 2), src.rows / 4 * 3 * (foursection / 2) + src.rows / 4), Range(src.cols / 4 * 3 * ((foursection + 2) % 2), src.cols / 4 * 3 * ((foursection + 2) % 2) + src.cols / 4)));
					//if (foursection=3)
					//imshow("resule4", src(Range(src.rows / 4 * 3 * (foursection / 2), src.rows / 4 * 3 * (foursection / 2) + src.rows / 4), Range(src.cols / 4 * 3 * ((foursection + 2) % 2), src.cols / 4 * 3 * ((foursection + 2) % 2) + src.cols / 4)));
				}
				if (foursection == 0){	//获取端点坐标
					SecPosX = (BorderXline[0] + BorderYline[0]) / 2;
					SecPosY = (BorderXline[1] + BorderYline[1]) / 2;
				}
				if (foursection == 1){
					SecPosX = (BorderXline[2] + BorderYline[0]) / 2;
					SecPosY = (BorderXline[3] + BorderYline[1]) / 2;
				}
				if (foursection == 2){
					SecPosX = (BorderXline[0] + BorderYline[2]) / 2;
					SecPosY = (BorderXline[1] + BorderYline[3]) / 2;
				}
				if (foursection == 3){
					SecPosX = (BorderXline[2] + BorderYline[2]) / 2;
					SecPosY = (BorderXline[3] + BorderYline[3]) / 2;
				}
				fourpoint[foursection][0] = src.cols / 4 * 3 * (foursection % 2) + SecPosX;	//x全局坐标
				fourpoint[foursection][1] = src.rows / 4 * 3 * (foursection / 2) + SecPosY;	//y全局坐标
			}

			/*fourpoint[][];*/	//根据四点切割
			/*list[filestep][0]*/
			string filespicpath = files[filestep].substr(0, files[filestep].size() - 5);	// -5 =".jpeg"
			//LINE(POINT(fourpoint[0][0], fourpoint[0][1]), POINT(fourpoint[1][0], fourpoint[1][1]));
			//LINE(POINT(fourpoint[2][0], fourpoint[2][1]), POINT(fourpoint[3][0], fourpoint[3][1]));
		
			int radius = sqrtf(powf((fourpoint[0][1] - fourpoint[2][1]), 2) + powf((fourpoint[0][0] - fourpoint[2][0]), 2));
			int length = sqrtf(powf((fourpoint[3][1] + fourpoint[1][1]) / 2 - (fourpoint[2][1] + fourpoint[0][1]) / 2, 2) + powf((fourpoint[3][0] + fourpoint[1][0]) / 2 - (fourpoint[0][0] + fourpoint[2][0]) / 2, 2));
			//int length = sqrt(abs((fourpoint[3][1] + fourpoint[1][1]) / 2 - (fourpoint[2][1] + fourpoint[0][1]) / 2) ^ 2 + abs((fourpoint[3][0] + fourpoint[1][0]) / 2 - (fourpoint[0][0] + fourpoint[2][0]) / 2) ^ 2);
			int x1 = (fourpoint[3][0] + fourpoint[1][0]) / 2;
			int y1 = (fourpoint[1][1] + fourpoint[3][1]) / 2;
			int x0 = (fourpoint[0][0] + fourpoint[2][0]) / 2;
			int y0 = (fourpoint[0][1] + fourpoint[2][1]) / 2;
			float theta0 = atan((fourpoint[0][1] - fourpoint[2][1]) / (fourpoint[0][0] - fourpoint[2][0]));
			float dtheta = (atan(((float)fourpoint[1][1] - fourpoint[3][1]) / (fourpoint[1][0] - fourpoint[3][0])) - atan((fourpoint[0][1] - fourpoint[2][1]) / (fourpoint[0][0] - fourpoint[2][0]))) / (x1 - x0);
			float r0 = sqrtf(powf(fourpoint[0][1] - fourpoint[2][1], 2) + powf(fourpoint[0][0] - fourpoint[2][0], 2)) / 2;
			//float r0 = sqrt(abs(fourpoint[0][1] - fourpoint[2][1]) ^ 2 + abs(fourpoint[0][0] - fourpoint[2][0]) ^ 2) / 2;
			float dr = (sqrtf(powf(fourpoint[1][1] - fourpoint[3][1], 2) + powf(fourpoint[1][0] - fourpoint[3][0], 2)) / 2 - sqrtf(powf(fourpoint[0][1] - fourpoint[2][1], 2) + powf(fourpoint[0][0] - fourpoint[2][0], 2)) / 2) / (x1 - x0);
			//float dr = (sqrt(abs(fourpoint[1][1] - fourpoint[3][1]) ^ 2 + abs(fourpoint[1][0] - fourpoint[3][0]) ^ 2) / 2 - sqrt((abs(fourpoint[0][1] - fourpoint[2][1]) ^ 2 + abs(fourpoint[0][0] - fourpoint[2][0]) ^ 2)) / 2) / (x1 - x0);
			float kx, ky;
			if (list[filestep][0] = 2){
				for (int stepstep = 0; stepstep < 24; stepstep++){	//Pic2Ratio[25][2][2]
					kx = Pic2Ratio[stepstep][0][0];
					ky = Pic2Ratio[stepstep][0][1];
					float asc = (r0+dr*(x1 - x0)*kx)*ky;
					float asda = theta0 + dtheta*(x1 - x0)*kx/PI*180;
					float fixedpoint1x = (x1 - x0)*kx + x0 + (r0 + dr*(x1 - x0)*kx)*ky*cos(theta0 + dtheta*(x1 - x0)*kx);
					float fixedpoint1y = y0 - (y0 - y1)*kx + (r0 + dr*(x1 - x0)*kx)*ky*cos(theta0 + dtheta*(x1 - x0)*kx);
					kx = Pic2Ratio[stepstep][1][0];
					ky = Pic2Ratio[stepstep][1][1];
					float fixedpoint2x = (x1 - x0)*kx + x0 + (r0 + dr*(x1 - x0)*kx)*ky*cos(theta0 + dtheta*(x1 - x0)*kx);
					float fixedpoint2y = y0 - (y0 - y1)*kx + (r0 + dr*(x1 - x0)*kx)*ky*cos(theta0 + dtheta*(x1 - x0)*kx);
					float temppoint;
					if (fixedpoint1x - fixedpoint2x>0){
						temppoint = fixedpoint1x;
						fixedpoint1x = fixedpoint2x;
						fixedpoint2x = temppoint;
					}
					if (fixedpoint1y - fixedpoint2y>0){
						temppoint = fixedpoint1y;
						fixedpoint1y = fixedpoint2y;
						fixedpoint2y = temppoint;
					}
					img = src(Range(fixedpoint1y + InterSpace / 2, fixedpoint2y - InterSpace / 2), Range(fixedpoint1x + InterSpace / 2, fixedpoint2x - InterSpace / 2));
					imwrite(filespicpath + "\\" + Pic2Diction[0], img);
				}
			}

			if (list[filestep][0] = 3){
				MessageBox(TEXT("Not ready yet!"), TEXT("Error"), MB_OK);
			}

		}
	}
}


void CpicV4Dlg::OnBnClickedButton16()
{
	// TODO: Add your control notification handler code here

}
