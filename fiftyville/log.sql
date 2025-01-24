-- Keep a log of any SQL queries you execute as you solve the mystery.

--info known  took place on July 28, 2023 and that it took place on Humphrey Street.
select * from crime_scene_reports where year=2023 and month=7 and day =28 and street ='Humphrey Street';


--id of case is 295
--time: 10:15am HS bakery- 163 raymond

select * from interviews where year=2023 and month=7 and day =28 and transcript like '%bakery%';

--car in backery parking see footage, cars left at that time
--atm withdrawel laggett street before crime
--call: flight out tomorrow, accomplice buys the ticket, less than a minit

--exit details from security logs
select * from bakery_security_logs where year=2023 and month=7 and day =28 and hour=10 and activity='exit';

--infos of people exited
select * from people where license_plate in (select license_plate from bakery_security_logs where year=2023 and month=7 and day =28 and hour=10 and minute<20 and activity='exit');
--total 9 people

--their passport no
select passport_number from people where license_plate in (select license_plate from bakery_security_logs where year=2023 and month=7 and day =28 and hour=10 and activity='exit');

select * from passengers where passport_number in (select passport_number from people where license_plate in (select license_plate from bakery_security_logs where year=2023 and month=7 and day =28 and hour=10 and activity='exit'));

--idenitfy flights
 select id from airports where city='Fiftyville';
 --flights from fv on next day
 select * from flights where origin_airport_id=8 and year=2023 and month=7 and day =29;
 --id: 18,23,36,43,53
--6people now
select * from passengers join people on people.passport_number=passengers.passport_number where flight_id in (select id from flights where origin_airport_id=8 and year=2023 and month=7 and day =29)
AND passengers.passport_number in (select passport_number from people where license_plate in (select license_plate from bakery_security_logs where year=2023 and month=7 and day =28 and hour=10 and activity='exit'));


--ATM withdrawal and licence plate in parking
select * from people join bank_accounts on people.id=bank_accounts.person_id where bank_accounts.account_number in
(select account_number from atm_transactions where atm_location='Leggett Street' and transaction_type='withdraw' and year=2023 and month=7 and day=28)
and people.license_plate in (select license_plate from bakery_security_logs where year=2023 and month=7 and day =28 and hour=10 and activity='exit');


--ATM withdrawal and licence plate in parking and flight next day (4people now)
--thief and his info
select * from passengers join people on people.passport_number=passengers.passport_number join bank_accounts on people.id=bank_accounts.person_id where bank_accounts.account_number in
(select account_number from atm_transactions where atm_location='Leggett Street' and transaction_type='withdraw' and year=2023 and month=7 and day=28)
and people.license_plate in (select license_plate from bakery_security_logs where year=2023 and month=7 and day =28 and hour=10 and minute<20 and activity='exit')
and flight_id in (select id from flights where origin_airport_id=8 and year=2023 and month=7 and day =29)
AND passengers.passport_number in (select passport_number from people where license_plate in (select license_plate from bakery_security_logs where year=2023 and month=7 and day =28 and hour=10 and activity='exit'))
AND people.phone_number in (select caller from phone_calls where year=2023 and month=7 and day =28 and duration <60);


--city escaped
select city from airports where id =(select Destination_airport_id from flights where id=36);

--accomplice Robin
select * from people where phone_number = (select receiver from phone_calls where caller='(367) 555-5533' and year=2023 and month=7 and day =28 and duration <60);
