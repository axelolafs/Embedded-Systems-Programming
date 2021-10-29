#ifndef P_CONTROLLER_H
#define P_CONTROLLER_H

class Controller
{
public:
    // P_controller(double constant);
    virtual double update(double ref, double actual) = 0;
    virtual int control(int V_m, int u) = 0;

// private:
//     double k_p;
//     double k_i;
};
class P_controller : public Controller
{
public:
    P_controller(double constant);
private:
    double k_p;
}

#endif