package homework.ch11_13.p4;

import java.util.ArrayList;

public class ComponentList extends ArrayList<Component> implements ComponentIterator {

    private int position = 0;

    public ComponentList() {
        super();
        position = 0;
    }

    @Override
    public boolean hasNext() {
//        if(position < size()){
//            return true;
//        }else {
//            this.position = 0;
//            return false;
//        }
        return position < size();
    }

    @Override
    public Component next() {
        return get(position++);
    }

    public ComponentIterator createIterator() {
        this.position = 0;
        return new CompositeIterator(this);
    }
}
