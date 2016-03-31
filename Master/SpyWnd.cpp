#include "stdafx.h"
#include "SpyWnd.h"
#include "Spy.h"

namespace AceBear
{
    CSpyWnd::CSpyWnd()
        :m_pSpy(nullptr)
    {
    }


    CSpyWnd::~CSpyWnd()
    {
    }

    LRESULT CSpyWnd::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg) {
            HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
        default:
            return __super::WndProc(hWnd, uMsg, wParam, lParam);
        }
        return 0L;
    }

    void CSpyWnd::OnPaint(HWND hwnd)
    {
        PAINTSTRUCT ps;
        HDC hdc = ::BeginPaint(hwnd, &ps);

        if (m_pSpy->GetProcessId()) {
            wchar_t buf[64];
            StringCchPrintf(buf, sizeof(buf) / sizeof(wchar_t), L"%d", m_pSpy->GetProcessId());
            TextOut(hdc, 0, 0, buf, (int)wcslen(buf));
        }

        ::EndPaint(hwnd, &ps);
    }
}