
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
    `countryId`     VARCHAR(2)                                          COMMENT 'Country',
    `creationDate`  DATE NOT NULL                                       COMMENT 'Creation date',
    PRIMARY KEY(`id`),
    FOREIGN KEY `fkCustomerCountry` (`countryId`) REFERENCES `country` (`id`)
) COMMENT 'Customer';

CREATE TABLE `something` (
    `id`            BIGINT NOT NULL DEFAULT '0'                         COMMENT 'Id',
    `name`          VARCHAR(80) NOT NULL DEFAULT ''                     COMMENT 'Name',
    `customerId`    BIGINT NOT NULL DEFAULT '0'                         COMMENT 'Customer',
    `countryId`     VARCHAR(2) NOT NULL DEFAULT ''                      COMMENT 'Country',
    PRIMARY KEY(`id`),
    FOREIGN KEY `fkSomethingCustomer` (`customerId`) REFERENCES `customer` (`id`),
    FOREIGN KEY `fkSomethingCountry` (`countryId`) REFERENCES `country` (`id`)
) COMMENT 'Something';



