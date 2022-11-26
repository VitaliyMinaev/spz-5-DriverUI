
// MFCApplication2Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <winsvc.h>


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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
END_MESSAGE_MAP()


// Обработчики сообщений CMFCApplication2Dlg

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

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

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
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
void CMFCApplication2Dlg::OnBnClickedAdd()
{
	LPWSTR out = nullptr;
    if (filepath.GetString() == nullptr) {
        Trace(L"File name is empty");
        return;
    }
	schSCManager = InitManager();  // full access rights 
	if (schSCManager == NULL)
	{		
		Trace(L"OpenSCManager failed (%d)");		
		return;
	}
	schService = CreateService(
		schSCManager,              // SCM database 
		svcname.GetString(),       // name of service 
		svcname.GetString(),       // service name to display 
		SERVICE_ALL_ACCESS,        // desired access 
		SERVICE_WIN32_OWN_PROCESS, // service type 
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
		Trace(L"CreateService failed (%d)\n");		
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
	LPWSTR out = nullptr;
	schSCManager = InitManager();  // full access rights 
	if (schSCManager == NULL)
	{
		Trace(_T("OpenSCManager failed (%d)"));
		return;
	}
	schService = OpenService(
		schSCManager,					// SCM database 
		svcname.GetString(),			// name of service 
		DELETE);						// need delete access 

	if (schService == NULL)
	{
		Trace(_T("OpenService failed (%d)\n"));
		CloseServiceHandle(schSCManager);
		return;
	}
	// Delete the service.

	if (!DeleteService(schService))
	{
		Trace(_T("DeleteService failed (%d)\n"));
	}
	else {
		Trace(_T("Service deleted successfully\n"));
	}

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
}
void Trace(LPWSTR info)
{
	wsprintf(info, info, GetLastError());
	MessageBox(0,info,0,0);
}
SC_HANDLE InitManager()
{
	return OpenSCManager(
		NULL,                    // local computer
		NULL,                    // ServicesActive database 
		SC_MANAGER_ALL_ACCESS);
}