-- SQL query to list all movies released in 2010 and their ratings, in
-- descending order by rating. For movies with the same rating, order them
-- alphabetically by title
SELECT movies.title, rating
FROM ratings
JOIN movies ON movie_id = movies.id
WHERE movies.year = 2010
ORDER BY rating DESC, title;
