import java.rmi.*;

public interface TTTClientRemote extends Remote
{
   void updateBoard(TTTBoard new_board) throws RemoteException;
}
