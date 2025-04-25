
import java.util.Random;

public class RandomLic {

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
