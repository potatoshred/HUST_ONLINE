package hust.cs.java.c4_function_string_loop;

import java.util.Objects;

public class C4 {
    public static void main(String[] args) {
        String s1 = "Welcome";
        String s2 = new String("Welcome");
        String s3 = s2.intern();
        String s4 = "Wel" + "come";
        String s5 = "Wel";
        String s6 = "come";
        String s7 = s5 + s6;
        String s8 = "Wel" + new String("come");
        final String s9 = "Wel";
        final String s10 = "come";
        final String s11 = s9 + s10;

        System.out.println(s1 == s2); // false
        System.out.println(s1 == s3); // true
        System.out.println(s1 == s4); // true
        System.out.println(s1 == s7); // false
        System.out.println(s1 == s8); // false
        System.out.println(s1 == s11);// true
        System.out.println(s5 == s9); // true

        m(s1);
        System.out.println(s1); // Welcome

        String[] arrString=new String[]{
                new String("a1"),
                new String("b2"),
                new String("c3")};
        for(String v:arrString) v=v.concat("--1"); // 同m()，不改变数组内String，
        for(String v:arrString) System.out.println(v);
    }

    static void m(String s){
        s = "Changed";
    }
}

class TestStringBuffer{
    public static void main(String[] args) {
        // StringBuffer sb = "asavbhs"; // 不支持
        StringBuffer sb = new StringBuffer("FUCKC");
        // sb[1] = 'a'; // 不支持
        sb.charAt(1); // U
        sb.setCharAt(1, 'u');
        sb.append("asdf");
        boolean flag = true;
        sb.append(flag); // +"true"
        sb.reverse();
        System.out.println(sb.length());
        System.out.println(sb.capacity());// 21
    }
}

class TestStringFormat {
    public static void main(String[] argv){
        int t=10;
        double f=20.12345678;
        String str=String.format("t=%4d,%-5d,%06d,f=%f,%-10.4f,%10.9f",t,t,t,f,f,f);
        System.out.println(str);
        System.out.printf("t=%2$4d,%2$-5d,%2$06d,f=%1$f,%1$-10.4f,%1$10.9f",f,t);
        // t=  10,10   ,000010,f=20.123457,20.1235   ,20.123456780
    }
}

class TestStringLength {
    public static void main(String[] argv){
        StringBuffer sb1=new StringBuffer(),sb2=new StringBuffer(),sb3=new StringBuffer();
        System.out.println("sb1："+sb1.toString()+"的length="+sb1.length()+"，缓冲区容量="+sb1.capacity());
        sb1.append("Welcome");
        sb2.append("Welcome");
        sb3.append("Welcome");
        System.out.println("sb1："+sb1.toString()+"的length="+sb1.length()+"，缓冲区容量="+sb1.capacity());
        sb1.setLength(9);
        System.out.println("sb1："+sb1.toString()+"的length="+sb1.length()+"，缓冲区容量="+sb1.capacity());
        sb2.append("WelcomeWelcomeWelcome");
        System.out.println("sb2："+sb2.toString()+"的length="+sb2.length()+"，缓冲区容量="+sb2.capacity());
        sb3.append("WelcomeWelcomeWelcomeWelcome");
        System.out.println("sb3："+sb3.toString()+"的length="+sb3.length()+"，缓冲区容量="+sb3.capacity());
        sb3.append("Welcome");
        System.out.println("sb3："+sb3.toString()+"的length="+sb3.length()+"，缓冲区容量="+sb3.capacity());
    }
    /**
     * sb1：的length=0，缓冲区容量=16
     * sb1：Welcome的length=7，缓冲区容量=16
     * sb1：Welcome  的length=9，缓冲区容量=16
     * sb2：WelcomeWelcomeWelcomeWelcome的length=28，缓冲区容量=34
     * sb3：WelcomeWelcomeWelcomeWelcomeWelcome的length=35，缓冲区容量=35
     * sb3：WelcomeWelcomeWelcomeWelcomeWelcomeWelcome的length=42，缓冲区容量=72
     */
}

class StringEquals{
    public static void main(String[] args) {
        StringBuffer sb1 = new StringBuffer("aaa");
        StringBuffer sb2 = new StringBuffer("aaa");
        System.out.println(sb1 == sb2); // false
        System.out.println(sb1.equals(sb2)); // false
        System.out.println(Objects.equals(sb1, sb2)); // false
        System.out.println(Objects.equals(sb1.toString(), sb2.toString())); // true
    }
}

class TestLoop{
    public static void main(String[] args) {
        int [] arr0=new int[0];
        int [] arr1=null;
        // int i; //会与下面i冲突
        for(int i : arr0){ System.out.println(i); }
        // 但这俩i不冲突
        for(int i : arr1){ System.out.println(i); } // NullPointerException
    }
}

