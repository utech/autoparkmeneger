ALTER TABLE `users` ADD COLUMN `Prizv` VARCHAR(15) AFTER `id`,
 ADD COLUMN `Imya` VARCHAR(10) AFTER `Prizv`,
 ADD COLUMN `Pobatk` VARCHAR(15) AFTER `Imya`,
 ADD COLUMN `PosadaName` VARCHAR(45) AFTER `Pobatk`;

CREATE TABLE `printDocsEnum` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `Name` VARCHAR(100),
  `Prymitka` VARCHAR(45),
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;

CREATE TABLE  `printDocsSigns` (
  `PrintDoc_id` int(10) unsigned DEFAULT NULL,
  `User_id` int(10) unsigned DEFAULT NULL,
  `SortOrder` tinyint(3) unsigned DEFAULT NULL,
  KEY `Index_2` (`PrintDoc_id`,`User_id`)
) ENGINE=MyISAM;