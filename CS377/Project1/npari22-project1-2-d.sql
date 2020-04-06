/* THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS. Nihar Parikh */

SELECT name, role, year
FROM movie m, actor a, casts c
WHERE fname = "Steve" AND lname = "Carell" 
/* The attribute name for the foreign key referencing actor(id) in the casts table is aid not pid, as listed on the project outline.*/
AND c.aid = a.id AND c.mid = m.id
ORDER BY year DESC;