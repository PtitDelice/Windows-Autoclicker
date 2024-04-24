#include "controler.h"

class Window
{
    private:
        Controler control;
        std::thread thread;
        HWND hwnd;
        HINSTANCE hInstance;
        std::vector<HWND> vecButtons;
        std::vector<HWND> vecControls;
        int checked,sleepTime=30000;
        int threadStarted=false;

    public:
        HWND hSlider;
        Window();
        ~Window();
        void setHWND(const HWND &hwnd);
        void setHinstance(const HINSTANCE &hInstance);
        void setSleepTime(int sec);
        void setChecked(int checked);
        void createTexts();
        void createInputs();
        void createButtons();
        void toggleThread();
        HWND CreateControl(LPCSTR className, LPCSTR text, HWND hwnd, DWORD style, int x, int y, int width, int height, int controlId);
        HWND CreatePushButton(LPCSTR text, HWND hwnd, int x, int y, int width, int height, DWORD buttonStyle, int buttonId);
};
