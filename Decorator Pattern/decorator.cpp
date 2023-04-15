#include <iostream>
#include <string>

using namespace std;

class Beverage
{
public:
    string description = "Unknown Beverage";

    virtual string getDescription()
    {
        return description;
    }

    virtual double cost() = 0;
};

class CondimentDecorator : public Beverage
{
public:
    virtual string getDescription() = 0;
};

class Espresso : public Beverage
{
public:
    Espresso() { description = "Espresso"; }

    double cost()
    {
        return 1.99;
    }
};

class HouseBlend : public Beverage
{
public:
    HouseBlend() { description = "House Blend Coffee"; }

    double cost()
    {
        return 0.89;
    }
};

class DarkRoast : public Beverage
{
public:
    DarkRoast() { description = "Dark Roast Coffee"; }

    double cost()
    {
        return 0.99;
    }
};

class Mocha : public CondimentDecorator
{
private:
    Beverage* beverage;

public:
    Mocha(Beverage* beverage)
    {
        this->beverage = beverage;
    }

    string getDescription()
    {
        return beverage->getDescription() + ", Mocha";
    }

    double cost()
    {
        return 0.20 + beverage->cost();
    }
};

class Soy : public CondimentDecorator
{
private:
    Beverage* beverage;

public:
    Soy(Beverage* beverage)
    {
        this->beverage = beverage;
    }

    string getDescription()
    {
        return beverage->getDescription() + ", Soy";
    }

    double cost()
    {
        return 0.15 + beverage->cost();
    }
};

class Whip : public CondimentDecorator
{
private:
    Beverage* beverage;

public:
    Whip(Beverage* beverage)
    {
        this->beverage = beverage;
    }

    string getDescription()
    {
        return beverage->getDescription() + ", Whip";
    }

    double cost()
    {
        return 0.10 + beverage->cost();
    }
};

int main()
{
    Beverage* beverage1 = new Espresso();
    cout << beverage1->getDescription() << " $" << beverage1->cost() << endl;

    Beverage* beverage2 = new DarkRoast();
    beverage2 = new Mocha(beverage2);
    beverage2 = new Mocha(beverage2);
    beverage2 = new Whip(beverage2);
    cout << beverage2->getDescription() << " $" << beverage2->cost() << endl;

    Beverage* beverage3 = new HouseBlend();
    beverage3 = new Soy(beverage3);
    beverage3 = new Mocha(beverage3);
    beverage3 = new Whip(beverage3);
    cout << beverage3->getDescription() << " $" << beverage3->cost() << endl;

    return 0;
}
