#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PizzaIngredientFactory {
public:
  virtual string createDough() = 0;

  virtual string createSauce() = 0;

  virtual string createCheese() = 0;

  virtual vector<string> createVeggies() = 0;

  virtual string createPepperoni() = 0;
  
  virtual string createClam() = 0;
};

class NYPizzaIngredientFactory : public PizzaIngredientFactory {
public:
  string createDough() {return "thin crust dough";}

  string createSauce() {return "Marinara sauce";}

  string createCheese() {return "Reggiano cheese";}

  vector<string> createVeggies() {
    vector<string> result;
    result.push_back("garlic");
    result.push_back("onion");
    result.push_back("mushroom");
    result.push_back("red pepper");
    return result;
  }

  string createPepperoni() {return "sliced pepperoni";}
  
  string createClam() {return "fresh clams";}
};

class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory {
public:
  string createDough() {return "thick burned dough";}

  string createSauce() {return "ripe tomato sauce";}

  string createCheese() {return "Mozzarella cheese";}

  vector<string> createVeggies() {
    vector<string> result;
    result.push_back("rosemary");
    result.push_back("onion");
    result.push_back("pineapple");
    result.push_back("black pepper");
    return result;
  }

  string createPepperoni() {return "hot pepperoni";}
  
  string createClam() {return "frozen clams";}
};

class Pizza
{
public:
    string name;
    string dough;
    string sauce;
    string cheese;
    string clam;
    vector<string> veggies;
    PizzaIngredientFactory* ingredientFactory;

    virtual void prepare() = 0;

    void bake() {
        cout << "Bake for 25 minutes at 350" << endl;
    }

    void cut() {
        cout << "Cutting the pizza into diagonal slices" << endl;
    }

    void box() {
        cout << "Place pizza in official PizzaStore box" << endl;
    }

    string getName() {
        return name;
    }
};

class CheesePizza : public Pizza {
public:
    CheesePizza(PizzaIngredientFactory* ingredientFactory) {
      name = "Cheese Pizza";
      this->ingredientFactory = ingredientFactory;
    }

    void prepare(){
      cout << "Preparing " << name << endl;
      dough = ingredientFactory->createDough();
      cout << "\t Using " << dough << endl;
      sauce = ingredientFactory->createSauce();
      cout << "\t Using " << sauce << endl;
      cheese = ingredientFactory->createCheese();
      cout << "\t Using " << cheese << endl;
    }
};

class VeggiePizza : public Pizza {
public:
    VeggiePizza(PizzaIngredientFactory* ingredientFactory) {
      name = "Veggie Pizza";
      this->ingredientFactory = ingredientFactory;
    }

    void prepare(){
      cout << "Preparing " << name << endl;
      dough = ingredientFactory->createDough();
      cout << "\t Using " << dough << endl;
      sauce = ingredientFactory->createSauce();
      cout << "\t Using " << sauce << endl;
      veggies = ingredientFactory->createVeggies();
      for (int i = 0; i < veggies.size(); i++) {
        cout << "\t Adding " << veggies[i] << endl;
      }
      cheese = ingredientFactory->createCheese();
      cout << "\t Using " << cheese << endl;
    }
};

class ClamPizza : public Pizza {
public:
    ClamPizza(PizzaIngredientFactory* ingredientFactory) {
      name = "Clam Pizza";
      this->ingredientFactory = ingredientFactory;
    }

    void prepare(){
      cout << "Preparing " << name << endl;
      dough = ingredientFactory->createDough();
      cout << "\t Using " << dough << endl;
      sauce = ingredientFactory->createSauce();
      cout << "\t Using " << sauce << endl;
      clam = ingredientFactory->createClam();
      cout << "\t Using " << clam << endl;
      cheese = ingredientFactory->createCheese();
      cout << "\t Using " << cheese << endl;
    }
};

class PizzaStore {
public:
    virtual Pizza* createPizza(string type) = 0;

    Pizza* orderPizza(string type) {
        Pizza* pizza = createPizza(type);
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();
        return pizza;
    }
};

class NYPizzaStore : public PizzaStore {
public:
    Pizza* createPizza(string type) {
        Pizza* pizza = nullptr;
        PizzaIngredientFactory* ingredientFactory = new NYPizzaIngredientFactory();

        if (type == "cheese pizza") {
            pizza = new CheesePizza(ingredientFactory);
        } else if (type == "veggie pizza") {
            pizza = new VeggiePizza(ingredientFactory);
        } else if (type == "clam pizza") {
            pizza = new ClamPizza(ingredientFactory);
        }
        pizza->name = "New York Style " + pizza->name;

        return pizza;
    }
};

class ChicagoPizzaStore : public PizzaStore {
public:
    Pizza* createPizza(string type) {
        Pizza* pizza = nullptr;
        PizzaIngredientFactory* ingredientFactory = new ChicagoPizzaIngredientFactory();

        if (type == "cheese pizza") {
            pizza = new CheesePizza(ingredientFactory);
        } else if (type == "veggie pizza") {
            pizza = new VeggiePizza(ingredientFactory);
        } else if (type == "clam pizza") {
            pizza = new ClamPizza(ingredientFactory);
        }
        pizza->name = "Chicago Style " + pizza->name;

        return pizza;
    }
};

int main() {
    PizzaStore* nyStore = new NYPizzaStore();
    PizzaStore* chicagoStore = new ChicagoPizzaStore();

    Pizza* pizza = nyStore->orderPizza("cheese pizza");
    cout << "Ethan ordered a " << pizza->getName() << endl << endl;

    pizza = chicagoStore->orderPizza("veggie pizza");
    cout << "Joel ordered a " << pizza->getName() << endl << endl;

    pizza = nyStore->orderPizza("clam pizza");
    cout << "Ethan ordered a " << pizza->getName() << endl << endl;

    pizza = chicagoStore->orderPizza("clam pizza");
    cout << "Joel ordered a " << pizza->getName() << endl << endl;

    return 0;
}