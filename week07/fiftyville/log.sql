-- Keep a log of any SQL queries you execute as you solve the mystery.
------------------------
-- Get the thief name --
------------------------
SELECT people.name
FROM people
WHERE people.id IN (
    -- Get Licence Plates to person IDs
    SELECT people.id
    FROM people
    WHERE people.license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10
        AND minute >= 15 AND minute <=25
        AND activity = 'exit'
    )
)
AND people.id IN (
    -- Get phone numbers to IDs
    SELECT people.id
    FROM people
    WHERE people.phone_number IN (
        SELECT caller
        FROM phone_calls
        WHERE year = 2023 AND month = 7 AND day = 28
        AND duration < 60
    )
)
AND people.id IN (
    -- Get account number to people IDs
    SELECT people.id
    FROM people
    WHERE people.id IN (
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN (
            SELECT account_number
            FROM atm_transactions
            WHERE year = 2023 AND month = 7 AND day = 28
            ORDER BY amount
        )
    )
)
AND people.id IN (
    -- Get Passport Numbers to people IDs
    SELECT people.id
    FROM people
    WHERE people.passport_number IN (
        SELECT passengers.passport_number
        FROM people
        JOIN passengers
        ON people.passport_number = passengers.passport_number
        JOIN flights
        ON passengers.flight_id = flights.id
        WHERE flights.year = 2023
        AND flights.month = 7 AND flights.day = 29
		-- First flight of the day
        AND flights.hour = 8  AND flights.minute = 20
        ORDER BY passengers.passport_number
    )
);

-----------------------
-- Get the city name --
-----------------------
SELECT city FROM airports
-- From the first flight of the day
WHERE id IN (
    SELECT destination_airport_id FROM flights
	WHERE year = 2023 AND month = 7 AND day = 29
    ORDER BY hour, minute ASC LIMIT 1
);

-------------------------------
-- Get the accomplice's name --
-------------------------------
SELECT name FROM people
-- Using their phone number
WHERE phone_number IN (
    -- From the list of phone calls
    SELECT receiver FROM phone_calls
    -- On the date of the crime
    WHERE year = 2023 AND month = 7 AND day = 28
    -- And where the caller was our criminal
    AND caller = (
        -- Bruce is the thief
        SELECT phone_number FROM people WHERE name = 'Bruce'
    )
    -- And to reduce the likelihood of getting more than one result, let's constrain it a little more
    AND duration < 60
);
