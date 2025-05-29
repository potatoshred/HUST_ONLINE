package hust.cs.java.c13_abstract_interface;

public class C13 {
}
interface C1 {
    int a1 = 1;
    void m();

}

interface C2 {
    int a2 = 2;
    void m();

    private int m1(){ return 0; };
    static void m2(){}
    default void m3(){}
}

abstract class C3 {
    private int a3 = 3;

    private static void m3() {}

//    abstract C3(){} // 不允许
//    static abstract void m4();
//    private abstract void m4();
//    final abstract void m4();

    {
        a3 = 4;
    }
}
interface I extends C1, C2 {
    // I(){} 不能定义构造函数
    // 所有数据字段隐含为public static final
    int b = 1; // 编译器转为public static final
    static int a = 0; // 静态常量和实例方法必须是public

    // 接口体中的方法自动为public abstract
    void m3();

    void m4(); // 只有实例方法可声明为抽象方法，所有实例方法自动为virtual函数
    // {} 不可定义函数体
    // {} 不可包含初始化模块
}

interface I0 extends C1, C2 {
    // I(){} 不能定义构造函数
    // 所有数据字段隐含为public static final
    int b = 1; // 编译器转为public static final
    static int a = 0; // 静态常量和实例方法必须是public

    // 接口体中的方法自动为public abstract
    void m3();

    void m4(); // 只有实例方法可声明为抽象方法，所有实例方法自动为virtual函数
    // {} 不可定义函数体
    // {} 不可包含初始化模块

//    private void m5();
//    default void m6();
//    protected void m7();
    public void m7();

    private void m5() {}
    default void m6() {}
//    protected void m7() {}
//    public void m7() {}

    private static void m8() {}
//    default static void m9() {}
    static void m9() {}
//    protected static void m10(){}
    public static void m11(){}

//    private abstract void m12();
    abstract void m13(); // 自动转public
//    protected abstract void m14();
    public abstract void m15();
}

abstract class IA implements I {
    @Override
    public void m3() {
        System.out.println("m3");
    }
}

class IB extends IA implements I { // implement I 可省略

    Float a = Float.valueOf(3.0f);

    @Override
    public void m3() { // 必须加public，否则为package降级
        super.m3();
    }

    @Override
    public void m4() {

    }

    @Override
    public void m() {

    }
}

// class 描述ISA的血缘关系
// interface 描述了cando的行为能力