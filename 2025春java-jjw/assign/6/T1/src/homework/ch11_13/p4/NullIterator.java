package homework.ch11_13.p4;


public class NullIterator implements ComponentIterator {
    @Override
    public boolean hasNext() {
        return false;
    }

    @Override
    public Component next() {
        return null;
    }
}
