-- 1️⃣ Create the project role (user)
-- DROP ROLE IF EXISTS inicio_admin;
-- CREATE ROLE inicio_admin WITH LOGIN PASSWORD 'QTC2324inicio_financial';

-- Make inicio_schema the default schema for this role
ALTER ROLE inicio_admin SET search_path = inicio_schema;

-- 2️⃣ Create the database
-- DROP DATABASE IF EXISTS inicio_db;
-- CREATE DATABASE inicio_db
--     WITH OWNER = inicio_admin
--          ENCODING 'UTF8'
--          LC_COLLATE 'C.UTF-8'
--          LC_CTYPE 'C.UTF-8'
--          TEMPLATE template0;

-- 3️⃣ Connect to the database
\c inicio_db inicio_admin

-- Drop schema (instead of database) to avoid ownership conflicts
-- DROP SCHEMA IF EXISTS inicio_schema CASCADE;
CREATE SCHEMA inicio_schema AUTHORIZATION inicio_admin;

ALTER DEFAULT PRIVILEGES IN SCHEMA inicio_schema
GRANT SELECT, INSERT, UPDATE, DELETE ON TABLES TO inicio_admin;

-- Drop & create tables inside schema
CREATE TABLE IF NOT EXISTS inicio_schema.users (
    id SERIAL PRIMARY KEY,
    email TEXT UNIQUE NOT NULL,
    full_name TEXT,
    password_hash TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS inicio_schema.transactions (
    id SERIAL PRIMARY KEY,
    user_id INT REFERENCES inicio_schema.users(id),
    type TEXT,
    amount NUMERIC,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    ticker TEXT
);

-- Insert demo data only if table is empty
INSERT INTO inicio_schema.users (email, full_name, password_hash, created_at)
SELECT 'demo@example.com', 'Demo User', '$2y$12$4iA9JG6kJY8nY/9e0wquu6G6rT4vVqsc2tG5xYf0g8yKq8R2h6Sa', '2025-09-28 14:29:43'
WHERE NOT EXISTS (SELECT 1 FROM inicio_schema.users);
INSERT INTO inicio_schema.transactions (user_id, type, amount, created_at, ticker)
VALUES
(1, 'deposit', 3000.00, '2025-03-24', 'CASH'),
(1, 'buy', 7.00, '2025-03-25', 'ACA.PA'),
(1, 'buy', 20.00, '2025-03-31', 'ACA.PA'),
(1, 'buy', 33.00, '2025-04-29', 'ACA.PA'),
(1, 'buy', 5.00, '2025-04-30', 'ACA.PA'),
(1, 'buy', 10.00, '2025-05-27', 'AMUN.PA'),
(1, 'buy', 7.00, '2025-05-30', 'AMUN.PA'),
(1, 'buy', 5.00, '2025-06-13', 'ACA.PA'),
(1, 'buy', 7.00, '2025-07-29', 'AMUN.PA');