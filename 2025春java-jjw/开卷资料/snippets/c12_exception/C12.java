package hust.cs.java.c12_exception;

import java.io.IOException;
import java.util.Scanner;

public class C12 {
}

class AA {}

class BB extends AA implements Cloneable {
    @Override
    protected Object clone() throws CloneNotSupportedException {
        return super.clone();
    }
}

class C {
    public static void main(String[] args) throws CloneNotSupportedException {
        AA a = new BB();
        AA newObject = (AA) ((BB)a).clone(); // a未实现cloneable接口
        System.out.println(a == newObject);  // false
    }
}

/**************************/

class TestCallStack {

    public static void methodA() {
        System.out.println("in methodA");
        try {
            methodB();
        } catch (Exception e) {
            System.out.println(e);
        }
        System.out.println("end methodA");
    }

    public static void methodB() {
        System.out.println("in methodB");
        methodC();
        System.out.println("end methodB");
    }

    public static void methodC() {
        System.out.println("in methodC");
        int i = 10 / 0;
        System.out.println(i);
        System.out.println("end methodC");
    }

    public static void main(String[] args) {
        System.out.println("in methodMain");
        methodA();
        System.out.println("end methodMain");
    }
    /**
     * in methodMain
     * in methodA
     * in methodB
     * in methodC
     * java.lang.ArithmeticException: / by zero
     * end methodA
     * end methodMain
     */
}

class TestExceptionsPriority {
    static int div(int x, int y) {  //各种Exception都被捕获，函数无须声明异常
        int r = 0;
        try {
            //自己抛出异常对象
            r = 1/0;
            if (y == 0) throw new ArithmeticException();
            r = x / y;
        } catch (ArithmeticException ae) {
            System.out.println(ae.toString());
            throw ae;
        } catch (Exception ae) {//捕获各种Exception：若是第1个catch，则后续的catch子句无机会捕获
            System.out.println(ae.toString());
            throw ae;
        } catch (Error e) {
            System.out.println(e.toString());
            throw e;
        } catch (Throwable e) {
            System.out.println(e.toString());
            throw e;
        } finally {
            r = -1;
            return r;
        }        //无论是否有异常，r=-1
    }

    public static void main(String[] args) {
        int x = 10;
        try {
            x = div(5, 0);
        } //调用div(5, 0)后，div函数的执行轨迹已用红色标出
        catch (Throwable ae) { //任何异常都被捕获，包括Error类型异常
            System.out.println(ae.toString());
        }finally {
            System.out.println(x);
        }
    }
    /**
     * java.lang.ArithmeticException: / by zero
     * -1
     */
}

/********************/
class TestCatch{
    public static void main(String[] args) {
        System.out.println(m(0));
        /**
         * Enter m(0)
         * catch e
         * catch return
         * finally
         * 2
         */
        System.out.println("----------");
        System.out.println(m(1));
        /**
         * Enter m(1)
         * finally
         * 4
         */
        System.out.println("----------");
        System.out.println(m(2));
        /**
         * Enter m(2)
         * catch e
         * finally
         * -1
         */
        System.out.println("----------");
        System.out.println(m(3));
        /**
         * Enter m(3)
         * catch e
         * finally
         * 3
         */
    }

    static int m(int k) {
        try{
            System.out.printf("Enter m(%d)\n", k);
            if (k != 1) throw new Exception("111");
        }catch (Exception e) {
            System.out.println("catch e");
            if (k==0){
                System.out.println("catch return");
                return 2;
            }else {
                return -1;
            }
        }finally {
            System.out.println("finally");
            if (k==3){
                return 3;
            }
        }
        return 4;
    }
}
/****************/
class TestTryWithResources {
    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in)) {

        }catch (Exception e) {
            System.out.println(e);
        }
    }
}

/**********************/
class Test2_16 {
    public void m1() throws IOException {
        try {
            throw new IOException();
        }
        catch (IOException e){
            System.out.println("IOException caught");
        }
    }

    public void m2() throws IOException {
        m1();
    }

    public static void main(String[] args) throws IOException {
        new Test2_16().m2(); // IOException caught
    }
}

class Test2_16_2 {
    public void m1() {
        try {
            throw new IOException();
        }
        catch (IOException e){
            System.out.println("IOException caught");
        }
    }

    public void m2() {
        m1();
    }

    public static void main(String[] args) {
        new Test2_16_2().m2(); // IOException caught
    }
}

class Test2_17 {
    public void m1() throws RuntimeException{
        throw new RuntimeException();
    }


    public void m2(){
        m1();
    }

    public static void main(String[] args) {
        new Test2_17().m2(); // Exception in thread "main" java.lang.RuntimeException
    }
}

class Test2_18 {
    public void m1() throws IOException {
        throw new RuntimeException();
    }


    public void m2(){
        try {
            m1();
        } catch (IOException e) {
            System.out.println("IOException caught");
        } catch (RuntimeException e){
            System.out.println("RuntimeException caught");
        }
    }

    public static void main(String[] args) {
        new Test2_18().m2(); // RuntimeException caught
    }
}

class Test2_19 {
    public void m1() {
        try{
            throw new NullPointerException();
        }catch (NullPointerException e){
            throw new ArithmeticException("ArithmeticException caught");
        }catch (ArithmeticException e){
            System.out.println("ArithmeticException caught");
        }
    }

    public static void main(String[] args) {
        new Test2_19().m1(); // Exception in thread "main" java.lang.ArithmeticException:
    }
}



