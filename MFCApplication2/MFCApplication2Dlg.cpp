﻿#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"
#include "winioctl.h"
#include "Strsafe.h"
#include <winsvc.h>

#define DEVICE_SEND_BUFF			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED,	FILE_WRITE_DATA)
#define DEVICE_SEND_DIRECT			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_IN_DIRECT,	FILE_WRITE_DATA)
#define DEVICE_SEND_NEITHER			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_NEITHER,	FILE_WRITE_DATA)

#define DEVICE_SEND_UNK_BUFFERED	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x811, METHOD_BUFFERED,	FILE_WRITE_DATA)

#define DEVICE_REC_BUFF				CTL_CODE(FILE_DEVICE_UNKNOWN, 0x804, METHOD_BUFFERED,	FILE_READ_ACCESS)
#define DEVICE_REC_DIRECT			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x805, METHOD_OUT_DIRECT, FILE_READ_DATA)
#define DEVICE_REC_NEITHER			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x806, METHOD_NEITHER,	FILE_READ_DATA)



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);  
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

CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, &CMFCApplication2Dlg::OnBnClickedAdd)
	ON_EN_CHANGE(IDC_FILE, &CMFCApplication2Dlg::OnEnChangeFile)
	ON_EN_CHANGE(IDC_NAME, &CMFCApplication2Dlg::OnEnChangeName)
	ON_BN_CLICKED(IDC_DELETE, &CMFCApplication2Dlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_START, &CMFCApplication2Dlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CMFCApplication2Dlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_OPEN, &CMFCApplication2Dlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_CLOSE, &CMFCApplication2Dlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_SENDDIR, &CMFCApplication2Dlg::OnBnClickedSenddir)
	ON_BN_CLICKED(IDC_RECDIR, &CMFCApplication2Dlg::OnBnClickedRecdir)
	ON_BN_CLICKED(IDC_SENDNEITHER, &CMFCApplication2Dlg::OnBnClickedSendneither)
	ON_BN_CLICKED(IDC_RECNEITHER, &CMFCApplication2Dlg::OnBnClickedRecneither)
	ON_BN_CLICKED(IDC_SENDBUF, &CMFCApplication2Dlg::OnBnClickedSendbuf)
	ON_BN_CLICKED(IDC_RECBUF, &CMFCApplication2Dlg::OnBnClickedRecbuf)

	ON_BN_CLICKED(IDC_BTUNK, &CMFCApplication2Dlg::OnBnClickedBtunk)
END_MESSAGE_MAP()


// Обработчики сообщений CMFCApplication2Dlg

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString filepath = nullptr,svcname;
SC_HANDLE schSCManager;
SC_HANDLE schService;
SERVICE_STATUS ssStatus;
void Trace(LPWSTR info);
SC_HANDLE InitManager();
BOOL __stdcall StopDependentServices();

