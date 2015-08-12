
DROP TABLE IF EXISTS compound;
DROP TABLE IF EXISTS something;
DROP TABLE IF EXISTS customer;
DROP TABLE IF EXISTS country;

CREATE TABLE country (
    id            VARCHAR(2) NOT NULL DEFAULT '',
    name          VARCHAR(80) NOT NULL DEFAULT '',
    PRIMARY KEY(id)
);

COMMENT ON TABLE country IS 'Country';
COMMENT ON COLUMN country.id IS 'Id';
COMMENT ON COLUMN country.name IS 'Name';

INSERT INTO country VALUES('ES', 'Spain');
INSERT INTO country VALUES('FR', 'France');
INSERT INTO country VALUES('UK', 'United Kingdom');
INSERT INTO country VALUES('US', 'United States of America');

CREATE TABLE customer (
    id            BIGINT NOT NULL DEFAULT '0',
    name          VARCHAR(80) NOT NULL DEFAULT '',
    countryId     VARCHAR(2),
    creationDate  DATE NOT NULL,
    PRIMARY KEY(id),
    FOREIGN KEY (countryId) REFERENCES country (id)
);

COMMENT ON TABLE customer IS 'Customer';
COMMENT ON COLUMN customer.id IS 'Id';
COMMENT ON COLUMN customer.name IS 'Name';
COMMENT ON COLUMN customer.countryId IS 'Country';
COMMENT ON COLUMN customer.creationDate IS 'Creation date';

CREATE TABLE something (
    id            BIGINT NOT NULL DEFAULT '0',
    name          VARCHAR(80) NOT NULL DEFAULT '',
    customerId    BIGINT NOT NULL DEFAULT '0',
    countryId     VARCHAR(2) NOT NULL DEFAULT '',
    PRIMARY KEY(id),
    CONSTRAINT fkSomethingCustomer FOREIGN KEY (customerId) REFERENCES customer (id),
    CONSTRAINT fkSomethingCountry FOREIGN KEY (countryId) REFERENCES country (id)
);

COMMENT ON TABLE something IS 'Something';
COMMENT ON COLUMN something.id IS 'Id';
COMMENT ON COLUMN something.name IS 'Name';
COMMENT ON COLUMN something.customerId IS 'Customer id';
COMMENT ON COLUMN something.countryId IS 'Country id';


CREATE TABLE compound (
    customerId    BIGINT NOT NULL DEFAULT '0',
    countryId     VARCHAR(2) NOT NULL DEFAULT '',
    name          VARCHAR(80) NOT NULL DEFAULT '',
    PRIMARY KEY(customerId, countryId),
    CONSTRAINT fkCompoundCustomer FOREIGN KEY (customerId) REFERENCES customer (id),
    CONSTRAINT fkCompoundCountry FOREIGN KEY (countryId) REFERENCES country (id)
);

COMMENT ON TABLE compound IS 'Compound';
COMMENT ON COLUMN compound.customerId IS 'Customer id';
COMMENT ON COLUMN compound.countryId IS 'Country id';
COMMENT ON COLUMN compound.name IS 'Name';

