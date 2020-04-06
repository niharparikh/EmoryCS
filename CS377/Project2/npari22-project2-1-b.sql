/* THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS. Nihar Parikh */

/* ------------------------------------------
Update the ISBN number of one of the books and the email account of a customer you inserted.
Verify that your updates were propagated to the other tables (no mismatches). Show the queries
for the updates and the verifications (show the tables that reference these values with corresponding
changes). */

/* Fix contraints to include cascade provision. */

ALTER TABLE book DROP FOREIGN KEY bookFK;

ALTER TABLE book
ADD CONSTRAINT bookFK 
FOREIGN KEY(publisherName) 
REFERENCES publisher(name) 
ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE shopping_cart DROP FOREIGN KEY scfk;

ALTER TABLE shopping_cart
ADD CONSTRAINT scfk 
FOREIGN KEY(customerEmail) 
REFERENCES customer(email)
ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE written_by DROP FOREIGN KEY wbfk1;
ALTER TABLE written_by DROP FOREIGN KEY wbfk2;

ALTER TABLE written_by
ADD CONSTRAINT wbfk1 
FOREIGN KEY(bookISBN) 
REFERENCES book(ISBN)
ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE written_by
ADD CONSTRAINT wbfk2 
FOREIGN KEY(authorID) 
REFERENCES author(aID)
ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE contains DROP FOREIGN KEY containsfk1;
ALTER TABLE contains DROP FOREIGN KEY containsfk2;

ALTER TABLE contains
ADD CONSTRAINT containsfk1 
FOREIGN KEY(cartID) 
REFERENCES shopping_cart(cID)
ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE contains
ADD CONSTRAINT containsfk2 
FOREIGN KEY(bookISBN) 
REFERENCES book(ISBN)
ON DELETE CASCADE ON UPDATE CASCADE;

UPDATE book
SET ISBN = 1674957645
WHERE ISBN = 1674957649;

UPDATE customer
SET email = 'nihar06@gmail.com'
WHERE email = 'bob@gmail.com';

/* Check for proper updates. */

SELECT *
FROM book;

SELECT *
FROM written_by;

SELECT *
FROM contains;

SELECT *
FROM customer;

SELECT *
FROM shopping_cart;