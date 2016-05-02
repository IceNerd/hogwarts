DROP TABLE address;
DROP TABLE condition;
DROP TABLE icedepth;
DROP TABLE icedepth_measure;
DROP TABLE emp;
DROP TABLE measure;
DROP TABLE rink;
DROP TABLE rink_emp;

CREATE TABLE address ( 
	addressid bigint NOT NULL,
	address1 varchar(100) NOT NULL,
	address2 varchar(100),
	city varchar(50) NOT NULL,
	state varchar(2) NOT NULL,
	zip varchar(10) NOT NULL,
);

CREATE TABLE condition ( 
	conditionid bigint NOT NULL,
	airtemp numeric(6,2) NOT NULL,
	icetemp numeric(6,2) NOT NULL,
	stamp smalldatetime NOT NULL,
	rinkid bigint NOT NULL,
	empid bigint NOT NULL,
	windspeed int,
	weather int,
	seapressure numeric(6,2),
	dewpoint numeric(6,2),
	cloudcover int
);

CREATE TABLE icedepth ( 
	icedepthid bigint NOT NULL,
	rinkid bigint NOT NULL,
	empid bigint NOT NULL,
	stamp smalldatetime NOT NULL
);

CREATE TABLE icedepth_measure ( 
	icedepthid bigint NOT NULL,
	measureid bigint NOT NULL
);

CREATE TABLE emp ( 
	empid bigint NOT NULL,
	fname varchar(50) NOT NULL,
	lname varchar(50) NOT NULL,
	addressid bigint,
	active char(1) NOT NULL
);

CREATE TABLE measure ( 
	measureid bigint NOT NULL,
	height numeric(6,2) NOT NULL,
	sectionx int NOT NULL,
	sectiony int NOT NULL,
	subx int NOT NULL,
	suby int NOT NULL
);

CREATE TABLE rink ( 
	rinkid bigint NOT NULL,
	name varchar(50) NOT NULL,
	typeofrink varchar(50) NOT NULL,
	addressid bigint NOT NULL,
	height numeric(6,2) NOT NULL,
	width numeric(6,2) NOT NULL
);

CREATE TABLE rink_emp ( 
	rinkid bigint NOT NULL,
	empid bigint NOT NULL
);


ALTER TABLE address ADD CONSTRAINT PK_address PRIMARY KEY CLUSTERED (addressid);
ALTER TABLE condition ADD CONSTRAINT PK_condition PRIMARY KEY CLUSTERED (conditionid);
ALTER TABLE icedepth ADD CONSTRAINT PK_icedepth PRIMARY KEY CLUSTERED (icedepthid);
ALTER TABLE icedepth_measure ADD CONSTRAINT PK_icedepth_measure PRIMARY KEY (icedepthid, measureid);
ALTER TABLE emp ADD CONSTRAINT PK_emp PRIMARY KEY CLUSTERED (empid);
ALTER TABLE measure ADD CONSTRAINT PK_measure PRIMARY KEY CLUSTERED (measureid);
ALTER TABLE rink ADD CONSTRAINT PK_rink PRIMARY KEY CLUSTERED (rinkid);

ALTER TABLE condition ADD CONSTRAINT FK_condition_rinkid FOREIGN KEY (rinkid) REFERENCES rink(rinkid);
ALTER TABLE condition ADD CONSTRAINT FK_condition_empid FOREIGN KEY (empid) REFERENCES emp(empid);
ALTER TABLE icedepth ADD CONSTRAINT FK_icedepth_rinkid FOREIGN KEY (rinkid) REFERENCES rink(rinkid);
ALTER TABLE icedepth ADD CONSTRAINT FK_icedepth_empid FOREIGN KEY (empid) REFERENCES emp(empid);
ALTER TABLE icedepth_measure ADD CONSTRAINT FK_icedepth_measure_icedepthid FOREIGN KEY (icedepthid) REFERENCES icedepth(icedepthid);
ALTER TABLE icedepth_measure ADD CONSTRAINT FK_icedepth_measure_measureid FOREIGN KEY (measureid) REFERENCES measure(measureid);
ALTER TABLE emp ADD CONSTRAINT FK_emp_addressid FOREIGN KEY (addressid) REFERENCES address(addressid);
ALTER TABLE rink_emp ADD CONSTRAINT FK_rink_emp_rinkid FOREIGN KEY (rinkid) REFERENCES rink(rinkid);
ALTER TABLE rink_emp ADD CONSTRAINT FK_rink_emp_empid FOREIGN KEY (empid) REFERENCES emp(empid);