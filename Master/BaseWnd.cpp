#include "stdafx.h"
#include "BaseWnd.h"
#include "Master.h"

namespace AceBear
{
    DWORD CBaseWnd::s_dwTlsThis = ::TlsAlloc();

    CBaseWnd::CBaseWnd()
    {
        StringCchPrintf(m_wszClsName, sizeof(m_wszClsName) / sizeof(wchar_t), L"%S", typeid(this).name());
    }


    CBaseWnd::~CBaseWnd()
    {
    }

    DWORD CBaseWnd::Init(wchar_t *pwszTitle, CBaseWnd *pParent, const RECT &rc, DWORD dwStyle)
    {
        if (!CreateWnd(RegisterCls(), pwszTitle, pParent, rc, dwStyle)) return GetLastError();
        return NOERROR;
    }

    const wchar_t* CBaseWnd::RegisterCls()
    {
        WNDCLASSEX wcex;
        HINSTANCE hInstApp = CMaster::GetAppInst();
        if (!::GetClassInfoEx(hInstApp, m_wszClsName, &wcex)) {
            ::ZeroMemory(&wcex, sizeof(WNDCLASSEX));
            wcex.cbSize = sizeof(WNDCLASSEX);

            wcex.style = CS_HREDRAW | CS_VREDRAW;
            wcex.lpfnWndProc = (WNDPROC)CBaseWnd::BaseWndProc;
            wcex.hInstance = hInstApp;
            wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wcex.lpszClassName = m_wszClsName;

            RegisterClassEx(&wcex);
        }

        return m_wszClsName;
    }

    BOOL CBaseWnd::CreateWnd(const wchar_t *pwszCls, const wchar_t *pwszTitle, CBaseWnd *pParent, const RECT &rc , DWORD dwStyle)
    {
        ::TlsSetValue(s_dwTlsThis, this);
        HWND hwnd = ::CreateWindow(pwszCls, pwszTitle, dwStyle,
            rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, pParent != nullptr ? pParent->m_hWnd : nullptr, nullptr, nullptr, nullptr);
        ::TlsSetValue(s_dwTlsThis, 0);
        if (!hwnd) return FALSE;

        return TRUE;
    }

    LRESULT CBaseWnd::BaseWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        CBaseWnd *pThis = (CBaseWnd*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        if (!pThis) {
            // find it in TLS
            pThis = (CBaseWnd*)::TlsGetValue(s_dwTlsThis);
            pThis->m_hWnd = hWnd;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
        }
        return pThis->WndProc(hWnd, uMsg, wParam, lParam);
    }

    LRESULT CBaseWnd::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}