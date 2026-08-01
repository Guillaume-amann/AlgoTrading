document.addEventListener('DOMContentLoaded', () => {
  // --- Modal (login) ---
  const modal = document.getElementById('loginModal');
  const openBtn = document.getElementById('openLogin');
  const closeBtn = document.getElementById('closeLogin');

  if (modal && openBtn && closeBtn) {
    openBtn.addEventListener('click', () => { modal.style.display = 'flex'; });
    closeBtn.addEventListener('click', () => { modal.style.display = 'none'; });
    window.addEventListener('click', (e) => { if (e.target === modal) modal.style.display = 'none'; });
  }

  // --- Hamburger menu ---
  const hamburger = document.querySelector('.hamburger');
  const nav = document.querySelector('.nav');

  if (hamburger && nav) {
    hamburger.addEventListener('click', () => {
      hamburger.classList.toggle('active');
      nav.classList.toggle('open');
    });
  }

  // --- Intersection Observer for animations ---
  const hiddenElements = document.querySelectorAll('ul.hidden li');
  if (hiddenElements.length > 0) {
    const observer = new IntersectionObserver((entries) => {
      entries.forEach((entry) => {
        const delay = Array.from(entry.target.parentElement.children).indexOf(entry.target) * 70;
        if (entry.isIntersecting) {
          entry.target.style.transitionDelay = `${delay}ms`;
          entry.target.classList.add('show');
        } else {
          entry.target.classList.remove('show');
        }
      });
    });
    hiddenElements.forEach((el) => observer.observe(el));
  }
});