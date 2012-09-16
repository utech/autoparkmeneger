
CREATE TABLE IF NOT EXISTS `users`(
  `Id` int(10) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `Login` VARCHAR(30) DEFAULT null,
  `PassWord` VARCHAR(32) DEFAULT null,
  `Group_id` SMALLINT(3) DEFAULT 100,
  `PerevezAccess` SMALLINT(1) DEFAULT 0,
  `ZarplataAccess` SMALLINT(1) DEFAULT 0,
  `SkladAccess` SMALLINT(1) DEFAULT 0,
  `Active` BOOLEAN DEFAULT null
)
ENGINE=MyISAM;

CREATE TABLE IF NOT EXISTS `logUserOperations`(
  `Id` INT(10) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `User_id` VARCHAR(30) DEFAULT null,
  `Program_Id` TINYINT(2) DEFAULT null,
  `UserOper_Id` SMALLINT(3) DEFAULT null,
  `Prymitka` VARCHAR(10) DEFAULT null,
  `LoginDateTime` TIMESTAMP
)
ENGINE=MyISAM;

CREATE TABLE IF NOT EXISTS `ruhomyiSklad`(
  `Id` INT(10) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `AvtokolonaNumber` INT(6) DEFAULT null,
  `GarajNumber` INT(6) DEFAULT null,
  `NomernyiZnak` VARCHAR(12) DEFAULT null,
  `MarkaAuto_Id` INT(4) DEFAULT null,
  `TO1` INT(6) DEFAULT null,
  `TO2` INT(6) DEFAULT null,
  `ZagKilkMisc` SMALLINT(3) DEFAULT null,
  `KilkSydMisc` SMALLINT(3) DEFAULT null,
  `VvedenoVEkspluataciyu` DATE DEFAULT null,
  `RozhidPalnogo` DOUBLE(5, 2) DEFAULT null,
  `MarkaPalnogo_Id` SMALLINT(2) DEFAULT null,
  `Brygada_Id` INT(6) DEFAULT null
)
ENGINE=MyISAM;

CREATE TABLE IF NOT EXISTS `markaAuto`(
  `Id` INT(4) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `MarkaName` VARCHAR(15) DEFAULT null,
  `MarkaShyfr` VARCHAR(40) DEFAULT null
)
ENGINE=MyISAM;

INSERT INTO markaAuto (Id, MarkaName, MarkaShyfr) VALUES 
	(1, '���', '���-695'),
	(2, '���', '������-9'),
	(3, '���', '������-10'),
	(4, '���', '������-12'),
	(5, '���', '���-�291'),
	(6, '���', '���-5252'),
	(7, '���', '���-5208'),
	(8, '���', '���-�183'),
	(9, '���', '���-�183'),
	(10, '���', '���-�183'),
	(11, '���', '���-��183 "��������"'),
	
	(12, '������', '�06921 (�-2) ����'),
	(13, '������', '�06900 (�-2) ���������'),
	(14, '������', '�09202 (�-2) ����'),
	(15, '������', '�09204 (�-3) ����'),
	(16, '������', '�09212 (�-2) ���������'),
	(17, '������', '�09214 (�-3) ���������'),
	(18, '������', '�09212 (�-2) ������'),
	(19, '������', '�09214 (�-3) ������'),
	(20, '������', '�40160 (�-3) ������'),
	(21, '������', '�14451 (�-2) ������� ������'),
	(22, '������', '�1445 (�-2) ������� ������'),
	(23, '������', '�1452 (�-2) ���������'),
	(24, '������', '�601.10 (�-3) ������� ������'),
	(25, '������', 'UNIVERSE (�-3) ������'),
	(26, '������', '�231 (�-2) ������� ������'),
	
	(27, '������', '�148 (������)'),
	(28, '������', '�148.1 (���� 2)'),
	(29, '������', '�148.5 (���� 3)(���������)'),
	(30, '������', '�148.2 (���� 2)'),
	(31, '������', '�148.3 (���� 3)(������)'),
	(32, '������', '�079.14 (������)'),
	(33, '������', '�079.14 (���������)'),
	(34, '������', '�079.19(��������)'),
	(35, '������', '�079.23 (������)'),
	(36, '������', '�079.24 (������)'),
	(37, '������', '�079.25 (������-����)'),
	(38, '������', '��� 2215 (�������)'),
	(39, '������', 'A074 (������)');

