package hust.cs.java.c9_class;


import java.util.Arrays;
import java.util.List;
import java.util.Objects;

public class C9 {
}

/**************************/

class ConstructorTest {
    //构造函数前面不能有void/dataType
    public ConstructorTest() {
        System.out.println("constructor");
    }

    public static void main(String... args) {
        //先调用构造，再调用void ConstructorTest()
        new ConstructorTest().ConstructorTest();
    }

    //如果和类名同名函数前面加了void(可返回任何类型), 编译器看成是普通函数，这和C++不一样
    public void ConstructorTest() {
        System.out.println("normal instance method return void");
    }

    public double ConstructorTest(double d) {
        System.out.println("normal method return double");
        return d;
    }
}

/**************************/

class Father {
    public static char gender = 'F';
    public int age;

    public Father() {
        System.out.println("Father()");
    }

    public Father(int age) {
        this.age = age;
        System.out.println("Father(int age)");
    }

    public static void getGender() {
        System.out.println("Father gender " + gender);
    }

    public void getAge() {
        System.out.println("Father age " + age);
    }

}

class Child extends Father {

    public static char gender = 'C';
    public int age;

    public Child() {
        System.out.println("Child()");
    }

    // Overload
    public Child(int age) {
        super(age + 27);
        this.age = age;
        System.out.println("Child(int age)");
    }

    // Overload
    public Child(int age, char gender) {
        super(age + 27);
        this.age = age;
        gender = gender;
        System.out.println("Child(int age)");
    }

    // Overhide
    public static void getGender() {
        System.out.println("Child gender " + gender);
    }

    @Override
    public void getAge() {
        System.out.println("Child age " + age);
    }
}

class TestOverhide {
    public static void main(String[] args) {
        Father f = new Child(18);// Father(int age) \n Child(int age)
        f.getAge();                  // Child age 18
        f.getGender();               // Father gender F

        System.out.println(f.age);   // 45
        System.out.println(f.gender);// F

        Child c = (Child) f;
        c.getAge();                  // Child age 18
        c.getGender();               // Child gender C
        System.out.println(c.age);   // 18
        System.out.println(c.gender);// C
    }
}

/**************************/


class L {
    static {
        System.out.println("L static init block");
    }

    {
        System.out.println("L instance init block");
    }

    L() {
        System.out.println("L()");
    }
}

class M extends L {
    static {
        System.out.println("M static init block");
    }

    {
        System.out.println("M instance init block");
    }

    M() {
        System.out.println("M()");
    }
}

class N extends L {
    static {
        System.out.println("N static init block");
    }

    {
        System.out.println("N instance init block");
    }

    N() {
        System.out.println("N()");
    }
}

/**
 * InitDemo static init block1
 * InitDemo static init block2
 * InitDemo static main entry
 * InitDemo instance init block1
 * InitDemo instance init block2
 * L static init block
 * M static init block
 * L instance init block
 * L()
 * M instance init block
 * M()
 * N static init block
 * L instance init block
 * L()
 * N instance init block
 * N()
 */
class InitDemo {
    static {
        System.out.println("InitDemo static init block1");
    }

    static {
        System.out.println("InitDemo static init block2");
    }

    {
        System.out.println("InitDemo instance init block1");
    }

    {
        System.out.println("InitDemo instance init block2");
    }

    InitDemo() {
        new M();
        new N();
    }

    public static void main(String[] args) {
        System.out.println("InitDemo static main entry");
        new InitDemo();
    }
}


/**************************/

class A {
    static void s(int m) {
        System.out.println("A.s(int) " + m);
    }

    void f(int m) {
        System.out.println("A.f(int) " + m);
    }

    void f(double m) {
        System.out.println("A.f(double) " + m);
    }
}

class B extends A {
    static void s(int m) {
        System.out.println("B.s(int) " + m);
    }

    static void s(byte m) {
        System.out.println("B.s(byte) " + m);
    }

    void f(int m) {
        System.out.println("B.f(int) " + m);
    }

    void f(byte m) {
        System.out.println("B.f(byte) " + m);
    }
//    void f(long m) { System.out.println("B.f(long) " + m);}

    void f(double m) {
        System.out.println("B.f(double) " + m);
    }
}

