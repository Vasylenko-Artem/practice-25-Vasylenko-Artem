package app;

import java.util.*;

public class Main {
    public static void main(String[] args) {

        // Prototype 
        Stud original = new Stud(1, 1000);
        Stud clone = (Stud) original.clone();
        clone.setStipend(2000);

        // Iterator 
        StudCollection collection = new StudCollection();
        collection.add(original);
        collection.add(clone);

        // Decorator + Iterator 
        for (Stud s : collection) {

            StudPrinter printer =
                    new FancyPrinter(
                            new BasicPrinter(s)
                    );

            printer.print();
        }
    }

}