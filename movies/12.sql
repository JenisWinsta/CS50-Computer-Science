--both Bradley Cooper and Jennifer Lawrence starred
select title from movies where id in (select movie_id from stars where person_id = (select id from people where name='Jennifer Lawrence')
                                                            and movie_id in (select movie_id from stars where person_id = (select id from people where name='Bradley Cooper')));

