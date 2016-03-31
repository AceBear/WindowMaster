#include "stdafx.h"
#include "SpyWnd.h"
#include "Spy.h"
#include "MasterWnd.h"
namespace AceBear
{
    CSpyWnd::CSpyWnd()
        :m_pSpy(nullptr)
    {
    }


    CSpyWnd::~CSpyWnd()
    {
    }

    void CSpyWnd::UpdateScrollInfo()
    {
        RECT rc;
        ::GetClientRect(m_hWnd, &rc);

        HDC hdc = ::GetWindowDC(m_hWnd);
        HGDIOBJ fontOld = ::SelectObject(hdc, m_fontSimSun);

        TEXTMETRIC tm;
        ::GetTextMetrics(hdc, &tm);
        int yLine = tm.tmExternalLeading + tm.tmHeight + c_yGap;

        SCROLLINFO si;
        ZeroMemory(&si, sizeof(SCROLLINFO));
        si.cbSize = sizeof(SCROLLINFO);
        si.nMin = 0;
        si.nMax = yLine * (int)(m_pSpy->GetChildren().size() + 2);
        si.nPage = rc.bottom - rc.top - c_yGap;
        si.fMask = SIF_RANGE | SIF_PAGE;
        ::SetScrollInfo(m_hWnd, SB_VERT, &si, TRUE);

        ::SelectObject(hdc, fontOld);
        ::ReleaseDC(m_hWnd, hdc);
    }

    LRESULT CSpyWnd::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg) {
            HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
            HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
            HANDLE_MSG(hWnd, WM_SIZE, OnSize);
            HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
            HANDLE_MSG(hWnd, WM_VSCROLL, OnVScroll);
            HANDLE_MSG(hWnd, WM_LBUTTONUP, OnLButtonUp);
        default:
            return __super::WndProc(hWnd, uMsg, wParam, lParam);
        }
        return 0L;
    }

    BOOL CSpyWnd::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
    {
        LOGFONT lf;
        ZeroMemory(&lf, sizeof(LOGFONT));
        lf.lfHeight = 16;
        wcscpy_s(lf.lfFaceName, L"宋体");
        m_fontSimSun = CreateFontIndirect(&lf);
        m_brSelected = CreateSolidBrush(RGB(0xdd, 0xdd, 0xdd));
        return TRUE;
    }

    void CSpyWnd::OnDestroy(HWND hwnd)
    {
        DeleteObject(m_fontSimSun);
        DeleteObject(m_brSelected);
    }

    void CSpyWnd::OnPaint(HWND hwnd)
    {
        PAINTSTRUCT ps;
        HDC hdc = ::BeginPaint(hwnd, &ps);

        HGDIOBJ fontOld = ::SelectObject(hdc, m_fontSimSun);

        TEXTMETRIC tm;
        ::GetTextMetrics(hdc, &tm);
        SetBkMode(hdc, TRANSPARENT);

        int yLine = tm.tmExternalLeading + tm.tmHeight + c_yGap;
        int y = m_yBase + c_yGap, x = 4;

        if (m_pSpy->GetProcessId()) {
            wchar_t buf[256];
            ::StringCchPrintf(buf, sizeof(buf) / sizeof(wchar_t), L"%d:%s:%s",
                m_pSpy->GetProcessId(), m_pSpy->GetProcessName(), m_pSpy->GetWindowName());
            ::TextOut(hdc, x, y, buf, (int)wcslen(buf));
            y += yLine;

            vector<WNDESC> vWnds = m_pSpy->GetChildren();
            int xPos = x + tm.tmAveCharWidth * 4;
            for (vector<WNDESC>::iterator i = vWnds.begin(); i < vWnds.end(); i++) {

                if (i->bSelected) {
                    RECT rc;
                    GetClientRect(hwnd, &rc);
                    rc.top = y - c_yGap/2;
                    rc.bottom = y + yLine;
                    FillRect(hdc, &rc, m_brSelected);
                    SetTextColor(hdc, RGB(0x00, 0x00, 0xcc));
                }
                else
                    SetTextColor(hdc, RGB(0x00, 0x00, 0x00));

                ::StringCchPrintf(buf, sizeof(buf) / sizeof(wchar_t), L"0x%x:%s:(%d,%d,%d,%d)",
                    i->hWnd, i->wszText, i->rc.left, i->rc.top, i->rc.right, i->rc.bottom);
                ::TextOut(hdc, xPos, y, buf, (int)wcslen(buf));
                y += yLine;
            }
        }

        ::SelectObject(hdc, fontOld);

        ::EndPaint(hwnd, &ps);
    }

    void CSpyWnd::OnSize(HWND hwnd, UINT state, int cx, int cy)
    {
        UpdateScrollInfo();
    }

    void CSpyWnd::OnVScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
    {
        SCROLLINFO si;
        si.cbSize = sizeof(SCROLLINFO);
        si.fMask = SIF_ALL;
        ::GetScrollInfo(hwnd, SB_VERT, &si);

        switch (code)
        {
        case SB_THUMBTRACK:
        case SB_THUMBPOSITION:
            SetScrollPos(hwnd, SB_VERT, si.nTrackPos, TRUE);
            break;
        }

        m_yBase = -pos;
        Invalidate();
    }

    void CSpyWnd::OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
    {
        HDC hdc = ::GetWindowDC(m_hWnd);
        HGDIOBJ fontOld = ::SelectObject(hdc, m_fontSimSun);

        TEXTMETRIC tm;
        ::GetTextMetrics(hdc, &tm);

        y -= m_yBase;
        int yLine = tm.tmExternalLeading + tm.tmHeight + c_yGap;
        int nSelected = y / yLine;

        // 最上面的一行不算
        m_pSpy->Select(nSelected - 1);

        ::SelectObject(hdc, fontOld);
        ::ReleaseDC(m_hWnd, hdc);

        Invalidate();
    }
}