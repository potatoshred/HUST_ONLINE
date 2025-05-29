package hust.cs.java.c30_parallel;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class C30 {
}
/**************************/

class PrintChar implements Runnable //实现Runnable接口
{
    private char charToPrint;  // The character to print
    private int times;  // The times to repeat

    public PrintChar(char c, int t) {
        charToPrint = c;
        times = t;
    }

    public void run() { //实现Runnable中声明的run方法
        for (int i = 1; i < times; i++) System.out.print(charToPrint);
    }
}
class ThreadDemo
{
    public static void main(String[] args) throws InterruptedException {
        System.out.println(Thread.currentThread().getName());
        //以PrintChar对象实例为参数构造Thread对象
        Thread printA = new Thread(new PrintChar('a',100));
        Thread printB = new Thread(new PrintChar('b',100));
        printA.start();
        printB.start();

        System.out.println(printA.getName());
        System.out.println(printB.getName());
        printA.join();
    }
}

/***************************/
class ThreadCoop {
    private static Account account = new Account();

    public static void main(String[] args) {
        ExecutorService executor = Executors.newFixedThreadPool(2);
        executor.execute(new DepositTask());
        executor.execute(new WithdrawTask());
        executor.shutdown();
        System.out.println("Thread 1\t\tThread 2\t\t\t\tBalance");
    }

    private static class Account {// An inner class for account
        private static Lock lock = new ReentrantLock();
        private static Condition newDeposit = lock.newCondition();
        private int balance = 0;
        public int getBalance() {return balance;}
        public void withdraw(int amount) {
            lock.lock(); // Acquire the lock
            try {
                while (balance < amount) {
                    System.out.println("\t\t\t\tWait for a deposit");
                    newDeposit.await(); // 线程被挂起同时锁被释放，与sleep不同。
                }
                balance -= amount;
                System.out.println("\t\t\t\tWithdraw " + amount +"\t\t\t\t" + getBalance());
            }
            catch (InterruptedException ex) {ex.printStackTrace();}
            finally {lock.unlock(); }

        }
        public void deposit(int amount){
            lock.lock();
            try{
                balance+=amount;
                System.out.println("deposit " + amount + "\t\t\t\t\t\t\t\t" + getBalance( ));
                newDeposit.signalAll( );
            }
            finally{ lock.unlock( ); }
        }
    }

    public static class DepositTask implements Runnable {
        public void run() {
            try { // Purposely delay it to let the withdraw method proceed
                while (true) {
                    account.deposit((int)(Math.random() * 10) + 1);
                    Thread.sleep(1000);
                }
            }
            catch (InterruptedException ex) { ex.printStackTrace();}
        }
    }

    public static class WithdrawTask implements Runnable {
        public void run() {
            while (true) {
                account.withdraw((int)(Math.random() * 10) + 1);
            }
        }
    }
}

/************************/
class PrintNum implements Runnable { //实现新的线程任务类，打印数字
    private int lastNum;

    public PrintNum(int n) {
        lastNum = n;
    }

    @Override
    public void run() {
        Thread thread4 = new Thread(new PrintChar('c', 600));
        thread4.start();
        try {
            for (int i = 1; i < lastNum; i++) {
                System.out.print(" " + i);
                if (i == 50) thread4.join(); //join方法可以给参数指定至多等若干毫秒
            }
        } catch (InterruptedException e) {
        } //join方法可能会抛出这个异常
    }
}
class ExecutorDemo {
    public static void main(String[] args) {
        // Create a fixed thread pool with maximum three threads
        ExecutorService es = Executors.newFixedThreadPool(3);

        // Submit runnable tasks to the executor
        es.execute(new PrintChar('a', 100));
        es.execute(new PrintChar('b', 100));
        es.execute(new PrintNum(100));

        // Shut down
        es.shutdown();
    }

}
/************************/
class AccountWithoutSync {
    private static class Account {
        private int balance = 0;

        public int getBalance() {
            return balance;
        }

        public void deposit(int amount) {
            balance += amount;
        }
    }

    private static class AddPennyTask implements Runnable {
        public void run() {
            account.deposit(1);
        }

    }

    private static Account account = new Account();

