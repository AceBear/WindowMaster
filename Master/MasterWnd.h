#pragma once
#include "Spy.h"
#include "ToolWnd.h"
#include "SpyWnd.h"

namespace AceBear {
 
    class CMasterWnd : public CBaseWnd
    {
    public:
        CMasterWnd(HINSTANCE hInstApp);
        virtual ~CMasterWnd();

        static HINSTANCE GetAppInst();
        static CMasterWnd* GetMainWnd();

        RECT CalcPos();
    protected:
        LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        virtual const wchar_t* RegisterCls();

        BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
        void OnDestroy(HWND hWnd);
        void OnSize(HWND hwnd, UINT state, int cx, int cy);
        void OnSwitchSpy(WPARAM wParam, LPARAM lParam);
    private:
        static const wchar_t c_wszClassName[];
        HINSTANCE m_hInstApp;
        HWND m_hWndMain;

        CSpy m_spy;
        CToolWnd m_wndTool;
        CSpyWnd m_wndSpy;
    };

}