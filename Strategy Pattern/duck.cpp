#include <iostream>
#include <string>

using namespace std;

class FlyBehavior
{
  public:
    virtual void fly() = 0; 
};

class FlyWithWings : public FlyBehavior
{
  public:
    void fly(){
      cout << "I'm flying!" << endl;
    }
};

class FlyNoWay : public FlyBehavior
{
  public:
    void fly(){
      cout << "I can't fly!" << endl;
    }
};

class QuackBehavior
{
  public:
    virtual void quack() = 0; 
};

class Quack : public QuackBehavior
{
  public:
    void quack(){
      cout << "Quack!" << endl;
    }
};

class MuteQuack : public QuackBehavior
{
  public:
    void quack(){
      cout << "<<Silence>>" << endl;
    }
};

class Squeak : public QuackBehavior
{
  public:
    void quack(){
      cout << "Squeak!" << endl;
    }
};

class Duck
{
  public:
    FlyBehavior* flyBehavior; 
    QuackBehavior* quackBehavior; 

  public:
    Duck() {
      flyBehavior = 0; 
      quackBehavior = 0; 
    }

    virtual void display() = 0; // Make display() a pure virtual function

    void performFly() { 
      flyBehavior->fly();
    }

    void performQuack() { 
      quackBehavior->quack();
    }

    void swim() {
      cout << "All ducks float, even decoys!" << endl;
    }

    void setFlyBehavior(FlyBehavior* fb) { // Setter for flyBehavior
      flyBehavior = fb;
    }

    void setQuackBehavior(QuackBehavior* qb) { // Setter for quackBehavior
      quackBehavior = qb;
    }
};

class MallardDuck : public Duck
{
  public:
    MallardDuck() {
      quackBehavior = new Quack();
      flyBehavior = new FlyWithWings();
    }

    void display(){
      cout << "I'm a mallard" << endl;
    }
}; 

class ModelDuck : public Duck
{
  public:
    ModelDuck() {
      flyBehavior = new FlyNoWay();
      quackBehavior = new Squeak();
    }

    void display(){
      cout << "I'm a model duck!" << endl;
    }
};

int main() {
  MallardDuck mallard;
  mallard.display();
  mallard.performQuack();
  mallard.performFly();

  ModelDuck duck;
  duck.display();
  duck.performQuack();
  duck.setFlyBehavior(new FlyWithWings());
  duck.performFly();
  return 0;
}


