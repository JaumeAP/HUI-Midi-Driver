#ifndef HUITIMER_H
#define HUITIMER_H

class HUITimer {
public:
    HUITimer();
    ~HUITimer();
    virtual void timer() {};
private:
    void start();
    void stop();
};


#endif // HUITIMER_H