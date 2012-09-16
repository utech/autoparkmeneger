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
 (1,'����.','�','#00ff00'),
 (2,'˳�������','�','#0000ff'),
 (3,'³�������','�','#ffff00'),
 (4,'�� ��� ���.','�','#808000'),
 (5,'������ � ������� ��','�','#00ffff'),
 (6,'�������� �������� ������� (������� ����\'����)','�',NULL),
 (7,'������� ����������','�','#008080'),
 (8,'³������� � ��\'���� � ������','�',NULL),
 (9,'ϳ����� ������ �������','�',NULL),
 (10,'ϳ����� ������ �����������','�',NULL),
 (11,'������������� ������ ������','�',NULL),
 (12,'ֳ������ ������','�',NULL),
 (13,'������������� ������','�',NULL),
 (14,'�������','�','#ff0000'),
 (15,'��������','�',NULL),
 (16,'��������� �����. �������� ���� �����. ����','�',NULL),
 (17,'������� � ������� �����������','�',NULL),
 (18,'ϳ����� ��� ���. � ��������� ������� �����','�',NULL);