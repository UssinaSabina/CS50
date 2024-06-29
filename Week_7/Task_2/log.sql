-- Keep a log of any SQL queries you execute as you solve the mystery.

-- see what crime_scene_reports table looks like
SELECT * FROM crime_scene_reports LIMIT 5;

-- find our crime in crime_scene_reports table
SELECT * FROM crime_scene_reports WHERE street = 'Humphrey Street' AND day = 28 AND month = 7;

-- so now we know additional info: id = 295, year = 2023, time = 10:15, 3 witnesses, each of them mentions bakery

-- let's see interviews with witnesses
SELECT * FROM interviews WHERE day = 28 AND month = 7 AND year = 2023;
-- 161 Ruth: sometime whithin 10 minutes of the theft, I saw the thief get into a car. ! Security footage from bakery parking lot !
-- 162 Eugene: earlier that morning the thief was withdrawing some money at ATM on Leggett Street
-- 163 Raymond: thief called someone (less than a minute). Take the earliest flight out of Fiftyville tomorrow. The accomplice bought ticket

-- let's find out car's license plate number
SELECT * FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND activity = 'exit';


-- select all flights from Finderville on a next day
SELECT *
FROM flights
WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
AND year = 2023 AND month = 7 AND day = 29;
-- the earliest flight took place at 8:20, so now we can find out flight_id
SELECT id
FROM flights
WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
AND year = 2023 AND month = 7 AND day = 29 AND hour = 8;

-- select passport number of all passengers who took that flight
SELECT passport_number
FROM passengers
WHERE flight_id in (
    SELECT id
    FROM flights
    WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
    AND year = 2023 AND month = 7 AND day = 29 and hour = 8
);

-- combine all info we know from interviews
SELECT bank_accounts.account_number, amount, person_id, people.name, people.phone_number, people.passport_number, people.license_plate
FROM atm_transactions
JOIN bank_accounts on atm_transactions.account_number = bank_accounts.account_number
JOIN people on bank_accounts.person_id = people.id
WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location LIKE '%Leggett Street%' AND transaction_type = 'withdraw'
AND people.license_plate in (
    SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND activity = 'exit'
)
AND phone_number in (
    SELECT caller FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration <= 60
)
AND passport_number in (
    SELECT passport_number
    FROM passengers
    WHERE flight_id in (
        SELECT id
        FROM flights
        WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
        AND year = 2023 AND month = 7 AND day = 29 and hour = 8
    )
);
-- so... our thief is Bruce

-- let's find out city that bruce escaped to
SELECT city
FROM airports
WHERE id = (
    SELECT destination_airport_id
    FROM flights
    WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
    AND year = 2023 AND month = 7 AND day = 29 and hour = 8
);
-- now we know that Bruce escaped to New York City

-- finally, let's find out who's Bruce's accomplice
SELECT name
FROM people
WHERE phone_number = (
    SELECT receiver
    FROM phone_calls
    WHERE year = 2023 AND month = 7 AND day = 28 AND duration <= 60
    AND caller = (
        SELECT people.phone_number
        FROM atm_transactions
        JOIN bank_accounts on atm_transactions.account_number = bank_accounts.account_number
        JOIN people on bank_accounts.person_id = people.id
        WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location LIKE '%Leggett Street%' AND transaction_type = 'withdraw'
        AND people.license_plate in (
            SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND activity = 'exit'
        )
        AND phone_number in (
            SELECT caller FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration <= 60
        )
        AND passport_number in (
            SELECT passport_number
            FROM passengers
            WHERE flight_id in (
                SELECT id
                FROM flights
                WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
                AND year = 2023 AND month = 7 AND day = 29 and hour = 8
            )
        )
    )
);
-- it's Robin

-- full answer: Bruce, New York City, Robin
