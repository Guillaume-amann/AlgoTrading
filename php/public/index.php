<!DOCTYPE html class = "wainting">
<html lang="en">



<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <meta name="author" content="Guillaume Amann">
  <meta name="description" content="Portfolio Management">
  <meta property="image" content="docs/img/social-card.png">
  <title>Inicio Financial</title>
  <link rel="icon" href="public/favicon.ico" type="image/x-icon">
  <link rel="shortcut icon" href="public/favicon.ico" type="image/x-icon">
  <link rel="apple-touch-icon" href="public/favicon.ico">
  <link rel="stylesheet" href="/style.css" />
</head>



<body class="waiting-page">

  <!-- Main Content -->
  <div>
    <h1>Inicio Financial</h1>
    <p>Coming Soon</p>
  </div>

  <!-- Login button -->
  <button class="login-btn" id="openLogin">Login</button>

  <!-- Modal -->
  <div class="modal" id="loginModal">
    <div class="modal-content">
      <span class="close-btn" id="closeLogin">&times;</span>
      <h2>Sign in</h2>

      <form method="POST" action="login.php">
        <label for="email">Email</label>
        <input id="email" name="email" type="email" required placeholder="you@example.com" />
        <label for="password">Password</label>
        <input id="password" name="password" type="password" required placeholder="password" />
        <button type="submit">Login</button>
      </form>

      <!-- Error message (rendered by PHP redirect) -->
      <?php if (isset($_GET['error'])) {echo '<div class="error">' . htmlspecialchars($_GET['error']) . '</div>';} ?>
    </div>
  </div>
<script src="scripts.js"></script>
</body>
</html>