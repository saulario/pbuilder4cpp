
drop table IF exists compound;
drop table IF exists something;
drop table IF exists customer;
drop table IF exists country;

create table country (
    id            varchar(2) not NULL default '' primary key,
    name          varchar(80) not NULL default ''
);

comment on table country is 'Country';
comment on column country.id is 'Id';
comment on column country.name is 'Name';

insert into country values('ES', 'Spain');
insert into country values('FR', 'France');
insert into country values('UK', 'United Kingdom');
insert into country values('US', 'United States of America');

create table customer (
    id            bigint not NULL default '0' primary key,
    name          varchar(80) not NULL default '',
    country_id    varchar(2) references country,
    creation_date DATE not NULL
);

comment on table customer is 'Customer';
comment on column customer.id is 'Id';
comment on column customer.name is 'Name';
comment on column customer.country_id is 'Country';
comment on column customer.creation_date is 'Creation date';

create table something (
    id            bigint not NULL default '0' primary key,
    name          varchar(80) not NULL default '',
    customer_id   bigint not NULL default '0' references customer,
    country_id    varchar(2) not NULL default '' references country
);

comment on table something is 'Something';
comment on column something.id is 'Id';
comment on column something.name is 'Name';
comment on column something.customer_id is 'Customer id';
comment on column something.country_id is 'Country id';


create table compound (
    customer_id   bigint not NULL default '0' references customer,
    country_id    varchar(2) not NULL default '' references country,
    name          varchar(80) not NULL default '',
    PRIMARY KEY(customer_id, country_id)
);

comment on table compound is 'Compound';
comment on column compound.customer_id is 'Customer id';
comment on column compound.country_id is 'Country id';
comment on column compound.name is 'Name';

