
DROP TABLE IF EXISTS `my_compound`;
DROP TABLE IF EXISTS `something`;
DROP TABLE IF EXISTS `my_customer`;
DROP TABLE IF EXISTS `country`;

CREATE TABLE `country` (
    `id`            VARCHAR(2) NOT NULL DEFAULT ''                      COMMENT 'Id',
    `name`          VARCHAR(80) NOT NULL DEFAULT ''                     COMMENT 'Name',
    PRIMARY KEY(`id`)
) COMMENT 'Country';

INSERT INTO `country` VALUES('ES', 'Spain');
INSERT INTO `country` VALUES('FR', 'France');
INSERT INTO `country` VALUES('UK', 'United Kingdom');
INSERT INTO `country` VALUES('US', 'United States of America');

CREATE TABLE `my_customer` (
    `id`            BIGINT NOT NULL DEFAULT '0'                         COMMENT 'Id',
    `name`          VARCHAR(80) NOT NULL DEFAULT ''                     COMMENT 'Name',
    `country_id`    VARCHAR(2)                                          COMMENT 'Country',
    `creation_date` DATE NOT NULL                                       COMMENT 'Creation date',
    PRIMARY KEY(`id`),
    FOREIGN KEY `fkmy_customerCountry` (`country_id`) REFERENCES `country` (`id`)
) COMMENT 'my_customer';

CREATE TABLE `something` (
    `id`            	BIGINT NOT NULL DEFAULT '0'                         COMMENT 'Id',
    `name`          	VARCHAR(80) NOT NULL DEFAULT ''                     COMMENT 'Name',
    `my_customer_id`	BIGINT NOT NULL DEFAULT '0'                         COMMENT 'my_customer',
    `country_id`    	VARCHAR(2) NOT NULL DEFAULT ''                      COMMENT 'Country',
    PRIMARY KEY(`id`),
    FOREIGN KEY `fkSomethingmy_customer` (`my_customer_id`) REFERENCES `my_customer` (`id`),
    FOREIGN KEY `fkSomethingCountry` (`country_id`) REFERENCES `country` (`id`)
) COMMENT 'Something';

CREATE TABLE `my_compound` (
    `my_customer_id`	BIGINT NOT NULL DEFAULT '0'                         COMMENT 'my_customer',
    `country_id`	VARCHAR(2) NOT NULL DEFAULT ''                      COMMENT 'Country',
    `name`		VARCHAR(80) NOT NULL DEFAULT ''                     COMMENT 'Name',
    PRIMARY KEY(`my_customer_id`, `country_id`),
    FOREIGN KEY `fkmy_compoundmy_customer` (`my_customer_id`) REFERENCES `my_customer` (`id`),
    FOREIGN KEY `fkmy_compoundCountry` (`country_id`) REFERENCES `country` (`id`)
) COMMENT 'my_compound key';


