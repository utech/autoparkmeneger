ALTER TABLE ruhomyisklad 
	DROP COLUMN ZagKilkMisc,
	DROP COLUMN AvtokolonaNumber;

ALTER TABLE lystregulyarnostiruhu 
	DROP COLUMN AutokolonaNum;

UPDATE marshruty SET ChasZRozryvom=null;
	
ALTER TABLE `marshruty` CHANGE COLUMN `MarshrutVid` `MarshrutNapryamok` VARCHAR(25) CHARACTER SET cp1251 COLLATE cp1251_ukrainian_ci DEFAULT NULL,
 DROP COLUMN `MarshrutDo`,
 DROP COLUMN `MarshrutCherez`,
 DROP COLUMN `GodynyVRoboti`,
 MODIFY COLUMN `ChasZRozryvom` BOOLEAN DEFAULT false,
 DROP COLUMN `ChasInshyiRobochyi`,
 DROP COLUMN `ProbigReisu`,
 DROP COLUMN `ProbigMarshrutu`;
 
ALTER TABLE shlyahovyilyst CHANGE COLUMN `IsNormVal` `IsKoryguv` TINYINT(1) DEFAULT false;

INSERT INTO taryfni_sitky (id, Posada) VALUES (10, 'Водії');

ALTER TABLE npr DROP COLUMN `KolonaNum`;