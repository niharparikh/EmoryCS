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
Who are the top 100 directors who have directed the most movies from 2005 to 2010,
in descending order of the number of movies they have directed? Output their first name, last
name, and number of movies directed.
--------------------------------------------- */

SELECT d.fname, d.lname, count(mid) AS no_of_movies
FROM director d, movie_director
WHERE d.id = did 
AND mid IN (
	SELECT m.id
	FROM movie m
	WHERE year IN (2005,2006,2007,2008,2009,2010)
)
GROUP BY d.id
ORDER BY count(mid) DESC
LIMIT 100;