class TestOverride {
    public static void main(String[] args) {
        byte t1 = 18, t2 = 15;
        A a = new B();
        a.f(t1); // B.f(int)
        a.s(t2); // A.s(int)

        B b = (B) a;
        b.f(t1); // B.f(byte)
        b.s(t2); // B.s(byte)

        b.f(18); // B.f(int)
        b.f(18L); // B.f(long)
        b.f(18D); // B.f(double)
        b.f(18F); // B.f(double)
        b.f(0x18); // B.f(int)
        b.f(0x1818181818L); // B.f(long)
        b.s(15); // B.s(int)

        System.out.println(a.equals(b));
        System.out.println(a instanceof A); // true
        System.out.println(a instanceof B); // true
        System.out.println(b instanceof A); // true
        System.out.println(b instanceof B); // true
        A aa = new A();
        System.out.println(aa instanceof A); // true
        System.out.println(aa instanceof B); // false

        B bb = new B();
        System.out.println(bb instanceof A); // true
        System.out.println(bb instanceof B); // true
    }
}

/**************************/
class Base {
    Base() {
        System.out.print("A");
    }

    public Base(String s) {
        System.out.print("B");
    }

    void Draw() {
        System.out.print("Draw B.");
    }

    void Print() {
        this.Draw();
        System.out.print("Print B.");
    }
}

class Derived extends Base {
    public Derived(String s) {
        System.out.print("D");
    }

    public static void main(String[] args) {
        Derived d = new Derived("C"); // AD
        System.out.println();
        d.Print(); // Draw B.Draw D.Print B.Print D.
    }

    @Override
    void Draw() {
        System.out.print("Draw D.");
    }

    @Override
    void Print() {
        super.Draw();
        super.Print();
        System.out.print("Print D.");
    }
}

/**************************/
class ch11_A {
    static void s(int m) {
        System.out.println("ch11_A s(int):" + m);
    }

    void f(int m) {
        System.out.println("ch11_A f(int):" + m);
    }
}

class ch11_B extends ch11_A {
    static void s(int m) {
        System.out.println("ch11_B s(int):" + m);
    }

    static void s(byte m) {
        System.out.println("ch11_B s(byte):" + m);
    }

    void f(int m) {
        System.out.println("ch11_B f(int):" + m);
    }

    void f(byte m) {
        System.out.println("ch11_B f(byte):" + m);
    }
}

/**
 * ch11_B f(int):18
 * ch11_A s(int):15
 * Next 1
 * ch11_B f(byte):18
 * ch11_B s(byte):15
 * Next 2
 * ch11_B f(int):18
 * ch11_B s(int):15
 */
class TestOverride2 {
    public static void main(String[] args) {
        byte t1 = 18, t2 = 15;
        ch11_A a = new ch11_B();
        a.f(t1);
        a.s(t2);
        System.out.println("Next 1");
        ch11_B b = (ch11_B) a;
        b.f(t1);
        b.s(t2);
        System.out.println("Next 2");
        b.f(18);
        b.s(15);
    }
}
/**************************/

class TestEquals extends Father {
    private int val = 0;
    private String ref;

    private char[] arr;
    private List<Float> list;


    /**
     * 直接父类不是Object，使用super.toString()获得父类的信息字符串，然后和其它信息拼接。
     * 值类型属性、包装类型、String属性直接和其它信息拼接。
     * 一般类类型属性，使用对象.toString()获得信息和其它信息拼接。
     * 数组类型属性，可以使用下面的方法获得信息和其它信息拼接。
     *  Arrays.toString(对象)，可能不是我们需要的格式
     *  循环数组的每一个元素，按照要求的格式拼接成一个字符串，可以使用String拼接，也可以使用StringBuffer、StringBuilder进行拼接
     * 容器类型属性，遍历容器的每一个元素（迭代模式），按照要求的格式拼接成一个字符串，
     * 可以使用String拼接，也可以使用StringBuffer、StringBuilder进行拼接。
     */

    @Override
    public String toString() {
        return "TestEquals{" + super.toString() +
                "val=" + val +
                ", ref='" + ref + '\'' +
                ", arr=" + Arrays.toString(arr) +
                ", list=" + list +
                '}';
    }


