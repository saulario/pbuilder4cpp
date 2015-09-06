
DROP TABLE IF EXISTS `compound`;
DROP TABLE IF EXISTS `something`;
DROP TABLE IF EXISTS `customer`;
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

CREATE TABLE `customer` (
    `id`            BIGINT NOT NULL DEFAULT '0'                         COMMENT 'Id',
    `name`          VARCHAR(80) NOT NULL DEFAULT ''                     COMMENT 'Name',
    `country_id`    VARCHAR(2)                                          COMMENT 'Country',
    `creation_date` DATE NOT NULL                                       COMMENT 'Creation date',
    PRIMARY KEY(`id`),
    FOREIGN KEY `fkCustomerCountry` (`country_id`) REFERENCES `country` (`id`)
) COMMENT 'Customer';

CREATE TABLE `something` (
    `id`            BIGINT NOT NULL DEFAULT '0'                         COMMENT 'Id',
    `name`          VARCHAR(80) NOT NULL DEFAULT ''                     COMMENT 'Name',
    `customer_id`   BIGINT NOT NULL DEFAULT '0'                         COMMENT 'Customer',
    `country_id`    VARCHAR(2) NOT NULL DEFAULT ''                      COMMENT 'Country',
    PRIMARY KEY(`id`),
    FOREIGN KEY `fkSomethingCustomer` (`customer_id`) REFERENCES `customer` (`id`),
    FOREIGN KEY `fkSomethingCountry` (`country_id`) REFERENCES `country` (`id`)
) COMMENT 'Something';

CREATE TABLE `compound` (
    `customer_id`   BIGINT NOT NULL DEFAULT '0'                         COMMENT 'Customer',
    `country_id`    VARCHAR(2) NOT NULL DEFAULT ''                      COMMENT 'Country',
    `name`          VARCHAR(80) NOT NULL DEFAULT ''                     COMMENT 'Name',
    PRIMARY KEY(`customer_id`, `country_id`),
    FOREIGN KEY `fkCompoundCustomer` (`customer_id`) REFERENCES `customer` (`id`),
    FOREIGN KEY `fkCompoundCountry` (`country_id`) REFERENCES `country` (`id`)
) COMMENT 'Compound key';


