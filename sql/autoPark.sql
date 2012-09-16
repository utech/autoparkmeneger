
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
	(1, 'ЛАЗ', 'ЛАЗ-695'),
	(2, 'ЛАЗ', 'Лайнер-9'),
	(3, 'ЛАЗ', 'Лайнер-10'),
	(4, 'ЛАЗ', 'Лайнер-12'),
	(5, 'ЛАЗ', 'ЛАЗ-А291'),
	(6, 'ЛАЗ', 'ЛАЗ-5252'),
	(7, 'ЛАЗ', 'ЛАЗ-5208'),
	(8, 'ЛАЗ', 'ЛАЗ-А183'),
	(9, 'ЛАЗ', 'ЛАЗ-А183'),
	(10, 'ЛАЗ', 'ЛАЗ-А183'),
	(11, 'ЛАЗ', 'ЛАЗ-АХ183 "Аеропорт"'),
	
	(12, 'Богдан', 'А06921 (Е-2) місто'),
	(13, 'Богдан', 'А06900 (Е-2) передмістя'),
	(14, 'Богдан', 'А09202 (Е-2) місто'),
	(15, 'Богдан', 'А09204 (Е-3) місто'),
	(16, 'Богдан', 'А09212 (Е-2) передмістя'),
	(17, 'Богдан', 'А09214 (Е-3) передмістя'),
	(18, 'Богдан', 'А09212 (Е-2) турист'),
	(19, 'Богдан', 'А09214 (Е-3) турист'),
	(20, 'Богдан', 'А40160 (Е-3) турист'),
	(21, 'Богдан', 'А14451 (Е-2) середній міський'),
	(22, 'Богдан', 'А1445 (Е-2) середній міський'),
	(23, 'Богдан', 'А1452 (Е-2) приміський'),
	(24, 'Богдан', 'А601.10 (Е-3) середній міський'),
	(25, 'Богдан', 'UNIVERSE (Е-3) турист'),
	(26, 'Богдан', 'А231 (Е-2) великий міський'),
	
	(27, 'Еталон', 'А148 (міський)'),
	(28, 'Еталон', 'А148.1 (Євро 2)'),
	(29, 'Еталон', 'А148.5 (Євро 3)(приміський)'),
	(30, 'Еталон', 'А148.2 (Євро 2)'),
	(31, 'Еталон', 'А148.3 (Євро 3)(Турист)'),
	(32, 'Еталон', 'А079.14 (міський)'),
	(33, 'Еталон', 'А079.14 (приміський)'),
	(34, 'Еталон', 'А079.19(міжміський)'),
	(35, 'Еталон', 'А079.23 (Турист)'),
	(36, 'Еталон', 'А079.24 (Турист)'),
	(37, 'Еталон', 'А079.25 (Турист-Люкс)'),
	(38, 'Еталон', 'БАЗ 2215 (Дельфін)'),
	(39, 'Еталон', 'A074 (міський)');

CREATE TABLE IF NOT EXISTS `markaPalnogo`(
  `Id` SMALLINT(2) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `MarkaName` VARCHAR(10) DEFAULT null,
  `Cina` DOUBLE(8,2) DEFAULT null,
  `Prymitka` VARCHAR(10) DEFAULT null
)
ENGINE=MyISAM;

INSERT INTO markaPalnogo (Id, MarkaName) VALUES 
	(1, 'А-76'),
	(2, 'А-80'),
	(3, 'А-92'),
	(4, 'А-95'),
	(5, 'ДП'),
	(6, 'Газ'),
	(7, 'Pulls 95');

CREATE TABLE IF NOT EXISTS `typMarshrutu`(
  `Id` SMALLINT(2) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `TypName` VARCHAR(15) DEFAULT null,
  `TypNameMnoj` VARCHAR(15) DEFAULT null,
  `Prymitka` VARCHAR(20) DEFAULT null
)
ENGINE=MyISAM;

INSERT INTO typMarshrutu (Id, TypName, TypNameMnoj) VALUES 
	(1, 'Міжміський', 'Міжміські'),
	(2, 'Приміський', 'Приміські'),
	(3, 'Міжнародний', 'Міжнародні'),
	(4, 'Міський', 'Міські');

CREATE TABLE IF NOT EXISTS `typVytratyPalnogo`(
  `Id` SMALLINT(2) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `ShortTypName` VARCHAR(5) DEFAULT null,
  `TypName` VARCHAR(20) DEFAULT null,
  `Prymitka` VARCHAR(20) DEFAULT null
)
ENGINE=MyISAM;

INSERT INTO typVytratyPalnogo (Id, ShortTypName, TypName) VALUES 
	(1, 'Звичн', 'Звичайний розхід'),
	(2, 'Зима', 'Зимовий розхід');
	
CREATE TABLE IF NOT EXISTS `typPoNochivli`(
  `Id` SMALLINT(2) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `ShortTypName` VARCHAR(7) DEFAULT null,
  `TypName` VARCHAR(20) DEFAULT null,
  `Prymitka` VARCHAR(20) DEFAULT null
)
ENGINE=MyISAM;

INSERT INTO typPoNochivli (Id, ShortTypName, TypName) VALUES 
	(1, '-', 'Без ночівлі'),
	(2, 'Ніч', 'З ночівлею'),
	(3, 'Резерв', 'В резерві');

CREATE TABLE IF NOT EXISTS `typKorekcii`(
  `Id` SMALLINT(2) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `ShortTypName` VARCHAR(5) DEFAULT null,
  `TypName` VARCHAR(20) DEFAULT null,
  `Prymitka` VARCHAR(20) DEFAULT null
)
ENGINE=MyISAM;

INSERT INTO typKorekcii (Id, ShortTypName, TypName) VALUES 
	(1, '-', 'Без корекції'),
	(2, 'Кор.', 'Коректовано');

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
INSERT INTO `npr`(Prizv, Password, Grupa_id) VALUES ("Директор", '111', 1);
INSERT INTO `npr`(Prizv, Password, Grupa_id) VALUES ("Бухгалтер", '111', 2);
INSERT INTO `npr`(Prizv, Password, Grupa_id) VALUES ("Представник профспілки", '111', 4);

CREATE TABLE `progOptionsAPark` (
  `id` INT(10) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `Opys` VARCHAR(50) DEFAULT NULL,
  `Znach` VARCHAR(300) DEFAULT NULL
)
ENGINE = MyISAM;
INSERT INTO `progOptionsAPark` VALUES (1, 'ІД працівників ВОДІЇ', '10');

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