CREATE TABLE IF NOT EXISTS `markaPalnogo`(
  `Id` SMALLINT(2) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `MarkaName` VARCHAR(10) DEFAULT null,
  `Cina` DOUBLE(8,2) DEFAULT null,
  `Prymitka` VARCHAR(10) DEFAULT null
)
ENGINE=MyISAM;

INSERT INTO markaPalnogo (Id, MarkaName) VALUES 
	(1, '�-76'),
	(2, '�-80'),
	(3, '�-92'),
	(4, '�-95'),
	(5, '��'),
	(6, '���'),
	(7, 'Pulls 95');

CREATE TABLE IF NOT EXISTS `typMarshrutu`(
  `Id` SMALLINT(2) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `TypName` VARCHAR(15) DEFAULT null,
  `TypNameMnoj` VARCHAR(15) DEFAULT null,
  `Prymitka` VARCHAR(20) DEFAULT null
)
ENGINE=MyISAM;

INSERT INTO typMarshrutu (Id, TypName, TypNameMnoj) VALUES 
	(1, '̳�������', '̳�����'),
	(2, '���������', '�������'),
	(3, '̳���������', '̳�������'),
	(4, '̳�����', '̳���');

CREATE TABLE IF NOT EXISTS `typVytratyPalnogo`(
  `Id` SMALLINT(2) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `ShortTypName` VARCHAR(5) DEFAULT null,
  `TypName` VARCHAR(20) DEFAULT null,
  `Prymitka` VARCHAR(20) DEFAULT null
)
ENGINE=MyISAM;

INSERT INTO typVytratyPalnogo (Id, ShortTypName, TypName) VALUES 
	(1, '�����', '��������� ������'),
	(2, '����', '������� ������');
	
CREATE TABLE IF NOT EXISTS `typPoNochivli`(
  `Id` SMALLINT(2) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `ShortTypName` VARCHAR(7) DEFAULT null,
  `TypName` VARCHAR(20) DEFAULT null,
  `Prymitka` VARCHAR(20) DEFAULT null
)
ENGINE=MyISAM;

INSERT INTO typPoNochivli (Id, ShortTypName, TypName) VALUES 
	(1, '-', '��� ������'),
	(2, 'ͳ�', '� ��������'),
	(3, '������', '� ������');

CREATE TABLE IF NOT EXISTS `typKorekcii`(
  `Id` SMALLINT(2) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `ShortTypName` VARCHAR(5) DEFAULT null,
  `TypName` VARCHAR(20) DEFAULT null,
  `Prymitka` VARCHAR(20) DEFAULT null
)
ENGINE=MyISAM;

INSERT INTO typKorekcii (Id, ShortTypName, TypName) VALUES 
	(1, '-', '��� ��������'),
	(2, '���.', '�����������');

