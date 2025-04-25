package homework.ch11_13.p3;

import java.util.Objects;

/**
 * This class represents a person with a name and an age.
 * It implements the Cloneable interface to allow cloning of objects.
 *
 * @author potatoshred
 * @version 1.0
 * @date 2025-03-26
 */
public class Person implements Cloneable {

    private String name;
    private int age;

    public Person() {

    }

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    @Override
    public String toString() {
        return "Person{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Person person)) return false;
        return age == person.age
                && Objects.equals(name, person.name);
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        Person newPerson = (Person) super.clone();
        newPerson.name = new String(name);
        newPerson.age = age;
        return newPerson;
    }
}
