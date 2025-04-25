package homework.ch11_13.p4;

import java.util.ArrayList;
import java.util.List;

public class CompositeIterator implements ComponentIterator {

    protected List<ComponentIterator> iterators;

    CompositeIterator(ComponentIterator iterator){
        iterators = new ArrayList<>();
        iterators.add(iterator);
    }

    @Override
    public boolean hasNext() {
        while (!iterators.isEmpty()){
            if (iterators.get(0).hasNext()) break;
            iterators.remove(0);
        }
        return !iterators.isEmpty();
    }

    @Override
    public Component next() {
        Component c = iterators.get(0).next();
        iterators.add(c.createIterator());
        return c;
    }

}
