ALTER TABLE shlyahovyilyst CHANGE COLUMN Korekciya_id IsNormVal BOOLEAN DEFAULT 0;

ALTER TABLE lystregulyarnostiruhu CHANGE COLUMN PlanVyruchka PlanNaZminu DOUBLE(8,2) DEFAULT NULL;

ALTER TABLE lystregulyarnostiruhu 
	DROP COLUMN DniVRoboti, 
	DROP COLUMN GodVRoboti,
	DROP COLUMN VyruchkaFact,
	DROP COLUMN EconomPaln,
	DROP COLUMN VidhylOplGazu,
	DROP COLUMN Vidhylennya;

CREATE TABLE usersSessionsApark (
  `user_id` INTEGER UNSIGNED NOT NULL,
  `window_id` INTEGER UNSIGNED NOT NULL,
  `window_order` INTEGER UNSIGNED NOT NULL,
  `window_isActive` BOOLEAN DEFAULT false,
  INDEX `ind_user_id`(`user_id`),
  INDEX `ind_window_id`(`window_id`),
  INDEX `ind_window_order`(`window_order`)
)
ENGINE = MyISAM;