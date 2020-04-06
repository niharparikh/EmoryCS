/* THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS. Nihar Parikh */

/* ------------------------------------------
Delete one of the publishers that you have 
inserted that has published a book. */

/* Deleting publisher will also delete any book and contains entries that are dependent on the publisher. */

DELETE FROM publisher WHERE name = 'Penguin';