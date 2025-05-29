package hust.cs.java.c2_basic;
import javax.swing.*;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Random;
import java.util.Scanner;

public class C2 {
    public static void main(String[] args) {
        boolean bool; // false

        byte b;
        char c; // \u0000
        short s;
        int i;
        long l;
        float f;
        double d;

        b = 'a';
        c = 'b';
        // b = c;
        b = (byte)c;
        // bool = (bool)b; // boolean不与任意类型转换
        // b = (byte)bool;

        // s = c;
        s = (short)c;

        i = 5;
        // i = 5L; 大类型无法自动转小类型
        d = i;

        l = i;

        f = i;
        f = 0x1818181818L;
        d = f;
        d = l;

    }
}
class TestInteger {
    public static void main(String[] args) {
//        Integer i1 = new Integer(32);
//        Integer i1 = new Integer("32");
        Integer i1 = 32;
        Integer i2 = Integer.valueOf(32);
        Integer i3 = Integer.valueOf(32);
        Integer i4 = Integer.valueOf("32");
//        Integer i5 = Integer.valueOf("0A");
        Integer i5 = Integer.parseInt("0A", 16);
        System.out.println(i1==i2); // true
        System.out.println(i2==i3); // true
        System.out.println(i3==i4); // true
        System.out.println(i5); // 10

        System.out.println(i4 + i5);
        System.out.println("" + i4 + i5);

        Integer i0 = Integer.valueOf(128);
        System.out.println(i0.byteValue());


//        Float f0 = Float.valueOf(128.0); // Error
        Float f0 = Float.valueOf(128.0f);
        Float f1 = Float.valueOf(128.00f);
        Float f2 = Float.valueOf(128.00f);
        Float f3 = Float.valueOf("128.00f");
        Float f4 = Float.valueOf("128.00f");
        System.out.println(f0==f1); // false
        System.out.println(f1==f2); // false
        System.out.println(f2==f3); // false
        System.out.println(f3==f4); // false


        Double d0 = Double.valueOf(128.0f);
        Double d1 = Double.valueOf(128.0);
        Double d2 = Double.valueOf(128.0d);
        Double _d2 = Double.valueOf(128.0d);
        Double d3 = Double.valueOf("128.0d");
        Double d4 = Double.valueOf(128.00d);
        Double d5 = Double.valueOf("128.00d");

        System.out.println(d0==d1); // false
        System.out.println(d1==d2); // false
        System.out.println(d2==d3); // false
        System.out.println(d3==d4); // false
        System.out.println(d4==d5); // false


        BigInteger bi0 = BigInteger.valueOf(128);
        BigInteger bi1 = BigInteger.valueOf(128);
        BigInteger bi2 = new BigInteger("128");
        BigInteger bi3 = new BigInteger("128");


        System.out.println(bi0==bi1); // false
        System.out.println(bi1==bi2); // false
        System.out.println(bi2==bi3); // false


        BigDecimal bd0 = BigDecimal.valueOf(0.1);
//        BigDecimal bd1 = BigDecimal.valueOf("0.1");
        BigDecimal bd1 = new BigDecimal("0.1");
        System.out.println(bd0);
        System.out.println(bd1);

    }
}

class TestSwitch{
    public static void main(String[] args) {
        Integer i = null; // 可以为byte, char, short, int, String, 不能为long！以及boolean等
        String a = switch (i) {
            case 1, 2, 3, 4 ->
                    "AS";
            case 5, 6, 7, 8 ->
                    "ASS";
            case null ->
                    "NULL";
            default ->
                    "RNADOM";
        };
        System.out.println(a); // NULL
    }
}

class TestScanner {
    public static void main(String[ ] args) {
        // Create a scanner
        Scanner scanner = new Scanner(System.in);

        // Prompt the user to enter an integer
        System.out.print("Enter an integer: ");
        int intValue = scanner.nextInt();
        System.out.println("You entered the integer: " + intValue);

        // Prompt the user to enter a double value
        System.out.print("Enter a double value: ");
        double doubleValue = scanner.nextDouble();
        System.out.println("You entered the double value: " + doubleValue);

        System.out.print("Enter a string without space: ");
        String string = scanner.next();
        System.out.println("You entered the string: " + string);

        scanner.close();
    }
}

class AlphaStatics {
    public static void main(String[] args) {
        String msg = JOptionPane.showInputDialog("Enter some words").toLowerCase();

        int[] checkin = new int[26];
        for (char c : msg.toCharArray()) {
            if (c >= 'a' && c <= 'z') {
                checkin[c - 'a']++;
            }
        }
        for (int i = 0; i < 26; ++i) {
            System.out.printf("%c: %d\n", 'a' + i, checkin[i]);
        }
    }
}

class RandomSeq1 {
    public static void main(String[] args) {
        for (int i = 0; i < 5; ++i) {
            System.out.println(getRandCarNum());
        }
    }
    static char getRandAlpha() {
        return (char) (Math.random() * 26 + 'A');
    }
    static char getRandDigit() {
        return (char) (Math.random() * 10 + '0');
    }
    static String getRandCarNum() {
        StringBuffer sb = new StringBuffer();
        sb.append(getRandAlpha());
        sb.append(getRandAlpha());
        sb.append(getRandDigit());
        sb.append(getRandDigit());
        return sb.toString();
    }
}

class RandomSeq2 {
    public static void main(String[] args) {
        for (int i = 0; i < 5; i++) {
            System.out.println(generateRandomLicense());
        }
    }
    static String generateRandomLicense() {
        Random rand = new Random();
        StringBuffer sb = new StringBuffer();
        for (int i = 0; i < 3; i++) {
            sb.append((char) (rand.nextInt(26) + 'A'));
        }
        for (int i = 0; i < 4; i++) {
            sb.append((char) (rand.nextInt(10) + '0'));
        }
        return sb.toString();
    }
}

