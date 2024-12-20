# CREATE TABLE
```
CREATE TABLE employees (
    employee_id NUMBER GENERATED CONSTRAINT pk_val PRIMARY KEY,
    first_name VARCHAR2(50) NOT NULL,
    last_name VARCHAR2(50) NOT NULL,
    email VARCHAR2(100) UNIQUE NOT NULL,
    phone_number VARCHAR2(15),
    hire_date DATE DEFAULT SYSDATE,
    salary NUMBER(8, 2) CHECK (salary >= 0),
    department_id NUMBER,
    CONSTRAINT fk_department
        FOREIGN KEY (department_id) REFERENCES departments (department_id)
	ON DELETE CASCADE || ON DELETE SET NULL
);
```
# Create table using subquery
```
CREATE TABLE high_salary_employees AS
SELECT employee_id, first_name, last_name, salary
FROM employees
WHERE salary > 60000;
```
# Inserting Data
```
INSERT INTO employees (employee_id, first_name, last_name, salary)
VALUES (101, 'John', 'Doe', 55000);
```

# UPDATE
```
UPDATE employees
SET 
    first_name = 'John',
    last_name = 'Doe',
WHERE employee_id = 1;
```
# DELETE FROM
```
DELETE FROM employees
WHERE department_id = 2;
```
# Adding a New Column
```
ALTER TABLE employees
ADD birth_date DATE;
```
# Modifying an Existing Column
```
ALTER TABLE employees
MODIFY salary NUMBER(10, 2) NOT NULL;
```
# Dropping a Column
```
ALTER TABLE employees
DROP COLUMN phone_number;
```
# Renaming a Column
```
ALTER TABLE employees
RENAME COLUMN last_name TO surname;
```
# Adding a Constraint
```
ALTER TABLE employees
ADD CONSTRAINT fk_department
FOREIGN KEY (department_id) REFERENCES departments (department_id);
```
# Dropping a Constraint
```
ALTER TABLE employees
DROP CONSTRAINT fk_department;
```
# Drop table
```
DROP TABLE table_name;
OR
DROP TABLE employees CASCADE CONSTRAINTS;
```
# Create View
```
CREATE VIEW high_salary_employees AS
SELECT employee_id, first_name, last_name, salary
FROM employees
WHERE salary > 60000;
WITH CHECK OPTION CONSTRAINT constraint_name;
```
# Describe the striucture of a view
```
DESCRIBE high_salary_employees;
```
# Modifing a view
```
CREATE OR REPLACE VIEW high_salary_employees AS
SELECT employee_id, first_name, last_name, salary
FROM employees
WHERE salary > 50000;
```
# Denying DML Operations
```
CREATE VIEW high_salary_employees AS
SELECT employee_id, first_name, last_name, salary
FROM employees
WHERE salary > 50000;
WITH READ ONLY
```
# Removing a View
```
DROP VIEW high_salary_employees
```
# Creating Users
```
CREATE USER username IDENTIFIED BY password;
```
# Granting System Privileges
```
GRANT create session, create table TO new_user;
```
# Granting Object Privileges
```
GRANT select, insert on table TO user, second_user;
```
### System Privileges
System privileges allow users to perform administrative tasks at the database level. Some commonly used system privileges include:
1. create session: allows a user to connect to the database.
2. create table: allows a user to create tables in their own schema.
3. create view: allows a user to create views in their own schema.
4. create procedure: allows a user to create stored procedures and functions.
5. create sequence: allows a user to create sequences.
6. create trigger: allows a user to create triggers.
7. create user: allows a user to create new database users.
8. drop user: allows a user to drop existing database users.
9. grant any privilege: allows a user to grant any system or object privilege to other users.
10. alter any table: allows a user to alter any table in the database.
11. select any table: allows a user to select data from any table in the database.
12. insert any table: allows a user to insert data into any table.
13. update any table: allows a user to update data in any table.
14. delete any table: allows a user to delete data from any table.
15. execute any procedure: allows a user to execute any stored procedure or function.
### Object Privileges
Object privileges allow users to perform specific actions on database objects (tables, views, procedures, etc.). Here are some commonly used object privileges:
1. **select**: allows a user to select data from a table or view.
2. **insert**: allows a user to insert data into a table or view.
3. **update**: allows a user to update existing data in a table or view.
4. **delete**: allows a user to delete data from a table or view.
5. **execute**: allows a user to execute a stored procedure or function.
6. **references**: allows a user to create foreign keys that reference the specified table.
7. **index**: allows a user to create an index on a table.
8. **alter**: allows a user to alter the structure of a table or view.
9. **drop**: allows a user to drop a table, view, or other database object.
10. **grant**: allows a user to grant specified object privileges to other users.
# Create Role
```
CREATE ROLE role_name;
```
# Assigning the Role to Users
```
GRANT role_name TO user, second_user;
```
# Changing password
```
ALTER USER username IDENTIFIED BY new_password;
```
# Passing privilages
```
GRANT select, insert ON employees
TO new_user
WITH GRANT OPTION;
```
# Revoking Object Privilages
```
REVOKE SELECT ON employees FROM new_user;
```
# Revoking System Privilages
```
REVOKE create session FROM new_user;
```
