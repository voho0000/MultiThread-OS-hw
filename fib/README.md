# Fibonacci sequence

This is a Java program that generates the Fibonacci sequence using multiple threads.

## 環境建置

To run this program, you will need to have Java Development Kit (JDK) installed on your computer. You can download the latest version of JDK from the official website: https://www.oracle.com/java/technologies/downloads/.

## 如何執行程式

To execute the program, you need to compile the source code first. Open a terminal and navigate to the directory where the source file is located. Then, use the following command to compile the code:

```
javac FibMultiThread.java
```

This will create a .class file for the program. To run the program, use the following command:

```
java FibMultiThread [numElements]
```

Replace `[numElements]` with the number of elements you want to generate in the Fibonacci sequence.

## 執行結果
！[](./Fibonacci-snapshot.png)

## 程式碼說明

The program consists of two classes: `FibGeneratorThread` and `FibMultiThread`. 

### `FibGeneratorThread` 

This class extends the `Thread` class and generates the Fibonacci sequence. It takes the number of elements to generate as a parameter in the constructor. The `run()` method generates the sequence and stores it in an array. The `getFibArray()` method returns the generated sequence.

### `FibMultiThread`

This class is the main class of the program. It takes the number of elements to generate as a command-line argument. It creates an instance of `FibGeneratorThread` and starts the thread. It then waits for the thread to finish using the `join()` method. Finally, it retrieves the generated sequence from the `FibGeneratorThread` object and prints it to the console.
