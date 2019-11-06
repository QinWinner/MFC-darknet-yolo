
// HatdetecteDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Hatdetecte.h"
#include "HatdetecteDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHatdetecteDlg 对话框



CHatdetecteDlg::CHatdetecteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HATDETECTE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHatdetecteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHatdetecteDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &CHatdetecteDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_DETECTE, &CHatdetecteDlg::OnBnClickedDetecte)
	ON_BN_CLICKED(IDC_OPENVIDEO, &CHatdetecteDlg::OnBnClickedOpenvideo)
END_MESSAGE_MAP()


// CHatdetecteDlg 消息处理程序

BOOL CHatdetecteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_CameraView.InitCameraView(this);
	m_darknet.InitDarkNet(this);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CHatdetecteDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHatdetecteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHatdetecteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHatdetecteDlg::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CString fileName;
	TCHAR szFilter[] = _T("JPEG文件(*.jpg)|*.jpg|png文件(*.png)|*.png|");
	CFileDialog fileDlg(TRUE, _T("jpg"), NULL, 0, szFilter, this);

	if (fileDlg.DoModal() != IDOK)     //没有点确定按钮，返回
		return;

	fileName = fileDlg.GetPathName();
	std::string tempName = (LPCSTR)CStringA(fileName);
	image = cv::imread(tempName);
	m_CameraView.ShowImage(image);
}




void CHatdetecteDlg::OnBnClickedDetecte()
{
	// TODO: 在此添加控件通知处理程序代码
	m_darknet.PictureDetecte(image, 0.5);
	AfxMessageBox(TEXT("预测完成"));
}


void CHatdetecteDlg::OnBnClickedOpenvideo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString fileName;
	TCHAR szFilter[] = _T("MP4文件(*.mp4)|*.mp4");
	CFileDialog fileDlg(TRUE, _T("mp4"), NULL, 0, szFilter, this);

	if (fileDlg.DoModal() != IDOK)     //没有点确定按钮，返回
		return;

	fileName = fileDlg.GetPathName();
	std::string tempName = (LPCSTR)CStringA(fileName);
	//m_darknet.VideoDetecte(tempName);
}
