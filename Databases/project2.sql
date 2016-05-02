drop table aspectratio cascade constraints
/
drop table studio cascade constraints
/
drop table rating cascade constraints
/
drop table dvd cascade constraints
/
drop table genre cascade constraints
/
drop table person cascade constraints
/
drop table dvd_genre cascade constraints
/
drop table dvd_actor cascade constraints
/
drop table dvd_director cascade constraints
/
drop table dvd_writer cascade constraints
/

create table aspectratio
(

	aspectratio_id number( 8 ),
	name varchar2( 25 ) not null,
	description varchar2( 300 ),
	
	Constraint aspectratio_id_PK Primary Key( aspectratio_id )

)
/
create table studio
(

	studio_id number( 8 ),
	name varchar2( 25 ) not null,
	description varchar2( 300 ),

	Constraint studio_id_PK Primary Key( studio_id ),

)
/
create table rating
(

	rating_id number( 8 ),
	name varchar2( 25 ) not null,
	description varchar2( 300 ),

	Constraint rating_id_PK Primary Key( rating_id )

)
/
create table dvd
(
	dvd_id number( 8 ),
	title varchar2( 50 ) not null,
	runningtime number( 3 ),
	releaseyear number( 4 ),
	plotdescription varchar2( 300 ),
	color varchar2( 25 ),
	studio_id number( 8 ),
	aspectratio_id number( 8 ),
	rating_id number( 8 ),
	
	Constraint dvd_id_PK Primary Key( dvd_id ),
	Constraint dvd_FK_studio_id Foreign Key ( studio_id ) References studio( studio_id ),
	Constraint dvd_FK_aspectratio_id Foreign Key ( aspectratio_id ) References aspectratio( aspectratio_id ),
	Constraint dvd_FK_rating_id Foreign Key ( rating_id ) References rating( rating_id )
)
/
create table genre
(

	genre_id number( 8 ),
	name varchar2( 25 ) not null,
	description varchar2( 300 ),

	Constraint genre_id_PK Primary Key( genre_id )

)
/
create table person
(

	person_id number( 8 ),
	firstname varchar2( 20 ) not null,
	lastname varchar2( 20 ) not null,
	
	Constraint person_id_PK Primary Key( person_id )

)
/
create table dvd_genre
(

	dvd_id number( 8 ),
	genre_id number( 8 ),

	Constraint dvd_genre_FK_dvd_id Foreign Key ( dvd_id ) References dvd( dvd_id ),
	Constraint dvd_genre_FK_genre_id Foreign Key ( genre_id ) References genre( genre_id )

)
/
create table dvd_actor
(

	dvd_id number( 8 ),
	person_id number( 8 ),
	character_firstname varchar2( 20 ),
	character_lastname varchar2( 20 ),

	Constraint dvd_actor_FK_dvd_id Foreign Key ( dvd_id ) References dvd( dvd_id ),
	Constraint dvd_actor_FK_person_id Foreign Key ( person_id ) References person( person_id )

)
/
create table dvd_director
(

	dvd_id number( 8 ),
	person_id number( 8 ),

	Constraint dvd_director_FK_dvd_id Foreign Key ( dvd_id ) References dvd( dvd_id ),
	Constraint dvd_director_FK_person_id Foreign Key ( person_id ) References person( person_id )

)
/
create table dvd_writer
(

	dvd_id number( 8 ),
	person_id number( 8 ),

	Constraint dvd_writer_FK_dvd_id Foreign Key ( dvd_id ) References dvd( dvd_id ),
	Constraint dvd_writer_FK_person_id Foreign Key ( person_id ) References person( person_id )

)
/