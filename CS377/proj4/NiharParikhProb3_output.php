<html>
<head>
<title>Nihar Parikh - Problem 3 - Output</title>
</head>
<body> 
<h1>View Shopping Cart:</h1><hr><br><br><br>

<a href="http://cs377spring16.mathcs.emory.edu/~npari22/NiharParikhProb3_input.php">Back</a><br><br>

<?php
	$email = '';
	$cartSequence = '';
	$email = $_POST['email'];
	$cartSequence = $_POST['cartSequence'];
	$email = trim($email);
	$cartSequence = trim($cartSequence);

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
		
		$query = "select * from shopping_cart, book where cEmail = '$email' and cartSequence = $cartSequence";
		if ( ! ( $result = mysqli_query($conn, $query)) )
		{
			printf("Error: %s<br>", mysqli_error($conn));
			exit(1);
		}	
		
		if (mysqli_num_rows($result) == 0) 
		{
			print("The email or shopping cart number is incorrect. Please retry.");
			exit(1);
		} 

		mysqli_free_result($result);

		$query = "select i.ISBN, title, price from item_cart i, book b where i.cEmail = '$email' and i.cartSequence = $cartSequence and i.ISBN = b.ISBN";
		if ( ! ( $result = mysqli_query($conn, $query)) )
		{
			printf("Error: %s<br>", mysqli_error($conn));
			exit(1);
		}

		if (mysqli_num_rows($result) == 0) 
		{
			print("The shopping cart is empty.");
			exit(1);
		} 

		while ( $row = mysqli_fetch_assoc( $result ) )
		{
			foreach ($row as $key => $value)
			{
				print ($key . " = " . $value . "<br>");			
			}
			print("================<br><br>");
		}

		//print("<br><br>Done.<br>");

		mysqli_free_result($result);

		$query = "select count(i.ISBN) as num_of_books, sum(price) as price_of_cart from item_cart i, book b where i.cEmail = '$email' and i.cartSequence = $cartSequence and i.ISBN = b.ISBN";
		if ( ! ( $result = mysqli_query($conn, $query)) )
		{
			printf("Error: %s<br>", mysqli_error($conn));
			exit(1);
		}

		$data = [];
		while ($row = $result->fetch_assoc()) {
		    $data[] = $row;
		}

		print("<br><hr><br>");
		print("Number of Books: " . $data[0]['num_of_books'] . "<br>");
		print("Total Price of Cart: $" . $data[0]['price_of_cart'] . "<br><br>");

		mysqli_free_result($result);

		mysqli_close($conn);

	}
	
	
?>

</body>
</html>
