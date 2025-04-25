package homework.ch11_13.p4;

import java.util.Objects;

public abstract class Component {
    protected int id;
    protected String name;
    protected double price;

    public Component() {
    }

    public Component(int id, String name, double price) {
        this.id = id;
        this.name = name;
        this.price = price;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getPrice() {
        price = calcPrice();
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public abstract void add(Component component) throws UnsupportedOperationException;

    public abstract void remove(Component component) throws UnsupportedOperationException;

    public abstract double calcPrice();

    public abstract ComponentIterator createIterator();

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Component component)) return false;

        return getId() == component.getId() && Double.compare(getPrice(), component.getPrice()) == 0 && Objects.equals(getName(), component.getName());
    }

    @Override
    public String toString() {
        return "id=" + id +
                ", name='" + name + '\'' +
                ", price=" + calcPrice() + "\n";
    }
}
