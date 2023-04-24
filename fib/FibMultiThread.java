class FibGeneratorThread extends Thread {
    private int numElements;
    private long[] fibArray;

    public FibGeneratorThread(int numElements) {
        this.numElements = numElements;
        this.fibArray = new long[numElements];
    }

    public void run() {
        if (numElements <= 0) return;

        fibArray[0] = 0;
        if (numElements == 1) return;

        fibArray[1] = 1;
        for (int i = 2; i < numElements; i++) {
            fibArray[i] = fibArray[i - 1] + fibArray[i - 2];
        }
    }

    public long[] getFibArray() {
        return fibArray;
    }
}

public class FibMultiThread {
    public static void main(String[] args) {
        int numElements = Integer.parseInt(args[0]);

        FibGeneratorThread fibGenThread = new FibGeneratorThread(numElements);
        fibGenThread.start();

        try {
            fibGenThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        long[] fibArray = fibGenThread.getFibArray();
        for (int i = 0; i < numElements; i++) {
            System.out.print(fibArray[i] + (i == numElements - 1 ? "\n" : ", "));
        }
    }
}
