DROP TRIGGER IF EXISTS shlyahovyiLyst_before_insert;
DROP TRIGGER IF EXISTS shlyahovyiLyst_before_update;
DROP TRIGGER IF EXISTS shlyahovyiLyst_before_delete;
DROP TRIGGER IF EXISTS lystRegulyarnostiRuhu_before_insert;
DROP TRIGGER IF EXISTS lystRegulyarnostiRuhu_before_update;
DROP TRIGGER IF EXISTS lystRegulyarnostiRuhu_before_delete;
DROP TRIGGER IF EXISTS pilgyAparkPokazn_before_insert;
DROP TRIGGER IF EXISTS pilgyAparkPokazn_before_update;
DROP TRIGGER IF EXISTS pilgyAparkPokazn_before_delete;
DROP TRIGGER IF EXISTS svyatkoviDni_before_insert;
DROP TRIGGER IF EXISTS svyatkoviDni_before_update;
DROP TRIGGER IF EXISTS svyatkoviDni_before_delete;
DROP TRIGGER IF EXISTS tabel_before_insert;
DROP TRIGGER IF EXISTS tabel_before_update;
DROP TRIGGER IF EXISTS tabel_before_delete;
DROP TRIGGER IF EXISTS tabel_sum_before_insert;
DROP TRIGGER IF EXISTS tabel_sum_before_update;
DROP TRIGGER IF EXISTS tabel_sum_before_delete;
DROP TRIGGER IF EXISTS cinaPalnogoDate_before_insert;
DROP TRIGGER IF EXISTS cinaPalnogoDate_before_update;
DROP TRIGGER IF EXISTS cinaPalnogoDate_before_delete;
DROP TRIGGER IF EXISTS cinaPalnogo_before_insert;
DROP TRIGGER IF EXISTS cinaPalnogo_before_update;
DROP TRIGGER IF EXISTS cinaPalnogo_before_delete;
DROP TRIGGER IF EXISTS planNaZminuDate_before_insert;
DROP TRIGGER IF EXISTS planNaZminuDate_before_update;
DROP TRIGGER IF EXISTS planNaZminuDate_before_delete;
DROP TRIGGER IF EXISTS planNaZminu_before_insert;
DROP TRIGGER IF EXISTS planNaZminu_before_update;
DROP TRIGGER IF EXISTS planNaZminu_before_delete;

DROP TRIGGER IF EXISTS zvitKupivliPalnogo_before_insert;
DROP TRIGGER IF EXISTS zvitKupivliPalnogo_before_update;
DROP TRIGGER IF EXISTS zvitKupivliPalnogo_before_delete;
DROP TRIGGER IF EXISTS zvitKupivliPalnogoOrders_before_insert;
DROP TRIGGER IF EXISTS zvitKupivliPalnogoOrders_before_update;
DROP TRIGGER IF EXISTS zvitKupivliPalnogoOrders_before_delete;

DROP FUNCTION IF EXISTS monthOpened;
DROP PROCEDURE IF EXISTS breakWithError;

DELIMITER //

CREATE FUNCTION monthOpened (_CDate DATE)
 RETURNS BOOLEAN
 DETERMINISTIC
  BEGIN
    DECLARE result BOOLEAN;
    SET result = not (SELECT Closed FROM monthPeriods
                  WHERE year(CDate)=year(_CDate) and month(CDate)=month(_CDate));
    IF result IS NULL THEN
      SET result = true;
    END IF;
    RETURN result;
  END; //

CREATE PROCEDURE breakWithError () SELECT error;//

# shlyahovyiLyst
CREATE TRIGGER shlyahovyiLyst_before_insert BEFORE INSERT ON shlyahovyiLyst
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(NEW.ToZvitDate)) THEN
      CALL breakWithError();
    END IF;
  END; //

CREATE TRIGGER shlyahovyiLyst_before_update BEFORE UPDATE ON shlyahovyiLyst
  FOR EACH ROW BEGIN
    IF (NOT monthOpened(date(OLD.ToZvitDate))) OR (NOT monthOpened(date(NEW.ToZvitDate))) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER shlyahovyiLyst_before_delete BEFORE DELETE ON shlyahovyiLyst
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(OLD.ToZvitDate)) THEN
      CALL breakWithError();
    END IF;
  END //

