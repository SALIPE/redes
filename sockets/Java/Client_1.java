import java.net.*;
import java.io.*;

public class Client_1 {
  public static void main(String[] args) {
    try {
      if (args.length < 2){
         System.out.println("Usage: Client <server-IP> <message>");
         System.exit(0);
      }

      InetAddress address = InetAddress.getByName(args[0]);
      Socket client = new Socket(address,12345);
      ObjectOutputStream output = new ObjectOutputStream(client.getOutputStream());
      output.flush();
      output.writeObject(args[1]);
      output.close();

    }
    catch(Exception e) {
      System.out.println("Error: " + e.getMessage());
    }
  }
}
