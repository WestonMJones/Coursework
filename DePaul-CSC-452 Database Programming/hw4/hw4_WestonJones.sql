--Weston Jones -- Homework 4 -- CSC 352 Database Programming -- Section 901

--Question 1
SET SERVEROUTPUT ON
DECLARE
    TYPE tp1 is TABLE of CHAR(1) INDEX BY BINARY_INTEGER;
    assoc_arr tp1;
BEGIN
    assoc_arr(1) := 'A';
    assoc_arr(2) := 'B';
    assoc_arr(3) := 'C';
    assoc_arr(4) := 'D';
    assoc_arr(5) := 'E';
    assoc_arr(6) := 'F';
    
    FOR i IN 1..6 LOOP
        DBMS_OUTPUT.PUT_LINE(assoc_arr(i));
    END LOOP;
END;

--Question 2
DECLARE
	TYPE emp_array IS TABLE OF Employees.SALARY%TYPE INDEX BY Employees.LAST_NAME%TYPE;
    Lname_salary emp_array;
    indx EMPLOYEES.LAST_NAME%TYPE;
    counter NUMBER(2);

    CURSOR cemp IS 
        SELECT LAST_NAME, SALARY
        FROM Employees 
        WHERE DEPARTMENT_ID = 50;
        
    emp_rec cemp%ROWTYPE;

BEGIN
    OPEN cemp;
    FOR counter in 1 .. 12 LOOP
        FETCH cemp into emp_rec;
        Lname_salary(emp_rec.LAST_NAME) := emp_rec.SALARY;
        DBMS_OUTPUT.PUT_LINE('Name: ' || emp_rec.LAST_NAME || ' || Salary: ' || TO_CHAR(Lname_salary(emp_rec.LAST_NAME)));
    END LOOP;
    CLOSE cemp;
    
    DBMS_OUTPUT.PUT_LINE('');
    DBMS_OUTPUT.PUT_LINE('Second Loop');
    DBMS_OUTPUT.PUT_LINE('');

    indx := Lname_salary.FIRST;
    WHILE indx IS NOT NULL LOOP
        DBMS_OUTPUT.PUT_LINE('Name: ' || indx || ' || Salary: ' || TO_CHAR(Lname_salary(indx)));
        indx := Lname_salary.NEXT(indx);
    END LOOP;
END;

--Question 3
DECLARE 
    TYPE Lname is VARRAY(15) OF EMPLOYEES.LAST_NAME%TYPE;
    v1 Lname := Lname();

    indx EMPLOYEES.LAST_NAME%TYPE;
    counter NUMBER(2);

    CURSOR cemp IS 
        SELECT LAST_NAME
        FROM Employees 
        WHERE DEPARTMENT_ID = 50
        ORDER BY EMPLOYEE_ID;
        
    emp_rec cemp%ROWTYPE;
BEGIN
    OPEN cemp;
    FOR counter in 1 .. 12 LOOP
        v1.EXTEND();
        FETCH cemp into emp_rec;
        v1(counter) := emp_rec.LAST_NAME;
        DBMS_OUTPUT.PUT_LINE(TO_CHAR(counter) || ': ' || v1(counter));
    END LOOP;
    CLOSE cemp;

    DBMS_OUTPUT.PUT_LINE('The limit of v1 is: ' || v1.LIMIT);
    DBMS_OUTPUT.PUT_LINE('The last value of v1 is: ' || v1(v1.LAST));
    
    v1.EXTEND(2);
    v1(13) := 'Washington';
    v1(14) := 'Lincoln';
    
    DBMS_OUTPUT.PUT_LINE('Added Washington and Lincoln');
    DBMS_OUTPUT.PUT_LINE('The limit of v1 is still: ' || v1.LIMIT);
    DBMS_OUTPUT.PUT_LINE('The new last value of v1 is: ' || v1(v1.last()));

    v1.DELETE;
    
    DBMS_OUTPUT.PUT_LINE('Deleted all values');
    DBMS_OUTPUT.PUT_LINE('The limit of v1 is still: ' || v1.LIMIT);
    DBMS_OUTPUT.PUT_LINE('The new last value of v1 is: NULL'); --Using v1(v1.last()) as above to retrieve the value of last the index results in an error

