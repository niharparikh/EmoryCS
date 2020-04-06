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
Which actor(s) has only been in Steven Soderbergh’s movies?
--------------------------------------------- */

/* Only means that the actor may be in a Steven Soderbergh that he co-directs with others. */


SELECT a.fname, a.lname
FROM actor a
WHERE NOT EXISTS
( SELECT * FROM casts
   WHERE mid IN (SELECT c.mid FROM casts c WHERE a.id = aid)
   AND mid NOT IN ( SELECT r.mid FROM director d, movie_director r
                    WHERE d.id = r.did AND fname = "Steven" AND lname = "Soderbergh" )
)
ORDER BY a.lname;

-- SELECT a.fname, a.lname, m.name, m.id, d.fname, d.lname 
-- FROM actor a, casts c, movie m, director d, movie_director r
-- WHERE a.id = c.aid AND m.id = r.mid AND c.mid = r.mid AND d.id = r.did AND m.name = "Erin Brockovich";
