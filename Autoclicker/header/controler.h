#include <chrono>
#include <random>
#include <Windows.h>
#include <vector>
#include <thread>
#include <commctrl.h>

class Controler{
    private:
        bool stopFlag=false;
        int input=MOUSEEVENTF_LEFTDOWN,sleepTime=30000;
    public:
        void setSleepTime(int sleepTime);
        void setInput(int input);


        void execInput();
        // Execute the input
        void execInputSafe(int sleepBetween);

        // Toggle stopFlag boolean
        void toggleStopFlag();

        // Check stopFlag when sleeping
        void mySleep(int milliseconds);
};
