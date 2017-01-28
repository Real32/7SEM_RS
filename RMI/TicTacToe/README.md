:~$ javac TTTServiceImpl.java
:~$ javac TicTacToe.java 


:~$ rmic TTTServiceImpl
:~$ rmic TicTacToe


:~$ rmiregistry 12345     -- open port


:~$ java -ea TTTServiceImpl		--server
:~$ java -ea TicTacToe			--client