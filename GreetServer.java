import java.net.*;
import java.io.*;
import java.util.Scanner;


public class GreetServer {
    private ServerSocket serverSocket;
    private Socket clientSocket;
    private PrintWriter out;
    private BufferedReader in;
    Scanner scanner = new Scanner(System.in);  // Create a Scanner object


    public void start(int port) throws IOException {
        serverSocket = new ServerSocket(port);
        clientSocket = serverSocket.accept();
        out = new PrintWriter(clientSocket.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

        String inputLine;
        while (true) {
            System.out.print("Response: ");
            String response = scanner.nextLine();
            out.println(response);
        }
    }

    public void stop() throws IOException {
        in.close();
        out.close();
        clientSocket.close();
        serverSocket.close();
    }
    public static void main(String[] args) {
        GreetServer server=new GreetServer();

        try {
            server.start(4444);
        }
        catch (Exception E){
            E.printStackTrace();
        }
    }
}