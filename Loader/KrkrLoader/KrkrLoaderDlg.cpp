
// KrkrLoaderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KrkrLoader.h"
#include "KrkrLoaderDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/***********************************************/

// CKrkrLoaderDlg �Ի���

CKrkrLoaderDlg::CKrkrLoaderDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CKrkrLoaderDlg::IDD, pParent),
CheckChildProcess(FALSE),
TryHack(FALSE),
RunLE(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKrkrLoaderDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Text(pDX, IDC_EDIT1, FilePath);
	DDV_MaxChars(pDX, FilePath, 2048);

	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKrkrLoaderDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CKrkrLoaderDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CKrkrLoaderDlg::OnEnChangeEdit1)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_CHECK1, &CKrkrLoaderDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CKrkrLoaderDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDOK, &CKrkrLoaderDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK3, &CKrkrLoaderDlg::OnBnClickedCheck3)
END_MESSAGE_MAP()


// CKrkrLoaderDlg ��Ϣ�������

BOOL CKrkrLoaderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_SHOW);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CKrkrLoaderDlg::OnPaint()
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
HCURSOR CKrkrLoaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKrkrLoaderDlg::OnBnClickedButton1()
{
	CString strFile = _T("");

	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Executable File (*.exe)|*.exe||"), NULL);

	if (dlgFile.DoModal())
	{
		strFile = dlgFile.GetPathName();
		FilePath = strFile;
		//UpdateData(TRUE);
	}
	UpdateData(FALSE);
}


void CKrkrLoaderDlg::OnEnChangeEdit1()
{
	GetDlgItemTextW(IDC_EDIT1, FilePath);
}


void CKrkrLoaderDlg::OnDropFiles(HDROP hDropInfo)
{
	HDROP hDrop = hDropInfo;
	UINT nFileNum = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
	if (nFileNum == 1)
	{
		WCHAR strFileName[MAX_PATH] = { 0 };
		DragQueryFileW(hDrop, 0, strFileName, MAX_PATH);

		FilePath = strFileName;
		UpdateData(FALSE);
		BOOL See = FALSE;
		BOOL m_Ret = OnInit::IsExeFile(strFileName, See);
		if (See && m_Ret)
		{
			
			OnInit::WriteLog(FilePath, this->CheckChildProcess, this->TryHack, this->RunLE);
			BOOL ret = OnInit::Inject(FilePath);
			if (ret)
			{
				DragFinish(hDrop);
				PostQuitMessage(0);
			}
			else
			{
				DeleteFileW(L"KrkrLaunch.ini");
			}
		}
		else
		{
			MessageBoxW(L"Not an executable file", L"KrkrLaoder");
			FilePath = "";
			UpdateData(FALSE);
		}
	}
	else
	{
		MessageBoxW(L"Please Drop one file on this window", L"KrkrLaoder");
		DragFinish(hDrop);
		FilePath = "";
		UpdateData(FALSE);
	}
	CDialogEx::OnDropFiles(hDropInfo);
}

//Process
void CKrkrLoaderDlg::OnBnClickedCheck1()
{
	CheckChildProcess = !CheckChildProcess;
}

//Hack
void CKrkrLoaderDlg::OnBnClickedCheck2()
{
	TryHack = !TryHack;
}


//Launch
void CKrkrLoaderDlg::OnBnClickedOk()
{
	
	if (FilePath.GetLength() == 0)
	{
		MessageBox(L"Empty File Path", L"KrkrLoader");
		return;
	}
	if (!OnInit::CheckFile(FilePath))
	{
		MessageBox(L"Could not open selected file", L"KrkrLoader");
		return;
	}

	BOOL s = FALSE;
	BOOL ret = OnInit::IsExeFile(FilePath, s);
	if (ret && s)
	{
		if (OnInit::Inject(FilePath))
		{
			OnInit::WriteLog(FilePath, this->CheckChildProcess, this->TryHack, this->RunLE);
		}
		else
		{
			MessageBox(L"Failed to inject @_@", L"KrkrLoader");
		}
	}
	else
	{
		MessageBoxW(L"Not an executable file", L"KrkrLaoder");
	}

	CDialogEx::OnOK();
}

//X'moe LE
void CKrkrLoaderDlg::OnBnClickedCheck3()
{
	RunLE = !RunLE;
}
