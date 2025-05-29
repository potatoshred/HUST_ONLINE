package hust.cs.java.c6_methods;

public class C6 {
}
class TestChangeableParam {
    static void print(String...args) {   //可看作String []args
        for (String temp : args)
            System.out.println(temp);
        System.out.println(args.length);
    }
    public static void main(String[] args) {
        print("Welcome", "Java", "Cpp", "Java", "C++", "Java");
    }
}