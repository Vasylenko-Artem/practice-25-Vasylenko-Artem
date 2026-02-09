package drink;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class OrderCollection implements Iterable<Drink> {

    private List<Drink> orders = new ArrayList<>();

    public void add(Drink drink) {
        orders.add(drink);
    }

    public Iterator<Drink> iterator() {
        return orders.iterator();
    }
}
