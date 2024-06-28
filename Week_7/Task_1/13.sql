SELECT DISTINCT(people.name)
FROM people
JOIN stars on people.id = stars.person_id
WHERE movie_id IN (
    SELECT movie_id FROM stars WHERE person_id = (
        SELECT id from people WHERE name = 'Kevin Bacon' AND birth = 1958
        )
) AND people.name != 'Kevin Bacon';