    public static void main(String[] args) {
        ExecutorService executor = Executors.newCachedThreadPool();
        for (int i = 0; i < 100; i++) {
            executor.execute(new AddPennyTask());
        }
        executor.shutdown();
        while (!executor.isTerminated()) {
        }
        System.out.println("What is balance?" + account.getBalance());
    }

}

class AccountWithSync {
    private static class Account {
        private int balance = 0;

        public int getBalance() {
            return balance;
        }

        public synchronized void deposit(int amount) {
            int newBalance = balance + amount;   //读取balance
            try {
                Thread.sleep(5);
            } catch (InterruptedException e) {
            }
            balance = newBalance;        //写balance
//            balance += amount;
        }
    }

    private static class AddPennyTask implements Runnable {
        public  void run() {
            synchronized (account) {
                account.deposit(1);
            }
        }
    }

    private static Account account = new Account();

    public static void main(String[] args) {
        ExecutorService executor = Executors.newCachedThreadPool();
        for (int i = 0; i < 100; i++) {
            executor.execute(new AddPennyTask());
        }
        executor.shutdown();
        while (!executor.isTerminated()) {
        }
        System.out.println("What is balance?" + account.getBalance());
    }
}

/**************************/

class AccountWithSyncUsingLock {
    private static Account account = new Account();

    public static void main(String[] args) {
        ExecutorService executor = Executors.newCachedThreadPool();
        // Create and launch 100 threads
        for (int i = 0; i < 100; i++) {
            executor.execute(new AddAPennyTask());
        }
        executor.shutdown();
        // Wait until all tasks are finished
        while (!executor.isTerminated()) {
        }
        System.out.println("What is balance ? " + account.getBalance());
    }

    // A thread for adding a penny to the account
    public static class AddAPennyTask implements Runnable {
        public void run() {
            account.deposit(1);
        }
    }

    public static class Account {// An inner class for account，主要变化在账户类
        private static Lock lock = new ReentrantLock(); // 注意这里是静态的，被所有Account实例共享，去掉static也可
        private int balance = 0;

        public int getBalance() {
            return balance;
        }

        public void deposit(int amount) {
            lock.lock(); // Acquire the lock
            try {
                int newBalance = balance + amount;
                Thread.sleep(5);
                balance = newBalance;
            } catch (InterruptedException ex) {
            } finally {
                lock.unlock(); // Release the lock，在finally中进行锁的释放。}
            }
        }
    }
}

class AccountWithSyncUsingLock2 {
    private static Account account = new Account();

    public static void main(String[] args) {
        ExecutorService executor = Executors.newCachedThreadPool();
        // Create and launch 100 threads
        for (int i = 0; i < 100; i++) {
            executor.execute(new AddAPennyTask());
        }
        executor.shutdown();
        // Wait until all tasks are finished
        while (!executor.isTerminated()) {
        }
        System.out.println("What is balance ? " + account.getBalance());
    }

    // A thread for adding a penny to the account
    public static class AddAPennyTask implements Runnable {
        private static Lock lock = new ReentrantLock(); // static会影响
        public void run() {
            lock.lock();
            account.deposit(1);
            lock.unlock();
        }
    }

    public static class Account {// An inner class for account，主要变化在账户类
        private int balance = 0;

        public int getBalance() {
            return balance;
        }

        public void deposit(int amount) {
            int newBalance = balance + amount;
            try {
                Thread.sleep(5);
            } catch (InterruptedException ex) {
            }
            balance = newBalance;

        }
    }
}
class AccountWithSyncUsingLock3 {
    private static Account account = new Account();

    public static void main(String[] args) {
        ExecutorService executor = Executors.newCachedThreadPool();
        // Create and launch 100 threads
        for (int i = 0; i < 100; i++) {
            executor.execute(new AddAPennyTask());
        }
        executor.shutdown();
        // Wait until all tasks are finished
        while (!executor.isTerminated()) {
        }
        System.out.println("What is balance ? " + account.getBalance());
    }

    // A thread for adding a penny to the account
    public static class AddAPennyTask implements Runnable {
        public void run() {
            account.deposit(1);
        }
    }