# lystRegulyarnostiRuhu
CREATE TRIGGER lystRegulyarnostiRuhu_before_insert BEFORE INSERT ON lystRegulyarnostiRuhu
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(NEW.VyizdDate)) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER lystRegulyarnostiRuhu_before_update BEFORE UPDATE ON lystRegulyarnostiRuhu
  FOR EACH ROW BEGIN
    IF (NOT monthOpened(date(OLD.VyizdDate))) OR (NOT monthOpened(date(NEW.VyizdDate))) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER lystRegulyarnostiRuhu_before_delete BEFORE DELETE ON lystRegulyarnostiRuhu
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(OLD.VyizdDate)) THEN
      CALL breakWithError();
    END IF;
  END //

# pilgyAparkPokazn
CREATE TRIGGER pilgyAparkPokazn_before_insert BEFORE INSERT ON pilgyAparkPokazn
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(NEW.CurDate)) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER pilgyAparkPokazn_before_update BEFORE UPDATE ON pilgyAparkPokazn
  FOR EACH ROW BEGIN
    IF (NOT monthOpened(date(OLD.CurDate))) OR (NOT monthOpened(date(NEW.CurDate))) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER pilgyAparkPokazn_before_delete BEFORE DELETE ON pilgyAparkPokazn
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(OLD.CurDate)) THEN
      CALL breakWithError();
    END IF;
  END //

# svyatkoviDni
CREATE TRIGGER svyatkoviDni_before_insert BEFORE INSERT ON svyatkoviDni
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(NEW.CDate)) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER svyatkoviDni_before_update BEFORE UPDATE ON svyatkoviDni
  FOR EACH ROW BEGIN
    IF (NOT monthOpened(date(OLD.CDate))) OR (NOT monthOpened(date(NEW.CDate))) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER svyatkoviDni_before_delete BEFORE DELETE ON svyatkoviDni
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(OLD.CDate)) THEN
      CALL breakWithError();
    END IF;
  END //

# tabel
CREATE TRIGGER tabel_before_insert BEFORE INSERT ON tabel
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(NEW.Cur_Date)) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER tabel_before_update BEFORE UPDATE ON tabel
  FOR EACH ROW BEGIN
    IF (NOT monthOpened(date(OLD.Cur_Date))) OR (NOT monthOpened(date(NEW.Cur_Date))) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER tabel_before_delete BEFORE DELETE ON tabel
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(OLD.Cur_Date)) THEN
      CALL breakWithError();
    END IF;
  END //

# tabel_sum
CREATE TRIGGER tabel_sum_before_insert BEFORE INSERT ON tabel_sum
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(NEW.Cur_Date)) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER tabel_sum_before_update BEFORE UPDATE ON tabel_sum
  FOR EACH ROW BEGIN
    IF (NOT monthOpened(date(OLD.Cur_Date))) OR (NOT monthOpened(date(NEW.Cur_Date))) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER tabel_sum_before_delete BEFORE DELETE ON tabel_sum
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(OLD.Cur_Date)) THEN
      CALL breakWithError();
    END IF;
  END //


# cinaPalnogoDate
CREATE TRIGGER cinaPalnogoDate_before_insert BEFORE INSERT ON cinaPalnogoDate
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(NEW.CDate)) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER cinaPalnogoDate_before_update BEFORE UPDATE ON cinaPalnogoDate
  FOR EACH ROW BEGIN
    IF (NOT monthOpened(date(OLD.CDate))) OR (NOT monthOpened(date(NEW.CDate))) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER cinaPalnogoDate_before_delete BEFORE DELETE ON cinaPalnogoDate
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(OLD.CDate)) THEN
      CALL breakWithError();
    END IF;
  END //


