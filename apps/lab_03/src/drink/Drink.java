package drink;

public interface Drink extends Cloneable {
    Drink clone();
    String getDescription();
    double getCost();
}
