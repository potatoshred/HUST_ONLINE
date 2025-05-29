package hust.cs.java.c7_array;

import java.util.Arrays;

public class C7 {
}

class TestArrayCopy {
    public static void main(String[] args) {

        // manual
        int[] sourceArray = {2, 3, 1, 5, 10};
        int[] targetArray = new int[sourceArray.length];
        for (int i = 0; i < sourceArray.length; i++) {
            targetArray[i] = sourceArray[i];//=赋值对引用类型是浅拷贝
        }

        // arraycopy(sourceArray,srcPos,targetArray,tarPos,length);
        System.arraycopy(sourceArray, 0, targetArray, 0, sourceArray.length);//target要求已存在

        // clone
        targetArray = sourceArray.clone();
    }
}

class TestArraySort {
    public static void main(String[] args) {
        int[] sourceArray = {2, 3, 1, 5, 10};
        Arrays.sort(sourceArray);// locally, ascend only
        System.out.println(Arrays.toString(sourceArray)); // [1, 2, 3, 5, 10]

    }

    public static int binarySearch(int[] list, int key) {
        int low = 0;
        int high = list.length - 1;

        while (high >= low) {
            int mid = (low + high) / 2;
            if (key < list[mid])
                high = mid - 1;
            else if (key == list[mid])
                return mid;
            else
                low = mid + 1;
        }
        return -1;
    }

    static void selectionSort(double[] list) {
        for (int i = list.length - 1; i >= 0; i--) {
            // Find the maximum in the list[0..i]
            double currentMax = list[0];
            int currentMaxIndex = 0;

            for (int j = 0; j <= i; j++) {
                if (currentMax < list[j]) {
                    currentMax = list[j];
                    currentMaxIndex = j;
                }
            }

            // Swap list[i] with list[currentMaxIndex] if necessary;
            if (currentMaxIndex != i) {
                list[currentMaxIndex] = list[i];
                list[i] = currentMax;
            }
        }
    }

}