    /**
     * 形参o不是当前类的类型，返回false。
     * 直接父类不是Object，super.equals(o)结果为false，直接返回false
     * 依次判断子类每一个实例属性、只要有一个为false，返回false，根据属性类型不同，按照下面的方法判断：
     *    值类型，包装类型，可以用==，!=判断
     *    一般类类型属性（包括String类型），使用equals判断：
     *      对象.equals(其它对象)
     *      Objects.equals(对象1,对象2)
     *      StringBuffer、StringBuilder需要转换成String比较内容
     *    数组类型属性：
     *      对象1==对象2，为真
     *      依次对比对象1和对象2的每一个元素，所有内容相同，结果为真（注意数组元素类型不同，判断内容相同的方法有区别）
     *      Objects.deepEquals(对象1,对象2)
     *      Arrays.equals(对象1,对象2), Arrays.deepEquals(对象1,对象2)
     * 容器类型属性：
     *      对象1==对象2，为真
     *      依次对比对象1和对象2的每一个元素，所有内容相同，结果为真（注意数组元素类型不同，判断内容相同的方法有区别）
     *      Objects.equals(对象1,对象2)
     */

    @Override
    public boolean equals(Object obj) {
        if (obj == null) return false;
        if (this == obj) return true;// 反射性
        if (!(obj instanceof TestEquals)) return false;
        if (!super.equals(obj)) return false;

        TestEquals test = (TestEquals) obj;

        return val == test.val
                && Objects.equals(ref, test.ref)
                && Arrays.equals(arr, test.arr) // 一层比较
                && list.size() == test.list.size() && list.containsAll(test.list); // 一层

    }
}

/****************/
class AA {}

class BB extends AA implements Cloneable {
    int [] arr;
    @Override
    protected Object clone() throws CloneNotSupportedException {
        // A newObj = new A(); //new一个新对象，该方法不好：在有继承关系的情况下，不利于复用父类的clone方法
        BB newObj = (BB)super.clone(); //强烈建议这么做
        newObj.arr = this.arr.clone(); //数组的clone是深拷贝，如果去掉clone，则是浅拷贝
        return newObj;
    }
}

class TestCloneable {
    public static void main(String[] args) throws CloneNotSupportedException {
        AA a = new BB();
        AA newObject = (AA) ((BB)a).clone(); // a未实现cloneable接口
        System.out.println(a == newObject);  // false
    }
}
/****************/

//首先必须实现Cloneable接口
class AAA implements Cloneable{
    public static final int SIZE = 10;
    private int[] values = new int[SIZE]; //A的values成员是数组

    public int[] getValues(){
        return values;
    }
    public void setValues(int[] newValues) {
        this.values = newValues;
    }
    //覆盖equals方法，比较二个A类型对象内容是否一样
    public boolean equals(Object obj) {
        if(obj instanceof A){
            AAA o = (AAA)obj;
            return java.util.Arrays.equals(this.getValues(),o.getValues());
        }
        else return false;
    }
    //覆盖clone方法，提升为public，重新实现为深拷贝
    public Object clone() throws CloneNotSupportedException {
        // A newObj = new A(); //new一个新对象，该方法不好：在有继承关系的情况下，不利于复用父类的clone方法
        AAA newObj = (AAA)super.clone(); //强烈建议这么做
        newObj.values = this.values.clone(); //数组的clone是深拷贝，如果去掉clone，则是浅拷贝
        return newObj;
    }
}

/**
 *     @Override
 *     public boolean equals(Object o) {
 *         if (this == o) return true;
 *         if (o == null || getClass() != o.getClass()) return false;
 *         if (!super.equals(o)) return false;
 *
 *         Dog dog = (Dog) o;
 *         return Objects.equals(hachimi, dog.hachimi);
 *     }
 */

/**
 * 当调用实例方法时，由Java虚拟机动态地决定所调用的方法，
 * 称为动态绑定(dynamic binding)或者晚期绑定或者延迟绑定(lazy binding)或者多态。
 */

/**
 * final可以修饰变量、方法、类
 * final修饰变量
 * final成员变量：常量，数据初始化后不能再修改。
 * final局部变量:常量，数据初始化后不能再修改。
 * final修饰方法（实例方法和静态方法）：最终方法，实例方法不能被子类覆盖，静态方法不能被隐藏
 * Object类的getClass( )
 * final类：最终类，不能派生子类。
 */

class CompA implements Comparable<CompA> {

    private int a;
    public CompA(int a) {
        this.a = a;
    }

    public int getA() {
        return a;
    }

    @Override
    public int compareTo(CompA o) {
        return this.a - o.a;
    }
}

