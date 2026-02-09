package app;

import drink.Drink;
import drink.MilkDecorator;
import drink.OrderCollection;
import drink.coffee.Coffee;

public class Main {

    public static void main(String[] args) {

        Drink coffee = new Coffee();
        Drink milkCoffee = new MilkDecorator(coffee);
        Drink copy = milkCoffee.clone();

        OrderCollection orders = new OrderCollection();
        orders.add(milkCoffee);
        orders.add(copy);
		orders.add(coffee);

        for (Drink d : orders) {
            System.out.println(d.getDescription() + " = " + d.getCost());
        }

		int sum = 0;
		for (Drink d : orders) {
			sum += d.getCost();
		}
		System.out.println("Total cost = " + sum);
    }
}
