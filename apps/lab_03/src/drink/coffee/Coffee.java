package drink.coffee;

import drink.Drink;

public class Coffee implements Drink {

    public Drink clone() {
        return new Coffee();
    }

    public String getDescription() {
        return "Coffee";
    }

    public double getCost() {
        return 30;
    }
}
