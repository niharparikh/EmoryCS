/* THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS. Nihar Parikh */

/* 
• actor(id, fname, lname, gender)
	– id = unique identifier for each actor
	– fname = first name of the actor
	– lname = last name of the actor
	– gender = gender of the actor
This relation contains information on the actors that can be found in the IMDB database.

• movie(id, name, year)
	– id = unique identifier for each movie
	– name = name of the movie
	– year = year the movie was released
This relation contains information on the movies that can be found in the IMDB database.

• director(id, fname, lname)
	– id = unique identifier for each director
	– fname = first name of the director
	– lname = last name of the director
This relation contains information on the directors of the movies that can be found in the IMDB
database.

• genre(mid, genre)
	– mid = foreign key referencing movie(id)
	– genre = the genre of the movie
This relation contains information about the genre (classification) of the movies in IMDB.

• casts(pid, mid, role)
	– aid = foreign key referencing actor(id)
	– mid = foreign key referencing movie(id)
	– role = name of the character in the movie
This relation contains information about the actors in each movie and the role they play.

• movie director(did, mid)
	– did = foreign key referencing director(id)
	– mid = foreign key referencing movie(id)
This relation contains information about the director(s) for each movie in IMDB.

*/

/* ------------------------------------------
List the movies and the year where Matt Damon, George Clooney, and Brad Pitt have
all played a role.
--------------------------------------------- */

/* Using relational division (won't run).

SELECT m.name, year
FROM movie m
WHERE NOT EXISTS (
	SELECT aid FROM casts c1
	WHERE aid IN (
		SELECT a.id
		FROM actor a
		WHERE (a.fname, a.lname) IN (('Matt','Damon'),('Brad','Pitt'),('George','Clooney'))
	)
	AND aid NOT IN (
		SELECT aid
		FROM casts c2
		WHERE m.id = c2.mid
	)
); */

SELECT DISTINCT name, year
FROM movie m, casts c1
WHERE c1.mid IN (SELECT c2.mid FROM casts c2, actor a1 WHERE a1.id = c2.aid AND a1.fname = 'Matt' AND a1.lname = 'Damon')
AND c1.mid IN (SELECT c3.mid FROM casts c3, actor a2 WHERE a2.id = c3.aid AND a2.fname = 'Brad' AND a2.lname = 'Pitt')
AND c1.mid IN (SELECT c4.mid FROM casts c4, actor a3 WHERE a3.id = c4.aid AND a3.fname = 'George' AND a3.lname = 'Clooney')
AND m.id = c1.mid;




