#include "window.h"

Window win;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN) {
            KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*)lParam;
            DWORD key = kbStruct->vkCode;
            if (key == VK_F2) {
                win.toggleThread();
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_HSCROLL:
        if ((HWND)lParam == win.hSlider) {
            int value = SendMessage(win.hSlider, TBM_GETPOS, 0, 0);
            char buffer[32];
            sprintf(buffer, "%d", value);
            SetWindowText(GetDlgItem(hwnd,10), buffer);
        }
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) // Button check 1
            win.setChecked(1);
        else if (LOWORD(wParam) == 2) // Button check 2
            win.setChecked(2);
        else if (LOWORD(wParam) == 3) // Button check 3
            win.setChecked(3);
        else if (LOWORD(wParam) == 4) // Button start
            win.toggleThread();
        else if (LOWORD(wParam) == 10) { // Textbox
            if (HIWORD(wParam) == EN_CHANGE) {
                TCHAR buffer[256];
                GetDlgItemText(hwnd, 10, buffer, 256);
                try{
                    int number = std::stoi(buffer);
                    win.setSleepTime(number);
                    // slider's maximum is 30k
                    if(number>30000)
                        number==30000;
                    SendMessage(win.hSlider, TBM_SETPOS, TRUE, number);
                }
                catch (const std::invalid_argument& e){
                    SetWindowText(GetDlgItem(hwnd,10),"0");
                }
            }
        }
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Autoclick";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    HWND hwnd = CreateWindowEx(
        0,
        "Autoclick",
        "Autoclick",
        dwStyle,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 500,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        return 0;
    }
    win.setHWND(hwnd);
    win.setHinstance(hInstance);
    ShowWindow(hwnd, nCmdShow);
    win.createButtons();
    win.createInputs();
    win.createTexts();

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    DestroyWindow(hwnd);
    UnhookWindowsHookEx(hHook);
    return 0;
}
