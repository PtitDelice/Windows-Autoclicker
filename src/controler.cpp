#include "controler.h"


void Controler::setInput(int input){
    this->input=input;
}

void Controler::setSleepTime(int sleepTime){
    this->sleepTime=sleepTime;
}

void Controler::mySleep(int milliseconds) {
    clock_t start = clock();

    clock_t ticksToWait = milliseconds * CLOCKS_PER_SEC / 1000;

    while (clock() < start + ticksToWait && !stopFlag) {
        // Limit CPU use
        Sleep(100);
    }
}

void Controler::execInputSafe(int sleepBetween){
    stopFlag=false;
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> randomBetween(sleepBetween-sleepBetween/3, sleepBetween+sleepBetween/3);
    std::uniform_int_distribution<> randomSleepTime(sleepTime-sleepTime/10, sleepTime+sleepTime/5);

    while(!stopFlag){
        int randomDelay = randomBetween(gen);
        if(input==MOUSEEVENTF_LEFTDOWN ){
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            Sleep(randomDelay);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
        else if(input==MOUSEEVENTF_RIGHTDOWN){
            mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
            Sleep(randomDelay);
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        }
        else{
            keybd_event(input, 0, 0, 0);
            Sleep(randomDelay);
            keybd_event(input, 0, KEYEVENTF_KEYUP, 0);
        }
        randomDelay = randomSleepTime(gen);
        mySleep(randomDelay);
    }
}

void Controler::execInput(){
    stopFlag=false;

    while(!stopFlag){
        if(input==MOUSEEVENTF_LEFTDOWN ){
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
        else if(input==MOUSEEVENTF_RIGHTDOWN){
            mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        }
        else{
            keybd_event(input, 0, 0, 0);
            keybd_event(input, 0, KEYEVENTF_KEYUP, 0);
        }
        Sleep(sleepTime);
    }
}


void Controler::toggleStopFlag(){
    stopFlag=!stopFlag;
}
