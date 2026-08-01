#!/bin/bash
set -e

# Start PostgreSQL
service postgresql start

# Wait for Postgres
sleep 3

# Create DB, user, and load schema if not already present
sudo -u postgres psql -tc "SELECT 1 FROM pg_roles WHERE rolname='${DB_USER}'" | grep -q 1 || \
  sudo -u postgres psql -c "CREATE USER ${DB_USER} WITH PASSWORD '${DB_PASSWORD}' SUPERUSER;"

sudo -u postgres psql -tc "SELECT 1 FROM pg_database WHERE datname='${DB_NAME}'" | grep -q 1 || \
  sudo -u postgres createdb -O ${DB_USER} ${DB_NAME}

sudo -u postgres psql -d ${DB_NAME} -f /init-sql/setup.sql || true

# Start Apache (foreground)
apache2-foreground