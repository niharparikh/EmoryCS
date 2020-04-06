import java.sql.*;

public class movies
{
  public static void main(String args []) throws Exception
  {

     String url = "jdbc:mysql://cs377spring16.mathcs.emory.edu/";
     String dbName = "imdb";
     String userName = "cs377";
     String password = "Dj@B5WFd3Pf+";
     String sslVer = "?useSSL=false";

     // Load the Oracle JDBC driver
     Class.forName("com.mysql.jdbc.Driver");

     // Connect to the database
     Connection conn = null;
     conn = DriverManager.getConnection(url + dbName + sslVer,userName,password);


     // Create a Statement
     Statement stmt = conn.createStatement();

     // ResultSet rset = stmt.executeQuery("SELECT name FROM actor a, casts, movie m WHERE a.id = aid AND m.id = mid AND fname = 'Matt' AND lname = 'Damon' ORDER BY year DESC LIMIT 10");

     ResultSet rset = stmt.executeQuery("SELECT * FROM actor LIMIT 10");


     // Iterate through the result and print the employee names
     while (rset.next ())
     {
          System.out.println (rset.getString (1));
     }

     // Close the ResultSet
     rset.close();

     // Close the Statement
     stmt.close();

     // Close the connection
     conn.close();   
  }
}