
drop table IF exists my_compound;
drop table IF exists something;
drop table IF exists my_customer;
drop table IF exists country;

create table country (
    id            varchar(2) not NULL default '' primary key,
    name          varchar(80) not NULL default ''
);

insert into country values('ES', 'Spain');
insert into country values('FR', 'France');
insert into country values('UK', 'United Kingdom');
insert into country values('US', 'United States of America');

create table my_customer (
    id            bigint not NULL default '0' primary key,
    name          varchar(80) not NULL default '',
    country_id    varchar(2) references country,
    creation_date DATE not NULL
);

create table something (
    id            bigint not NULL default '0' primary key,
    name          varchar(80) not NULL default '',
    my_customer_id   bigint not NULL default '0' references my_customer,
    country_id    varchar(2) not NULL default '' references country
);

create table my_compound (
    my_customer_id   bigint not NULL default '0' references my_customer,
    country_id    varchar(2) not NULL default '' references country,
    name          varchar(80) not NULL default '',
    PRIMARY KEY(my_customer_id, country_id)
);


