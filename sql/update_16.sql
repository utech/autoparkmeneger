ALTER TABLE `zvitKupivliPalnogoOrders` MODIFY COLUMN `id` INT(10) UNSIGNED NOT NULL,
 ADD COLUMN `KodZapravky` VARCHAR(10) AFTER `CDate`;