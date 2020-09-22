CREATE TABLE `movie_actors` (
 `pairid` int(10) unsigned NOT NULL AUTO_INCREMENT,
 `movieid` int(10) unsigned NOT NULL,
 `actorid` int(10) unsigned NOT NULL,
 PRIMARY KEY (`pairid`)
);

-- insert data into the tables

INSERT INTO movie_actors VALUES
  (1,1, 1),
  (2,2, 2),
  (3,3, 3),
  (4,4, 4),
  (5,4, 1),
  (6,5, 5),
  (7,5, 3);

