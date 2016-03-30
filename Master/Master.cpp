// Master.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Master.h"
using namespace AceBear;

CMaster *g_pMasterApp = NULL;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    CMaster master(hInstance);
    g_pMasterApp = &master;

    DWORD dwRet = master.Init(nCmdShow);
    if (dwRet != NOERROR) return dwRet;

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

namespace AceBear
{
    const wchar_t CMaster::c_wszClassName[] = L"MaSTeR";

    CMaster::CMaster(HINSTANCE hInstApp)
        :m_hInstApp(hInstApp), m_hWndMain(0)
    {
    }

    CMaster::~CMaster()
    {

    }

    DWORD CMaster::Init(int nCmdShow)
    {
        if (!RegisterCls()) return GetLastError();
        if (!CreateWnd(nCmdShow)) return GetLastError();
        return NOERROR;
    }

    BOOL CMaster::RegisterCls()
    {
        WNDCLASSEX wcex;
        ::ZeroMemory(&wcex, sizeof(WNDCLASSEX));
        wcex.cbSize = sizeof(WNDCLASSEX);

        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = (WNDPROC)MasterWndProc;
        wcex.hInstance = m_hInstApp;
        wcex.hIcon = ::LoadIcon(nullptr, IDI_APPLICATION);
        wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
        wcex.lpszClassName = c_wszClassName;

        return (RegisterClassExW(&wcex) != 0);
    }

    BOOL CMaster::CreateWnd(int nCmdShow)
    {
        int cx = ::GetSystemMetrics(SM_CXSCREEN);
        m_hWndMain = ::CreateWindow(c_wszClassName, c_wszClassName, WS_OVERLAPPEDWINDOW,
            cx - 280, 120, 240, 480, nullptr, nullptr, m_hInstApp, nullptr);
        if (!m_hWndMain) return FALSE;

        ShowWindow(m_hWndMain, nCmdShow);
        UpdateWindow(m_hWndMain);

        return TRUE;
    }

    inline LRESULT CMaster::MasterWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {   
        return g_pMasterApp->WndProc(hWnd, uMsg, wParam, lParam);
    }

    LRESULT CMaster::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg) {
            HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
        return 0L;
    }

    void CMaster::OnDestroy(HWND hWnd)
    {
        ::PostQuitMessage(0);
    }
}