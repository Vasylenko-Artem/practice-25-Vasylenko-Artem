package app;

public class FancyPrinter extends PrinterDecorator {

    public FancyPrinter(StudPrinter printer) {
        super(printer);
    }

    @Override
    public void print() {
        System.out.println("***** STUDENT INFO *****");
        super.print();
        System.out.println("************************");
    }
}
