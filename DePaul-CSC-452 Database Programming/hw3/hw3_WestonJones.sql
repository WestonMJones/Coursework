--Weston Jones -- Homework 3 -- CSC 352 Database Programming -- Section 901

-- Question 1
SET SERVEROUTPUT ON
DECLARE 
    cur_sal emp.sal%TYPE := 0;
    avg_sal emp.sal%TYPE :=0;
    CURSOR emps is SELECT sal FROM emp; 
BEGIN 
    OPEN emps; 
    LOOP 
        FETCH emps into cur_sal; 
        EXIT WHEN emps%notfound; 
        if cur_sal >= 1000 THEN
            avg_sal := avg_sal + cur_sal; 
        else
            avg_sal := avg_sal + 1000;
        end if;
    END LOOP;
    avg_sal := avg_sal / emps%ROWCOUNT;
    CLOSE emps; 
    DBMS_OUTPUT.put_line('The average salary is: ' ||avg_sal|| '.');
END; 

--Question 2
SET SERVEROUTPUT ON
BEGIN 
    UPDATE temp_emp
    SET sal = sal + (sal * .1)
    WHERE deptno = 10;
    dbms_output.put_line('' ||sql%rowcount|| ' employees from department 10 got a 10% raise.');    
    
    DELETE FROM temp_emp WHERE deptno = 20;
    dbms_output.put_line('' ||sql%rowcount|| ' employees from department 20 were deleted.');    
END; 

--Question 3
SET SERVEROUTPUT ON
DECLARE
    CURSOR c1 is SELECT last_name FROM employees;
    ename employees.last_name%TYPE;
BEGIN
    OPEN c1;
    FETCH c1 INTO ename; 
    IF c1%FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Yes, curse c1 is found');
    ELSE
        DBMS_OUTPUT.PUT_LINE('No, curse c1 is NOT found');
    END IF;
    CLOSE c1;
END; 

--Question 4
SET SERVEROUTPUT ON
DECLARE
    CURSOR cemp IS
    SELECT ename, sal
        FROM emp 
        WHERE deptno = 10 
        ORDER BY sal DESC;
BEGIN
    for indx in cemp LOOP
        DBMS_OUTPUT.put_line ('current row number is: '|| cemp%ROWCOUNT || ': ' || RPAD (indx.ename, 10) || ': ' ||indx.sal ||'.');
    END LOOP;
END;

--Question 5
SET SERVEROUTPUT ON
DECLARE
    CURSOR cemp IS
        SELECT EMPLOYEE_ID, FIRST_NAME, LAST_NAME, SALARY
        FROM employees 
        ORDER BY SALARY DESC;
    cur_emp cemp%ROWTYPE;
    counter number(2);
BEGIN
    OPEN cemp;
    FOR counter in 1 .. 5 LOOP
        FETCH cemp into cur_emp;
        DBMS_OUTPUT.put_line ('#' ||cur_emp.EMPLOYEE_ID|| ' ' ||cur_emp.FIRST_NAME|| ' ' ||cur_emp.LAST_NAME|| ' has a salary of: ' ||cur_emp.SALARY|| '');
    END LOOP;
    close cemp;
END;

--Question 6
SET SERVEROUTPUT ON
DECLARE
    CURSOR cemp IS
        SELECT EMPLOYEE_ID, FIRST_NAME, LAST_NAME, SALARY
        FROM employees 
        ORDER BY SALARY DESC;
    eid EMPLOYEES.EMPLOYEE_ID%TYPE;
    fname EMPLOYEES.FIRST_NAME%TYPE;
    lname EMPLOYEES.LAST_NAME%TYPE;
    sal EMPLOYEES.SALARY%TYPE;
    counter number(2);
BEGIN
    OPEN cemp;
    FOR counter in 1 .. 5 LOOP
        FETCH cemp into eid, fname, lname, sal;
        DBMS_OUTPUT.put_line ('#' ||eid|| ' ' ||fname|| ' ' ||lname|| ' has a salary of: ' ||sal|| '');
    END LOOP;
    close cemp;
END;

