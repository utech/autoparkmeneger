ALTER TABLE `pracivn_status` MODIFY COLUMN `Status_char` CHAR(2) DEFAULT NULL;

UPDATE pracivn_status SET Status_char='�' WHERE id=1;
UPDATE pracivn_status SET Status_char='��' WHERE id=2;
UPDATE pracivn_status SET Status_char='�' WHERE id=3;
UPDATE pracivn_status SET Status_char='��' WHERE id=4;
UPDATE pracivn_status SET Status_char='��' WHERE id=5;
UPDATE pracivn_status SET Status_char='��' WHERE id=6;
UPDATE pracivn_status SET Status_char='��' WHERE id=7;
UPDATE pracivn_status SET Status_char='��' WHERE id=8;
UPDATE pracivn_status SET Status_char='��' WHERE id=9;
UPDATE pracivn_status SET Status_char='��' WHERE id=11;
UPDATE pracivn_status SET Status_char='�' WHERE id=12;
UPDATE pracivn_status SET Status_char='��' WHERE id=14;
UPDATE pracivn_status SET Status_char='��' WHERE id=15;
UPDATE pracivn_status SET Status_char='�' WHERE id=17;
UPDATE pracivn_status SET Status_char='�' WHERE id=18;

DELETE FROM pracivn_status WHERE id=10;
DELETE FROM pracivn_status WHERE id=13;
DELETE FROM pracivn_status WHERE id=16;

INSERT INTO pracivn_status (id, Status_name, Status_char, Status_color) VALUES (10, '������ ������ ������','��','#800080');

UPDATE npr SET Naparnyky = 0;