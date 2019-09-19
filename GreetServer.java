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
        	System.out.println("Existen dos tipos de enemigos, rojos y azules");
        	System.out.println("Para enviar un enemigo Rojo digite R seguido de el numero de liana donde lo quiera colocar");
        	System.out.println("Ejemplo: R9");
        	System.out.println("Para enviar un enemigo Azul siga el mismo procedimiento pero empezando con la A y luego el numero de liana");
            System.out.print("Enemigo: ");
            String response = scanner.nextLine();
            if (validateString(response)){
            	out.println(response);
            }
            else {
            	System.out.println("Error en codigo de enemigo, intentelo de nuevo");
            }
            
        }
    }
    
    public boolean validateString(String response) {
    	if (response.length()== 2) {
    		if (("R").equals(response.substring(1)) || ("A").equals(response.substring(1))) {
    			switch(response.substring(1)){
    			case "0": return true;
    			case "1": return true;
    			case "2": return true;
    			case "3": return true;
    			case "4": return true;
    			case "5": return true;
    			case "6": return true;
    			case "7": return true;
    			case "8": return true;
    			case "9": return true;
    			default: return false;
    			}
    		}
    		else {
    			return false;
    		}
    	}
    	else return false;
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
        	System.out.println("Esperando cliente");
            server.start(4444);
        }
        catch (Exception E){
            E.printStackTrace();
        }
    }
}