    public static class Account {// An inner class for account，主要变化在账户类
        private int balance = 0;
        private static String totalAccount = ".";

        public int getBalance() {
            return balance;
        }

        public void deposit(int amount) {
            synchronized (totalAccount) { // 改成this
                totalAccount += "."; // 发生了改变，锁了个寂寞
                int newBalance = balance + amount;
                try {
                    Thread.sleep(5);
                } catch (InterruptedException ex) {
                }
                balance = newBalance;
            }
        }
    }
}

/**********************/
class SemaophoreTezt {
    // An inner class for account
    private static class Account {
        // Create a semaphore
        private static Semaphore semaphore = new Semaphore(1);
        private int balance = 0;

        public int getBalance() {
            return balance;
        }

        public void deposit(int amount) {
            try {
                semaphore.acquire();
                int newBalance = balance + amount;
                Thread.sleep(5);
                balance = newBalance;
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            } finally {
                semaphore.release();
            }
        }
    }
}

/**************************/
class TwoLock {
    public static void main(String[] args) {
        test1();
//        test2();
    }
    public static void test1(){
        int incAmount = 10; int decAmount = 5; int loops = 50;

        ResourceWithLock r = new ResourceWithLock();
        Runnable incTask = new IncTaskWithLock( r ,incAmount,loops);
        Runnable decTask = new DecTaskWithLock( r ,decAmount,loops);

        ExecutorService es = Executors.newCachedThreadPool();
        es.execute(incTask); es.execute(decTask);
        es.shutdown(); while(!es.isTerminated()){  }

        int correctValue = (incAmount - decAmount)  * loops;
        System.out.println("\nThe value: " + r.getValue() + ", correct value: " + correctValue);
    }
    public static void test2(){
        int incAmount = 10, decAmount = 5,loops = 20;
        ResourceWithLock r1 = new ResourceWithLock();  ResourceWithLock r2 = new ResourceWithLock();

        //incTask1，decTask1访问同一个对象r1，它们之间同步
        Runnable incTask1 = new IncTaskWithLock(r1,incAmount,loops);
        Runnable decTask1 = new DecTaskWithLock(r1,decAmount,loops);
        //incTask2，decTask2访问同一个对象r2，它们之间同步
        Runnable incTask2 = new IncTaskWithLock(r2,incAmount,loops);
        Runnable decTask2 = new DecTaskWithLock(r2,decAmount,loops);

        ExecutorService es = Executors.newCachedThreadPool();
        es.execute(incTask1); es.execute(decTask1); es.execute(incTask2); es.execute(decTask2);
        es.shutdown();
        while(!es.isTerminated()){  }
        int r1CorrectValue = (incAmount - decAmount)  * loops ; int r2CorrectValue = (incAmount - decAmount)  * loops;
        System.out.println("\nThe value of r1: " + r1.getValue() + ", correct value: " + r1CorrectValue);
        System.out.println("\nThe value of r2: " + r2.getValue() + ", correct value: " + r2CorrectValue);
    }

}

