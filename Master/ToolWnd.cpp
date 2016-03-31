#include "stdafx.h"
#include "ToolWnd.h"
#include "Spy.h"

namespace AceBear
{
    CToolWnd::CToolWnd()
        :m_pSpy(nullptr)
    {
    }


    CToolWnd::~CToolWnd()
    {
    }

    LRESULT CToolWnd::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg) {
            HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
            HANDLE_MSG(hWnd, WM_SIZE, OnSize);
            HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
            HANDLE_MSG(hWnd, WM_LBUTTONUP, OnLButtonUp);
            HANDLE_MSG(hWnd, WM_MOUSEMOVE, OnMouseMove);
        default:
            return __super::WndProc(hWnd, uMsg, wParam, lParam);
        }
        return 0L;
    }

    void CToolWnd::OnPaint(HWND hwnd)
    {
        RECT rc;

        rc = m_rcTarget;
        rc.top += 8;
        rc.bottom -= 8;
        rc.left += 8;
        rc.right -= 8;

        PAINTSTRUCT ps;
        HDC hdc = ::BeginPaint(hwnd, &ps);

        Ellipse(hdc, m_rcTarget.left, m_rcTarget.top, m_rcTarget.right, m_rcTarget.bottom);
        Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
        MoveToEx(hdc, (m_rcTarget.left + m_rcTarget.right) / 2, m_rcTarget.top, NULL);
        LineTo(hdc, (m_rcTarget.left + m_rcTarget.right) / 2, m_rcTarget.bottom);
        MoveToEx(hdc, m_rcTarget.left, (m_rcTarget.top + m_rcTarget.bottom) / 2, NULL);
        LineTo(hdc, m_rcTarget.right, (m_rcTarget.top + m_rcTarget.bottom) / 2);

        ::EndPaint(hwnd, &ps);
    }

    void CToolWnd::OnSize(HWND hwnd, UINT state, int cx, int cy)
    {
        m_rcTarget.top = 4;
        m_rcTarget.bottom = cy - 4;
        m_rcTarget.left = 4;
        m_rcTarget.right = m_rcTarget.left + (m_rcTarget.bottom - m_rcTarget.top);
        InvalidateRect(hwnd, NULL, TRUE);
    }

    void CToolWnd::OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
    {
        POINT point = { x, y };
        if (PtInRect(&m_rcTarget, point)) {
            SetCursor(::LoadCursor(nullptr, IDC_HELP));
            ::SetCapture(hwnd);
        }
    }

    void CToolWnd::OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
    {
        POINT point;
        ::GetCursorPos(&point);
        HWND hTargetWnd = ::WindowFromPoint(point);

        DWORD dwProcessId = 0;
        DWORD dwThreadId = ::GetWindowThreadProcessId(hTargetWnd, &dwProcessId);

        SetCursor(::LoadCursor(nullptr, IDC_ARROW));
        ::ReleaseCapture();

        m_pSpy->Switch(dwProcessId, dwThreadId);

        // wchar_t buf[128];
        // StringCchPrintf(buf, 128, L"0x%x ->%d:%d\n", hTargetWnd, dwProcessId, dwThreadId);
        // ::OutputDebugString(buf);
    }

    void CToolWnd::OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
    {
    }
}