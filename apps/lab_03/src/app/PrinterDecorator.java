package app;

public abstract class PrinterDecorator implements StudPrinter {
    protected StudPrinter printer;

    public PrinterDecorator(StudPrinter printer) {
        this.printer = printer;
    }

    public void print() {
        printer.print();
    }
}
