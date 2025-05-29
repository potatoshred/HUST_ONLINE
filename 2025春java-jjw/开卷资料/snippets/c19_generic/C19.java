package hust.cs.java.c19_generic;

import java.lang.reflect.Array;
import java.util.ArrayList;

public class C19 {
}

class TestGenericMethods{
    public static final <T extends Number> double add(T t1, T t2) {
        return t1.doubleValue() + t2.doubleValue();
    }

    public static void main(String[] args) {
        TestGenericMethods.add(1.5, 2); // 可以推断
//        TestGenericMethods.add(false, 2); // Boolean自闭
//        TestGenericMethods.<float>add(1.5, 2.0); // Float
        TestGenericMethods.<Float>add(1.5f, 2.0f);
//        TestGenericMethods.<Double>add(1f, 2d); // 不行，因为已经显式声明为Double类型
    }
}

class TestGenericClass<T>{
    T val;
    T[] arr;
    T getVal() {return val;}
    T[] getArr() {return arr;}
    void setArr(T[] arr) {this.arr = arr.clone();}
}

interface TestGenericInterface<T>{
//    T val; // 因为必须是final常量，必须初始化为固定值，所以与泛型理念冲突，不能有泛型成员变量
    T getValue();
    void setValue(T value);
}

/****************************/

class GenericOneDimensionArray<T> {
    private T[] elements = null;  //T[]类型

    public GenericOneDimensionArray(Class<? extends T> clz,int size){
        /**
         * 这里第一个参数是Class<? extends T> clz，表示一个T类型及其子类的Class对象。通过Class对象，可以通过反射创建运行时类型为T[]的数组。
         * 但是Array.newInstance方法返回的是Object（方法声明的返回类型），因此需要强制类型转换。但这里的强制类型转换是安全的，因为创建的数组的运行时类型就是T[]
         */
        elements = (T[]) Array.newInstance(clz,size);
        /**
         * Array.newInstance(数组元素类型的Class对象, size)
         * 通过反射机制创建运行时类型为T[]的数组
         */
    }

    //get, put等其他方法省略

    public T[] getElements(){ return elements; }

    public static void main(String[] args){
        GenericOneDimensionArray<String> stringArray =
                new GenericOneDimensionArray(String.class,10);
        String[] a = stringArray.getElements();  //这里不会抛出运行时异常了
//        a[0] = new Fruit(); //不是String类型的对象，编译报错
        a[1] = "Hello";
    }
}

/********************/

class GenericOneDimensionArrayUncheck<T> {//实现一维数组的泛型包装类。不可能实现泛型数组
    private T[] elements;  //T[]类型数组存放元素

    public GenericOneDimensionArrayUncheck(int size) {
        // elements = new T[]; // 编译失败，因为擦出法
        //new Object[]强制类型转换。强制类型转换就是uncheck，就是强烈要求编译器把=右边的类型解释成T[]
        elements = (T[]) new Object[size]; //注意：在运行时，elements引用变量指向的是Object[]
    }

    public static void main(String[] args) {
        GenericOneDimensionArrayUncheck<String> strArray = new GenericOneDimensionArrayUncheck<>(10);
        strArray.put("Hello", 0);
//        strArray.put(new Fruit(),0);  //不是String对象放不进去
        String s = strArray.get(0);  //strArray.get(0)返回对象的运行时类型一定是String，由put保证的
        //但是下面的语句抛出运行时异常：java.lang.ClassCastException
        //因为运行时，elements引用变量指向的是Object[]，无法转成String[]
        String[] a = strArray.getElements(); //返回内部数组，但为String[]类型
    }

    //这里value的类型是T，这点非常重要，保证了放进去的元素类型必须是T及子类型。否则编译报错
    public void put(T value, int index) {
        elements[index] = value;
    }

    public T get(int index) {
        return elements[index];
    }//elements声明类型就是T[]，因此类型一致

    public T[] getElements() {
        return elements;
    } //这个方法非常危险，编译没问题
}

/********************/
class GenericStack<E> {
    private ArrayList<E> list = new ArrayList<E>();
    public boolean isEmpty() {
        return list.isEmpty();
    }
    public int getSize() {
        return list.size();
    }
    public E peek() {
        return list.get(getSize() - 1);//取值不出栈
    }
    public E pop() {
        E o = list.get(getSize() - 1) ;
        list.remove(getSize() - 1);
        return o;
    }
    public void push(E o) {
        list.add(o);
    }
    public String toString() {
        return "stack: " + list.toString();
    }
}
/*****************/
class Fruit{}
class Apple extends Fruit{}
class Jonathan extends Apple{} //一种苹果
class Orange extends Fruit{}
class TestCovariant {
    public static void main(String[] args) {
        //由于数组的协变性，可以把Apple[]类型的引用赋值给Friut[]类型的引用
        Fruit[] fruits = new Apple[10];
        fruits[0] = new Apple();
        fruits[1] = new Jonathan(); // Jonathan是Apple的子类

        try{
            //下面语句fruits的声明类型是Fruit[]因此编译通过，但运行时将Fruit转型为Apple错误
            //数组是在运行时才去判断数组元素的类型约束；
            //而泛型正好相反，在运行时，泛型的类型信息是会被擦除的，编译的时候去检查类型约束
            fruits[2] = new Fruit();//运行时抛出异常 java.lang.ArrayStoreException，这是数组协变性导致的问题
        }catch(Exception e){
            System.out.println(e);
        }

//        ArrayList<Fruit> list = new ArrayList<Apple>(); //编译错误
        ArrayList<? extends Fruit> listProducer = new ArrayList<Apple>();
//        listProducer.add(new Apple());
        listProducer.getFirst(); // 能取不能存，散财童子，无私奉献的数据提供者，

//        ArrayList<? super Fruit> listConsumer = new ArrayList<Apple>(); // fault,
        ArrayList<? super Fruit> listConsumer = new ArrayList<Fruit>(); // ok
//        ArrayList<? super Fruit> listConsumer = new ArrayList<Object>(); // ok

        listConsumer.add(new Apple());
        listConsumer.add(new Jonathan());
        listConsumer.add(new Fruit());
//        listConsumer.add(new Object());
        Object o1 = listConsumer.get(0); //OK
//        Fruit o2 = listConsumer.get(0);  //报错，Object不能赋给Fruit，需要强制类型转换

    }
}

/**********************/

class WildCardNeedDemo {
    /* GenericStack<? extends Number>才是GenericStack<Integer> 的父类，
     * GenericStack<Number>不是GenericStack<Integer> 的父类
     */
    public static double max(GenericStack<? extends Number> stack){
        double max = stack.pop().doubleValue();
        while (! stack.isEmpty()){
            double value = stack.pop().doubleValue();
            if(value > max)
                max = value;
        }
        return max;
    }

    public static void main(String[] args){
        GenericStack<Number> intStack = new GenericStack<>();
//        GenericStack<Integer> intStack = new GenericStack<>();// 无协变性covariant
        intStack.push(1);intStack.push(2);intStack.push(3);
        System.out.println("Th max value is " + max(intStack));

    }
}
/********************/
class TypeErasureTest {
    public static void main(String[] args){
        ArrayList<String> strList = new ArrayList<>();
        ArrayList<Fruit> fruitList = new ArrayList<>();
        Class clz1 = strList.getClass(); //getClass返回运行时信息
        Class clz2 = fruitList.getClass();
        System.out.println(clz1.getSimpleName());   //ArrayList
        System.out.println(clz2.getSimpleName());   //ArrayList
        System.out.println(clz1 == clz2);           //true
    }
}


