#include <avr/io.h>

int limit(int val);

class Controller
{
public:
    // P_controller(double constant);
    virtual double update(double ref, double actual) = 0;
    virtual int control(int V_m, int u) = 0;
    virtual ~Controller() {}

// private:
//     double k_p;
//     double k_i;
};

class P_controller : public Controller
{
public:
    P_controller(double constant){ k_p = constant; }
    double update(double ref, double actual){ return k_p * (ref - actual); }
    int control(int V_m, int u){
      int V_m_1 = limit(V_m + u);
      OCR0B = V_m_1;
      return V_m_1;
    }
private:
    double k_p;
};
class PI_controller : public Controller
{
public:
    PI_controller(double constant_p, double constant_i){sum = 0; k_p = constant_p; k_i = constant_i; }
    double update(double ref, double actual){
      int error = ref - actual;
      sum += error*t;
      return k_p * error + k_i * error; 
    }
    int control(int V_m, int u){
      int V_m_1 = limit(V_m + u);
      OCR0B = V_m_1;
      return V_m_1;
    }
private:
    double k_p;
    double k_i;
    int sum;
    double t =0.004;
};

int limit(int val)
{
    if (val > 244)
    {
        return 244;
    }
    if (val < 1)
    {
        return 1;
    }
    return val;
}

int main(){
  P_controller P = P_controller(0.1);
  PI_controller PI = PI_controller(0.1, 0.1);

  return 0;
}