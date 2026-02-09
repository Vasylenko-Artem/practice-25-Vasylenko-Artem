package drink;

public class MilkDecorator extends DrinkDecorator {

    public MilkDecorator(Drink drink) {
        super(drink);
    }

    public Drink clone() {
        return new MilkDecorator(drink.clone());
    }

    public String getDescription() {
        return drink.getDescription() + " + Milk";
    }

    public double getCost() {
        return drink.getCost() + 10;
    }
}
