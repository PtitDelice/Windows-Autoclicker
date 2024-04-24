#include "window.h"

Window::Window(){
    checked=1;
}

Window::~Window(){
    hwnd=nullptr;
    vecButtons.clear();
    vecControls.clear();
}
void Window::setHWND(const HWND &hwnd){
    this->hwnd=hwnd;
}

void Window::setHinstance(const HINSTANCE &hInstance){
    this->hInstance=hInstance;
}

void Window::setSleepTime(int sec){
    sleepTime=sec;
}

void Window::createTexts(){
    // Title
    CreateControl("STATIC","Autocliqueur",hwnd,SS_CENTER | BS_CENTER | WS_BORDER,100,10,400,30,NULL);

    // Time
    CreateControl("STATIC","Temps entre chaque appui : ",hwnd,SS_CENTER | BS_CENTER,150,80,300,30,NULL);

    // Slider
    hSlider=CreateControl(TRACKBAR_CLASS,NULL,hwnd,NULL,100,120,400,20,10);
    SendMessage(hSlider, TBM_SETRANGE, TRUE, MAKELPARAM(0, 30000));
    SendMessage(hSlider, TBM_SETPOS, TRUE, 30000);

    // Textbox static
    CreateControl("STATIC","millisecondes",hwnd,SS_CENTER,300,150,100,20,NULL);

    // Barrier
    CreateControl("STATIC", NULL,hwnd, SS_ETCHEDHORZ, 50,190,500,2,NULL);
    CreateControl("STATIC", NULL,hwnd, SS_ETCHEDHORZ, 50,310,500,2,NULL);

    // Radio buttons
    CreateControl("STATIC","Choix de la touche : ",hwnd,SS_CENTER | BS_CENTER,150,210,300,30,NULL);

    CreateControl("STATIC","En pause",hwnd,SS_CENTER | BS_CENTER | WS_BORDER,150,400,300,30,5);
}

void Window::createInputs(){
    CreateControl("EDIT","30000",hwnd,WS_BORDER | SS_CENTER,240,150,50,20,10);
}

void Window::createButtons(){
    CreatePushButton("Clique Gauche",hwnd, 70, 260, 150, 30, BS_AUTORADIOBUTTON, 1);
    CreatePushButton("Clique Droit",hwnd, 230, 260, 150, 30, BS_AUTORADIOBUTTON, 2);
    CreatePushButton("Entrée",hwnd, 400, 260, 150, 30, BS_AUTORADIOBUTTON, 3);

    CreatePushButton("Démarrer/Pause (F2)",hwnd, 230, 330, 150, 30, NULL, 4);
    // Default
    SendMessage(vecButtons[0], BM_SETCHECK, BST_CHECKED, 0);
}





void Window::setChecked(int checked){
    this->checked = checked;
    int input;
        switch(checked){
            case 1:
                input=MOUSEEVENTF_LEFTDOWN;
                break;
            case 2:
                input=MOUSEEVENTF_RIGHTDOWN;
                break;
            case 3:
                input=VK_RETURN;
                break;
            default :
                input=MOUSEEVENTF_LEFTDOWN;
        }
    control.setInput(input);
}

HWND Window::CreateControl(LPCSTR className, LPCSTR text, HWND hwnd, DWORD style, int x, int y, int width, int height, int controlId)
{
    HWND control = CreateWindow(
        className,
        text,
        style | WS_VISIBLE | WS_CHILD,
        x, y,
        width, height,
        hwnd,
        (HMENU)controlId,
        hInstance,
        NULL
    );
    vecControls.push_back(control);
    return control;
}

HWND Window::CreatePushButton(LPCSTR text, HWND hwnd, int x, int y, int width, int height, DWORD buttonStyle, int buttonId){
    HWND button = CreateWindow(
        "BUTTON",
        text,
        WS_VISIBLE | WS_CHILD | buttonStyle,
        x, y, width, height,
        hwnd,
        (HMENU)buttonId,
        hInstance,
        NULL
    );
    vecButtons.push_back(button);
    return button;
}

void Window::toggleThread(){
    if(!threadStarted){
        control.setSleepTime(sleepTime);
        if(sleepTime<1000){
            thread = std::thread(&Controler::execInput,&control);
        }
        else
            thread = std::thread(&Controler::execInputSafe,&control,100);
        SetWindowText(GetDlgItem(hwnd,5), "En cours");
    }
    else{
        control.toggleStopFlag();
        thread.join();
        SetWindowText(GetDlgItem(hwnd,5), "En pause");
    }
    threadStarted=!threadStarted;
}


