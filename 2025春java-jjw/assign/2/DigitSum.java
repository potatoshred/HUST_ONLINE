
import java.util.Scanner;

public class DigitSum {

    public static void main(String[] args) {

        System.out.print("Enter a number between 0 and 1000: ");

        Scanner scanner = new Scanner(System.in);

        while (!scanner.hasNextInt()) {
            System.err.print("Please input an integer: ");
            scanner.next();
        }

        int i;

        while((i=scanner.nextInt())<0 || i>1000){
            System.err.print("The number should between 0 and 1000: ");
        }
        

        int sum = 0;

        while(i>0){
            sum+=i%10;
            i/=10;
        }

        System.out.println("The sum of the digits is " + sum);
        

        scanner.close();

    }
}
