<html>
<head>
<title> Nihar Parikh - Problem 1</title>
</head>
<body> 

<h1>All Books in the Bookstore:</h1><hr><br><br>

<p align="right"><a href="http://cs377spring16.mathcs.emory.edu/~npari22/NiharParikhProb2_input.php">Next Problem</a></p>


<?php

	$conn = mysqli_connect("cs377spring16.mathcs.emory.edu","cs377","Dj@B5WFd3Pf+","bookstore");
	if (mysqli_connect_errno())
	{
		printf("Connect failed: %s<br>", mysqli_connect_error());
		exit(1);
	}
	$query = 'select * from book';
	if ( ! ( $result = mysqli_query($conn, $query)) )
	{
		printf("Error: %s<br>", mysqli_error($conn));
		exit(1);
	}
	while ( $row = mysqli_fetch_assoc( $result ) )
	{
		foreach ($row as $key => $value)
		{
			print ($key . " = " . $value . "<br>");			
		}
		$author = '| ';
		$ISBN = $row['ISBN'];
		$query2 = "select * from author_book b, author a where b.aID = a.aID and ISBN = '$ISBN'";
		// print($query2 . "<br>");
		if ( ! ( $result2 = mysqli_query($conn, $query2)) )
		{
			printf("Error: %s<br>", mysqli_error($conn));
			exit(1);
		}
		// print(mysqli_fetch_all($result2));
		while ( $row2 = mysqli_fetch_assoc( $result2 ) ) 
		{
			$author = $author . $row2['name'] . " | ";
		}
		print ("author" . " = " . $author . "<br>");
		print("================<br><br>");
		mysqli_free_result($result2);
	}

	mysqli_free_result($result);
	mysqli_close($conn);
	
?>

<hr><br>



</body>
</html>
