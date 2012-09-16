ALTER TABLE `pracivn_status` MODIFY COLUMN `Status_char` CHAR(2) DEFAULT NULL;

UPDATE pracivn_status SET Status_char='Р' WHERE id=1;
UPDATE pracivn_status SET Status_char='ТН' WHERE id=2;
UPDATE pracivn_status SET Status_char='В' WHERE id=3;
UPDATE pracivn_status SET Status_char='НА' WHERE id=4;
UPDATE pracivn_status SET Status_char='РВ' WHERE id=5;
UPDATE pracivn_status SET Status_char='ІН' WHERE id=6;
UPDATE pracivn_status SET Status_char='ВД' WHERE id=7;
UPDATE pracivn_status SET Status_char='ВП' WHERE id=8;
UPDATE pracivn_status SET Status_char='РС' WHERE id=9;
UPDATE pracivn_status SET Status_char='НУ' WHERE id=11;
UPDATE pracivn_status SET Status_char='П' WHERE id=12;
UPDATE pracivn_status SET Status_char='ПР' WHERE id=14;
UPDATE pracivn_status SET Status_char='ІВ' WHERE id=15;
UPDATE pracivn_status SET Status_char='А' WHERE id=17;
UPDATE pracivn_status SET Status_char='Д' WHERE id=18;

DELETE FROM pracivn_status WHERE id=10;
DELETE FROM pracivn_status WHERE id=13;
DELETE FROM pracivn_status WHERE id=16;

INSERT INTO pracivn_status (id, Status_name, Status_char, Status_color) VALUES (10, 'Вечірні години роботи','ВЧ','#800080');

UPDATE npr SET Naparnyky = 0;