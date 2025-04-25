
import javax.swing.JOptionPane;

public class AlphaStatics {

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

class RandomSeq {

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
        // Random rand = new Random();
        sb.append(getRandAlpha());
        sb.append(getRandAlpha());
        sb.append(getRandAlpha());
        sb.append(getRandDigit());
        sb.append(getRandDigit());
        sb.append(getRandDigit());
        sb.append(getRandDigit());

        return sb.toString();
    }
}
