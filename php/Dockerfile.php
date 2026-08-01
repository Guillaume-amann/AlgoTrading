# Dockerfile for PHP + Apache
FROM php:8.2-apache


# Install PostgreSQL client and PHP extension (so PHP can talk to Postgres)
RUN apt-get update && apt-get install -y \
    libpq-dev \
    && docker-php-ext-install pdo pdo_pgsql \
    && rm -rf /var/lib/apt/lists/*

# Enable Apache rewrite
RUN a2enmod rewrite

# Copy your PHP app
COPY public/ /var/www/html/

EXPOSE 80