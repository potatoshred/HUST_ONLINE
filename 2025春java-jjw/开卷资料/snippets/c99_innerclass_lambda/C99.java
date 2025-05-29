package hust.cs.java.c99_innerclass_lambda;

import java.util.Arrays;
import java.util.List;

public class C99 {
}
interface MessageHandler {
    void handle(String message);
}

class Wrapper1 {
    //定义内部类MessageHandlerImpl实现Message接口
    class MessageHandlerImpl implements MessageHandler {
        @Override
        public void handle(String message) { System.out.println(message);}
    }

    //Wrapper1的实例变量
    private MessageHandler handler = new MessageHandlerImpl();
    public void sendMessage(String message){
        handler.handle(message);
    }
    public static void main(String[] args){
        new Wrapper1().sendMessage("Message from wrapper1");
    }
}

class Wrapper2 {
    //定义内部类MessageHandlerImpl实现Message接口
    class MessageHandlerImpl implements MessageHandler {
        @Override
        public void handle(String message) { System.out.println(message);}
    }

    //Wrapper2的实例变量
    private MessageHandler handler = new MessageHandlerImpl();
    public void sendMessage(String message){
        handler.handle(message);
    }
    public static void main(String[] args){
        new Wrapper2().sendMessage("Message from wrapper2");
    }
}

class Wrapper3 {
    //Wrapper1的实例变量
    private MessageHandler handler = null;
    public void setHandler(MessageHandler handler){ this.handler = handler;}
//    //定义内部类MessageHandlerImpl实现Message接口
//    class MessageHandlerImpl implements MessageHandler {
//        @Override
//        public void handle(String message){ System.out.println(message);}
//    }
//    public void init(){
//        setHandler(new MessageHandlerImpl());
//    }
    public void init(){
        setHandler(new MessageHandler(){ // 匿名内部类必须实现父类或者接口的所有抽象方法。
            @Override
            public void handle(String message) { System.out.println(message);}
        });
    }

}

/********************/
class TestInner {
    public static void main(String[] args){ //和class Wrapper同一个JAVA文件，即同一个包
        Wrapper w = new Wrapper();  //w.x = 0;
        //创建内部静态类实例
        Wrapper.A a = new Wrapper.A(); 	//a.y=0, a.q=0;
        Wrapper.A b = new Wrapper.A();	 //b.y=0, b.q=0;
        a.g();
        //a,b的实例成员彼此无关，因此执行完a.g()后，a.y = 1, b.y = 0;
        //a,b共享静态成员q，所以a.q=b.q = 1;

        //创建内部实例类实例
        //不能用new Wrapper.B();必须通过外部类对象去实例化内部类对象
        Wrapper.B  c = w.new B(); //类型声明还是外部类.内部类
        c.y=0;
        c.g(); //c.y = 1 ,c.getX() = 1

        //在外部类体外面，不能通过内部类对象访问外部类成员，只能在内部类里面访问，
        //编译器在这里只能看到内部类成员
        //   System.out.println(a.z); //错误
           System.out.println(c.y);
        //   System.out.println(c.x); //错误
        //不能通过c直接访问外部类的x，可通过c.gextX()
        System.out.println(c.getX());
    }

}

class Wrapper{
    private int x=0;
    private static int z = 0;
    //内部静态类
    static class A{
        int y=0;
        static int q=0;  //可以定义静态成员,
        //不能访问外部类的实例成员x，可访问外部类静态成员z
        int g() {  return ++q + ++y + ++z; }
    }
    //内部实例类,也定义静态成员（JDK16以后）
    //内部实例类可访问外部类的静态成员如z，实例成员如x
    class B{
        int y=0;
        public int g( ) {
            x++; y++;z++;
            return x+y;
        }
        public int getX(){return x;}
        //从JDK16开始，内部实例类可以定义静态成员
        static void f(){}
    }
}

/************************/
class TestClosure {

    public static void main(String[] args) {
        Closure<Dog> c1 = testClosure1();    //返回闭包1
        Closure<Dog> c2 = testClosure1();    //返回闭包2

        //二个闭包里面还有dog，而且是不同的dog，这个时候testClosure1方法已经结束了
        //二个闭包都捕获了局部变量dog，延长了dog的生命周期
        System.out.println(c1.get() == c2.get());  //false

    }

    public static Closure<Dog> testClosure1(){
        //匿名内部类需要访问匿名内部类所在方法中的局部变量的时候，
        //必须给局部变量加final进行修饰
        final Dog  dog = new Dog();
        //Java里，匿名内部类方法要捕获的外部闭包环境的自由变量必须是final的
        return new Closure<Dog>() {
            @Override
            public Dog get() {
                //匿名对象的get方法捕获了外面的自由变量dog，
                //使得testClosure1中的局部变量dog生命周期延长
                return dog;
            }
        };
    }

}

interface Closure<T>{
    T get();
}

class Dog{

}

/*****************/
class TestLambda {
    //Wrapper1的实例变量
    private MessageHandler handler = null;
    public void setHandler(MessageHandler handler){ this.handler = handler;}

    public void init(){
        String tst = "Hello World!";
//        setHandler(message -> System.out.println("Message from testlambda: " + message + tst));
        setHandler((message) -> {
//            tst = "";
            System.out. println("Message from testlambda: " + message + tst);
        });
    }
}

/**********************/
class TestMapReduce {
    public static void main(String[] args) {
        //Old way:
        List<Integer> list = Arrays.asList(1,2,3,4,5,6,7);
        int sum = 0;
        for(Integer n : list) {
            int x = n * n;
            sum = sum + x;
        }
        System.out.println(sum);

        //New way:
        sum = list.stream().map(x -> x*x).reduce((x,y) -> x + y).get();
        System.out.println(sum);

    }
}