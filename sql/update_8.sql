ALTER TABLE `shlyahovyilyst` ADD COLUMN `ToZvitDate` DATE AFTER `DataVyizdu`;

UPDATE shlyahovyilyst SET ToZvitDate = date(DataVyizdu);

UPDATE typMarshrutu SET VidsPodatkuPoVyruchci=1.5
WHERE id=4 or id=5;