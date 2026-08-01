<?php
// Load .env file if present (for local dev only — Docker already injects env vars)
$envFile = __DIR__ . '/../.env';
if (file_exists($envFile)) {
    foreach (file($envFile, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES) as $line) {
        if (strpos(trim($line), '#') === 0) continue; // skip comments
        putenv(trim($line));
    }
}

// Get environment variables (Docker injects these automatically via env_file:)
$DB_HOST = getenv('DB_HOST') ?: 'db';           // default to service name
$DB_PORT = getenv('DB_PORT') ?: '5432';
$DB_NAME = getenv('DB_NAME') ?: getenv('POSTGRES_DB') ?: 'inicio_db';
$DB_USER = getenv('DB_USER') ?: getenv('POSTGRES_USER') ?: 'inicio_admin';
$DB_PASS = getenv('DB_PASSWORD') ?: getenv('POSTGRES_PASSWORD') ?: '';

try {
    $dsn = "pgsql:host={$DB_HOST};port={$DB_PORT};dbname={$DB_NAME};";
    $pdo = new PDO($dsn, $DB_USER, $DB_PASS, [
        PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
        PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
    ]);
} catch (PDOException $e) {
    // Log internally (never show credentials)
    error_log("Database connection failed: " . $e->getMessage());
    die("Database connection failed. Please try again later.");
}