void CMFCApplication2Dlg::OnBnClickedAdd()
{	
    if (filepath.GetString() == L"") {
        Trace(L"File name is empty");
        return;
    }
	schSCManager = InitManager();  // full access rights 
	if (schSCManager == NULL)
	{		
		Trace(L"Can not open SCManager (%d)");		
		return;
	}
	schService = CreateService(
		schSCManager,              // SCM database 
		svcname.GetString(),       // name of service 
		svcname.GetString(),       // service name to display 
		SERVICE_ALL_ACCESS,        // desired access 
		SERVICE_KERNEL_DRIVER,	   // service type 
		SERVICE_DEMAND_START,      // start type 
		SERVICE_ERROR_NORMAL,      // error control type 
		filepath.GetString(),      // path to service's binary 
		NULL,                      // no load ordering group 
		NULL,                      // no tag identifier 
		NULL,                      // no dependencies 
		NULL,                      // LocalSystem account 
		NULL);                     // no password 
	if (schService == NULL)
	{
		Trace(L"Can not create service\n");		
		CloseServiceHandle(schSCManager);
		return;
	}
	else {
		MessageBox(0,_T("Service installed succesfully"),0);
	}

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);

}
void CMFCApplication2Dlg::OnEnChangeFile()
{
	GetDlgItem(IDC_FILE)->GetWindowTextW(filepath);
    MessageBox(filepath.GetString());
}
void CMFCApplication2Dlg::OnEnChangeName()
{
	GetDlgItem(IDC_NAME)->GetWindowTextW(svcname);
}
void CMFCApplication2Dlg::OnBnClickedDelete()
{	
	schSCManager = InitManager();  // full access rights 
	if (schSCManager == NULL)
	{
		Trace(_T("OpenSCManager failed"));
		return;
	}
	schService = OpenService(
		schSCManager,					// SCM database 
		svcname.GetString(),			// name of service 
		DELETE);						// need delete access 

	if (schService == NULL)
	{
		Trace(_T("OpenService failed\n"));
		CloseServiceHandle(schSCManager);
		return;
	}
	// Delete the service.

	if (!DeleteService(schService))
	{
		Trace(_T("Can not delete service\n"));
	}
	else {
		Trace(_T("Service deleted successfully!\n"));
	}

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
}
void Trace(LPWSTR info)
{
	/*StringCbPrintfW(info, wcslen(info)+1, info,);*/
	MessageBox(0,info,0,0);
}
BOOL __stdcall StopDependentServices()
{
	DWORD i;
	DWORD dwBytesNeeded;
	DWORD dwCount;

	LPENUM_SERVICE_STATUS   lpDependencies = NULL;
	ENUM_SERVICE_STATUS     ess;
	SC_HANDLE               hDepService;
	SERVICE_STATUS_PROCESS  ssp;

	DWORD dwStartTime = GetTickCount();
	DWORD dwTimeout = 30000; // 30-second time-out

	// Pass a zero-length buffer to get the required buffer size.
	if (EnumDependentServices(schService, SERVICE_ACTIVE,
		lpDependencies, 0, &dwBytesNeeded, &dwCount))
	{
		// If the Enum call succeeds, then there are no dependent
		// services, so do nothing.
		return TRUE;
	}
	else
	{
		if (GetLastError() != ERROR_MORE_DATA)
			return FALSE; // Unexpected error

		// Allocate a buffer for the dependencies.
		lpDependencies = (LPENUM_SERVICE_STATUS)HeapAlloc(
			GetProcessHeap(), HEAP_ZERO_MEMORY, dwBytesNeeded);

		if (!lpDependencies)
			return FALSE;

		__try {
			// Enumerate the dependencies.
			if (!EnumDependentServices(schService, SERVICE_ACTIVE,
				lpDependencies, dwBytesNeeded, &dwBytesNeeded,
				&dwCount))
				return FALSE;

			for (i = 0; i < dwCount; i++)
			{
				ess = *(lpDependencies + i);
				// Open the service.
				hDepService = OpenService(schSCManager,
					ess.lpServiceName,
					SERVICE_STOP | SERVICE_QUERY_STATUS);

				if (!hDepService)
					return FALSE;

				__try {
					// Send a stop code.
					if (!ControlService(hDepService,
						SERVICE_CONTROL_STOP,
						(LPSERVICE_STATUS)&ssp))
						return FALSE;

					// Wait for the service to stop.
					while (ssp.dwCurrentState != SERVICE_STOPPED)
					{
						Sleep(ssp.dwWaitHint);
						if (!QueryServiceStatusEx(
							hDepService,
							SC_STATUS_PROCESS_INFO,
							(LPBYTE)&ssp,
							sizeof(SERVICE_STATUS_PROCESS),
							&dwBytesNeeded))
							return FALSE;

						if (ssp.dwCurrentState == SERVICE_STOPPED)
							break;

						if (GetTickCount() - dwStartTime > dwTimeout)
							return FALSE;
					}
				}
				__finally
				{
					// Always release the service handle.
					CloseServiceHandle(hDepService);
				}
			}
		}
		__finally
		{
			// Always free the enumeration buffer.
			HeapFree(GetProcessHeap(), 0, lpDependencies);
		}
	}
	return TRUE;
}
SC_HANDLE InitManager()
{
	return OpenSCManager(
		NULL,                    // local computer
		NULL,                    // ServicesActive database 
		SC_MANAGER_ALL_ACCESS);
}
void CMFCApplication2Dlg::OnBnClickedStart()
{
	SERVICE_STATUS_PROCESS ssStatus;
	DWORD dwOldCheckPoint;
	DWORD dwStartTickCount;
	DWORD dwWaitTime;
	DWORD dwBytesNeeded;

	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager(
		NULL,                    // local computer
		NULL,                    // servicesActive database 
		SC_MANAGER_ALL_ACCESS);  // full access rights 

	if (NULL == schSCManager)
	{
		Trace(_T("OpenSCManager failed (%d)\n"));
		return;
	}

	// Get a handle to the service.

	schService = OpenService(
		schSCManager,         // SCM database 
		svcname.GetString(),            // name of service 
		SERVICE_ALL_ACCESS);  // full access 

	if (schService == NULL)
	{
		Trace(_T("OpenService failed (%d)\n"));
		CloseServiceHandle(schSCManager);
		return;
	}

	// Check the status in case the service is not stopped. 

	if (!QueryServiceStatusEx(
		schService,                     // handle to service 
		SC_STATUS_PROCESS_INFO,         // information level
		(LPBYTE)&ssStatus,             // address of structure
		sizeof(SERVICE_STATUS_PROCESS), // size of structure
		&dwBytesNeeded))              // size needed if buffer is too small
	{
		Trace(_T("QueryServiceStatusEx failed (%d)\n"));
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return;
	}

	// Check if the service is already running. It would be possible 
	// to stop the service here, but for simplicity this example just returns. 

	if (ssStatus.dwCurrentState != SERVICE_STOPPED && ssStatus.dwCurrentState != SERVICE_STOP_PENDING)
	{
		Trace(_T("Cannot start the service because it is already running\n"));
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return;
	}

	// Save the tick count and initial checkpoint.

	dwStartTickCount = GetTickCount();
	dwOldCheckPoint = ssStatus.dwCheckPoint;

	// Wait for the service to stop before attempting to start it.

	while (ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
	{
		// Do not wait longer than the wait hint. A good interval is 
		// one-tenth of the wait hint but not less than 1 second  
		// and not more than 10 seconds. 

		dwWaitTime = ssStatus.dwWaitHint / 10;

		if (dwWaitTime < 1000)
			dwWaitTime = 1000;
		else if (dwWaitTime > 10000)
			dwWaitTime = 10000;

		Sleep(dwWaitTime);

		// Check the status until the service is no longer stop pending. 

		if (!QueryServiceStatusEx(
			schService,                     // handle to service 
			SC_STATUS_PROCESS_INFO,         // information level
			(LPBYTE)&ssStatus,             // address of structure
			sizeof(SERVICE_STATUS_PROCESS), // size of structure
			&dwBytesNeeded))              // size needed if buffer is too small
		{
			Trace(_T("QueryServiceStatusEx failed (%d)\n"));
			CloseServiceHandle(schService);
			CloseServiceHandle(schSCManager);
			return;
		}

		if (ssStatus.dwCheckPoint > dwOldCheckPoint)
		{
			// Continue to wait and check.

			dwStartTickCount = GetTickCount();
			dwOldCheckPoint = ssStatus.dwCheckPoint;
		}
		else
		{
			if (GetTickCount() - dwStartTickCount > ssStatus.dwWaitHint)
			{
				Trace(_T("Timeout waiting for service to stop\n"));
				CloseServiceHandle(schService);
				CloseServiceHandle(schSCManager);
				return;
			}
		}
	}

	// Attempt to start the service.

	if (!StartService(
		schService,  // handle to service 
		0,           // number of arguments 
		NULL))      // no arguments 
	{
		Trace(_T("StartService failed (%d)\n"));
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return;
	}
	else Trace(_T("Service start pending...\n"));

	// Check the status until the service is no longer start pending. 

	if (!QueryServiceStatusEx(
		schService,                     // handle to service 
		SC_STATUS_PROCESS_INFO,         // info level
		(LPBYTE)&ssStatus,             // address of structure
		sizeof(SERVICE_STATUS_PROCESS), // size of structure
		&dwBytesNeeded))              // if buffer too small
	{
		Trace(_T("QueryServiceStatusEx failed (%d)\n"));
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return;
	}

	// Save the tick count and initial checkpoint.

	dwStartTickCount = GetTickCount();
	dwOldCheckPoint = ssStatus.dwCheckPoint;

	while (ssStatus.dwCurrentState == SERVICE_START_PENDING)
	{
		// Do not wait longer than the wait hint. A good interval is 
		// one-tenth the wait hint, but no less than 1 second and no 
		// more than 10 seconds. 

		dwWaitTime = ssStatus.dwWaitHint / 10;

		if (dwWaitTime < 1000)
			dwWaitTime = 1000;
		else if (dwWaitTime > 10000)
			dwWaitTime = 10000;

		Sleep(dwWaitTime);

		// Check the status again. 

		if (!QueryServiceStatusEx(
			schService,             // handle to service 
			SC_STATUS_PROCESS_INFO, // info level
			(LPBYTE)&ssStatus,             // address of structure
			sizeof(SERVICE_STATUS_PROCESS), // size of structure
			&dwBytesNeeded))              // if buffer too small
		{
			Trace(_T("QueryServiceStatusEx failed (%d)\n"));
			break;
		}

		if (ssStatus.dwCheckPoint > dwOldCheckPoint)
		{
			// Continue to wait and check.

			dwStartTickCount = GetTickCount();
			dwOldCheckPoint = ssStatus.dwCheckPoint;
		}
		else
		{
			if (GetTickCount() - dwStartTickCount > ssStatus.dwWaitHint)
			{
				// No progress made within the wait hint.
				break;
			}
		}
	}

	// Determine whether the service is running.

	if (ssStatus.dwCurrentState == SERVICE_RUNNING)
	{
		Trace(_T("Service started successfully.\n"));
	}
	else
	{
		Trace(_T("Service not started. \n"));
		Trace(_T("  Current State: %d\n"/*, ssStatus.dwCurrentState*/));
		Trace(_T("  Exit Code: %d\n"/*, ssStatus.dwWin32ExitCode*/));
		Trace(_T("  Check Point: %d\n"/*, ssStatus.dwCheckPoint*/));
		Trace(_T("  Wait Hint: %d\n"/*, ssStatus.dwWaitHint*/));
	}

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
}
void CMFCApplication2Dlg::OnBnClickedStop()
{
	SERVICE_STATUS_PROCESS ssp;
	DWORD dwStartTime = GetTickCount();
	DWORD dwBytesNeeded;
	DWORD dwTimeout = 30000; // 30-second time-out
	DWORD dwWaitTime;

	// Get a handle to the SCM database. 

	schSCManager = InitManager();

	if (NULL == schSCManager)
	{
		Trace(_T("OpenSCManager failed (%d)\n"));
		return;
	}

	// Get a handle to the service.

	schService = OpenService(
		schSCManager,         // SCM database 
		svcname.GetString(),            // name of service 
		SERVICE_STOP |
		SERVICE_QUERY_STATUS |
		SERVICE_ENUMERATE_DEPENDENTS);

	if (schService == NULL)
	{
		Trace(_T("OpenService failed (%d)\n"));
		CloseServiceHandle(schSCManager);
		return;
	}

	// Make sure the service is not already stopped.

	if (!QueryServiceStatusEx(
		schService,
		SC_STATUS_PROCESS_INFO,
		(LPBYTE)&ssp,
		sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded))
	{
		Trace(_T("QueryServiceStatusEx failed (%d)\n"));
		goto stop_cleanup;
	}

	if (ssp.dwCurrentState == SERVICE_STOPPED)
	{
		Trace(_T("Service is already stopped.\n"));
		goto stop_cleanup;
	}

	// If a stop is pending, wait for it.

	while (ssp.dwCurrentState == SERVICE_STOP_PENDING)
	{
		Trace(_T("Service stop pending...\n"));

		// Do not wait longer than the wait hint. A good interval is 
		// one-tenth of the wait hint but not less than 1 second  
		// and not more than 10 seconds. 

		dwWaitTime = ssp.dwWaitHint / 10;

		if (dwWaitTime < 1000)
			dwWaitTime = 1000;
		else if (dwWaitTime > 10000)
			dwWaitTime = 10000;

		Sleep(dwWaitTime);

		if (!QueryServiceStatusEx(
			schService,
			SC_STATUS_PROCESS_INFO,
			(LPBYTE)&ssp,
			sizeof(SERVICE_STATUS_PROCESS),
			&dwBytesNeeded))
		{
			Trace(_T("QueryServiceStatusEx failed (%d)\n"));
			goto stop_cleanup;
		}

		if (ssp.dwCurrentState == SERVICE_STOPPED)
		{
			Trace(_T("Service stopped successfully.\n"));
			goto stop_cleanup;
		}

		if (GetTickCount() - dwStartTime > dwTimeout)
		{
			Trace(_T("Service stop timed out.\n"));
			goto stop_cleanup;
		}
	}

	// If the service is running, dependencies must be stopped first.

	StopDependentServices();

	// Send a stop code to the service.

	if (!ControlService(
		schService,
		SERVICE_CONTROL_STOP,
		(LPSERVICE_STATUS)&ssp))
	{
		Trace(_T("ControlService failed (%d)\n"));
		goto stop_cleanup;
	}

	// Wait for the service to stop.

	while (ssp.dwCurrentState != SERVICE_STOPPED)
	{
		Sleep(ssp.dwWaitHint);
		if (!QueryServiceStatusEx(
			schService,
			SC_STATUS_PROCESS_INFO,
			(LPBYTE)&ssp,
			sizeof(SERVICE_STATUS_PROCESS),
			&dwBytesNeeded))
		{
			Trace(_T("QueryServiceStatusEx failed (%d)\n"));
			goto stop_cleanup;
		}

		if (ssp.dwCurrentState == SERVICE_STOPPED)
			break;

		if (GetTickCount() - dwStartTime > dwTimeout)
		{
			Trace(_T("Wait timed out\n"));
			goto stop_cleanup;
		}
	}
	Trace(_T("Service stopped successfully\n"));

stop_cleanup:
	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
}

HANDLE devicehandle = NULL;
void CMFCApplication2Dlg::OnBnClickedOpen()
{/*link-my-win-device*/
	devicehandle = CreateFile(
		L"\\\\.\\mydevicedriverlink",
		GENERIC_ALL,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_SYSTEM,
		NULL
	);
	if (devicehandle == INVALID_HANDLE_VALUE)
	{
		MessageBox(L"cannot open device", 0, 0);
		return;
	}
	MessageBox(L"device opened", 0, 0);
}


void CMFCApplication2Dlg::OnBnClickedClose()
{
	if (devicehandle != INVALID_HANDLE_VALUE) {
		CloseHandle(devicehandle);
		Trace(_T("Device closed succesfully"));
	}
}

void Read(PWCHAR* buffer, DWORD IoControlCode) {
	WCHAR message[1024] = { 0 };
	ULONG returnLength = 0;
	if (devicehandle != INVALID_HANDLE_VALUE && devicehandle != NULL)
	{
		if (!DeviceIoControl(
			devicehandle,
			IoControlCode,
			NULL,
			0,
			message,
			1024,
			&returnLength, 0
		))
		{
			MessageBox(0,L"DeviceIOControl BUFFERED error", 0, 0);
		}
		else
		{
			MessageBox(0, message, 0, 0);
		}
	}
}
void Write(PWCHAR buffer, DWORD IoControlCode) {
	PWCHAR message = buffer;
	ULONG returnLength;
	char wr[4] = { 0 };
	if (devicehandle != INVALID_HANDLE_VALUE && devicehandle != NULL)
	{
		if (!DeviceIoControl(
			devicehandle,
			IoControlCode,
			message,
			(wcslen(message) + 1)*2,
			NULL,
			0,
			&returnLength, 0
		))
		{
			MessageBox(0,L"DeviceIOControl BUFFERED error", 0, 0);
		}
		else
		{
			_itoa_s(returnLength, wr, 10);
			MessageBoxA(0, wr, 0, 0);
		}
	}
}


void CMFCApplication2Dlg::OnBnClickedSenddir()
{
	Write(L"Direct", DEVICE_SEND_DIRECT);
}


void CMFCApplication2Dlg::OnBnClickedRecdir()
{
	Read(NULL, DEVICE_REC_DIRECT);
}


void CMFCApplication2Dlg::OnBnClickedSendneither()
{
	Write(L"Neither", DEVICE_SEND_NEITHER);
}


void CMFCApplication2Dlg::OnBnClickedRecneither()
{
	Read(NULL,DEVICE_REC_NEITHER);
}


void CMFCApplication2Dlg::OnBnClickedSendbuf()
{
	Write(L"Buffered", DEVICE_SEND_BUFF);
}


void CMFCApplication2Dlg::OnBnClickedRecbuf()
{
	Read(NULL, DEVICE_REC_BUFF);
}

void CMFCApplication2Dlg::OnBnClickedBtunk()
{
	Write(L"Unknown", DEVICE_SEND_UNK_BUFFERED);
}
