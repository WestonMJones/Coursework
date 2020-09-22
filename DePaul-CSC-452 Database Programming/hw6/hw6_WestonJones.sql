--Weston Jones -- Homework 6 -- CSC 352 Database Programming -- Section 901

--Question 1
SET SERVEROUTPUT ON
DECLARE

    FUNCTION covertTemp(celsius IN NUMBER) RETURN NUMBER IS fahrenheit number(5,2); 
    BEGIN 
        fahrenheit := (celsius * 1.8) + 32;
        return fahrenheit;
    END; 

BEGIN

    DBMS_OUTPUT.PUT_LINE('21 degrees Celsuis coverted to Fahrenheit is: '||covertTemp(21));

END;

--Question 2
SET SERVEROUTPUT ON
DECLARE

    FUNCTION hwf2(emp_id IN NUMBER) RETURN NUMBER AS 
        bonus number(3);
        emp_sal EMPLOYEES.SALARY%TYPE;
        emp_com EMPLOYEES.COMMISSION_PCT%TYPE;
    BEGIN 
        SELECT SALARY, COMMISSION_PCT INTO emp_sal, emp_com
        FROM EMPLOYEES
        WHERE EMPLOYEE_ID=emp_id;
        
        if (emp_sal*(1+NVL(emp_com,0))>10000) THEN
            bonus := 100;
        else
            bonus := 500;
        end if;
        
        return bonus;
    END; 

BEGIN

    DBMS_OUTPUT.PUT_LINE('Bonus for employee #170 is: '||hwf2(170));
    DBMS_OUTPUT.PUT_LINE('Bonus for employee #160 is: '||hwf2(160));


END;

--Question 3A
SET SERVEROUTPUT ON
DECLARE

    CURSOR depts is SELECT UNIQUE DEPARTMENT_ID
    FROM EMPLOYEES
    ORDER BY DEPARTMENT_ID;

    TYPE dept_mgr IS RECORD(dept_id EMPLOYEES.EMPLOYEE_ID%TYPE,
                            mgr_id EMPLOYEES.EMPLOYEE_ID%TYPE,
                            lname  VARCHAR2 (20),
                            num_emps NUMBER (5));
                            
    dept_info dept_mgr;

    FUNCTION F6(dept_id IN NUMBER) RETURN dept_mgr AS 
        info dept_mgr;
    BEGIN 
            
        SELECT DEPARTMENTS.DEPARTMENT_ID, DEPARTMENTS.MANAGER_ID, COUNT(EMPLOYEES.EMPLOYEE_ID) INTO
            info.dept_id, info.mgr_id, info.num_emps
        FROM DEPARTMENTS
        INNER JOIN EMPLOYEES ON DEPARTMENTS.DEPARTMENT_ID = EMPLOYEES.DEPARTMENT_ID
        WHERE DEPARTMENTS.DEPARTMENT_ID=dept_id
        GROUP BY DEPARTMENTS.DEPARTMENT_ID, DEPARTMENTS.MANAGER_ID;
        
        SELECT LAST_NAME INTO info.lname
        FROM EMPLOYEES
        WHERE EMPLOYEE_ID = info.mgr_id;
        
        return info;
    END; 
    

BEGIN
    
    for indx in depts LOOP
        
        dept_info := F6(indx.DEPARTMENT_ID);
        dbms_output.put_line('Info for department: '||dept_info.dept_id);
        dbms_output.put_line('Manager id: '||dept_info.mgr_id);
        dbms_output.put_line('Last name of manager: '||dept_info.lname);
        dbms_output.put_line('Number of employees: '||dept_info.num_emps);
        dbms_output.put_line('');

    END LOOP;


END;

--Question 3B
SET SERVEROUTPUT ON
DECLARE

    CURSOR depts is SELECT DEPARTMENT_NAME, DEPARTMENT_ID
    FROM DEPARTMENTS
    WHERE MANAGER_ID IS NOT NULL
    ORDER BY DEPARTMENT_ID;

    TYPE dept_mgr IS RECORD(dept_id EMPLOYEES.EMPLOYEE_ID%TYPE,
                            mgr_id EMPLOYEES.EMPLOYEE_ID%TYPE,
                            lname  VARCHAR2 (20),
                            num_emps NUMBER (5));
                            
    dept_info dept_mgr;

    FUNCTION F6(dept_name DEPARTMENTS.DEPARTMENT_NAME%TYPE) RETURN dept_mgr IS 
        info dept_mgr;
        dept_id DEPARTMENTS.DEPARTMENT_ID%TYPE;
    BEGIN 
        SELECT DEPARTMENT_ID into dept_id
        FROM DEPARTMENTS
        WHERE DEPARTMENT_NAME=dept_name;
            
        SELECT DEPARTMENTS.DEPARTMENT_ID, DEPARTMENTS.MANAGER_ID, COUNT(EMPLOYEES.EMPLOYEE_ID) INTO
            info.dept_id, info.mgr_id, info.num_emps
        FROM DEPARTMENTS
        INNER JOIN EMPLOYEES ON DEPARTMENTS.DEPARTMENT_ID = EMPLOYEES.DEPARTMENT_ID
        WHERE DEPARTMENTS.DEPARTMENT_ID=dept_id
        GROUP BY DEPARTMENTS.DEPARTMENT_ID, DEPARTMENTS.MANAGER_ID;
        
        SELECT LAST_NAME INTO info.lname
        FROM EMPLOYEES
        WHERE EMPLOYEE_ID = info.mgr_id;
        
        return info;
    END; 
    
    FUNCTION F6(dept_id IN NUMBER) RETURN dept_mgr AS 
        info dept_mgr;
    BEGIN 
            
        SELECT DEPARTMENTS.DEPARTMENT_ID, DEPARTMENTS.MANAGER_ID, COUNT(EMPLOYEES.EMPLOYEE_ID) INTO
            info.dept_id, info.mgr_id, info.num_emps
        FROM DEPARTMENTS
        INNER JOIN EMPLOYEES ON DEPARTMENTS.DEPARTMENT_ID = EMPLOYEES.DEPARTMENT_ID
        WHERE DEPARTMENTS.DEPARTMENT_ID=dept_id
        GROUP BY DEPARTMENTS.DEPARTMENT_ID, DEPARTMENTS.MANAGER_ID;
        
        SELECT LAST_NAME INTO info.lname
        FROM EMPLOYEES
        WHERE EMPLOYEE_ID = info.mgr_id;
        
        return info;
    END; 
    
