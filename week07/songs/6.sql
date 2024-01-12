-- SQL query that lists the names of songs that are by Post Malone
SELECT songs.name
FROM songs
JOIN artists ON (artist_id = artists.id)
WHERE artists.name = 'Post Malone';
