
// KrkrLoader.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include <string>

using std::wstring;

void WriteLogFile(const wchar_t* Path, bool CheckProcess, bool TryHack, bool runLE);
bool ReadLogFile(wstring& Path, bool& CheckProcess, bool& TryHack, bool& runLE);
BOOL IsPEFileW(LPCWSTR pPath, BOOL &bIsSucceed);
bool FileIsExist(const wchar_t* FileName);
BOOL Inject(wchar_t* ExePath);

class OnInit
{
public:
	static BOOL IsExeFile(CString pPath, BOOL &bIsSucceed)
	{
		WCHAR Path[MAX_PATH] = { 0 };
		wcsncpy(Path, CW2CW(pPath), pPath.GetLength());
		BOOL See;
		BOOL Ret = IsPEFileW(Path, See);
		bIsSucceed = See;
		return Ret && See;
	}
	static BOOL CheckLogFile()
	{
		return FileIsExist(L"KrkrLaunch.ini");
	}
	static BOOL CheckFile(CString& File)
	{
		WCHAR Path[MAX_PATH] = { 0 };
		wcsncpy(Path, CW2CW(File), File.GetLength());
		return FileIsExist(Path);
	}
	static VOID WriteLog(CString& pPath, BOOL CheckProcess, BOOL TryHack, BOOL runLE)
	{
		WCHAR Path[MAX_PATH] = { 0 };
		wcsncpy(Path, CW2CW(pPath), pPath.GetLength());
		WriteLogFile(Path, CheckProcess, TryHack, runLE);
	}
	static BOOL ReadLog(CString& pPath, BOOL& CheckProcess, BOOL& TryHack, BOOL& runLE)
	{
		wstring Path;
		bool bCheck;
		bool bHack;
		bool brunLe;
		BOOL ret = (BOOL)ReadLogFile(Path, bCheck, bHack, brunLe);
		CheckProcess = bCheck;
		TryHack = bHack;
		runLE = brunLe;
		pPath = Path.c_str();
		return ret;
	}
	static BOOL Inject(CString& ExePath)
	{
		WCHAR Path[MAX_PATH] = { 0 };
		wcsncpy(Path, CW2CW(ExePath), ExePath.GetLength());
		return ::Inject(Path);
	}
};

class CKrkrLoaderApp : public CWinApp
{
public:
	CKrkrLoaderApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	DECLARE_MESSAGE_MAP()
};

extern CKrkrLoaderApp theApp;