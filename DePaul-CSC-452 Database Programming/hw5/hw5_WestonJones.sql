--Weston Jones -- Homework 5 -- CSC 352 Database Programming -- Section 901

--Question 1
SET SERVEROUTPUT ON
DECLARE
    TYPE emp_phone IS RECORD
    (
        last_name varchar(20),
        first_name varchar(20),
        phone varchar(20)
    );
    cur_emp emp_phone;
BEGIN
    SELECT LAST_NAME, FIRST_NAME, PHONE_NUMBER
    INTO cur_emp
    FROM EMPLOYEES
    WHERE EMPLOYEE_ID = 160;

    DBMS_OUTPUT.PUT_LINE('Last Name: ' || cur_emp.last_name || ' First Name: ' || cur_emp.first_name || ' Phone: ' || cur_emp.phone || '');
END;

--Question 2
SET SERVEROUTPUT ON
DECLARE
    TYPE phone_num IS RECORD
    (
        Last_name VARCHAR2(20),
        First_name VARCHAR2(20),
        Area_code VARCHAR2(3),
        Prefix VARCHAR2(3),
        PhoneNumber VARCHAR2(4)
    );
      
    rec phone_num;
    
    CURSOR emps is SELECT last_name, first_name, phone_number
    FROM EMPLOYEES
    WHERE DEPARTMENT_ID=20 OR DEPARTMENT_ID=80 OR DEPARTMENT_ID=90; 
BEGIN
    for indx in emps LOOP
        
        if indx.PHONE_NUMBER NOT LIKE '011.%' then       
            rec.Last_name := indx.LAST_NAME;
            rec.First_name := indx.FIRST_NAME;
            rec.Area_code := SUBSTR(indx.Phone_Number, 1, 3);
            rec.Prefix := SUBSTR(indx.Phone_Number, 5,3);
            rec.PhoneNumber := SUBSTR(indx.Phone_Number, 9,4);
            
            insert into PHONEBOOK VALUES rec;
        end if;
        
    END LOOP;
    
END;

/* 
Result of SELECT * FROM PHONEBOOK
LAST_NAME            FIRST_NAME           ARE PRE NUM 
-------------------- -------------------- --- --- ----
Kochhar              Neena                515 123 4568
De Haan              Lex                  515 123 4569
Hartstein            Michael              515 123 5555
Fay                  Pat                  603 123 6666
King                 Steven               515 123 4567 
*/

--Question 3
SET SERVEROUTPUT ON
DECLARE
    TYPE phone_num IS RECORD
    (
        Last_name VARCHAR2(20),
        First_name VARCHAR2(20),
        Area_code VARCHAR2(3),
        Prefix VARCHAR2(3),
        PhoneNumber VARCHAR2(4)
    );
      
    rec phone_num;
    
    CURSOR emps is SELECT last_name, first_name, phone_number
    FROM EMPLOYEES
    WHERE DEPARTMENT_ID=20 OR DEPARTMENT_ID=80 OR DEPARTMENT_ID=90; 
    
    TYPE NTphonebook IS TABLE OF phone_num;
    v1 NTphonebook := NTphonebook();
    
BEGIN
    for indx in emps LOOP
        
        if indx.PHONE_NUMBER NOT LIKE '011.%' then 
            rec.Last_name := indx.LAST_NAME;
            rec.First_name := indx.FIRST_NAME;
            rec.Area_code := SUBSTR(indx.Phone_Number, 1, 3);
            rec.Prefix := SUBSTR(indx.Phone_Number, 5,3);
            rec.PhoneNumber := SUBSTR(indx.Phone_Number, 9,4);
            
            v1.extend();
            
            v1(v1.last()):= rec;
        end if;
        
    END LOOP;
    
    For indx in v1.First .. v1.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(
            v1(indx).Last_name || ' ' || 
            v1(indx).First_name || ' ' || 
            v1(indx).Area_code || ' ' || 
            v1(indx).Prefix || ' ' || 
            v1(indx).PhoneNumber
        );
    END LOOP;
    
END;

--Question 4
SET SERVEROUTPUT ON
DECLARE
    TYPE  empcurtyp IS REF CURSOR RETURN EMPLOYEES%ROWTYPE;
    emps  empcurtyp;
    
    cemp EMPLOYEES%ROWTYPE;
BEGIN
    OPEN emps FOR
    SELECT * FROM employees
    WHERE department_id = 100
    ORDER BY last_name;
    
    LOOP
        FETCH emps INTO cemp;
        EXIT WHEN emps%NOTFOUND;
        dbms_output.put_line(cemp.LAST_NAME || ' ' || cemp.FIRST_NAME);
    END LOOP;
    CLOSE emps;
    
    dbms_output.put_line('');
    dbms_output.put_line('----------------------');
    dbms_output.put_line('');

    OPEN emps FOR
    SELECT * FROM employees
    WHERE department_id = 30
    ORDER BY last_name;
    
    LOOP
        FETCH emps INTO cemp;
        EXIT WHEN emps%NOTFOUND;
        dbms_output.put_line(cemp.LAST_NAME || ' ' || cemp.FIRST_NAME);
    END LOOP;
    CLOSE emps;
        
END;

--Question 5
SET SERVEROUTPUT ON
DECLARE
    
    c_nemps PLS_INTEGER := 2;
    c_sal PLS_INTEGER := 3;
    
    PROCEDURE hw5(dept IN PLS_INTEGER, nemps OUT PLS_INTEGER, sal OUT PLS_INTEGER) IS
    BEGIN 
        SELECT COUNT(EMPLOYEE_ID), AVG(SALARY) INTO nemps, sal
        FROM EMPLOYEES
        WHERE DEPARTMENT_ID=dept;
    END;

    
BEGIN

    hw5(100,c_nemps,c_sal);
    dbms_output.put_line('Number of Employees: ' || c_nemps);
    dbms_output.put_line('Average Salary: ' || c_sal);

END;

--Question 6
SET SERVEROUTPUT ON
DECLARE
    
    CURSOR depts is SELECT UNIQUE DEPARTMENT_ID
    FROM EMPLOYEES
    ORDER BY DEPARTMENT_ID;
    
    c_nemps PLS_INTEGER := 2;
    c_sal PLS_INTEGER := 3;
    
    PROCEDURE hw5(dept IN PLS_INTEGER, nemps OUT PLS_INTEGER, sal OUT PLS_INTEGER) IS
    BEGIN 
        SELECT COUNT(EMPLOYEE_ID), AVG(SALARY) INTO nemps, sal
        FROM EMPLOYEES
        WHERE DEPARTMENT_ID=dept;
    END;

    
BEGIN

    for indx in depts LOOP
        
        hw5(indx.DEPARTMENT_ID,c_nemps,c_sal);
        dbms_output.put_line('Running procedure on department: ' || indx.DEPARTMENT_ID);
        dbms_output.put_line('Number of Employees: ' || c_nemps);
        dbms_output.put_line('Average Salary: ' || c_sal);
        dbms_output.put_line('');

        
    END LOOP;


END;