CREATE TABLE IF NOT EXISTS `marshruty`(
  `Id` INT(10) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `KodMarshrutu` INT(6) DEFAULT null,
  `MarshrutVid` VARCHAR(25) DEFAULT null,
  `MarshrutDo` VARCHAR(25) DEFAULT null,
  `MarshrutCherez` VARCHAR(25) DEFAULT null,
  `GrafikNum` INT(6) DEFAULT 1,
  `ZminaNum` INT(6) DEFAULT 1,
  `DovjynaMarshrutu` DOUBLE(8, 2) DEFAULT 100,
  `TypMarshrutu_Id` SMALLINT(2) DEFAULT 1,
  `TypVytratyPalnogo` SMALLINT(2) DEFAULT 1,
  `ChasVyizdu` TIME DEFAULT '00:00',
  `ChasZaizdu` TIME DEFAULT '00:00',
  `TypPoNochivli` SMALLINT(2) DEFAULT 1,
  `DniVRoboti` SMALLINT(2) DEFAULT 1,
  `GodynyVRoboti` TIME DEFAULT '0:00',
  `ChasVNaryadi` TIME DEFAULT '0:00',
  `PlanNaZminu` DOUBLE(8, 2) DEFAULT 1000,
  `ChasVMarshruti` TIME DEFAULT '0:00',
  `ChasZRozryvom` TIME DEFAULT '0:00',
  `ChasInshyiRobochyi` TIME DEFAULT '0:00',
  `ChasNichnyi` TIME DEFAULT '0:00',
  `ChasNaReis` TIME DEFAULT '0:00',
  `KilkReisiv` SMALLINT(2) DEFAULT '1',
  `ProbigReisu` DOUBLE(6, 2) DEFAULT '100',
  `ProbigMarshrutu` DOUBLE(6, 2) DEFAULT '100',
  `ProbigNulovyi` DOUBLE(6, 2) DEFAULT '0',
  `ProbigZagalnyi` DOUBLE(6, 2) DEFAULT '0'
)
ENGINE=MyISAM;
	
CREATE TABLE IF NOT EXISTS `shlyahovyiLyst`(
  `Id` INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `ShlyahovyiLystNum_id` INT DEFAULT null,
  `TypPoNochivli_id` TINYINT DEFAULT 1,
  `GarajNum_id` INT DEFAULT null,
  `DataVyizdu` DATETIME DEFAULT null,
  `VodiyTabelNum_id` INT DEFAULT null,
  `DataZaizdu` DATETIME DEFAULT null,
  `KodMarshrutu_id` INT DEFAULT null,
  `GrafikNum` SMALLINT DEFAULT 1,
  `ZminaNum` SMALLINT DEFAULT 1,
  `Korekciya_id` TINYINT DEFAULT 0,
  `ChasVMarshruti` TIME DEFAULT '0:00',
  `ChasVRezervi` TIME DEFAULT '0:00',
  `ChasVNaryadi` TIME DEFAULT '0:00',
  `KilkProdKvytkiv` SMALLINT DEFAULT 0,
  `VartProdKvytkiv` DOUBLE(8, 2) DEFAULT 0,
  `KilkProdKvytkivAutoStat` SMALLINT DEFAULT 0,
  `VartProdKvytkivAutoStat` DOUBLE(8, 2) DEFAULT 0,
  `PlanNaZminu` DOUBLE(8, 2) DEFAULT 0,
  `PilgoviPasajyry` SMALLINT DEFAULT 0,
  `ZagalnProbig` DOUBLE(8, 2) DEFAULT 0,
  `NulyovyiProbig` DOUBLE(8, 2) DEFAULT 0,
  `PlanKilkReisiv` SMALLINT DEFAULT 0,
  `FaktKilkReisiv` SMALLINT DEFAULT 0,
  `PlanRozhidPalnogo` DOUBLE(8, 2) DEFAULT 0,
  `FactRozhidPalnogo` DOUBLE(8, 2) DEFAULT 0
)
ENGINE=MyISAM;

CREATE TABLE IF NOT EXISTS `lystRegulyarnostiRuhu`(
  `Id` INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `Auto_id` INT DEFAULT null,
  `Vodiy_Id` SMALLINT DEFAULT null,
  `Marshrut_id` INT DEFAULT null,
  `GrafikNum` TINYINT DEFAULT null,
  `ZminaNum` TINYINT DEFAULT null,
  `ReisyCount` TINYINT DEFAULT null,
  `AutokolonaNum` SMALLINT DEFAULT null,
  `BrygadaNum` SMALLINT DEFAULT null,
  `VyizdDate` DATE DEFAULT null,
  `ZaizdDate` DATE DEFAULT null,
  `Nochivlya` TINYINT DEFAULT null,
  `PlanVyruchka` DOUBLE(8, 2) DEFAULT null,
  `DniVRoboti` TINYINT DEFAULT null,
  `GodVRoboti` TIME DEFAULT null,
  `VyruchkaFact` DOUBLE(8, 2) DEFAULT null,
  `Vidhylennya` DOUBLE(8, 2) DEFAULT null,
  `EconomPaln` DOUBLE(8, 2) DEFAULT null,
  `VidhylOplGazu` DOUBLE(8, 2) DEFAULT null,
  `MarkaPalnogo_id` TINYINT DEFAULT null,
  `PlanNormaPalnogo` DOUBLE(8, 2) DEFAULT null,
  `CinaPalnogo` DOUBLE(8, 2) DEFAULT null
)
ENGINE=MyISAM;

