/* THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS. Nihar Parikh */

SELECT c.name, title, publisherName, p.address
FROM contains, shopping_cart, customer c, book, publisher p
WHERE cartID = cID AND customerEmail = email AND bookISBN = ISBN AND publisherName = p.name
ORDER BY c.name;