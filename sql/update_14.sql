CREATE TABLE `zvitKupivliPalnogo` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `Npr_id` INTEGER UNSIGNED,
  `CDate` DATE,
  `MarkaPalnogo_id` TINYINT UNSIGNED,
  `ZvitNum` VARCHAR(10),
  PRIMARY KEY (`id`),
  INDEX `Index_2`(`Npr_id`, `CDate`, `MarkaPalnogo_id`)
)
ENGINE = MyISAM
COMMENT = 'Звіт про використання коштів (на пальне)';

CREATE TABLE `zvitKupivliPalnogoOrders` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `ZvitKupivliPalnogo_id` INTEGER UNSIGNED,
  `CDate` DATE,
  `DocNum` VARCHAR(20),
  `Kilkist` DOUBLE,
  `Suma` DOUBLE,
  PRIMARY KEY (`id`),
  INDEX `Index_2`(`ZvitKupivliPalnogo_id`, `CDate`)
)
ENGINE = MyISAM
COMMENT = 'Чеки до звіт про використання коштів (на пальне)';
