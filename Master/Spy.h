#pragma once
#include <vector>

using namespace std;

namespace AceBear
{
    struct WNDESC
    {
        HWND hWnd;
        wchar_t wszText[64];
        RECT rc;
        BOOL bSelected;
    };
 
    class CSpy
    {
    public:
        CSpy();
        virtual ~CSpy();

        DWORD GetProcessId() { return m_dwProcessId; }
        DWORD GetThreadId() { return m_dwThreadId; }
        const wchar_t* GetProcessName() { return m_wszProcessName; }
        const wchar_t* GetWindowName() { return m_wszWindowName; }
        vector<WNDESC>& GetChildren() { return m_vWnds; }
        BOOL Select(int iSelected);

        void MoveSelectedUp(int range);
        void MoveSelectedDown(int range);
        void MoveSelectedLeft(int range);
        void MoveSelectedRight(int range);
        void MoveSelected(POINT point);

        void Switch(DWORD dwProcessId, DWORD dwThreadId, HWND hWnd);
        void Clear();
    protected:
        void FindBaseName();
        void FindChildren();
        void UpdateOne(WNDESC &desc);
    private:
        DWORD m_dwProcessId;
        DWORD m_dwThreadId;
        HANDLE m_hProcess;
        HWND m_hWnd;
        wchar_t m_wszProcessName[256];
        wchar_t m_wszWindowName[256];
        vector<WNDESC> m_vWnds;
        int m_iSelected;

        static BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);
    };

}