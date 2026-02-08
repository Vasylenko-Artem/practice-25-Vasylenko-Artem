import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class StudCollection implements Iterable<Stud> {

    private List<Stud> list = new ArrayList<>();

    public void add(Stud s) {
        list.add(s);
    }

    @Override
    public Iterator<Stud> iterator() {
        return list.iterator();
    }
}
