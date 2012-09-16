ALTER TABLE `typmarshrutu` ADD COLUMN `VidsPodatkuPoVyruchci` DOUBLE(5,2) AFTER `TypNameMnoj`;

UPDATE typmarshrutu SET VidsPodatkuPoVyruchci=1.5 WHERE id=1;
UPDATE typmarshrutu SET VidsPodatkuPoVyruchci=3 WHERE id=2;
UPDATE typmarshrutu SET VidsPodatkuPoVyruchci=3 WHERE id=3;
UPDATE typmarshrutu SET VidsPodatkuPoVyruchci=3 WHERE id=4;
UPDATE typmarshrutu SET VidsPodatkuPoVyruchci=3 WHERE id=5;

ALTER TABLE `tabel` 
 MODIFY COLUMN `God_zag` TIME DEFAULT '0.0',
 MODIFY COLUMN `God_nichni` TIME DEFAULT '0.0',
 MODIFY COLUMN `God_sv` TIME DEFAULT '0.0';

CREATE TABLE  `svyatkoviDni` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `SvyatoName` varchar(45) DEFAULT NULL,
  `CDate` date,
  PRIMARY KEY (`id`) USING BTREE,
  KEY `CDateInd` (`CDate`)
) ENGINE=MyISAM;

DROP TABLE IF EXISTS `pracivn_status`;
CREATE TABLE `pracivn_status` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `Status_name` varchar(50) DEFAULT NULL,
  `Status_char` char(1) DEFAULT NULL,
  `Status_color` char(7) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=20 DEFAULT CHARSET=cp1251;

--
-- Dumping data for table `pracivn_status`
--
INSERT INTO `pracivn_status` (`id`,`Status_name`,`Status_char`,`Status_color`) VALUES 
 (1,'Прац.','З','#00ff00'),
 (2,'Лікарняне','Б','#0000ff'),
 (3,'Відпустка','О','#ffff00'),
 (4,'За свій рах.','У','#808000'),
 (5,'Вихідні і святкові дні','В','#00ffff'),
 (6,'Невиходи дозволені Законом (державні обов\'язки)','Г',NULL),
 (7,'Службові відрядження','К','#008080'),
 (8,'Відпустка у зв\'язку з родами','Р',NULL),
 (9,'Пільгові години матерям','М',NULL),
 (10,'Пільгові години неповнолітнім','Л',NULL),
 (11,'Понаднормовані години роботи','С',NULL),
 (12,'Цілозмінні простої','Ц',NULL),
 (13,'Внутрішньозмінні простої','Ч',NULL),
 (14,'Прогули','П','#ff0000'),
 (15,'Спізнення','Н',NULL),
 (16,'Виконання служб. доручень поза терит. підпр','Т',NULL),
 (17,'Невихід з дозволу адміністрації','А',NULL),
 (18,'Пільгові год роб. з шкідливими умовами праці','Д',NULL);