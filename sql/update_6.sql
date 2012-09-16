ALTER TABLE `shlyahovyilyst` ADD COLUMN `ZapravkaZaGotivku` DOUBLE(8,2) AFTER `PlanNaZminu`;

ALTER TABLE `markaPalnogo` ADD COLUMN `MarkaRozm` VARCHAR(6) AFTER `MarkaName`;
UPDATE markaPalnogo SET MarkaRozm='л.' WHERE id=1;
UPDATE markaPalnogo SET MarkaRozm='л.' WHERE id=2;
UPDATE markaPalnogo SET MarkaRozm='л.' WHERE id=3;
UPDATE markaPalnogo SET MarkaRozm='л.' WHERE id=4;
UPDATE markaPalnogo SET MarkaRozm='л.' WHERE id=5;
UPDATE markaPalnogo SET MarkaRozm='м.куб.' WHERE id=6;
UPDATE markaPalnogo SET MarkaRozm='л.' WHERE id=7;

ALTER TABLE `npr` ADD COLUMN `Naparnyky` SMALLINT UNSIGNED AFTER `IsBrygadyr`;