# cinaPalnogo
CREATE TRIGGER cinaPalnogo_before_insert BEFORE INSERT ON cinaPalnogo
  FOR EACH ROW BEGIN
  DECLARE dt DATE;
  SET dt = (SELECT CDate FROM cinaPalnogoDate WHERE id=NEW.CinaPalnogoDate_id);
    IF NOT monthOpened(dt) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER cinaPalnogo_before_update BEFORE UPDATE ON cinaPalnogo
  FOR EACH ROW BEGIN
  DECLARE dt DATE;
  SET dt = (SELECT CDate FROM cinaPalnogoDate WHERE id=OLD.CinaPalnogoDate_id);
    IF NOT monthOpened(dt) THEN
      CALL breakWithError();
    END IF;
  SET dt = (SELECT CDate FROM cinaPalnogoDate WHERE id=NEW.CinaPalnogoDate_id);
    IF NOT monthOpened(dt) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER cinaPalnogo_before_delete BEFORE DELETE ON cinaPalnogo
  FOR EACH ROW BEGIN
  DECLARE dt DATE;
  SET dt = (SELECT CDate FROM cinaPalnogoDate WHERE id=OLD.CinaPalnogoDate_id);
    IF NOT monthOpened(dt) THEN
      CALL breakWithError();
    END IF;
  END //


# planNaZminuDate
CREATE TRIGGER planNaZminuDate_before_insert BEFORE INSERT ON planNaZminuDate
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(NEW.CDate)) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER planNaZminuDate_before_update BEFORE UPDATE ON planNaZminuDate
  FOR EACH ROW BEGIN
    IF (NOT monthOpened(date(OLD.CDate))) OR (NOT monthOpened(date(NEW.CDate))) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER planNaZminuDate_before_delete BEFORE DELETE ON planNaZminuDate
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(OLD.CDate)) THEN
      CALL breakWithError();
    END IF;
  END //

# planNaZminu
CREATE TRIGGER planNaZminu_before_insert BEFORE INSERT ON planNaZminu
  FOR EACH ROW BEGIN
  DECLARE dt DATE;
  SET dt = (SELECT CDate FROM PlanNaZminuDate WHERE id=NEW.PlanNaZminuDate_id);
    IF NOT monthOpened(dt) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER planNaZminu_before_update BEFORE UPDATE ON planNaZminu
  FOR EACH ROW BEGIN
  DECLARE dt DATE;
  SET dt = (SELECT CDate FROM PlanNaZminuDate WHERE id=OLD.PlanNaZminuDate_id);
    IF NOT monthOpened(dt) THEN
      CALL breakWithError();
    END IF;
  SET dt = (SELECT CDate FROM PlanNaZminuDate WHERE id=NEW.PlanNaZminuDate_id);
    IF NOT monthOpened(dt) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER planNaZminu_before_delete BEFORE DELETE ON planNaZminu
  FOR EACH ROW BEGIN
  DECLARE dt DATE;
  SET dt = (SELECT CDate FROM PlanNaZminuDate WHERE id=OLD.PlanNaZminuDate_id);
    IF NOT monthOpened(dt) THEN
      CALL breakWithError();
    END IF;
  END //

# zvitKupivliPalnogo
CREATE TRIGGER zvitKupivliPalnogo_before_insert BEFORE INSERT ON zvitKupivliPalnogo
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(NEW.CDate)) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER zvitKupivliPalnogo_before_update BEFORE UPDATE ON zvitKupivliPalnogo
  FOR EACH ROW BEGIN
    IF (NOT monthOpened(date(OLD.CDate))) OR (NOT monthOpened(date(NEW.CDate))) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER zvitKupivliPalnogo_before_delete BEFORE DELETE ON zvitKupivliPalnogo
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(OLD.CDate)) THEN
      CALL breakWithError();
    END IF;
  END //
  
# zvitKupivliPalnogoOrders
CREATE TRIGGER zvitKupivliPalnogoOrders_before_insert BEFORE INSERT ON zvitKupivliPalnogoOrders
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(NEW.CDate)) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER zvitKupivliPalnogoOrders_before_update BEFORE UPDATE ON zvitKupivliPalnogoOrders
  FOR EACH ROW BEGIN
    IF (NOT monthOpened(date(OLD.CDate))) OR (NOT monthOpened(date(NEW.CDate))) THEN
      CALL breakWithError();
    END IF;
  END //

CREATE TRIGGER zvitKupivliPalnogoOrders_before_delete BEFORE DELETE ON zvitKupivliPalnogoOrders
  FOR EACH ROW BEGIN
    IF NOT monthOpened(date(OLD.CDate)) THEN
      CALL breakWithError();
    END IF;
  END //
  
DELIMITER