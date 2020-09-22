/*
	Clubs2020.sql
	CSC 355 Spring 2020
	Eric J. Schwabe

	For use in assignment only -- do not copy, post, or distribute
*/

DROP TABLE REGISTRATION;
DROP TABLE CLASS;
DROP TABLE MEMBER;
DROP TABLE CLUB;

CREATE TABLE CLUB
(
	CID 		CHAR(3)		PRIMARY KEY,
	City		VARCHAR(20),
	State		CHAR(2)
);
CREATE TABLE MEMBER
(
	MID		CHAR(8) 	PRIMARY KEY,
	ClubID		CHAR(3)		REFERENCES CLUB(CID),
	Name		VARCHAR(20),
	Age		NUMBER(3) 	CHECK (Age >= 0),
	Gender		CHAR(1),
	MonthlyFee	NUMBER(5,2) 	CHECK (MonthlyFee >= 0),
	StartDate	DATE
);
CREATE TABLE CLASS
(
	CLID		CHAR(5) 	PRIMARY KEY,
	Title		VARCHAR(20),
	ClubID		CHAR(3) 	REFERENCES CLUB(CID),
	ClassDate	DATE,
	Cost		NUMBER(4,2) 	CHECK (Cost >= 0)
);
CREATE TABLE REGISTRATION
(
	MemberID	CHAR(8) 	REFERENCES MEMBER (MID),
	ClassID		CHAR(5) 	REFERENCES CLASS(CLID),
	CONSTRAINT PK_REGISTRATION PRIMARY KEY(MemberID, ClassID)
);

insert into club values ('001', 'Northbrook', 'IL');
insert into club values ('002', 'Rockford', 'IL');
insert into club values ('003', 'Rockford', 'IL');
insert into club values ('004', 'Kenosha', 'WI');
insert into club values ('005', 'Kenosha', 'WI');
insert into club values ('006', 'Janesville', 'WI');
insert into club values ('007', 'Rockford', 'IN');
insert into club values ('008', 'Kenosha', 'MN');
insert into club values ('009', 'Kankakee', 'IL');

insert into member values ('S2345678', '001', 'Stone', 40, 'F', 63.00, DATE '2019-01-01');
insert into member values ('G3456789', '002', 'Gonzalez', 38, 'M', 30.00, DATE '2019-07-12');
insert into member values ('G4567890', '002', 'Gonzalez', 36, 'F', 30.00, DATE '2019-07-12');
insert into member values ('G5678901', '002', 'Gonzalez', 15, 'F', 20.00, DATE '2019-07-12');
insert into member values ('Y6789012', '004', 'Yao', 28, 'F', 40.00, DATE '2020-01-01');
insert into member values ('Y6789013', '004', 'Yao', 29, 'M', 40.00, DATE '2020-01-01');
insert into member values ('Y7890123', '004', 'Ahmed', 36, 'M', 45.00, DATE '2020-01-01');
insert into member values ('S8901234', '003', 'Smith', 62, 'F', 80.00, DATE '2019-09-20');
insert into member values ('M9012345', '005', 'Malik', 50, 'M', 55.00, DATE '2018-12-25');
insert into member values ('N0123456', '007', 'Costales', 43, 'M', 45.00, DATE '2019-09-01');
insert into member values ('P1234567', '007', 'Peterson', 30, 'F', 40.00, DATE '2018-12-31');
insert into member values ('L4567890', '008', 'Leblanc', 41, 'M', 60.00, DATE '2020-01-01');

insert into class values ('Yo011', 'Yoga', '001', DATE '2020-04-04', 10.00);
insert into class values ('Yo123', 'Yoga', '001', DATE '2020-04-15', 10.00);
insert into class values ('Ca001', 'Cardio', '002', DATE '2020-04-08', 0.00);
insert into class values ('Ca002', 'Cardio', '002', DATE '2020-04-10', 5.00);
insert into class values ('Zu114', 'Zumba', '004', DATE '2020-03-01', 5.00);
insert into class values ('Zu116', 'Zumba', '005', DATE '2020-03-01', 7.00);
insert into class values ('In019', 'Intervals', '002', DATE '2020-03-15', 0.00);
insert into class values ('In029', 'Intervals', '003', DATE '2020-04-15', 0.00);
insert into class values ('St999', 'Strength', '007', DATE '2020-05-01', 5.00);

insert into registration values ('S2345678', 'Yo011');
insert into registration values ('S2345678', 'Yo123');
insert into registration values ('G4567890', 'Ca001');
insert into registration values ('G4567890', 'Ca002');
insert into registration values ('Y6789012', 'Zu114');
insert into registration values ('Y6789012', 'Yo011');
insert into registration values ('Y6789013', 'Yo011');
insert into registration values ('Y6789013', 'Ca001');
insert into registration values ('S8901234', 'Yo011');
insert into registration values ('S8901234', 'Zu114');
insert into registration values ('S8901234', 'Zu116');
insert into registration values ('N0123456', 'Ca001');
insert into registration values ('N0123456', 'Ca002');
insert into registration values ('N0123456', 'Zu114');
insert into registration values ('N0123456', 'Zu116');

select * from club;
select * from member;
select * from class;
select * from registration;
	
	