END;

--Question 4
DECLARE 
    TYPE Lname IS TABLE OF EMPLOYEES.LAST_NAME%TYPE;
    v1 Lname := Lname();

    indx EMPLOYEES.LAST_NAME%TYPE;
    counter NUMBER(2);

    CURSOR cemp IS 
        SELECT LAST_NAME
        FROM Employees 
        WHERE DEPARTMENT_ID = 50
        ORDER BY EMPLOYEE_ID;
        
    emp_rec cemp%ROWTYPE;
BEGIN
    OPEN cemp;
    FOR counter in 1 .. 12 LOOP
        v1.extend();
        FETCH cemp into emp_rec;
        v1(counter) := emp_rec.LAST_NAME;
        DBMS_OUTPUT.PUT_LINE(TO_CHAR(counter) || ': ' || v1(counter));
    END LOOP;
    CLOSE cemp;

    DBMS_OUTPUT.PUT_LINE('The limit of v1 is: ' || v1.LIMIT);
    DBMS_OUTPUT.PUT_LINE('The last value of v1 is: ' || v1(v1.LAST));
    
    v1.EXTEND(2);
    v1(13) := 'Washington';
    v1(14) := 'Lincoln';

    DBMS_OUTPUT.PUT_LINE('Added Washington and Lincoln');

    For indx in v1.First .. v1.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(v1(indx));
    END LOOP;
    
    DBMS_OUTPUT.PUT_LINE('The size of v1 is: ' || v1.COUNT);
    DBMS_OUTPUT.PUT_LINE('The new last value of v1 is: ' || v1(v1.last()));
    
    v1.DELETE(5,7);
    
    DBMS_OUTPUT.PUT_LINE('Deleted elements 5 thru 7.');
    DBMS_OUTPUT.PUT_LINE('The new size of v1 is: ' || v1.COUNT);
    DBMS_OUTPUT.PUT_LINE('The new last value of v1 is: ' || v1(v1.last()));
    DBMS_OUTPUT.PUT_LINE('Printing table again!');
    
    For indx in v1.First .. v1.LAST LOOP
        if v1.EXISTS(indx) THEN
            DBMS_OUTPUT.PUT_LINE(v1(indx));
        end if;
    END LOOP;

END;

--Question 5
DECLARE
	TYPE Lname IS TABLE OF Employees.LAST_NAME%TYPE INDEX BY PLS_INTEGER;
    v1 Lname;
    indx EMPLOYEES.LAST_NAME%TYPE;
    counter NUMBER(2);

    CURSOR cemp IS 
        SELECT LAST_NAME
        FROM Employees 
        WHERE DEPARTMENT_ID = 50
        ORDER BY EMPLOYEES.EMPLOYEE_ID;
        
    emp_rec cemp%ROWTYPE;

BEGIN
    OPEN cemp;
    FOR counter in 1 .. 12 LOOP
        FETCH cemp into emp_rec;
        v1(counter) := emp_rec.LAST_NAME;
    END LOOP;
    CLOSE cemp;
    
    FOR counter in 1 .. 12 LOOP
        DBMS_OUTPUT.PUT_LINE(counter || ': ' || v1(counter));
    END LOOP;
END;

--Question 6
DECLARE
    TYPE NT1 IS TABLE OF INTEGER;
    X1 NT1 := NT1(4,5,6);
    TYPE nNT1 IS TABLE OF NT1;
    nY1 nNT1 := nNT1(X1, X1, X1);
BEGIN
    DBMS_OUTPUT.PUT_LINE('nY1 (2) (3) = ' || nY1(2)(3));
    
    nY1.extend();
    nY1(4) := NT1(11, 22, 33, 44, 55, 66);
    
    DBMS_OUTPUT.PUT_LINE('nY1 (4) (3) = ' || nY1(4)(3));
END;
