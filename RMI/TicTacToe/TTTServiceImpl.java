import java.rmi.*;
import java.rmi.server.*;
import java.util.*;

class TTTServiceImpl extends UnicastRemoteObject
   implements TTTService
{
   public final static String ServiceName = "TTT";


   public final static int ServicePort = 12345;

   // the object being served up
   protected TTTBoard board = new TTTBoard();


   public TTTServiceImpl() throws RemoteException
   {
      super();
   }

   public TTTBoard getState() throws RemoteException
   {
      return board;
   }

   public void pick(int col, int row) throws RemoteException
   {
      board.pick(col, row);
      updateClients();
   }

   public void reset() throws RemoteException
   {
      board.reset();
      updateClients();
   }

   List clients = Collections.synchronizedList(new LinkedList());
   public void register(TTTClientRemote newClient) throws RemoteException
   {
      clients.add(newClient);
   }

   public void updateClients()
   {
      Iterator it = clients.iterator();
      while ( it.hasNext() )
      {
         TTTClientRemote client = (TTTClientRemote)it.next();
         try
         {
            client.updateBoard(board);
         }
         catch ( Exception e )
         {
            System.out.println("Could not update client " + client.toString());
         }
      }
          
   }

   public static void main(String args[])
   {
      System.out.println("Initializing TTTService...");
      try
      {
         TTTService cserv = new TTTServiceImpl();
         String serverObjectName = "rmi://localhost:" + ServicePort
            + "/" + ServiceName;
         Naming.rebind(serverObjectName, cserv);
         System.out.println("TTTService running.");
      }
      catch (Exception e)
      {
         System.out.println("Exception: " + e.getMessage());
         e.printStackTrace();
      }
   }
}
