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