BEGIN
    
    for indx in depts LOOP
        
        dept_info := F6(indx.DEPARTMENT_ID);
        dbms_output.put_line('Info for department: '||dept_info.dept_id);
        dbms_output.put_line('Manager id: '||dept_info.mgr_id);
        dbms_output.put_line('Last name of manager: '||dept_info.lname);
        dbms_output.put_line('Number of employees: '||dept_info.num_emps);
        dbms_output.put_line('');

    END LOOP;


END;

--Question 4
DROP TABLE salary_log;
CREATE TABLE salary_log (
    EMPLOYEE_ID NUMBER(6,0),
    OLD_SAL NUMBER(8,2),
    NEW_SAL NUMBER(8,2),
    BYWHO VARCHAR(15),
    DATEOF DATE
);

CREATE OR REPLACE TRIGGER salary_change AFTER UPDATE OF SALARY ON EMPLOYEES FOR EACH ROW
BEGIN
    INSERT INTO salary_log VALUES(:NEW.EMPLOYEE_ID,:OLD.SALARY,:NEW.SALARY,User,Sysdate);
END;

UPDATE employees set salary = salary +200 where employee_id = 105;
SELECT * FROM salary_log;

/* 
EMPLOYEE_ID    OLD_SAL    NEW_SAL BYWHO           DATEOF   
----------- ---------- ---------- --------------- ---------
        105       4800       5000 WJONES17        04-JUN-20

 */


--Question 5
DROP TABLE  access_dept_log;
CREATE TABLE access_dept_log (
    BYWHO VARCHAR(15),
    DATEOF DATE,
    DEPARTMENT_ID NUMBER(4,0),
    ACTION VARCHAR(20)
);

DROP TRIGGER access_dept_log;
CREATE OR REPLACE TRIGGER access_dept_log AFTER DELETE OR INSERT OR UPDATE OF MANAGER_ID ON DEPARTMENTS
FOR EACH ROW
BEGIN
    IF UPDATING('MANAGER_ID') THEN
        INSERT INTO access_dept_log VALUES(User, Sysdate, :OLD.DEPARTMENT_ID, 'Change Manager');
    ELSIF INSERTING THEN
        INSERT INTO access_dept_log VALUES(User, Sysdate, :NEW.DEPARTMENT_ID, 'New Department');
    ELSIF DELETING THEN
        INSERT INTO access_dept_log VALUES(User, Sysdate, :OLD.DEPARTMENT_ID, 'Deleted Department');
    END IF;
END;

Select * from departments;
SELECT * from access_dept_log ;
INSERT INTO departments VALUES (999, 'FAKE', 161, 1700);
UPDATE departments set manager_id = 203 WHERE department_id = 70;
DELETE departments where department_id = '999';
SELECT * from access_dept_log ;
rollback;

/* 
DEPARTMENT_ID DEPARTMENT_NAME                MANAGER_ID LOCATION_ID
------------- ------------------------------ ---------- -----------
           10 Administration                        200        1700
           20 Marketing                             201        1800
           30 Purchasing                            114        1700
           40 Human Resources                       203        2400
           50 Shipping                              121        1500
           60 IT                                    103        1400
           70 Public Relations                      204        2700
           80 Sales                                 145        2500
           90 Executive                             100        1700
          100 Finance                               108        1700
          110 Accounting                            205        1700

DEPARTMENT_ID DEPARTMENT_NAME                MANAGER_ID LOCATION_ID
------------- ------------------------------ ---------- -----------
          120 Treasury                                         1700
          130 Corporate Tax                                    1700
          140 Control And Credit                               1700
          150 Shareholder Services                             1700
          160 Benefits                                         1700
          170 Manufacturing                                    1700
          180 Construction                                     1700
          190 Contracting                                      1700
          200 Operations                                       1700
          210 IT Support                                       1700
          220 NOC                                              1700

DEPARTMENT_ID DEPARTMENT_NAME                MANAGER_ID LOCATION_ID
------------- ------------------------------ ---------- -----------
          230 IT Helpdesk                                      1700
          240 Government Sales                                 1700
          250 Retail Sales                                     1700
          260 Recruiting                                       1700
          270 Payroll                                          1700

27 rows selected. 

no rows selected

1 row inserted.


1 row updated.


1 row deleted.


BYWHO           DATEOF    DEPARTMENT_ID ACTION              
--------------- --------- ------------- --------------------
WJONES17        04-JUN-20           999 New Department      
WJONES17        04-JUN-20            70 Change Manager      
WJONES17        04-JUN-20           999 Deleted Department  


Rollback complete.
 */