--Question 7
SET SERVEROUTPUT ON
DECLARE
    CURSOR cemp IS
        SELECT SALARY, COMMISSION_PCT
        FROM employees
        WHERE DEPARTMENT_ID = 80 or DEPARTMENT_ID = 30;
    bonus EMPLOYEES.SALARY%TYPE := 0;
BEGIN
    for indx in cemp LOOP
        CASE
            WHEN indx.commission_pct >= .2 THEN
                CASE
                    WHEN indx.salary >= 10000 THEN bonus := bonus + 500;
                    WHEN indx.salary < 10000 and indx.salary >= 8000 then bonus := bonus + 600;
                    WHEN indx.salary >= 7000 and indx.salary < 8000 then bonus := bonus + 700;
                    WHEN indx.salary < 7000 then bonus := bonus + 800;
                END CASE;
            WHEN indx.commission_pct is NULL THEN
                CASE
                    WHEN indx.salary >= 10000 THEN bonus := bonus + 300;
                    WHEN indx.salary < 10000 and indx.salary >= 3000 then bonus := bonus + 400;
                    WHEN indx.salary >= 2600 and indx.salary < 3000 then bonus := bonus + 500;
                    WHEN indx.salary < 2600 then bonus := bonus + 600;
                END CASE;
            WHEN indx.commission_pct < .2 THEN
                 CASE
                    WHEN indx.salary >= 10000 THEN bonus := bonus + 400;
                    WHEN indx.salary < 10000 and indx.salary >= 8000 then bonus := bonus + 500;
                    WHEN indx.salary >= 7000 and indx.salary < 8000 then bonus := bonus + 600;
                    WHEN indx.salary < 7000 then bonus := bonus + 700;
                END CASE;
        END CASE;
    END LOOP;
    DBMS_OUTPUT.put_line ('The total bonus to be payed is: ' ||bonus|| '');
END;

--QUestion 8
SET SERVEROUTPUT ON
DECLARE
    CURSOR cemp(dept_no number) IS
        SELECT EMPLOYEE_ID, FIRST_NAME, LAST_NAME
        FROM employees
        WHERE DEPARTMENT_ID = dept_no;
    cur_emp cemp%ROWTYPE;
BEGIN
    OPEN cemp(20);
    LOOP
        FETCH cemp into cur_emp;
        EXIT WHEN cemp%notfound; 
        DBMS_OUTPUT.put_line ('#' ||cur_emp.EMPLOYEE_ID|| ' ' ||cur_emp.FIRST_NAME|| ' ' ||cur_emp.LAST_NAME||'');
    END LOOP;
    close cemp;
    OPEN cemp(90);
    LOOP
        FETCH cemp into cur_emp;
        EXIT WHEN cemp%notfound; 
        DBMS_OUTPUT.put_line ('#' ||cur_emp.EMPLOYEE_ID|| ' ' ||cur_emp.FIRST_NAME|| ' ' ||cur_emp.LAST_NAME||'');
    END LOOP;
    close cemp;
END;

--QUESTION 9
SET SERVEROUTPUT ON
DECLARE
    CURSOR cemp IS
        SELECT EMPLOYEE_ID, LAST_NAME, SALARY, COMMISSION_PCT
        FROM employees 
        FOR UPDATE OF SALARY;
    eid EMPLOYEES.EMPLOYEE_ID%TYPE;
    lname EMPLOYEES.LAST_NAME%TYPE;
    old_sal EMPLOYEES.SALARY%TYPE;
    new_sal EMPLOYEES.SALARY%TYPE;
    comm employees.commission_pct%TYPE;
BEGIN
    OPEN cemp;
    LOOP
        FETCH cemp into eid, lname, old_sal, comm;
        EXIT WHEN cemp%notfound; 
        if old_sal < 2499 and comm is null then
            new_sal := old_sal + (old_sal*.05);
            UPDATE EMPLOYEES
                SET SALARY = new_sal
                WHERE current of cemp;
            DBMS_OUTPUT.put_line ('#' ||eid|| ' ' ||lname|| ' salary was raised from ' ||old_sal|| ' to ' ||new_sal|| '');
        end if;
    END LOOP;
    close cemp;
END;