class ResourceWithLock { //重新定义资源类，采用Lock锁
    private Lock lock = new ReentrantLock();  //创建Lock锁对象，注意是实例变量
    private int value = 0;   //多个线程会同时对这个数据成员读写
    public int getValue(){ return  value; }
    public void inc(int amount)   {
        lock.lock( ); // Acquire the lock
        try{ System.out.print("\nThread " + Thread.currentThread().getId() + " 进入inc: ");
            int newValue = value + amount;  try{ Thread.sleep(5); }  catch(InterruptedException e){ }
            value = newValue; System.out.print("-->Thread " + Thread.currentThread().getId() + " 离开inc.");
        } finally{ lock.unlock(); }
    }
    public void dec(int amount) {
        lock.lock( ); // Acquire the lock
        try{ System.out.print("\nThread " + Thread.currentThread().getId() + " 进入dec: ");
            int newValue = value - amount; try{ Thread.sleep(2); }  catch(InterruptedException e){	}
            value = newValue; System.out.print("-->Thread " + Thread.currentThread().getId() + " 离开dec.");
        } finally { lock.unlock(); }
    }
}
class IncTaskWithLock implements Runnable{
    private ResourceWithLock r = null;
    private int amount = 0;
    private int loops = 0;  //循环次数
    public IncTaskWithLock(ResourceWithLock r,int amount,int loops){
        this.r = r; this.amount = amount; this.loops = loops;
    }
    public void run() {
        for(int i = 0; i < loops; i++) { r.inc(amount); }
    }
}
class DecTaskWithLock implements  Runnable{
    private ResourceWithLock r = null;
    private int amount = 0;
    private int loops = 0;  //循环次数
    public DecTaskWithLock(ResourceWithLock r, int amount, int loops){
        this.r = r; this.amount = amount; this.loops = loops;
    }
    public void run() {
        for(int i = 0; i < loops; i++) { r.dec(amount); }
    }
}
/******************/
class Resource{ //共享资源类，这个类的实例被多个线程访问
    private int value = 0;   //多个线程会同时对这个数据成员读写
    public int getValue(){return  value;}
    public synchronized void inc(int amount)  {
        System.out.print("\nThread " + Thread.currentThread().getId() + " enter inc: ");
        int newValue = value + amount;
        try{ Thread.sleep(5); }  catch(InterruptedException e){	}
        value = newValue;
        System.out.print("-->Thread " + Thread.currentThread().getId() + " leave inc.");
    }
    public synchronized void dec(int amount)  {
        System.out.print("\nThread " + Thread.currentThread().getId() + " enter dec: ");
        int newValue = value - amount;
        try{ Thread.sleep(2); } catch(InterruptedException e){	}
        value = newValue;
        System.out.print("-->Thread " + Thread.currentThread().getId() + " leave dec.");
    }
}
class IncTask implements Runnable{
    private Resource r = null; //要访问的对象
    private int amount = 0; //每次增加量
    private int loops = 0;  //循环次数
    public IncTask(Resource r,int amount,int loops){
        this.r = r; this.amount = amount; this.loops = loops;
    }
    public void run() {
        for(int i = 0; i < loops; i++) { r.inc(amount); }
    }
}
class DecTask implements Runnable{
    private Resource r = null; //要访问的对象
    private int amount = 0; //每次减少量
    private int loops = 0;  //循环次数
    public DecTask(Resource r, int amount, int loops){
        this.r = r;this.amount = amount;this.loops = loops;
    }
    public void run() {
        for(int i = 0; i < loops; i++) {  r.dec(amount); }
    }
}

class TwoSync {

    public static void main(String[] args) {
//        test1();
        test2();
    }
    public static void test1(){
        int incAmount = 10;
        int decAmount = 5;
        int loops = 100;

        Resource r = new Resource();
        Runnable incTask = new IncTask( r, incAmount, loops );
        Runnable decTask = new DecTask( r, decAmount, loops );

        ExecutorService es = Executors.newCachedThreadPool();
        es.execute(incTask);
        es.execute(decTask);
        es.shutdown();
        while(!es.isTerminated()){  }

        int correctValue = (incAmount - decAmount)  * loops;
        System.out.println("\nThe value: " +  r.getValue() + ", correct value: " + correctValue);
    }

    public static void test2(){
        int incAmount = 10,decAmount = 5, loops = 3;

        Resource r1 = new Resource();
        Resource r2 = new Resource();
        Runnable incTask1 = new IncTask(r1,incAmount,loops);      Runnable decTask1 = new DecTask(r1,decAmount,loops);
        Runnable incTask2 = new IncTask(r2,incAmount,loops);     Runnable decTask2 = new DecTask(r2,decAmount,loops);

        ExecutorService es = Executors.newCachedThreadPool();
        es.execute(incTask1);es.execute(decTask1);
        es.execute(incTask2);es.execute(decTask2);
        es.shutdown();
        while(!es.isTerminated()){  }
        int r1CorrectValue = (incAmount - decAmount)  * loops ;	int r2CorrectValue = (incAmount - decAmount)  * loops;
        System.out.println("\nThe value of r1: " + r1.getValue() + ", correct value: " + r1CorrectValue);
        System.out.println("\nThe value of r2: " + r2.getValue() + ", correct value: " + r2CorrectValue);
    }

}



