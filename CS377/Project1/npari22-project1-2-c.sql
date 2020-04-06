/* THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS. Nihar Parikh */

SELECT name, year
FROM movie m, genre g, movie_director md, director d
WHERE fname = "Steven" AND lname = "Soderbergh" AND genre = "Thriller" 
AND m.id = g.mid AND m.id = md.mid AND md.did = d.id
ORDER BY year DESC;