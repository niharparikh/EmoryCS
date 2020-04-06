/* THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS. Nihar Parikh */

CREATE DATABASE online_bookstore;
USE online_bookstore;  
CREATE TABLE author
(
	aID INT NOT NULL,
	address VARCHAR(50),
	phone CHAR(11),
	URL VARCHAR(50),
	CONSTRAINT authorpk PRIMARY KEY(aID)
);
CREATE TABLE publisher 
(
	name VARCHAR(50) NOT NULL,
	address VARCHAR(50),
	phone CHAR(11),
	URL VARCHAR(50),
	CONSTRAINT publisherpk PRIMARY KEY(name)
);
CREATE TABLE book 
(
	ISBN INT NOT NULL,
	title VARCHAR(50),
	year INT,
	price NUMERIC(10,2),
	publisherName VARCHAR(50) NOT NULL,
	CONSTRAINT bookpk PRIMARY KEY(ISBN),
	CONSTRAINT bookFK FOREIGN KEY(publisherName) REFERENCES publisher(name)
);

CREATE TABLE customer 
(
	email VARCHAR(50) NOT NULL,
	name VARCHAR(50),
	address VARCHAR(50),
	phone CHAR(11),
	CONSTRAINT customerpk PRIMARY KEY(email)
);
CREATE TABLE shopping_cart 
(
	cID INT NOT NULL,
	customerEmail VARCHAR(50) NOT NULL,
	CONSTRAINT scpk PRIMARY KEY(cID,customerEmail),
	CONSTRAINT scfk FOREIGN KEY(customerEmail) REFERENCES customer(email)
);
CREATE TABLE written_by 
(
	bookISBN INT NOT NULL,
	authorID INT NOT NULL,
	CONSTRAINT wbfk1 FOREIGN KEY(bookISBN) REFERENCES book(ISBN),	
	CONSTRAINT wbfk2 FOREIGN KEY(authorID) REFERENCES author(aID)	
);
CREATE TABLE contains 
(
	cartID INT NOT NULL,
	bookISBN INT NOT NULL,		
	CONSTRAINT containsfk1 FOREIGN KEY(cartID) REFERENCES shopping_cart(cID),
	CONSTRAINT containsfk2 FOREIGN KEY(bookISBN) REFERENCES book(ISBN)	
);

/* Insert author tuples */
INSERT INTO author VALUES(1, '605 Asbury Circle, Atlanta, GA 30322', '15108561936', 'http://jkrowling.com');
INSERT INTO author VALUES(2, '605 Asbury Circle, Atlanta, GA 30322', '15108561936', 'http://jkrowling.com');
INSERT INTO author VALUES(3, '605 Asbury Circle, Atlanta, GA 30322', '15108561936', 'http://jkrowling.com');

/* Insert publisher tuples */
INSERT INTO publisher VALUES('Random House', '605 Asbury Circle, Atlanta, GA 30322', '15108561936', 'http://jkrowling.com');
INSERT INTO publisher VALUES('Penguin', '605 Asbury Circle, Atlanta, GA 30322', '15108561936', 'http://jkrowling.com');
INSERT INTO publisher VALUES('Scholastic', '605 Asbury Circle, Atlanta, GA 30322', '15108561936', 'http://jkrowling.com');

/* Insert book tuples */
INSERT INTO book VALUES(1674957649, 'Awesome Book', 1995, 10.35, 'Random House');
INSERT INTO book VALUES(1674957648, 'Awesome Book2', 1995, 10.35, 'Penguin');
INSERT INTO book VALUES(1674957647, 'Awesome Book3', 1995, 10.35, 'Random House');

/* Insert customer tuples */
INSERT INTO customer VALUES('bob@gmail.com', 'Bob', '605 Asbury Circle, Atlanta, GA 30322', '15108561936');
INSERT INTO customer VALUES('fred@gmail.com', 'Fred', '605 Asbury Circle, Atlanta, GA 30322', '15108561936');
INSERT INTO customer VALUES('george@gmail.com', 'George', '605 Asbury Circle, Atlanta, GA 30322', '15108561936');


/* Insert shopping_cart tuples */
INSERT INTO shopping_cart VALUES(1, 'bob@gmail.com');
INSERT INTO shopping_cart VALUES(2, 'fred@gmail.com');
INSERT INTO shopping_cart VALUES(3, 'george@gmail.com');

/* Insert written_by tuples */
INSERT INTO written_by VALUES(1674957649, 1);
INSERT INTO written_by VALUES(1674957648, 2);
INSERT INTO written_by VALUES(1674957647, 3);

/* Insert contains tuples */
INSERT INTO contains VALUES(1, 1674957649);
INSERT INTO contains VALUES(2, 1674957648);
INSERT INTO contains VALUES(3, 1674957647);


/* ------------------------------------------
Question 1a Query - Find the total numbers of books that each costumer has bought of each publisher. */

SELECT email, publisherName, COUNT(DISTINCT ISBN) AS books
FROM book, shopping_cart, publisher p, contains, customer
WHERE email = customerEmail AND cID = cartID AND bookISBN = ISBN AND publisherName = p.name
GROUP BY email, publisherName;



