#include<iostream>
#include<chrono>
#include<thread>
using namespace std;

double simulationTime = 0;
double fixedTime = 20;
bool isLoop = true;

bool Quit()
{
    return !isLoop;
}

double GetTime(const std::chrono::time_point<std::chrono::steady_clock>& realTime, const std::chrono::time_point<std::chrono::steady_clock>& nextTime)
{
    auto interval = realTime - nextTime;
    double milliseconds = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(interval).count();
    return milliseconds;
}


void FixedUpdate()
{
    printf("我是FixedUpdate");
    cout << endl;
}

void Update()
{
    printf("我是Update");
    cout << endl;
    //std::this_thread::sleep_for(std::chrono::milliseconds(20));
}

//主线程主循环
void Loop(int framenumber = 50)
{
    auto startTime = std::chrono::steady_clock::now();
    auto nextTime = startTime;
    auto realTime = startTime;
    auto lastTime = startTime;
    fixedTime = 1000 / framenumber;
    int  i = 0;
    while (!Quit()&&i<=10)
    {
        realTime = std::chrono::steady_clock::now();
        while(realTime>=nextTime)
        {
            simulationTime += GetTime(realTime, lastTime);
            while (simulationTime > fixedTime)
            {
                simulationTime -= fixedTime;
                FixedUpdate();
            }
            lastTime = nextTime;
            nextTime += std::chrono::milliseconds((int)fixedTime);
            Update();
            i++;
        }
    }
}

int mainLoop()
{
    Loop();

    return 0;
}