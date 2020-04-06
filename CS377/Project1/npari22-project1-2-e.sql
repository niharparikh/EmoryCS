/* THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS. Nihar Parikh */

SELECT DISTINCT a.fname, a.lname
FROM movie m, director d, actor a, casts c, movie_director md
WHERE d.fname = "Woody" AND d.lname = "Allen" 
/* The attribute name for the foreign key referencing actor(id) in the casts table is aid not pid, as listed on the project outline.*/
AND c.aid = a.id AND c.mid = m.id AND md.did = d.id AND md.mid = m.id
ORDER BY a.fname ASC, a.lname ASC;