import java.net.*;
import java.io.*;

public class Server_1 {
  public static void main(String[] args) {
    boolean flag;
    try {
      // Start server on port 12345
      ServerSocket server = new ServerSocket(12345);
      flag = true;
      while(flag) {
        System.out.println("I am the server");
        // Waits for a connection
        Socket client_socket = server.accept();
        System.out.println("Connection established: " + client_socket.getInetAddress().getHostAddress()
                           + ", " + client_socket.getPort());
        ObjectInputStream input = new ObjectInputStream(client_socket.getInputStream());
        String msg = (String)input.readObject();

        System.out.println(msg);
        input.close();
        client_socket.close();

        if (msg.equals("over")) {
          server.close();
          flag = false;
        }

      }
    }
    catch(Exception e) {
       System.out.println("Error: " + e.getMessage());
    }

  }
}
