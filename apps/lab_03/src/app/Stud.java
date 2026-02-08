package app;

public class Stud implements Prototype {
    private int id;
    private int stipend;

    public Stud(int id, int stipend) {
        this.id = id;
        this.stipend = stipend;
    }

    public void setStipend(int stipend) {
        this.stipend = stipend;
    }
    
    public void print() {
        System.out.println("Stud id=" + id + " stipend=" + stipend);
    }

    @Override
    public Prototype clone() {
        return new Stud(id, stipend);
    }
}
