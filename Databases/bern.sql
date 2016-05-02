drop table mushroom cascade constraints
/
drop table grade cascade constraints
/
drop table station_price cascade constraints
/
drop table trans_item cascade constraints
/
drop table station cascade constraints
/
drop table address cascade constraints
/
drop table picker cascade constraints
/
drop table trans_action cascade constraints
/
drop table employee cascade constraints
/
create table address
(
	addressid number( 4 ),
	street1 varchar2( 50 ),
	street2 varchar2( 50 ),
	city varchar2( 50 ),
	state varchar2( 50 ),
	zip varchar2( 50 ),
	
	Constraint addressid_PK Primary Key( addressid )
)
/
create table mushroom
(
	shroomid number(4),
	shroomname varchar2(50),
	shroomdescription varchar2( 50 ),
	season date,
	
	Constraint mushroom_PK Primary Key( shroomid ),
)
/
create table grade
(
	gradeid number( 4 ),
	shroomid number( 4 ),
	gradename varchar2( 50 ),
	gradedescription varchar2( 50 ),
	
	Constraint grade_PK Primary Key( gradeid ),
	Constraint grade_FK_shroomid Foreign Key ( shroomid ) References mushroom( shroomid )
)
/
create table station
(
	stationid number( 4 ),
	town varchar2( 50 ),
	locationdesc varchar2( 50 ),
	active char(1),
	phone varchar2( 20 ),
	
	Constraint station_PK Primary Key( stationid )
)
/
create table station_price
(
	stationid number( 4 ),
	gradeid number( 4 ),
	price number( 4, 2 ),
	time_stamp date,
	
	Constraint station_price_PK Primary Key( stationid, itemid ),
	Constraint station_price_FK_stationid Foreign Key ( stationid ) References station( stationid ),
	Constraint station_price_FK_gradeid Foreign Key ( gradeid ) References grade( gradeid )
)
/
create table picker
(
	pickerid number( 4 ),
	addressid number( 4 ),
	firstname varchar2( 50 ),
	lastname varchar2( 50 ),
	licensenumber varchar2( 50 ),
	phone varchar2( 20 ),
	
	Constraint picker_PK Primary Key( pickerid ),
	Constraint picker_FK_addressid Foreign Key ( addressid ) References address( addressid )
)
/
create table employee
(
	employeeid number( 4 ),
	stationid number( 4 ),
	addressid number( 4 ),
	firstname varchar2( 50 ),
	lastname varchar2( 50 ),
	phone varchar2( 20 ),
	
	Constraint employee_PK Primary Key( employeeid ),
	Constraint employee_FK_stationid Foreign Key ( stationid ) References station( stationid ),
	Constraint employee_FK_addressid Foreign Key ( addressid ) References address( addressid )
)
/
create table trans_action
(
	transid number( 4 ),
	stationid number( 4 ),
	employeeid number( 4 ),
	pickerid number( 4 ),
	transnumber number( 4 ),
	transdate date,
	
	Constraint trans_action_PK Primary Key( transid ),
	Constraint trans_action_FK_stationid Foreign Key ( stationid ) References station( stationid ),
	Constraint trans_action_FK_employeeid Foreign Key ( employeeid ) References employee( employeeid ),
	Constraint trans_action_FK_pickerid Foreign Key ( pickerid ) References picker( pickerid )
)
/
create table trans_item
(
	transid number( 4 ),
	gradeid number( 4 ),
	qty number( 4 ),
	price number( 4, 2 ),
	bonus number( 4, 2 ),
	
	Constraint trans_item_PK Primary Key( transid, gradeid ),
	Constraint trans_item_FK_transid Foreign Key ( transid ) References trans_action( transid ),
	Constraint trans_item_FK_gradeid Foreign Key ( gradeid ) References grade( gradeid )
)
/
