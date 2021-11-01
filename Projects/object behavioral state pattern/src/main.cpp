#include <Arduino.h>
#include <string.h>

class Context;

class State {
  /**
   * @var Context
   */
 protected:
  Context *context_;

 public:
  virtual ~State() {
  }
  void set_context(Context *context) {
    this->context_ = context;
  }

  virtual void HandleStop() = 0;
  virtual void HandleGo() = 0;
  virtual void Entry() = 0;

};

/**
 * The Context defines the interface of interest to clients. It also maintains a
 * reference to an instance of a State subclass, which represents the current
 * state of the Context.
 */
class Context {
  /**
   * @var State A reference to the current state of the Context.
   */
 private:
  State *state_;

 public:
  Context(State *state) : state_(nullptr) {
    this->TransitionTo(state);
  }
  ~Context() {
    delete state_;
  }
  
 
  /**
   * The Context allows changing the State object at runtime.
   */
  void TransitionTo(State *state) {
    if (this->state_ != nullptr)
      delete this->state_;
    this->state_ = state;
    this->state_->set_context(this);
    this->state_->Entry();
  }
  /**
   * The Context delegates part of its behavior to the current State object.
   */
  void Stop() {
    this->state_->HandleStop();
  }
  void Go() {
    this->state_->HandleGo();
  }
};

/**
 * Concrete States implement various behaviors, associated with a state of the
 * Context.
 */

class Red : public State {
 public:
  void HandleStop() override{
    Serial.println("Red -> Red");
  }
  
  void HandleGo() override;
  void Entry() override{};
};

class Green : public State {
 public:
  void HandleStop() override;
  void HandleGo() override {
    Serial.println("Green -> Green");
  }
  void Entry() override{};
};

class Yellow : public State {
 public:
  void HandleStop() override {
    Serial.println("Yellow -> Yellow");
  }
  void HandleGo() override {
    Serial.println("Yellow -> Yellow");
  }
  void Entry() override {
    // Serial.println("Green -> Yellow");
    _delay_ms(2000);
    Serial.println("Yellow -> Red");
    this->context_->TransitionTo(new Red);
  }
};

void Red::HandleGo() {
  Serial.println("Red -> Green");
  this->context_->TransitionTo(new Green);
}

void Green::HandleStop() {
  Serial.println("Green -> Yellow");
  this->context_->TransitionTo(new Yellow);
}


/**
 * The client code.
 */
void streetlights() {
  int command;
  Context *context = new Context(new Red);
  while(1){
    if (Serial.available() > 0){
      command = Serial.read();
      switch (command){
        case 'g':
          context->Go();
          break;
        case 's':
          context->Stop();
          break;
      }
    }
  }
  delete context;
}


int main() {
  init();
  Serial.begin(9600);
  char paddo[10] = "ass" + "or pass";
  Serial.println("ass" + "or pass");
  streetlights();
  return 0;
}