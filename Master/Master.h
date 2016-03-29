#pragma once

namespace AceBear {
 
    class CMaster
    {
    public:
        CMaster(HINSTANCE hInstApp);
        virtual ~CMaster();
        DWORD Init(int nCmdShow);
    protected:
        static inline LRESULT MasterWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        BOOL RegisterCls();
        BOOL CreateWnd(int nCmdShow);

        void OnDestroy(HWND hWnd);
    private:
        HINSTANCE m_hInstApp;
        HWND m_hWndMain;
        static const wchar_t c_wszClassName[];
    };

}