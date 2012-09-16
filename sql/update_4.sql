ALTER TABLE `markapalnogo` DROP COLUMN `Cina`,
 DROP COLUMN `Prymitka`;

CREATE TABLE `cinaPalnogoDate` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `CDate` DATE,
  `Prymitka` VARCHAR(100),
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;

CREATE TABLE `CinaPalnogo` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `Palne_id` SMALLINT UNSIGNED NOT NULL,
  `CinaPalnogoDate_id` INTEGER UNSIGNED NOT NULL,
  `Cina` DOUBLE(8,2),
  PRIMARY KEY (`id`),
  INDEX `CinaPalnogo_indexes`(`Palne_id`, `CinaPaldogoDate_id`)
)
ENGINE = MyISAM;

CREATE TABLE `planNaZminuDate` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `CDate` DATE,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;

CREATE TABLE `planNaZminu` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `Marshrut_id` SMALLINT UNSIGNED NOT NULL,
  `PlanNaZminuDate_id` INTEGER UNSIGNED NOT NULL,
  `Plan` DOUBLE(8,2),
  PRIMARY KEY (`id`),
  INDEX `CinaPalnogo_indexes`(`Marshrut_id`, `PlanNaZminuDate_id`)
)
ENGINE = MyISAM;

ALTER TABLE `users` ADD COLUMN `PerevezAccessDif` VARCHAR(200) AFTER `PerevezAccess`;