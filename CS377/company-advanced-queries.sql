/* Set Division Example: 
Find lname of all employees who work on all projects
controlled by department number 4 */
SELECT fname, lname
FROM employee
WHERE NOT EXISTS
( SELECT pnumber FROM project
  WHERE pnumber in
   (SELECT pnumber FROM project WHERE dnum = 4)
   AND pnumber NOT IN 
   ( SELECT pno FROM works_on WHERE essn = ssn));

/* Only Example:
Find the names of projects that are worked
on by only employees in the ‘Research’ department? 
*/
SELECT pname
FROM project
WHERE NOT EXISTS
 ( SELECT ssn FROM employee
   WHERE ssn IN (SELECT essn FROM WORKS_on WHERE pno = pnumber)
   AND ssn NOT IN ( SELECT ssn FROM employee, department
                    WHERE dno = dnumber AND dname = 'Research') );

/* Find the name of the departments with 2 or more male employees */
SELECT dname
FROM department, employee
WHERE dnumber = dno AND sex = 'M'
GROUP BY dname
HAVING COUNT(ssn) >= 2;

/* Find the name of employees who have more than
two dependents and work on more than 2 projects  */
SELECT ssn, fname, lname
FROM employee
WHERE ssn IN ( SELECT essn FROM dependent
               GROUP BY essn
               HAVING COUNT(name) > 2 )
AND ssn IN ( SELECT essn FROM works_on
             GROUP BY essn
             HAVING COUNT(pno) > 2 );

/* Find the name of the employees with the most number of dependents */
SELECT fname, lname
FROM employee, dependent
WHERE ssn = essn
GROUP BY ssn
HAVING COUNT(name) = ( SELECT COUNT(name) AS totalCount
                       FROM dependent GROUP BY essn
                       ORDER BY totalCount DESC
                       LIMIT 1);

/* Insert new tuples */
INSERT INTO employee
VALUES ('Joyce', 'C', 'Ho', '111223333', '1985-02-05', '400 Dowman, Atlanta, GA',
        'F', 80000.00, '987654321', 5);


/* Insert using SQL*/
CREATE TABLE dept_info (
    dept_name VARCHAR(15),
    no_of_emp INT,
    tot_salary INT);

INSERT INTO dept_info 
( SELECT dname, count(*), sum(salary)
  FROM department, employee
  WHERE dno = dnumber
  GROUP BY dno);

/* Delete Joyce Ho from employee table */
DELETE FROM employee where fname = 'Joyce' AND lname = 'Ho';

/* Update location of project number 10 */
UPDATE project
SET plocation = 'Bellaire', dnum = 5
WHERE pnumber = 10;

/* Create view for admin */
CREATE VIEW emp_activity
AS ( SELECT fname, lname, pname, hours
     FROM employee, works_on, project
     WHERE ssn = essn AND pno = pnumber);

/* Find employee that has more than 2 dependents */
SELECT essn FROM dependent
GROUP BY essn HAVING COUNT(name) > 2;

/* Find employees that works on all projects controlled by department #1
- set difference technique */
SELECT ssn 
FROM employee e
WHERE NOT EXISTS
( SELECT pnumber FROM project
  WHERE pnumber IN ( SELECT pnumber FROM project WHERE dnum = 1)
  AND pnumber NOT IN ( SELECT pno FROM works_on WHERE essn = e.ssn));

/* Find the fname, lname of employees with more than 2 dependents
and work on all projects controlled by department #1  */
SELECT fname, lname
FROM employee
WHERE ssn IN
 ( SELECT essn FROM dependent
   GROUP BY essn HAVING COUNT(name) > 2)
AND ssn IN
 ( SELECT ssn FROM employee e
WHERE NOT EXISTS
( SELECT pnumber FROM project
  WHERE pnumber IN ( SELECT pnumber FROM project WHERE dnum = 1)
  AND pnumber NOT IN ( SELECT pno FROM works_on WHERE essn = e.ssn)));
