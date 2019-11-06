
// HatdetecteDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Hatdetecte.h"
#include "HatdetecteDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CHatdetecteDlg �Ի���



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


// CHatdetecteDlg ��Ϣ�������

BOOL CHatdetecteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_CameraView.InitCameraView(this);
	m_darknet.InitDarkNet(this);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHatdetecteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHatdetecteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHatdetecteDlg::OnBnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString fileName;
	TCHAR szFilter[] = _T("JPEG�ļ�(*.jpg)|*.jpg|png�ļ�(*.png)|*.png|");
	CFileDialog fileDlg(TRUE, _T("jpg"), NULL, 0, szFilter, this);

	if (fileDlg.DoModal() != IDOK)     //û�е�ȷ����ť������
		return;

	fileName = fileDlg.GetPathName();
	std::string tempName = (LPCSTR)CStringA(fileName);
	image = cv::imread(tempName);
	m_CameraView.ShowImage(image);
}




void CHatdetecteDlg::OnBnClickedDetecte()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_darknet.PictureDetecte(image, 0.5);
	AfxMessageBox(TEXT("Ԥ�����"));
}


void CHatdetecteDlg::OnBnClickedOpenvideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString fileName;
	TCHAR szFilter[] = _T("MP4�ļ�(*.mp4)|*.mp4");
	CFileDialog fileDlg(TRUE, _T("mp4"), NULL, 0, szFilter, this);

	if (fileDlg.DoModal() != IDOK)     //û�е�ȷ����ť������
		return;

	fileName = fileDlg.GetPathName();
	std::string tempName = (LPCSTR)CStringA(fileName);
	//m_darknet.VideoDetecte(tempName);
}
