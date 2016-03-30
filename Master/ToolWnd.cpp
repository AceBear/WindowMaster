#include "stdafx.h"
#include "ToolWnd.h"

namespace AceBear
{
    CToolWnd::CToolWnd()
    {
        StringCchPrintf(m_wszClsName, sizeof(m_wszClsName) / sizeof(wchar_t), L"%S", typeid(this).name());
    }


    CToolWnd::~CToolWnd()
    {
    }

    LRESULT CToolWnd::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg) {
            HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
        default:
            return __super::WndProc(hWnd, uMsg, wParam, lParam);
        }
        return 0L;
    }

    void CToolWnd::ReSize(int width, int height)
    {
        ::SetWindowPos(m_hWnd, NULL, 0, 0, width, height, SWP_NOMOVE);
    }

    void CToolWnd::OnPaint(HWND hwnd)
    {
        PAINTSTRUCT ps;
        HDC hdc = ::BeginPaint(hwnd, &ps);
        ::EndPaint(hwnd, &ps);
    }
}