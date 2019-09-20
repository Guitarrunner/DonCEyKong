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
    	InetAddress ip = InetAddress.getByName("192.168.43.209");
        serverSocket = new ServerSocket(port,1,ip);
        clientSocket = serverSocket.accept();
        out = new PrintWriter(clientSocket.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        System.out.println("Perro1");

        String inputLine;
        while (true) {
        	System.out.println("Existen dos tipos de enemigos, rojos y azules");
        	System.out.println("Para enviar un enemigo Rojo digite R seguido de el numero de liana donde lo quiera colocar, use numeros de dos digitos del 01 al 12");
        	System.out.println("Ejemplo: R09");
        	System.out.println("Para enviar un enemigo Azul siga el mismo procedimiento pero empezando con la A y luego el numero de liana");
            System.out.print("Enemigo: ");
            String response = scanner.nextLine();
            if (validateString(response)){
            	String finalresponse = response.substring(0,1) + "&" +response.substring(1);
            	out.println(finalresponse);
            }
            else {
            	System.out.println("Error en codigo de enemigo, intentelo de nuevo");
            }
            
        }
    }
    
    public boolean validateString(String response) {
    	if (response.length()== 3) {
    		if (("R").equals(response.substring(0,1)) || ("A").equals(response.substring(0,1))) {
    			switch(response.substring(1)){
    			case "12": return true;
    			case "01": return true;
    			case "02": return true;
    			case "03": return true;
    			case "04": return true;
    			case "05": return true;
    			case "06": return true;
    			case "07": return true;
    			case "08": return true;
    			case "09": return true;
    			case "10": return true;
    			case "11": return true;
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
