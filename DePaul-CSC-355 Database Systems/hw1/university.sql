-- university.sql
-- CSC 355 Spring 2020

-- (For study and review purposes only. Copying of any part of this document 
-- into a submitted assignment constitutes plagiarism.)

-- create tables
drop table MEMBERSHIP;
drop table ENROLLMENT;
drop table STUDENTGROUP;
drop table COURSE;
drop table STUDENT;
create table STUDENT (
  LastName      varchar(40) not null,
  FirstName     varchar(40),
  SID           number(5),
  SSN           number(9),
  Career      	varchar(4),
  Program       varchar(10),
  City          varchar(40),
  Started       number(4),
  primary key (SID),
  unique(SSN)
);
create table COURSE (
  CID   number(4),
  CourseName    varchar(40),
  Department    varchar(4),
  CourseNumber  char(3),
  primary key (CID)
);
create table STUDENTGROUP (
  GID     	number(5),
  Name  	varchar(40),
  PresidentID   number(5),
  Founded       number(4),
  primary key (GID),
  unique (Name),
  foreign key (PresidentID) references STUDENT(SID)
);
create table ENROLLMENT (
  StudentID     number(5),
  CourseID      number(4),
  Quarter       varchar(6),
  Year          number(4),
  primary key (StudentID, CourseID),
  foreign key (StudentID) references STUDENT(SID),
  foreign key (CourseID) references COURSE(CID)
); 
create table MEMBERSHIP (
  StudentID     number(5),
  GroupID     	number(5),
  Joined        number(4),
  primary key (StudentID, GroupID),
  foreign key (StudentID) references STUDENT(SID),
  foreign key (GroupID) references STUDENTGROUP(GID)
);
-- populate tables
insert into STUDENT values ('Brennigan', 'Marcus', 90421, 987654321, 'UGRD', 'COMP-GAM', 'Evanston', 2010);
insert into STUDENT values ('Patel', 'Deepa', 14662, null, 'GRAD', 'COMP-SCI', 'Evanston', 2013);
insert into STUDENT values ('Snowdon', 'Jonathan', 88871, 123123123, 'GRAD', 'INFO-SYS', 'Springfield', 2009);
insert into STUDENT values ('Starck', 'Jason', 19992, 789789789, 'UGRD', 'INFO-SYS', 'Springfield', 2009);
insert into STUDENT values ('Johnson', 'Peter', 32105, 123456789, 'UGRD', 'COMP-SCI', 'Chicago', 2010);
insert into STUDENT values ('Winter', 'Abigail', 11035, 111111111, 'GRAD', 'PHD', 'Chicago', 2009);
insert into STUDENT values ('Patel', 'Prakash', 75234, null, 'UGRD', 'COMP-SCI', 'Chicago', 2011);
insert into STUDENT values ('Snowdon', 'Jennifer', 93321, 321321321, 'GRAD', 'COMP-SCI', 'Springfield', 2012);
insert into STUDENT values ('Degroff', 'Jarvis', 14998, 113311331, 'GRAD', 'COMP-GAM', 'Evanston', 2012);
insert into STUDENT values ('Kubik', 'Dwayne', 57923, 979797979, 'UGRD', 'COMP-GAM', 'Springfield', 2013);
insert into STUDENT values ('Skelly', 'Trinity', 58992, 555222555, 'GRAD', 'PHD', 'Springfield', 2012);
insert into STUDENT values ('Krol', 'Angelo', 60973, null, 'UGRD', 'COMP-SCI', 'Springfield', 2011);
insert into STUDENT values ('Pollard', 'Joya', 39077, null, 'GRAD', 'INFO-SYS', 'Springfield', 2010);
insert into STUDENT values ('Peoples', 'Brandon', 22989, 555443333, 'UGRD', 'COMP-GAM', 'Milwaukee', 2014);
insert into STUDENT values ('Peoples', 'Bridget', 21705, 571441234, 'UGRD', 'COMP-SCI', 'Milwaukee', 2014);
insert into COURSE values (1020, 'Theory of Computation', 'CSC', 489);
insert into COURSE values (1092, 'Cryptography', 'CSC', 440);
insert into COURSE values (3201, 'Data Analysis', 'IT', 223);
insert into COURSE values (9219, 'Database Systems', 'CSC', 355);
insert into COURSE values (3111, 'Theory of Computation', 'CSC', 389);
insert into COURSE values (8772, 'History of Games', 'GAM', 206 );
insert into COURSE values (2987, 'Topics in Digital Cinema', 'DC', 270);
insert into STUDENTGROUP values (1, 'Computer Science Society', 75234, 1998);
insert into STUDENTGROUP values (30, 'Robotics Society', 32105, 2001);
insert into STUDENTGROUP values (25, 'HerCDM', 21705, 2003);
insert into STUDENTGROUP values (449, 'DeFrag', 90421, 2005);
insert into ENROLLMENT values (11035, 3201, 'Spring', 2011);
insert into ENROLLMENT values (11035, 1020, 'Fall', 2012);
insert into ENROLLMENT values (11035, 1092, 'Fall', 2012);
insert into ENROLLMENT values (75234, 3201, 'Winter', 2012);
insert into ENROLLMENT values (88871, 3201, 'Spring', 2011);
insert into ENROLLMENT values (88871, 1092, 'Fall', 2013);
insert into ENROLLMENT values (39077, 8772, 'Fall', 2012);
insert into ENROLLMENT values (39077, 1092, 'Fall', 2013);
insert into ENROLLMENT values (57923, 9219, 'Winter', 2013);
insert into ENROLLMENT values (60973, 9219, 'Winter', 2013);
insert into ENROLLMENT values (19992, 3201, 'Winter', 2013);
insert into ENROLLMENT values (60973, 8772, 'Spring', 2013);
insert into ENROLLMENT values (90421, 8772, 'Spring', 2013);
insert into ENROLLMENT values (90421, 2987, 'Spring', 2013);
insert into ENROLLMENT values (60973, 2987, 'Spring', 2013);
insert into ENROLLMENT values (22989, 8772, 'Fall', 2014);
insert into ENROLLMENT values (22989, 3201, 'Fall', 2014);
insert into ENROLLMENT values (21705, 9219, 'Fall', 2014);
insert into ENROLLMENT values (21705, 1092, 'Fall', 2014);
insert into MEMBERSHIP values (75234, 449, 2011);
insert into MEMBERSHIP values (11035, 25, 2010);
insert into MEMBERSHIP values (93321, 25, 2013);
insert into MEMBERSHIP values (75234, 1, 2011);
insert into MEMBERSHIP values (32105, 449, 2011);
insert into MEMBERSHIP values (32105, 1, 2012);
insert into MEMBERSHIP values (32105, 25, 2012);
insert into MEMBERSHIP values (32105, 30, 2013);
insert into MEMBERSHIP values (14662, 30, 2013);
insert into MEMBERSHIP values (39077, 25, 2011);
insert into MEMBERSHIP values (22989, 449, 2014);
insert into MEMBERSHIP values (21705, 1, 2014);
insert into MEMBERSHIP values (21705, 25, 2014);
commit;