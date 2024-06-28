SELECT title
FROM movies
WHERE id in (
    SELECT movie_id
    FROM stars
    WHERE person_id = (SELECT id FROM people WHERE name = 'Bradley Cooper')
) AND id in (
    SELECT movie_id
    FROM stars
    WHERE person_id = (SELECT id FROM people WHERE name = 'Jennifer Lawrence')
);

