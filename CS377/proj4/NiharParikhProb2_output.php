<html>
<head>
<title>Nihar Parikh - Problem 2 - Output</title>
</head>
<body> 
<h1>Add Book to Shopping Cart:</h1><hr><br><br><br>

<a href="http://cs377spring16.mathcs.emory.edu/~npari22/NiharParikhProb2_input.php">Back</a><br>
<p align="right"><a href="http://cs377spring16.mathcs.emory.edu/~npari22/NiharParikhProb3_input.php">Next Problem</a></p>
<br>

<?php
	$email = '';
	$cartSequence = '';
	$ISBN = '';
	$email = $_POST['email'];
	$cartSequence = $_POST['cartSequence'];
	$ISBN = $_POST['ISBN'];
	$email = trim($email);
	$cartSequence = trim($cartSequence);
	$ISBN = trim($ISBN);

	if ($email == NULL) 
	{
		print("Please provide a value for email.<br>");
		exit(1);
	}
	elseif ($cartSequence == NULL OR !(is_numeric($cartSequence))) 
	{
		print("Please provide a valid value for shopping cart number.<br>");
		exit(1);
	}
	elseif ($ISBN == NULL) 
	{
		print("Please provide a value for ISBN.<br>");
		exit(1);
	}
	else 
	{
		$cartSequence = (int) $cartSequence;
		//print("Checked values.<br>");
		
		$conn = mysqli_connect("cs377spring16.mathcs.emory.edu","cs377","Dj@B5WFd3Pf+","bookstore");
		
		if (mysqli_connect_errno())
		{
			printf("Connect failed: %s<br>", mysqli_connect_error());
			exit(1);
		}
		
		$query = "select * from customer where email = '$email'";
		$query2 = "select * from book where ISBN = '$ISBN'";
		
		if ( ! ( $result = mysqli_query($conn, $query)) )
		{
			printf("Error: %s<br>", mysqli_error($conn));
			exit(1);
		}
		if ( ! ( $result2 = mysqli_query($conn, $query2)) )
		{
			printf("Error: %s<br>", mysqli_error($conn));
			exit(1);
		}
		
		if (mysqli_num_rows($result) == 0) 
		{
			print("Customer email is not in database.<br>");
			exit(1);
		} 
		elseif (mysqli_num_rows($result2) == 0) 
		{
			print("ISBN is not in database.<br>");
			exit(1);
		}
		else 
		{
			//print("Checked email and ISBN.<br>");
			$query3 = "select * from shopping_cart where cEmail = '$email' and cartSequence = $cartSequence";
			if ( ! ( $result3 = mysqli_query($conn, $query3)) )
			{
				printf("Error: %s<br>", mysqli_error($conn));
				exit(1);
			}	
			
			if (mysqli_num_rows($result3) == 0) 
			{
				$query4 = "insert into shopping_cart values('$email', $cartSequence)";
				if ( ! ( $result4 = mysqli_query($conn, $query4)) )
				{
					printf("Error: %s<br>", mysqli_error($conn));
					exit(1);
				}
				//mysqli_free_result($result4);
			} 

			$query5 = "insert into item_cart values('$email', $cartSequence, '$ISBN')";
			if ( ! ( $result5 = mysqli_query($conn, $query5)) )
			{
				printf("Error: %s<br>", mysqli_error($conn));
				exit(1);
			}

			print("Book successfully added into shopping cart.<br>");

			mysqli_free_result($result3);
			//mysqli_free_result($result5);	

		}

		mysqli_free_result($result);
		mysqli_free_result($result2);
		mysqli_close($conn);

	}
	
?>

</body>
</html>
