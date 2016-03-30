#pragma once

namespace AceBear
{
    class CBaseWnd
    {
    public:
        CBaseWnd();
        virtual ~CBaseWnd();

        virtual DWORD Init(wchar_t *pwszTitle, CBaseWnd *pParent, const RECT &rc, DWORD dwStyle = WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE);
    protected:
        wchar_t m_wszClsName[64];

        virtual const wchar_t* RegisterCls();
        virtual BOOL CreateWnd(const wchar_t *pwszCls, const wchar_t *pwszTitle, CBaseWnd *pParent, const RECT &rc, DWORD dwStyle);

        static DWORD s_dwTlsThis;
        static LRESULT BaseWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        
        virtual LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    private:
        HWND m_hWnd;
    };

}