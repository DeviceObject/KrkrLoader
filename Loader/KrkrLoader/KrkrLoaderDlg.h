
// KrkrLoaderDlg.h : ͷ�ļ�
//

#pragma once


// CKrkrLoaderDlg �Ի���
class CKrkrLoaderDlg : public CDialogEx
{
// ����
public:
	CKrkrLoaderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KRKRLOADER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

	CString FilePath;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedCheck1();


	BOOL CheckChildProcess;
	BOOL TryHack;
	BOOL RunLE;

	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheck3();
};
