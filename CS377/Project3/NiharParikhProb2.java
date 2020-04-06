/* THIS CODE IS MY OWN WORK.
IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS.
Nihar Parikh */

import java.sql.*;
import java.util.*;

public class NiharParikhProb2
{
  public static void main(String args []) throws Exception
  {

     System.out.println("Nihar Parikh\nProblem 2\nTHIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS. - Nihar Parikh\n\n\n");

     if(args.length < 2 || (args.length % 2) > 0) {
        System.out.println("There are an incorrect number of command line arguments. Please enter both the first and last name of an actor or actress. Exiting.");
        System.exit(0);
     }

     ArrayList<String> fname = new ArrayList<String>();
     ArrayList<String> lname = new ArrayList<String>();
     
     for(int i = 0; i < args.length; i+=2) fname.add(args[i]);
     for(int i = 1; i < args.length; i+=2) lname.add(args[i]);

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

     for(int i = 0; i < fname.size(); i++) {
            ResultSet rset = stmt.executeQuery("SELECT * FROM actor WHERE fname = '" + fname.get(i) + "' AND lname = '" + lname.get(i) + "'");
            if(!rset.isBeforeFirst()) {
                System.out.println("Actor does not exist. Exiting.");
                System.exit(0);
            }
            rset.close();
     }

     String baseQuery = "SELECT DISTINCT name, year FROM movie m, casts c1 WHERE m.id = c1.mid";

     for(int i = 0; i < fname.size(); i++) baseQuery += " AND c1.mid IN (SELECT mid FROM casts, actor WHERE id = aid AND fname = '" + fname.get(i) + "' AND lname = '" + lname.get(i) + "')";
     
     ResultSet finalResults = stmt.executeQuery(baseQuery);

     if(!finalResults.isBeforeFirst()) {
            System.out.println("No results were found.");
            System.exit(0);
     }

     finalResults.last();
     int nRows = finalResults.getRow();
     System.out.println("Total number of movies where all actors were in the same movie: " + nRows + "\n");

     finalResults.beforeFirst();

     // Iterate through the result and print the movie names
     while (finalResults.next())
     {
            System.out.println(finalResults.getString(1) + " ; " + finalResults.getString(2));
     }

     // Close the ResultSet
     finalResults.close();

     // Close the Statement
     stmt.close();

     // Close the connection
     conn.close();   
  }
}