/* THIS CODE IS MY OWN WORK.
IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS.
Nihar Parikh */

import java.sql.*;

public class NiharParikhProb1
{
  public static void main(String args []) throws Exception
  {

     System.out.println("Nihar Parikh\nProblem 1\nTHIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS. - Nihar Parikh\n\n\n");

     String url = "jdbc:mysql://localhost:3306/";
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

     ResultSet rset = stmt.executeQuery("SELECT name, role, year FROM actor a, casts, movie m WHERE a.id = aid AND m.id = mid AND fname = 'Matt' AND lname = 'Damon' ORDER BY year DESC LIMIT 10");

     // Iterate through the result and print the movie names
     while (rset.next())
     {
            System.out.println(rset.getString(1) + " ; " + rset.getString(2) + " ; " + rset.getString(3));
     }

     // Close the ResultSet
     rset.close();

     // Close the Statement
     stmt.close();

     // Close the connection
     conn.close();   
  }
}