
drop table IF exists my_compound;
drop table IF exists something;
drop table IF exists my_customer;
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

create table my_customer (
    id            bigint not NULL default '0' primary key,
    name          varchar(80) not NULL default '',
    country_id    varchar(2) references country,
    creation_date DATE not NULL
);

comment on table my_customer is 'my_customer';
comment on column my_customer.id is 'Id';
comment on column my_customer.name is 'Name';
comment on column my_customer.country_id is 'Country';
comment on column my_customer.creation_date is 'Creation date';

create table something (
    id            bigint not NULL default '0' primary key,
    name          varchar(80) not NULL default '',
    my_customer_id   bigint not NULL default '0' references my_customer,
    country_id    varchar(2) not NULL default '' references country
);

comment on table something is 'Something';
comment on column something.id is 'Id';
comment on column something.name is 'Name';
comment on column something.my_customer_id is 'my_customer id';
comment on column something.country_id is 'Country id';


create table my_compound (
    my_customer_id   bigint not NULL default '0' references my_customer,
    country_id    varchar(2) not NULL default '' references country,
    name          varchar(80) not NULL default '',
    PRIMARY KEY(my_customer_id, country_id)
);

comment on table my_compound is 'my_compound';
comment on column my_compound.my_customer_id is 'my_customer id';
comment on column my_compound.country_id is 'Country id';
comment on column my_compound.name is 'Name';

