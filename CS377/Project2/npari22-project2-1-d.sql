/* THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS. Nihar Parikh */

/* ------------------------------------------
 Create a view for the director of sales which contains a list of customers with their name, email,
phone, the total number of books in their shopping cart (assuming that everybody orders just 1
copy of the book), and the total cost of their shopping carts. */

CREATE VIEW customer_profile
AS (	SELECT c.name, email, phone, COUNT(DISTINCT ISBN) as total_books, SUM(price) as total_cost
		FROM customer c, shopping_cart, contains, book
		WHERE email = customerEmail AND cID = cartID AND bookISBN = ISBN
		GROUP BY email
);