CREATE TABLE IF NOT EXISTS `TOLog`(
  `Id` INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `GarajNum_id` INT DEFAULT null,
  `TONum` TINYINT DEFAULT null,
  `TODate` DATE DEFAULT null,
  `TOProbig` DOUBLE(8, 2) DEFAULT null
)
ENGINE=MyISAM;

DROP TABLE IF EXISTS npr;
CREATE TABLE IF NOT EXISTS `npr` (
  `id` INT(10) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `Prizv` VARCHAR(25) NULL,
  `Imia` VARCHAR(15) NULL,
  `Pobatk` VARCHAR(20) NULL,
  `Data_nar` DATE NULL,
  `Posada_id` INT(4) NULL,
  `TypRoboty` TINYINT(1) DEFAULT 0,
  `TypOplaty` TINYINT(1) DEFAULT 0,
  `Iden_kod` VARCHAR(12) NULL,
  `Tel` VARCHAR(20) NULL,
  `Rozryad` TINYINT(1) DEFAULT 1,
  `Stavka` DOUBLE(8, 2) DEFAULT 0.00,
  `Num_dit` TINYINT(1) NULL,
  `Ozn_pilgy` SMALLINT(2) NULL,
  `Data_pruin_na_rob` DATE NULL,
  `Klasnist_vodiya` DOUBLE(4,2) DEFAULT 0.00,
  `VidsDoplaty` DOUBLE(4,2) DEFAULT 0.00,
  `Alimenty` DOUBLE(4,2) DEFAULT 0.00,
  `Pensioner` BOOLEAN DEFAULT false,
  Password varchar(20) NULL,
  Buh_rahunok INT UNSIGNED DEFAULT 0,
  Grupa_id INT UNSIGNED DEFAULT 11,
  `ChlenProfspilky` BOOLEAN DEFAULT false,
  `Invalid` BOOLEAN DEFAULT false,
  `Pracuye` BOOLEAN DEFAULT true,
  `KolonaNum` SMALLINT DEFAULT 0,
  `BrygadaNum` SMALLINT DEFAULT 0,
  `KlasVodiya` SMALLINT DEFAULT 0,
  `IsBrygadyr` BOOLEAN DEFAULT false
)
ENGINE = MyISAM;
INSERT INTO `npr`(Prizv, Password, Grupa_id) VALUES ("��������", '111', 1);
INSERT INTO `npr`(Prizv, Password, Grupa_id) VALUES ("���������", '111', 2);
INSERT INTO `npr`(Prizv, Password, Grupa_id) VALUES ("����������� ���������", '111', 4);

CREATE TABLE `progOptionsAPark` (
  `id` INT(10) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `Opys` VARCHAR(50) DEFAULT NULL,
  `Znach` VARCHAR(300) DEFAULT NULL
)
ENGINE = MyISAM;
INSERT INTO `progOptionsAPark` VALUES (1, '�� ���������� ��Ĳ�', '10');

CREATE TABLE `pilgyAParkPokazn` (
  `id` INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `CurDate` DATE DEFAULT NULL,
  `VyruchkaZagalna` DOUBLE(8,2) DEFAULT 0.00,
  `TaryfZaPasajKm` DOUBLE(8,2) DEFAULT 0.00,
  `KilkistPlatnPasaj` INT DEFAULT 0,
  `Koef` DOUBLE(8,4) DEFAULT 0.0000,
  `KilkistPilgovykiv` INT DEFAULT 0,
  `KilkistVrahPilgovykiv` INT DEFAULT 0,
  `Prymitka` VARCHAR(100) DEFAULT NULL
)
ENGINE = MyISAM;
