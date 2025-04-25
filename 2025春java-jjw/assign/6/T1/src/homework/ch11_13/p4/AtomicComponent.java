package homework.ch11_13.p4;

public class AtomicComponent extends Component{
    public AtomicComponent() {
        super();
    }

    public AtomicComponent(int id, String name, double price) {
        super(id, name, price);
    }

    @Override
    public void add(Component component)  throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Atomic Component has no component any more.");
    }

    @Override
    public void remove(Component component)  throws UnsupportedOperationException {
        throw new UnsupportedOperationException("Atomic Component has no component any more.");
    }

    @Override
    public double calcPrice() {
        return price;
    }

    @Override
    public ComponentIterator createIterator() {
        return new NullIterator();
    }
}
