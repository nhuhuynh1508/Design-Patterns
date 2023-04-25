#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Pizza
{
    public:
        string name;
        string dough;
        string sauce;
        vector<Toppings> toppings;

        void prepare()
        {
            cout << "Preparing " << name << endl;
            cout << "Tossing dough... " << dough << endl;
            cout << "Adding sauce... " << sauce << endl;
            cout << "Adding toppings..." << endl;
            for (int i = 0; i < toppings.size(); i++)
            {
                cout << "\t" << toppings[i];
            }
        } 

        void bake()
        {
            cout << "Bake for 25 minutes at 350" << endl;
        }

        void cut()
        {
            cout << "Cutting the pizza into diagonal slices" << endl;
        }

        void box()
        {
            cout << "Place pizza in official PizzaStore box" << endl;
        }

        string getName()
        {
            return name;
        }
};

class CheesePizza : public Pizza
{
    public:
        CheesePizza(string dough, string sauce, string cheese, string clams) 
        {
            name = "Cheese Pizza";
        }
}
 

class PizzaStore
{
    public:
    virtual Pizza createPizza() = 0;
    Pizza orderPizza(string type)
    {
        Pizza pizza;
        pizza = createPizza(type);

        pizza.prepare();
        pizza.bake();
        pizza.cut();
        pizza.box();

        return pizza;
    }

};

class NYPizzaStore
{
    public:
        Pizza createPizza() {

        };
}

