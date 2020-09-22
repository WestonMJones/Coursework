/*
Weston Jones 
CS 355 Database Systems 
Section 602 
Assignment 6
6/1/20
*/

SET SERVEROUTPUT ON
DECLARE
    h NUMBER(2,0);
    m NUMBER(2,0);
    f NUMBER(2,0);
    q NUMBER(2,0);
        
    TYPE StudentInfo is TABLE OF STUDENT%ROWTYPE;
    Students StudentInfo := StudentInfo();

    CURSOR cur IS 
        SELECT SID, SNAME, SHW, SMID, SFIN, SQUIZ
        FROM STUDENT
        ORDER BY SID;
    cur_student cur%ROWTYPE;
    counter NUMBER(3):=0;
    
    score NUMBER(3,1);
    scores NUMBER(8,2) :=0;
    
BEGIN

    SELECT HWWEIGHT, MIDWEIGHT, FINWEIGHT, QUIZWEIGHT 
    INTO h,m,f,q
    FROM WEIGHTS;
    
    DBMS_OUTPUT.PUT_LINE('Weights: '||h||', '||m||', '||f||', '||q||'');
    DBMS_OUTPUT.PUT_LINE('');
    
    OPEN cur;
    LOOP
        FETCH cur into cur_student;
        EXIT WHEN cur%notfound;
        counter := counter + 1;
        Students.extend();
        Students(counter) := cur_student;
        
        score := (h/100)*Students(counter).SHW;
        score := score + (m/100)*Students(counter).SMID;
        score := score + (f/100)*Students(counter).SFIN;
        score := score + (q/100)*Students(counter).SQUIZ;      
        
        IF score>=70 THEN
            DBMS_OUTPUT.PUT_LINE(Students(counter).SID || ' ' || Students(counter).SNAME || ' '||to_char(score,'99.9'));
        ELSE
            DBMS_OUTPUT.PUT_LINE(Students(counter).SID || ' ' || Students(counter).SNAME || ' '||to_char(score,'99.9') || ' *');
        END IF;

        scores := scores + score;
        
    END LOOP;
    
    CLOSE cur;
    
    scores := scores / counter;
    DBMS_OUTPUT.PUT_LINE('');
    DBMS_OUTPUT.PUT_LINE('Average overall score: '||scores);
  
END;