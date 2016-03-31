// Master.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "MasterWnd.h"

using namespace AceBear;

CMasterWnd *g_pMasterApp = NULL;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    CMasterWnd master(hInstance);
    g_pMasterApp = &master;

    DWORD dwRet = master.Init(L"MaSTeR", nullptr, master.CalcPos(), WS_OVERLAPPEDWINDOW);
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
    CMasterWnd::CMasterWnd(HINSTANCE hInstApp)
        :m_hInstApp(hInstApp), m_hWndMain(0)
    {
        m_wndTool.SetSpy(&m_spy);
        m_wndSpy.SetSpy(&m_spy);
    }

    CMasterWnd::~CMasterWnd()
    {
    }

    HINSTANCE CMasterWnd::GetAppInst()
    {
        return g_pMasterApp->m_hInstApp;
    }

    CMasterWnd * CMasterWnd::GetMainWnd()
    {
        return g_pMasterApp;
    }

    RECT CMasterWnd::CalcPos()
    {
        RECT rc;
        rc.left = ::GetSystemMetrics(SM_CXSCREEN) - 280;
        rc.right = rc.left + 240;
        rc.top = 120;
        rc.bottom = rc.top + 480;
        return rc;
    }

    const wchar_t* CMasterWnd::RegisterCls()
    {
        wcscpy_s(m_wszClsName, L"CMasterWnd");

        WNDCLASSEX wcex;
        ::ZeroMemory(&wcex, sizeof(WNDCLASSEX));
        wcex.cbSize = sizeof(WNDCLASSEX);

        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = (WNDPROC)CBaseWnd::BaseWndProc;
        wcex.hInstance = m_hInstApp;
        wcex.hIcon = ::LoadIcon(nullptr, IDI_APPLICATION);
        wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
        wcex.lpszClassName = m_wszClsName;

        RegisterClassExW(&wcex);

        return m_wszClsName;
    }

    LRESULT CMasterWnd::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg) {
            HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
            HANDLE_MSG(hWnd, WM_SIZE, OnSize);
            HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
        case UM_SWITCHSPY:
            OnSwitchSpy(wParam, lParam);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
        return 0L;
    }

    BOOL CMasterWnd::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
    {
        RECT rcMain;
        ::GetClientRect(hwnd, &rcMain);

        RECT rcTool = rcMain;
        rcTool.top += 1;
        rcTool.bottom = rcTool.top + 50;
        m_wndTool.Init(L"ToolBox", this, rcTool);

        RECT rcSpy = rcMain;
        rcSpy.top = rcTool.bottom + 1;
        m_wndSpy.Init(L"Spy", this, rcSpy);

        ::ShowWindow(hwnd, SW_SHOW);
        return TRUE;
    }

    void CMasterWnd::OnDestroy(HWND hWnd)
    {
        ::PostQuitMessage(0);
    }

    void CMasterWnd::OnSize(HWND hwnd, UINT state, int cx, int cy)
    {
        m_wndTool.ReSize(cx, 50);
        m_wndSpy.ReSize(cx, cy - 50 - 1);
    }

    void CMasterWnd::OnSwitchSpy(WPARAM wParam, LPARAM lParam)
    {
        m_wndSpy.Invalidate();
    }
}