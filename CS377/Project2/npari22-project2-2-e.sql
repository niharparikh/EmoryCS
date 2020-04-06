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
For each year, count the number of movies in that year that had only female actors
(and at least one actor).
--------------------------------------------- */

SELECT year, count(m.id) AS no_of_movies
FROM movie m
WHERE m.id IN (
	SELECT mid
	FROM casts
	GROUP BY mid
	HAVING count(aid) > 0
)
AND m.id NOT IN (
	SELECT mid
	FROM casts, actor a
	WHERE aid = a.id AND a.gender = 'M'
)
GROUP BY year;
