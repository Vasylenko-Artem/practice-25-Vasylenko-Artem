public class BasicPrinter implements StudPrinter {

    private Stud stud;

    public BasicPrinter(Stud stud) {
        this.stud = stud;
    }

    @Override
    public void print() {
        stud.print();
    }
}
