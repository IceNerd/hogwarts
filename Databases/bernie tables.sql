drop table Station_Price
/
drop table Trans_Item
/
drop table Grade
/
drop table Mushroom
/
drop table Trans
/
drop table Employee
/
drop table Station
/
drop table Picker
/
drop table Address
/
create table Mushroom
(
	ShroomID			number(10),
	ShroomName			varchar2(40)	not null,
	ShroomDescription	varchar2(255)	not null,
	Season				varchar2(50)	not null,
	Constraint Mushroom_PK 				Primary Key (ShroomID)
)
/
create table Grade
(
	GradeID				number(10),
	ShroomID			number(10),
	GradeName			varchar2(8)		not null,
	GradeDescription	varchar2(255)	not null,
	Constraint Grade_PK 				Primary Key (GradeID),
	Constraint Grade_Mushroom_FK		Foreign Key (ShroomID) References Mushroom(ShroomID)
)
/
create table Address
(
	AddressID		number(10),
	Street1			varchar2(30)	not null,
	Street2			varchar2(30),
	City			varchar2(30)	not null,
	State			char(2)			not null,
	Zip				varchar2(10)	not null,
	Constraint Address_PK 			Primary Key (AddressID)
)
/
create table Employee
(
	EmployeeID		number(10),
	AddressID		number(10),
	FirstName		varchar2(15)	not null,
	LastName		varchar2(20)	not null,
	Phone			varchar2(20)	not null,
	Constraint Employee_PK			Primary Key (EmployeeID),
	Constraint Employee_Address_FK	Foreign Key (AddressID) References Address(AddressID)
)
/
create table Station
(
	StationID		number(10),
	EmployeeID		number(10), 	
	Town			varchar2(30)	not null,
	LocationDesc	varchar2(255)	not null,
	Active			char(1)			not null,
	Phone			varchar2(20)	not null,
	Constraint Station_PK 			Primary Key (StationID),
	Constraint Station_Active_CK	Check (Active In ('Y', 'N')),
	Constraint Station_Employee_FK	Foreign Key (EmployeeID) References Employee(EmployeeID)
)
/
create table Picker
(
	PickerID		number(10),
	AddressID		number(10)		not null,
	FirstName		varchar2(15)	not null,
	LastName		varchar2(20)	not null,
	LicenseNumber	varchar2(15)	not null,
	Phone			varchar2(20),
	Constraint Picker_PK 			Primary Key (PickerID),
	Constraint Picker_Address_FK	Foreign Key (AddressID) References Address(AddressID)	
)
/
create table Station_Price
(
	StationID		number(10),
	GradeID			number(10),
	Price			number(6, 2) 		not null,
	Timestamp		Date				Default Sysdate not null,		
	Constraint Station_Price_PK			Primary Key (StationID, GradeID),
	Constraint Station_Price_Station_FK	Foreign Key (StationID) References Station(StationID),
	Constraint Station_Price_Grade_FK	Foreign Key (GradeID) References Grade(GradeID)
)
/

create table Trans
(
	TransID			number(10),			
	StationID		number(10)			not null,
	PickerID		number(10)			not null,
	TransNumber		varchar2(15)		not null,
	TransDate		Date				default sysdate not null,
	Constraint Transaction_PK			Primary Key (TransID),
	Constraint Transaction_Station_FK	Foreign Key (StationID) References Station(StationID),
	Constraint Transaction_Picker_FK	Foreign Key (PickerID) References Picker(PickerID)
)
/
create table Trans_Item
(
	TransID			number(10),			
	GradeID			number(10),
	Qty				number(10, 2)			not null,
	Price			number(10, 2)			not null,
	Bonus			number(5, 2),
	Constraint Trans_Item_PK				Primary Key (TransID, GradeID),
	Constraint Trans_Item_Transaction_FK	Foreign Key (TransID) References Trans(TransID),
	Constraint Trans_Item_Grade_FK			Foreign Key (GradeID) References Grade(GradeID)
)
/
