-- create the tables for our movies

CREATE TABLE `actors` (
 `actorid` int(10) unsigned NOT NULL AUTO_INCREMENT,
 `first_names` varchar(100) NOT NULL,
 `last_name` varchar(100) NOT NULL,
 `dob` char(10) DEFAULT NULL,
 PRIMARY KEY (`actorid`)
);


-- insert data into the tables

INSERT INTO actors VALUES
  (1, "Cate", "Blanchett","1969-05-14"),
  (2, "Per Christian", "Ellefsen", "1954-02-14"),
  (3, "George","Clooney", "1961-05-06"),
  (4, "Elijah","Wood", "1981-01-28"),
  (5, "Anna","Kendrick", "1985-08-09");

