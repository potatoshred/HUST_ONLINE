package homework.ch11_13.p4;

import java.util.Objects;

public class CompositeComponent extends Component {
    protected ComponentList childs;

    public CompositeComponent() {
        super();
        childs = new ComponentList();
    }

    public CompositeComponent(int id, String name, double price) {
        super(id, name, price);
    }

    @Override
    public void add(Component component) {
        if (childs == null) childs = new ComponentList();
        childs.add(component);
    }

    @Override
    public void remove(Component component) {
        if (childs == null || childs.isEmpty()) return;
        childs.remove(component);
    }

    @Override
    public double calcPrice() {
        if (childs == null || childs.isEmpty()) return 0.0;
        double sum = 0.0;
        for (Component component : childs) {
            sum += component.getPrice();
        }
//        ComponentIterator it = createIterator();
//        while (it.hasNext()) {
//            Component component = it.next();
//            sum += component.getPrice();
//        }
        return sum;
    }

    @Override
    public ComponentIterator createIterator() {
        if (childs == null || childs.isEmpty()) return new NullIterator();
        return childs.createIterator();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof CompositeComponent that)) return false;
        if (!super.equals(o)) return false;

        return Objects.equals(childs, that.childs);
    }

    @Override
    public String toString() {
        if (childs == null) {
            childs = new ComponentList();
        }
        StringBuffer sb = new StringBuffer(super.toString() +
                "\n" + childs.size() + " sub components of " + name + ":\n");

        for (Component c : childs) {
            sb.append(c.toString());
        }

        return sb.toString();
    }
}
