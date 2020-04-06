/* THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS. Nihar Parikh */

USE online_bookstore; 

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
INSERT INTO book VALUES(1674957648, 'Awesome Book', 1995, 10.35, 'Random House');
INSERT INTO book VALUES(1674957647, 'Awesome Book', 1995, 10.35, 'Random House');

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


