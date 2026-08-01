<?php
session_start();
require_once('db.php');

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    header('Location: index.php');
    exit;
}

$email = trim($_POST['email'] ?? '');
$password = $_POST['password'] ?? '';

if (!$email || !$password) {
    header('Location: index.php?error=' . urlencode('Missing credentials.'));
    exit;
}

try {
    $stmt = $pdo->prepare('SELECT id, email, password_hash FROM users WHERE email = :email LIMIT 1');
    $stmt->execute([':email' => $email]);
    $user = $stmt->fetch();

    if (!$user || !password_verify($password, $user['password_hash'])) {
        header('Location: index.php?error=' . urlencode('Invalid email or password.'));
        exit;
    }

    session_regenerate_id(true);
    $_SESSION['user_id'] = $user['id'];
    $_SESSION['user_email'] = $user['email'];

    header('Location: dashboard.php');
    exit;

} catch (Exception $e) {
    error_log("Login error: " . $e->getMessage());
    header('Location: index.php?error=' . urlencode('Internal error.'));
    exit;
}