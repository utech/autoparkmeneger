ALTER TABLE `zvitkupivlipalnogo` ADD COLUMN `DovPartners_id` INTEGER UNSIGNED AFTER `ZvitNum`,
 DROP INDEX `Index_2`,
 ADD INDEX `Index_2` USING BTREE(`Npr_id`, `CDate`, `MarkaPalnogo_id`, `DovPartners_id`);
 
UPDATE zvitkupivlipalnogo SET DovPartners_id = 1;