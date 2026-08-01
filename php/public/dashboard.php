<?php
session_start();

require_once 'db.php';

if (!isset($_SESSION['user_id'])) {
    header('Location: index.html?error=' . urlencode('Please log in.'));
    exit;
}

$user_id = (int)$_SESSION['user_id'];

// Fetch user profile
$profileStmt = $pdo->prepare('SELECT id, email, full_name, created_at FROM users WHERE id = :id');
$profileStmt->execute([':id' => $user_id]);
$profile = $profileStmt->fetch();

if (!$profile) {
    echo "User not found.";
    exit;
}

// Fetch recent transactions
$acctStmt = $pdo->prepare('
    SELECT t.id, t.type, t.amount, t.ticker,
           TO_CHAR(DATE_TRUNC(\'day\', t.created_at), \'YYYY-MM-DD\') AS created_date
    FROM transactions t
    WHERE t.user_id = :id
    ORDER BY created_date ASC
    LIMIT 50
');
$acctStmt->execute([':id' => $user_id]);
$transactions = $acctStmt->fetchAll();
?>
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8" />
  <title>Dashboard</title>
  <link rel="stylesheet" href="style.css" />
</head>
<body>

  <!-- Main site header -->
  <header class="header">
      <div class="header-top">
        <a href="index.html" class="brand">Inicio<br>Financial</a>
        <button class="hamburger" id="hamburger">
          <span class="bar"></span>
          <span class="bar"></span>
          <span class="bar"></span>
        </button>
      </div>
      <nav class="nav" id="nav">
        <ul class="nav-menu">
          <li><a href="index.html">Home</a></li>
          <li><a href="dashboard.php">Dashboard</a></li>
          <li><a href="page1.html">Finance</a></li>
          <li><a href="page2.html">AI</a></li>
          <li><a href="algo.html">Programming</a></li>
        </ul>
      </nav>
  </header>

  <!-- User top section -->
  <div class="user-top">
      <div>
        <h2 style="margin:0">Welcome, <?php echo htmlspecialchars($profile['full_name'] ?: $profile['email']); ?></h2>
        <div class="small">Member since <?php echo htmlspecialchars(substr($profile['created_at'],0,10)); ?></div>
      </div>
      <div>
        <a class="logout" href="/logout.php">Log out</a>
      </div>
  </div>

  <!-- Main content: Recent transactions -->
  <section>
    <h3>Recent transactions</h3>
    <?php if (count($transactions) === 0): ?>
      <p>No transactions found.</p>
    <?php else: ?>
      <table>
        <thead>
          <tr><th>ID</th><th>Type</th><th>Ticker</th><th>Amount</th><th>Date</th></tr>
        </thead>
        <tbody>
          <?php foreach ($transactions as $t): ?>
            <tr>
              <td><?php echo htmlspecialchars($t['id']); ?></td>
              <td><?php echo htmlspecialchars($t['type']); ?></td>
              <td><?php echo htmlspecialchars($t['ticker']); ?></td>
              <td><?php echo htmlspecialchars($t['amount']); ?></td>
              <td><?php echo htmlspecialchars($t['created_date']); ?></td>
            </tr>
          <?php endforeach; ?>
        </tbody>
      </table>
    <?php endif; ?>
  </section>
  <!--Run Python script to refresh pie chart -->
  <?php exec('python3 /pie_chart.py'); ?>
  <!-- Pie chart of ticker holdings -->
  <div style="margin-top:30px; text-align:center;">
      <h3>Your Holdings</h3>
      <img src="docs/img/holdings_pie.png" alt="Holdings Pie Chart" style="max-width:400px; width:80%;">
  </div>
  <script src="scripts.js"></script>
</body>
</html>